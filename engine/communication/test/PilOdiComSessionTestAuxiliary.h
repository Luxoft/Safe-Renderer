#ifndef LUXOFTSAFERENDERER_PILODICOMSESSIONTESTAUXILLARY_H
#define LUXOFTSAFERENDERER_PILODICOMSESSIONTESTAUXILLARY_H

/******************************************************************************
**
**   File:        PilOdiComSessionTestAuxiliary.h
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

#include "gmock/gmock.h"
#include "OdiTypes.h"
#include "PilOdiComSession.h"
#include "pil_config.h"
#include "InputStream.h"


/*!
* @addtogroup lsr
* @{
*/
namespace lsr
{

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4373 )
#endif

class MockDummyRecevier : public IMsgReceiver
{
public:
    MOCK_METHOD3(onMessage, LSRError(IMsgTransmitter* pMsgTransmitter, const U8 messageType, InputStream& stream));
    MOCK_METHOD1(onConnect, void(IMsgTransmitter* pMsgTransmitter));
    MOCK_METHOD1(onDisconnect, void(IMsgTransmitter* pMsgTransmitter));
private:
    PILMailbox m_To;
    U8 m_MessageType;
    U8* m_pData;
    U8* m_DataLen;
};

class MockInititalSenderRecevier : public IMsgReceiver
{
public:
    MockInititalSenderRecevier(U8 messageType, U8* data, U32 dataLen)
        : m_MessageType(messageType)
        , m_pData(data)
        , m_DataLen(dataLen)
    {}

    LSRError onMessage(IMsgTransmitter* pMsgTransmitter, const U8 messageType, InputStream& stream);
    MOCK_METHOD1(onConnect, void(IMsgTransmitter* pMsgTransmitter));
    MOCK_METHOD1(onDisconnect, void(IMsgTransmitter* pMsgTransmitter));
private:
    PILMailbox m_To;
    U8 m_MessageType;
    U8* m_pData;
    U32 m_DataLen;
};

LSRError MockInititalSenderRecevier::onMessage(IMsgTransmitter* pMsgTransmitter, const U8, InputStream&)
{
    return pMsgTransmitter->transmitMessage(m_pData, m_DataLen);
}

class MockMirrorRecevier : public IMsgReceiver
{
public:
    MockMirrorRecevier(const U8 messageType)
        : m_messageType(messageType)
    {}
    LSRError onMessage(IMsgTransmitter* pMsgTransmitter, const U8 messageType, InputStream& stream);

    MOCK_METHOD1(onConnect, void(IMsgTransmitter* pMsgTransmitter));
    MOCK_METHOD1(onDisconnect, void(IMsgTransmitter* pMsgTransmitter));
private:
    const U8 m_messageType;
};

LSRError MockMirrorRecevier::onMessage(IMsgTransmitter* pMsgTransmitter, const U8 messageType, InputStream& stream)
{
    LSRError errValue = LSR_UNKNOWN_ERROR;
    U32 dataLen = stream.bytesToRead();
    U8* pData = new U8[dataLen];

    if (NULL != pData)
    {
        errValue = pMsgTransmitter->transmitMessage(pData, dataLen);
        delete [] pData;
    }

    return errValue;
}

class PilComSessionWithError : public PilOdiComSessionBase
{

public:

    PilComSessionWithError(const PILMailbox connection, const bool isEngine)
    : PilOdiComSessionBase(isEngine)
    , m_pDummyTransmitter(NULL)
    , m_pDummyReceiver(NULL)
    , m_DummyMessageType(MessageTypes::UNKNOWN)
    , m_DummyError(LSR_NO_ERROR)
    , m_transmittersArraySize(0)
    {
        for (int i = 0; i < 10; ++i)
        {
            m_pDummyTransmittersArr[i] = NULL;
        }
    }

    void SetDummyError(LSRError dummyError)
    {
        m_DummyError = dummyError;
    }

    void SetDummyReceiver(IMsgReceiver* pReceiver)
    {
        m_pDummyReceiver = pReceiver;
    }

    void SetDummyMessageType(U8 messageType)
    {
        m_DummyMessageType = messageType;
    }

