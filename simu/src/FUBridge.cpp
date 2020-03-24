/******************************************************************************
**
**   File:        FUBridge.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "FUBridge.h"
#include "InputStream.h"
#include "logmsg.h"
#include <OdiTypes.h>
#include <OdiMsgHeader.h>
#include <MessageHeader.h>
#include <RegistrationMsgReader.h>
#include <DDHType.h>
#include <DataResponseMessage.h>
#include <DataHandler.h>
#include <LSRErrorCollector.h>

using namespace lsr;


FUBridge::FUBridge(DataHandler& dh, int port, const std::string& hostname)
: m_session()
, m_dataHandler(dh)
, m_transmitter(NULL)
{
    m_session.Listen(hostname, port);
    m_session.registerMsgReceiver(this, MessageTypes::REGISTRATION, 0, 256);
    m_session.registerMsgReceiver(this, MessageTypes::ODI, 0, 256);
}

FUBridge::~FUBridge()
{
}

ComError FUBridge::handleIncomingData(uint32_t timeout)
{
    // Check for data upstream (Editor -> Engine)
    if (NULL != m_transmitter)
    {
        refresh();
    }
    return m_session.handleIncomingData(timeout);
}

ComError FUBridge::onMessage(IMsgTransmitter* pTransmitter, const U8 messageType, InputStream& stream)
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
    return COM_NO_ERROR;
}

ComError FUBridge::onRegistration(IMsgTransmitter* pTransmitter, InputStream& stream)
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
ComError FUBridge::subscribeAll()
{
    U8 buf[256];
    for (DataHandler::iterator it = m_dataHandler.begin(); it != m_dataHandler.end(); ++it)
    {
        const DynamicData id(it->config.fuDataId);
        OutputStream out(buf, sizeof(buf));
        out << static_cast<U8>(MessageTypes::ODI);
        out << static_cast<U8>(5); //data request
        out << id.getFUClassId();
        out << static_cast<U8>(0); // subscribe
        out << static_cast<U8>(1); // display mask
        out << static_cast<U8>(0); // validity
        out << id.getDataId();
        out << static_cast<U16>(0);
        out << static_cast<U16>(0);
        out << static_cast<U16>(0);
        out << static_cast<U16>(0);
        if (m_transmitter)
        {
            m_transmitter->transmitMessage(buf, out.bytesWritten());
        }
    }

    return COM_NO_ERROR;
}

/**
 * Refreshes the timestamp of all valid data
 * Could be removed if the FU Simulator evaluates the repeat timeout
 */
void FUBridge::refresh()
{
    for (DataHandler::iterator it = m_dataHandler.begin(); it != m_dataHandler.end(); ++it)
    {
        const DynamicData id(it->config.fuDataId);
        Number value;
        DataStatus status = m_dataHandler.getNumber(id, value);
        if (DataStatus::VALID == status)
        {
            m_dataHandler.setData(id, value, status);
        }
    }
}

ComError FUBridge::onODI(IMsgTransmitter* pTransmitter, InputStream& stream)
{
    const OdiMsgHeader odiMsgHeader = OdiMsgHeader::fromStream(stream);
    TErrorCollector<ComError> err = COM_NO_ERROR;
    if (odiMsgHeader.getOdiType() == DataMessageTypes::DYN_DATA_RESP)
    {
        err = onODIDynamicData(stream);
    }
    else
    {
        // Engine only supports dynamic data responses
        // Other messages (Events, Indications are treated as errors)
    }
    err = stream.getError();
    return err.get();
}

ComError FUBridge::onODIDynamicData(InputStream& stream)
{
    const DataResponseMessage dataResponse = DataResponseMessage::fromStream(stream);
    const DynamicData dynData(dataResponse.getFuId(), dataResponse.getDataId());

    const Number value(dataResponse.getDataValue(), dataResponse.getDataType());
    const DataStatus status = dataResponse.getInvalidFlag() ? DataStatus::INVALID : DataStatus::VALID;
    const bool success = m_dataHandler.setData(dynData, value, status);
    return success ? COM_NO_ERROR : COM_INVALID_MESSAGE_TYPE;
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
