/******************************************************************************
**
**   File:        PilOdiComSessionBase.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   Luxoft Safe Renderer is free software: you can redistribute it and/or
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

#include "PilOdiComSessionBase.h"
#include "PilMsgTransmitter.h"
#include "OdiRecorder.h"
#include "HealthLog.h"
#include "pil.h"
#include "LsrLimits.h"
#include "OdiTypes.h"
#include "InputStream.h"
#include "MessageHeader.h"
#include "LSRErrorCollector.h"

namespace lsr
{

PilOdiComSessionBase::PilOdiComSessionBase(const bool isEngine)
    : m_pOdiRecorder(NULL)
    , m_isEngine(isEngine)
{
}

LSRError PilOdiComSessionBase::onMessage(PILMailbox transmitter, const U8* data, const U32 dataLen)
{
    LSRError errValue = LSR_SESSION_UNDEFINED_RECEIVER;
    PilMsgTransmitter* pTransmitter = getTransmitter(transmitter);

    if (NULL == pTransmitter)
    {
        errValue = LSR_SESSION_UNDEFINED_TRANSMITTER;
    }
    else
    {
        InputStream stream(data, dataLen);
        MessageHeader header = MessageHeader::fromStream(stream);

        if (stream.getError() != LSR_NO_ERROR)
        {
            errValue = stream.getError();
        }
        else if (header.getDataSize() > stream.bytesToRead())
        {
            errValue = LSR_PIL_INVALID_MSG;
        }
        else
        {
            U8 messageType = header.getType();
            U8 curMsgType = MessageTypes::UNKNOWN;
            U8 index = 0;
            IMsgReceiver* pCurMsgReceiver = getReceiver(index, curMsgType);

            while (NULL != pCurMsgReceiver)
            {
                if (messageType == curMsgType)
                {
                    errValue = pCurMsgReceiver->onMessage(pTransmitter, messageType, stream);
                    break;
                }

                ++index;
                pCurMsgReceiver = getReceiver(index, curMsgType);
            }
        }
    }

    return errValue;
}

LSRError PilOdiComSessionBase::handleIncomingData(U32 msTimeout)
{
    LSRErrorCollector errValue = LSR_NO_ERROR;
    U32 numMessages = 0;
    PILMailbox fromConnection = PIL_UNKNOWN_MAILBOX;
    U8 messageType = MessageTypes::UNKNOWN;
    U32 dataLen = 0;
    U8* data = NULL;

    if (m_isEngine)
    { // Wait event only from Engine side
        errValue = convertErrorPil2Lsr(pilMailboxWait(getConnection(), msTimeout));
        // TODO: Should be implemented as soon as Health monitor functionality will be implemented.
        LOG_HEALTH(errValue != LSR_NO_ERROR, LSR_COMP_COMMUNICATION, errValue, NULL);
    }

    errValue = convertErrorPil2Lsr(pilMailboxGet(getConnection(), &fromConnection, &data, &dataLen));

    // TODO: Should be implemented as soon as Health monitor functionality will be implemented.
    LOG_HEALTH(errValue != LSR_NO_ERROR, LSR_COMP_COMMUNICATION, errValue, NULL);

    while ((NULL != data) && numMessages < MAX_NUM_MESSAGE_TO_PROCESS)
    {
        if (m_pOdiRecorder)
        {
            if (0 == numMessages)
            {
                m_pOdiRecorder->beginChunk(OdiRecorder::MessageDirection::INCOMING);
            }
            m_pOdiRecorder->write(data, dataLen, messageType);
        }

        // Process data. Almost errors in onMessage should not cause fatal error.
        // HandleIncomingData() should be robust to failure
        errValue = onMessage(fromConnection, data, dataLen);

        LOG_HEALTH(errValue != LSR_NO_ERROR, LSR_COMP_COMMUNICATION, errValue, NULL);

        pilMailboxPop(getConnection());
        ++numMessages;

        errValue = convertErrorPil2Lsr(pilMailboxGet(getConnection(), &fromConnection, &data, &dataLen));
        // TODO: Should be implemented as soon as Health monitor functionality will be implemented.
        LOG_HEALTH(errValue != LSR_NO_ERROR, LSR_COMP_COMMUNICATION, errValue, NULL);

    }

    // This callback should return information to customer that there are unhandled messages in incoming buffer
    // TODO: Should be implemented as soon as Health monitor functionality will be implemented.
    LOG_HEALTH(MAX_NUM_MESSAGE_TO_PROCESS == numMessages, LSR_COMP_COMMUNICATION, PIL_NO_ERROR, NULL);

    if (m_pOdiRecorder && numMessages)
    {
        m_pOdiRecorder->endChunk(OdiRecorder::MessageDirection::INCOMING);
    }

    return errValue.get();
}

void PilOdiComSessionBase::setOdiRecorder(OdiRecorder *pRecorder)
{
    m_pOdiRecorder = pRecorder;
}

LSRError PilOdiComSessionBase::activateFUConnection(IFuConnection* pFuConnection)
{
    LSRError errValue = LSR_NO_ERROR;

    if (NULL == pFuConnection)
    {
        errValue = LSR_INVALID_PARAMETER;
    }
    else if (m_isEngine)
    {
        errValue = LSR_UNKNOWN_ERROR;
    }

    if (errValue == LSR_NO_ERROR)
    {
        U8 index = 0;

        while (PilMsgTransmitter* pMsgTransmitter = getTransmitter(index))
        {
            errValue = pFuConnection->registerFu(pMsgTransmitter);
            ++index;
        }
    }

    return errValue;
}

LSRError PilOdiComSessionBase::registerMsgReceiver(IMsgReceiver* pReceiver, const U8 newMsgType,
                                     U32 minPayload /*= NO_PAYLOAD_LIMIT*/, U32 maxPayload /*= NO_PAYLOAD_LIMIT*/)
{
    LSRError errValue = LSR_UNKNOWN_ERROR;
    U8 messageType = MessageTypes::UNKNOWN;
    bool needToAdd = true;
    U32 index = 0;

    while (NULL != getReceiver(index, messageType))
    {
        if (messageType == newMsgType)
        {
            errValue = LSR_SESSION_RECEIVER_ALREADY_REGISTERED;
            needToAdd = false;
            break;
        }

        ++index;
    }

    if (needToAdd)
    {
        errValue = setReceiver(index, pReceiver, newMsgType);
    }

    return errValue;
}

