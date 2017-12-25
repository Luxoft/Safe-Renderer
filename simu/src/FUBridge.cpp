/******************************************************************************
**
**   File:        FUBridge.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Render is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Render.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "FUBridge.h"
#include "InputStream.h"
#include "logmsg.h"
#include <OdiTypes.h>
#include <OdiMsgHeader.h>
#include <MessageHeader.h>
#include <RegistrationMsgReader.h>
#include <FUDatabaseType.h>
#include <FUClassType.h>
#include <DynamicDataEntryType.h>
#include <DataResponseMessage.h>
#include <DataHandler.h>
#include <PSCErrorCollector.h>

using namespace psc;


FUBridge::FUBridge(const FUDatabaseType* ddh, int port, DataHandler& dh)
: m_session()
, m_dataHandler(dh)
, m_ddh(ddh)
, m_transmitter(NULL)
{
    m_session.Listen("0.0.0.0", port);
    m_session.registerMsgReceiver(this, MessageTypes::REGISTRATION, 0, 256);
    m_session.registerMsgReceiver(this, MessageTypes::ODI, 0, 256);
}

FUBridge::~FUBridge()
{
}

PSCError FUBridge::handleIncomingData(uint32_t timeout)
{
    // Check for data upstream (Editor -> Engine)
    if (NULL != m_transmitter)
    {
        refresh();
    }
    return m_session.handleIncomingData(timeout);
}


PSCError FUBridge::onMessage(IMsgTransmitter* pTransmitter, const U8 messageType, InputStream& stream)
{
    switch (messageType)
    {
    case MessageTypes::REGISTRATION:
        onRegistration(pTransmitter, stream);
        break;
    case MessageTypes::ODI:
        onODI(pTransmitter, stream);
        break;
    default:
        LOG_WARN(("FUBridge ignored message type :%d", messageType));
        break;
    }
    return PSC_NO_ERROR;
}

PSCError FUBridge::onRegistration(IMsgTransmitter* pTransmitter, InputStream& stream)
{
    // Editor/FUApp sends registration message for each FU
    // Engine ignores registration messages, but we need to simulate data subscriptions to make the Editor send data responses
    RegistrationMsgReader msg(stream);
    const U8 fuCount = msg.getFuCount();
    const U8 major = msg.getMajorVersion();
    const U8 minor = msg.getMinorVersion();
    FUClassId fu = 0;
    LOG_VERB(("FUApp connected. protocol version %d.%d FUs:%d", major, minor, fuCount));
    while ((fu = msg.getNextFu()) != 0)
    {
        LOG_VERB(("Registered FU:%d", fu));
    }
    return subscribeAll();
}

/**
 * Sends data subscriptions for all FU data which is used by the Engine
 * Without these subscriptions the FU-simulator won't send data responses
 * (Sending data subscriptions is the expected behaviour for the non-asil Engine.
 * ASIL-FUs won't expect subscription messages.)
 */
PSCError FUBridge::subscribeAll()
{
    U8 buf[256];
    for (U16 i = 0; i < m_ddh->GetFUCount(); ++i)
    {
        const FUClassType* fu = m_ddh->GetFU(i);
        if (!fu->GetInternalFU() && fu->GetFUClassId() != 0)
        {
            for (U16 k = 0; k < fu->GetDynamicDataEntryCount(); ++k)
            {
                OutputStream out(buf, sizeof(buf));
                out << static_cast<U8>(MessageTypes::ODI);
                out << static_cast<U8>(5); //data request
                out << fu->GetFUClassId();
                out << static_cast<U8>(0); // subscribe
                out << static_cast<U8>(1); // display mask
                out << static_cast<U8>(0); // validity
                const DynamicDataEntryType* data = fu->GetDynamicDataEntry(k);
                out << data->GetDataId();
                out << static_cast<U16>(0);
                out << static_cast<U16>(0);
                out << static_cast<U16>(0);
                out << static_cast<U16>(0);
                if (m_transmitter)
                {
                    m_transmitter->transmitMessage(buf, out.bytesWritten());
                }
            }
        }
    }
    return PSC_NO_ERROR;
}

/**
 * Refreshes the timestamp of all valid data
 * Could be removed if the FU Simulator evaluates the repeat timeout
 */
void FUBridge::refresh()
{
    for (U16 i = 0; i < m_ddh->GetFUCount(); ++i)
    {
        const FUClassType* fu = m_ddh->GetFU(i);
        if (!fu->GetInternalFU() && fu->GetFUClassId() != 0)
        {
            const U16 fuId = fu->GetFUClassId();
            for (U16 k = 0; k < fu->GetDynamicDataEntryCount(); ++k)
            {
                const U16 dataId = fu->GetDynamicDataEntry(k)->GetDataId();
                Number value;
                DataStatus status = m_dataHandler.getNumber(fuId, dataId , value);
                if (DataStatus::VALID == status)
                {
                    m_dataHandler.setData(fuId, dataId, value, status);
                }
            }
        }
    }
}

PSCError FUBridge::onODI(IMsgTransmitter* pTransmitter, InputStream& stream)
{
    const OdiMsgHeader odiMsgHeader = OdiMsgHeader::fromStream(stream);
    PSCErrorCollector err = PSC_NO_ERROR;
    if (odiMsgHeader.getOdiType() == DataMessageTypes::DYN_DATA_RESP)
    {
        err = m_dataHandler.dynamicDataResponseHandler(stream);
    }
    else
    {
        // Engine only supports dynamic data responses
        // Other messages (Events, Indications are treated as errors)
    }
    err = stream.getError();
    return err.get();
}

void FUBridge::onConnect(IMsgTransmitter* pMsgTransmitter)
{
    // Editor connected
    m_transmitter = pMsgTransmitter;
}

void FUBridge::onDisconnect(IMsgTransmitter* pMsgTransmitter)
{
    // Editor disconnected
    if (m_transmitter == pMsgTransmitter)
    {
        // For now use only one transmitter
        m_transmitter = NULL;
    }
}