    void SetDummyTransmitter(PilMsgTransmitter* pTransmitter)
    {
        m_pDummyTransmitter = pTransmitter;
        m_transmittersArraySize = 0;
    }

    void SetDummyTransmittersArray(PilMsgTransmitter** ppTransmitterArr, U32 transmitterArraySize)
    {
        m_transmittersArraySize = transmitterArraySize;

        for (U32 i = 0; i < m_transmittersArraySize; ++i)
        {
            m_pDummyTransmittersArr[i] = ppTransmitterArr[i];
        }
    }

protected:
    virtual IMsgReceiver* getReceiver(U8 index, U8& messageType) P_OVERRIDE
    {
        messageType = m_DummyMessageType;
        IMsgReceiver* pReceiver = m_pDummyReceiver;

        m_DummyMessageType = MessageTypes::UNKNOWN;
        m_pDummyReceiver = NULL;

        return pReceiver;
    }

    virtual LSRError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) P_OVERRIDE
    {
        LSRError errValue = m_DummyError;
        m_DummyError = LSR_NO_ERROR;
        return errValue;
    }

    virtual PilMsgTransmitter* getTransmitter(U8 index) P_OVERRIDE
    {
        if (0 == m_transmittersArraySize)
        {
            PilMsgTransmitter* pTransmitter = m_pDummyTransmitter;
            m_pDummyTransmitter = NULL;
            return pTransmitter;
        }
        else
        {
            PilMsgTransmitter* pTransmitter = m_pDummyTransmittersArr[m_transmittersArraySize - 1];
            --m_transmittersArraySize;
            return pTransmitter;
        }
    }

private:
    PilMsgTransmitter* m_pDummyTransmitter;
    IMsgReceiver* m_pDummyReceiver;
    U8 m_DummyMessageType;
    LSRError m_DummyError;
    PilMsgTransmitter* m_pDummyTransmittersArr[10];
    U32 m_transmittersArraySize;
};

class PilComSessionDefaultConstructor : public PilOdiComSessionBase
{
public:
    PilComSessionDefaultConstructor()
        : PilOdiComSessionBase(true)
        {
        }
protected:
    virtual IMsgReceiver* getReceiver(U8 index, U8& messageType) P_OVERRIDE
    {
        return NULL;
    }

    virtual LSRError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) P_OVERRIDE
    {
        return LSR_NO_ERROR;
    }

    virtual PilMsgTransmitter* getTransmitter(U8 index) P_OVERRIDE
    {
        return NULL;
    }

};

#ifdef WIN32
#pragma warning( pop )
#endif

class TestBroadcastFuConnection : public lsr::IFuConnection
{
public:
    TestBroadcastFuConnection(U8* pRegisterMsgData, U32 registerMsgSize)
        : m_pData(pRegisterMsgData)
        , m_DataSize(registerMsgSize)
    {

    }

    virtual LSRError registerFu(PilMsgTransmitter*);
private:
    U8* m_pData;
    U32 m_DataSize;
};

LSRError TestBroadcastFuConnection::registerFu(PilMsgTransmitter* pTransmitter)
{
    m_pData[0] = MessageTypes::REGISTRATION;
    return pTransmitter->transmitMessage(static_cast<U8*>(m_pData), m_DataSize);
}

class TestFuConnection : public lsr::IFuConnection
{
public:
    TestFuConnection(U8* pRegisterMsgData, U32 registerMsgSize)
        : m_pData(pRegisterMsgData)
        , m_DataSize(registerMsgSize)
    {

    }

    virtual LSRError registerFu(PilMsgTransmitter*);
private:
    U8* m_pData;
    U32 m_DataSize;
};

LSRError TestFuConnection::registerFu(PilMsgTransmitter* pTransmitter)
{
    LSRError ret = LSR_NO_ERROR;

    if ( ConnectionIndex::PILConn_Lsr == pTransmitter->getTo() )
    {
        m_pData[0] = MessageTypes::REGISTRATION;
        ret = pTransmitter->transmitMessage(static_cast<U8*>(m_pData), m_DataSize);
    }

    return ret;
}

} // namespace lsr
/*! @} */

#endif // LUXOFTSAFERENDERER_PILODICOMSESSIONTESTAUXILLARY_H
