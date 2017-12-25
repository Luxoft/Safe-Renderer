#ifndef POPULUSSC_PGWODICOMSESSIONTESTAUXILLARY_H
#define POPULUSSC_PGWODICOMSESSIONTESTAUXILLARY_H

/******************************************************************************
**
**   File:        PgwOdiComSessionTestAuxiliary.h
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

#include "gmock/gmock.h"
#include "OdiTypes.h"
#include "PgwOdiComSession.h"
#include "pgw_config.h"
#include "InputStream.h"


/*!
* @addtogroup psc
* @{
*/
namespace psc
{

#ifdef WIN32
#pragma warning( push )
#pragma warning( disable : 4373 )
#endif

class MockDummyRecevier : public IMsgReceiver
{
public:
    MOCK_METHOD3(onMessage, PSCError(IMsgTransmitter* pMsgTransmitter, const U8 messageType, InputStream& stream));
    MOCK_METHOD1(onConnect, void(IMsgTransmitter* pMsgTransmitter));
    MOCK_METHOD1(onDisconnect, void(IMsgTransmitter* pMsgTransmitter));
private:
    PGWMailbox m_To;
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

    PSCError onMessage(IMsgTransmitter* pMsgTransmitter, const U8 messageType, InputStream& stream);
    MOCK_METHOD1(onConnect, void(IMsgTransmitter* pMsgTransmitter));
    MOCK_METHOD1(onDisconnect, void(IMsgTransmitter* pMsgTransmitter));
private:
    PGWMailbox m_To;
    U8 m_MessageType;
    U8* m_pData;
    U32 m_DataLen;
};

PSCError MockInititalSenderRecevier::onMessage(IMsgTransmitter* pMsgTransmitter, const U8, InputStream&)
{
    return pMsgTransmitter->transmitMessage(m_pData, m_DataLen);
}

class MockMirrorRecevier : public IMsgReceiver
{
public:
    MockMirrorRecevier(const U8 messageType)
        : m_messageType(messageType)
    {}
    PSCError onMessage(IMsgTransmitter* pMsgTransmitter, const U8 messageType, InputStream& stream);

    MOCK_METHOD1(onConnect, void(IMsgTransmitter* pMsgTransmitter));
    MOCK_METHOD1(onDisconnect, void(IMsgTransmitter* pMsgTransmitter));
private:
    const U8 m_messageType;
};

PSCError MockMirrorRecevier::onMessage(IMsgTransmitter* pMsgTransmitter, const U8 messageType, InputStream& stream)
{
    PSCError errValue = PSC_UNKNOWN_ERROR;
    U32 dataLen = stream.bytesToRead();
    U8* pData = new U8[dataLen];

    if (NULL != pData)
    {
        errValue = pMsgTransmitter->transmitMessage(pData, dataLen);
        delete [] pData;
    }

    return errValue;
}

class PgwComSessionWithError : public PgwOdiComSessionBase
{

public:

    PgwComSessionWithError(const PGWMailbox connection, const bool isEngine)
    : PgwOdiComSessionBase(isEngine)
    , m_pDummyTransmitter(NULL)
    , m_pDummyReceiver(NULL)
    , m_DummyMessageType(MessageTypes::UNKNOWN)
    , m_DummyError(PSC_NO_ERROR)
    , m_transmittersArraySize(0)
    {
        for (int i = 0; i < 10; ++i)
        {
            m_pDummyTransmittersArr[i] = NULL;
        }
    }

    void SetDummyError(PSCError dummyError)
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

    void SetDummyTransmitter(PgwMsgTransmitter* pTransmitter)
    {
        m_pDummyTransmitter = pTransmitter;
        m_transmittersArraySize = 0;
    }

    void SetDummyTransmittersArray(PgwMsgTransmitter** ppTransmitterArr, U32 transmitterArraySize)
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

    virtual PSCError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) P_OVERRIDE
    {
        PSCError errValue = m_DummyError;
        m_DummyError = PSC_NO_ERROR;
        return errValue;
    }

    virtual PgwMsgTransmitter* getTransmitter(U8 index) P_OVERRIDE
    {
        if (0 == m_transmittersArraySize)
        {
            PgwMsgTransmitter* pTransmitter = m_pDummyTransmitter;
            m_pDummyTransmitter = NULL;
            return pTransmitter;
        }
        else
        {
            PgwMsgTransmitter* pTransmitter = m_pDummyTransmittersArr[m_transmittersArraySize - 1];
            --m_transmittersArraySize;
            return pTransmitter;
        }
    }

private:
    PgwMsgTransmitter* m_pDummyTransmitter;
    IMsgReceiver* m_pDummyReceiver;
    U8 m_DummyMessageType;
    PSCError m_DummyError;
    PgwMsgTransmitter* m_pDummyTransmittersArr[10];
    U32 m_transmittersArraySize;
};

class PgwComSessionDefaultConstructor : public PgwOdiComSessionBase
{
public:
    PgwComSessionDefaultConstructor()
        : PgwOdiComSessionBase(true)
        {
        }
protected:
    virtual IMsgReceiver* getReceiver(U8 index, U8& messageType) P_OVERRIDE
    {
        return NULL;
    }

    virtual PSCError setReceiver(U8 index, IMsgReceiver* pMsgReceiver, const U8 messageType) P_OVERRIDE
    {
        return PSC_NO_ERROR;
    }

    virtual PgwMsgTransmitter* getTransmitter(U8 index) P_OVERRIDE
    {
        return NULL;
    }

};

#ifdef WIN32
#pragma warning( pop )
#endif

class TestBroadcastFuConnection : public psc::IFuConnection
{
public:
    TestBroadcastFuConnection(U8* pRegisterMsgData, U32 registerMsgSize)
        : m_pData(pRegisterMsgData)
        , m_DataSize(registerMsgSize)
    {

    }

    virtual PSCError registerFu(PgwMsgTransmitter*);
private:
    U8* m_pData;
    U32 m_DataSize;
};

PSCError TestBroadcastFuConnection::registerFu(PgwMsgTransmitter* pTransmitter)
{
    m_pData[0] = MessageTypes::REGISTRATION;
    return pTransmitter->transmitMessage(static_cast<U8*>(m_pData), m_DataSize);
}

class TestFuConnection : public psc::IFuConnection
{
public:
    TestFuConnection(U8* pRegisterMsgData, U32 registerMsgSize)
        : m_pData(pRegisterMsgData)
        , m_DataSize(registerMsgSize)
    {

    }

    virtual PSCError registerFu(PgwMsgTransmitter*);
private:
    U8* m_pData;
    U32 m_DataSize;
};

PSCError TestFuConnection::registerFu(PgwMsgTransmitter* pTransmitter)
{
    PSCError ret = PSC_NO_ERROR;

    if ( ConnectionIndex::PGWConn_Populus == pTransmitter->getTo() )
    {
        m_pData[0] = MessageTypes::REGISTRATION;
        ret = pTransmitter->transmitMessage(static_cast<U8*>(m_pData), m_DataSize);
    }

    return ret;
}

} // namespace psc
/*! @} */

#endif // POPULUSSC_PGWODICOMSESSIONTESTAUXILLARY_H