void PilOdiComSessionBase::unregisterAllMsgReceivers()
{
    U32 index = 0;
    U8 messageType = MessageTypes::UNKNOWN;

    while (NULL != getReceiver(index, messageType))
    {
        setReceiver(index, NULL, MessageTypes::UNKNOWN);
        ++index;
    }
}

PILMailbox PilOdiComSessionBase::getConnection()
{
    PilMsgTransmitter* pTransmitter = getTransmitter(0);
    PILMailbox targetConnection = PIL_UNKNOWN_MAILBOX;

    if (NULL != pTransmitter)
    {
        // For all transmitters in list in PilOdiComSession the m_form field always has the same value.
        // Each communication component has always at least on transmitters.
        // So no need to enumerate all transmitters. We just get first and return m_form value.
        targetConnection = pTransmitter->getFrom();
    }

    return targetConnection;
}

LSRError PilOdiComSessionBase::unregisterMsgReceiver(IMsgReceiver* pMsgReceiver, U8 receiverMsgType)
{
    U32 currentIndex = 0;
    U32 previousIndex = 0;
    U8 currentMsgType = MessageTypes::UNKNOWN;
    IMsgReceiver* pCurrentReceiver = NULL;
    LSRError errValue = LSR_UNKNOWN_ERROR;
    bool needToShift = false;

    if (NULL != pMsgReceiver)
    {
        do
        {
            pCurrentReceiver = getReceiver(currentIndex, currentMsgType);

            if (needToShift)
            {
                // Shift tail of array to remove found receiver
                // NULL receiver should be shifted as well to remove last element and reduce size of array
                errValue = setReceiver(previousIndex, pCurrentReceiver, currentMsgType);
                if (errValue != LSR_NO_ERROR)
                {
                    break;
                }

                ++previousIndex;
            }
            else
            {
                if (receiverMsgType == currentMsgType && pMsgReceiver == pCurrentReceiver)
                {
                    needToShift = true;
                    previousIndex = currentIndex;
                    errValue = LSR_NO_ERROR;
                }
            }

            ++currentIndex;
        } while (NULL != pCurrentReceiver);
    }

    return errValue;
}

} // namespace lsr
