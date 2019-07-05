/******************************************************************************
**
**   File:        PilOdiComSessionTest.cpp
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

#include "gtest/gtest.h"
#include "InputStream.h"
#include "OdiRecorder.h"
#include "PilOdiComSessionTestAuxiliary.h"

#include <algorithm>


using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::AtLeast;

namespace lsr
{

/**
 * As gtest provides only one template parameter in test fixture
 * to be checked in TYPED_TEST_CASE we have to hide template parameters in some struct.
 */
template <U8 A, U8 B>
class RangeDefinitions
{
public:
    static const U8 ReceiversNumber = A;
    static const U8 TransmittersNumber = B;
};

template<U8 A, U8 B> const U8 RangeDefinitions<A,B>::ReceiversNumber;
template<U8 A, U8 B> const U8 RangeDefinitions<A,B>::TransmittersNumber;

template <class T>
class PilOdiComSessionTest : public ::testing::Test
{
public:
    PilOdiComSessionTest()
        : m_engine(ConnectionIndex::PILConn_Lsr, true)
        , m_fu(ConnectionIndex::PILConn_Fu1App, false)
    {
    }

    virtual ~PilOdiComSessionTest()
    {
    }

protected:
    void SetUp()
    {
        pilClose();
    }
    void TearDown()
    {
        pilClose();
    }

protected:
    PilOdiComSession<T::ReceiversNumber, T::TransmittersNumber> m_engine;
    PilOdiComSession<T::ReceiversNumber, T::TransmittersNumber> m_fu;
};


template <U8 ReceiversNumber, U8 TransmittersNumber>
void dynamicAllocationTest()
{
    PilOdiComSession<ReceiversNumber, TransmittersNumber>* pNode =
        new PilOdiComSession<ReceiversNumber, TransmittersNumber>(ConnectionIndex::PILConn_Lsr, true);
    ASSERT_TRUE(NULL != pNode);
    delete pNode;
    pNode = NULL;

    pNode = new PilOdiComSession<ReceiversNumber, TransmittersNumber>(ConnectionIndex::PILConn_Lsr, false);
    ASSERT_TRUE(NULL != pNode);
    delete pNode;
}

template <U8 ReceiversNumber, U8 TransmittersNumber>
void nonInitializedPilLibraryTest(PilOdiComSessionBase* pEngine, PilOdiComSessionBase* pFu)
{
    // Try to use communication component without pil library initialization
    MockDummyRecevier r1;

    U8 dummyBuffer[] = { 0, 0, 0, 0, 0 };
    TestBroadcastFuConnection fuConn(&dummyBuffer[0], sizeof(dummyBuffer));

    EXPECT_FALSE(pEngine->activateFUConnection(&fuConn) == LSR_NO_ERROR);
    EXPECT_FALSE(pEngine->handleIncomingData(0) == LSR_NO_ERROR);

    EXPECT_FALSE(pFu->activateFUConnection(&fuConn) == LSR_NO_ERROR);
    EXPECT_FALSE(pFu->handleIncomingData(0) == LSR_NO_ERROR);
}

template <U8 ReceiversNumber, U8  TransmittersNumber>
void defaultCopyConstructorTest(PilOdiComSession<ReceiversNumber, TransmittersNumber>* pEngine, PilOdiComSession<ReceiversNumber, TransmittersNumber>* pFu)
{
    PilOdiComSession<ReceiversNumber, TransmittersNumber> engine(*pEngine);
    PilOdiComSession<ReceiversNumber, TransmittersNumber> fu(*pFu);

    U8 dummyBuffer[] = { 0, 0, 0, 0, 0 };

    pilInit();

    TestBroadcastFuConnection fuConn(&dummyBuffer[0], sizeof(dummyBuffer));
    EXPECT_FALSE(engine.activateFUConnection(&fuConn) == LSR_NO_ERROR);
    EXPECT_TRUE(fu.activateFUConnection(&fuConn) == LSR_PIL_MBOX_NOT_INITIALIZED);
}

typedef ::testing::Types < RangeDefinitions<2, 3>, RangeDefinitions<5, 4> > ValuesSet;

TYPED_TEST_CASE(PilOdiComSessionTest, ValuesSet);

TYPED_TEST(PilOdiComSessionTest, dynamicAllocation)
{
    dynamicAllocationTest<TypeParam::ReceiversNumber, TypeParam::TransmittersNumber>();
}

TYPED_TEST(PilOdiComSessionTest, nonInitializedPilLibrary)
{
    nonInitializedPilLibraryTest<TypeParam::ReceiversNumber, TypeParam::TransmittersNumber>(&this->m_engine, &this->m_fu);
}

TYPED_TEST(PilOdiComSessionTest, defaultCopyConstructor)
{
    defaultCopyConstructorTest<TypeParam::ReceiversNumber, TypeParam::TransmittersNumber>(&this->m_engine, &this->m_fu);
}

TYPED_TEST(PilOdiComSessionTest, receiverRegistration)
{
    MockDummyRecevier receiver[TypeParam::ReceiversNumber + 1];

    // Normal receiver registration
    for (int i = 0 ; i < TypeParam::ReceiversNumber; ++i)
    {
        EXPECT_TRUE(this->m_engine.registerMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
        EXPECT_TRUE(this->m_fu.registerMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
    }

    // Register too many receivers
    EXPECT_TRUE(this->m_engine.registerMsgReceiver(&receiver[TypeParam::ReceiversNumber], MessageTypes::REGISTRATION + TypeParam::ReceiversNumber) == LSR_SESSION_TOO_MANY_RECEIVERS);
    EXPECT_TRUE(this->m_fu.registerMsgReceiver(&receiver[TypeParam::ReceiversNumber], MessageTypes::REGISTRATION + TypeParam::ReceiversNumber) == LSR_SESSION_TOO_MANY_RECEIVERS);

    for (int i = 0 ; i < TypeParam::ReceiversNumber; ++i)
    {
        MockDummyRecevier r1;
        // Try to register twice
        EXPECT_TRUE(this->m_engine.registerMsgReceiver(&r1, MessageTypes::REGISTRATION + i) == LSR_SESSION_RECEIVER_ALREADY_REGISTERED);
        EXPECT_TRUE(this->m_fu.registerMsgReceiver(&r1, MessageTypes::REGISTRATION + i) == LSR_SESSION_RECEIVER_ALREADY_REGISTERED);
    }


    for (int i = 0 ; i < TypeParam::ReceiversNumber; ++i)
    {
        // Unregister all receivers one-by-one
        EXPECT_TRUE(this->m_engine.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
        EXPECT_FALSE(this->m_engine.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);

        EXPECT_TRUE(this->m_fu.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
        EXPECT_FALSE(this->m_fu.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
    }

    // Check that we can register maximum receivers again
    for (int i = 0 ; i < TypeParam::ReceiversNumber; ++i)
    {
        EXPECT_TRUE(this->m_engine.registerMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
        EXPECT_TRUE(this->m_fu.registerMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
    }

    // Unregister all receivers again
    this->m_engine.unregisterAllMsgReceivers();
    this->m_fu.unregisterAllMsgReceivers();

    // Check one more time that we can register maximum receivers number again
    for (int i = 0 ; i < TypeParam::ReceiversNumber; ++i)
    {
        EXPECT_TRUE(this->m_engine.registerMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
        EXPECT_TRUE(this->m_fu.registerMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
    }

    for (int i = TypeParam::ReceiversNumber - 1; i >= 0; --i)
    {
        // Unregister all receivers one-by-one
        EXPECT_TRUE(this->m_engine.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
        EXPECT_FALSE(this->m_engine.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);

        EXPECT_TRUE(this->m_fu.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
        EXPECT_FALSE(this->m_fu.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
    }

    // Check one more time that we can register maximum receivers number again
    for (int i = 0 ; i < TypeParam::ReceiversNumber; ++i)
    {
        EXPECT_TRUE(this->m_engine.registerMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
        EXPECT_TRUE(this->m_fu.registerMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
    }

    // Unregister all receivers again
    this->m_engine.unregisterAllMsgReceivers();
    this->m_fu.unregisterAllMsgReceivers();

    // Check that there aren't any receivers registered
    for (int i = 0 ; i < TypeParam::ReceiversNumber; ++i)
    {
        EXPECT_FALSE(this->m_engine.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
        EXPECT_FALSE(this->m_fu.unregisterMsgReceiver(&receiver[i], MessageTypes::REGISTRATION + i) == LSR_NO_ERROR);
    }
}

bool readMsgAndCheckFormat(PILMailbox connection, U8 from, U8* refData, U32 refDataLen)
{
    bool retValue = true;
    PILMailbox fromConnection = PIL_UNKNOWN_MAILBOX;
    uint8_t* data = NULL;
    uint32_t dataLen = 0;

    if (PIL_NO_ERROR != pilMailboxGet(connection, &fromConnection, &data, &dataLen))
    {
        retValue = false;
        EXPECT_TRUE(retValue);
    }
    else if (fromConnection != from || dataLen != refDataLen)
    {
        retValue = false;
        EXPECT_TRUE(retValue);
    }
    else if (0 != memcmp(data, refData, refDataLen))
    {
        retValue = false;
        EXPECT_TRUE(retValue);
    }

    EXPECT_TRUE(PIL_NO_ERROR == pilMailboxPop(connection));

    return retValue;
}

TYPED_TEST(PilOdiComSessionTest, activateFUConnectionTest)
{
    U8 dummyBuffer[] = { 0, 0, 0, 0, 0 };
    TestBroadcastFuConnection fuConn(&dummyBuffer[0], sizeof(dummyBuffer));

    // Check that mbox cannot be initialized without pilInit()
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NOT_INITIALIZED == pilMailboxInit(i));
    }

    // Check that ActivateFuConnection returns error without pilInit()
    EXPECT_TRUE(this->m_engine.activateFUConnection(&fuConn) == LSR_UNKNOWN_ERROR);
    EXPECT_TRUE(this->m_fu.activateFUConnection(&fuConn) == LSR_PIL_NOT_INITIALIZED);
    EXPECT_TRUE(this->m_engine.activateFUConnection(NULL) == LSR_INVALID_PARAMETER);
    EXPECT_TRUE(this->m_fu.activateFUConnection(NULL) == LSR_INVALID_PARAMETER);

    pilInit();

    // Check that mbox are initialized successfully
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NO_ERROR == pilMailboxInit(i));
    }

    // Check that FU activation doesn't work for NULL IFuConnection* argument
    EXPECT_TRUE(this->m_engine.activateFUConnection(NULL) == LSR_INVALID_PARAMETER);
    EXPECT_TRUE(this->m_fu.activateFUConnection(NULL) == LSR_INVALID_PARAMETER);

    // Check that FU activation doesn't work for engine side
    EXPECT_TRUE(this->m_engine.activateFUConnection(&fuConn) == LSR_UNKNOWN_ERROR);

    // Check activation success on fu side
    EXPECT_TRUE(this->m_fu.activateFUConnection(&fuConn) == LSR_NO_ERROR);

    const U8 maxTransmittersNumber = std::min<U8>(ConnectionIndex::PILConn_Last - 1, TypeParam::TransmittersNumber);

    for (U8 i = ConnectionIndex::PILConn_Lsr; i < maxTransmittersNumber; ++i)
    {
        EXPECT_EQ(true, readMsgAndCheckFormat(i, ConnectionIndex::PILConn_Fu1App, &dummyBuffer[0], sizeof(dummyBuffer)));
    }
}

TYPED_TEST(PilOdiComSessionTest, handleIncomingDataTest)
{
    char buffer[255] = {0};

    U8 dummyBuffer[] = { 0, 0, 0, 0, 0 };
    TestFuConnection fuConn(&dummyBuffer[0], sizeof(dummyBuffer));
    MockInititalSenderRecevier regReceiver(MessageTypes::ODI, &dummyBuffer[0], sizeof(dummyBuffer));

    EXPECT_TRUE(this->m_engine.handleIncomingData(0) == LSR_PIL_NOT_INITIALIZED);

    pilInit();
    EXPECT_TRUE(this->m_engine.handleIncomingData(0) == LSR_PIL_MBOX_NOT_INITIALIZED);

    // Check that mbox are initialized successfully
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NO_ERROR == pilMailboxInit(i));
    }

    OdiRecorder odiRecorder(static_cast<void*>(buffer), sizeof(buffer));

    this->m_engine.setOdiRecorder(&odiRecorder);
    this->m_fu.setOdiRecorder(&odiRecorder);

    EXPECT_TRUE(this->m_engine.registerMsgReceiver(&regReceiver, MessageTypes::ODI) == LSR_NO_ERROR);
    EXPECT_TRUE(this->m_engine.registerMsgReceiver(&regReceiver, MessageTypes::REGISTRATION) == LSR_NO_ERROR);

    EXPECT_TRUE(this->m_fu.activateFUConnection(&fuConn) == LSR_NO_ERROR);
    EXPECT_TRUE(this->m_engine.handleIncomingData(0) == LSR_NO_ERROR);


    this->m_engine.setOdiRecorder(NULL);
    this->m_fu.setOdiRecorder(NULL);

    EXPECT_TRUE(this->m_fu.activateFUConnection(&fuConn) == LSR_NO_ERROR);
    EXPECT_TRUE(this->m_engine.handleIncomingData(0) == LSR_NO_ERROR);

    // This test case is needed to cover some branches with pTransmitter == NULL in private onMessage function
    PilComSessionWithError errorOdiSession(ConnectionIndex::PILConn_Lsr, true);
    dummyBuffer[0] = MessageTypes::REGISTRATION;
    PilMsgTransmitter transmitter;
    transmitter.setConnection(ConnectionIndex::PILConn_Lsr, ConnectionIndex::PILConn_Fu1App);
    PilMsgTransmitter* pTrArr[] = {NULL, &transmitter, &transmitter};

    errorOdiSession.SetDummyError(LSR_NO_ERROR);
    errorOdiSession.SetDummyTransmittersArray(&pTrArr[0], sizeof(pTrArr) / sizeof(PilMsgTransmitter*));
    errorOdiSession.SetDummyReceiver(reinterpret_cast<IMsgReceiver*>(&regReceiver));
    errorOdiSession.SetDummyMessageType(MessageTypes::REGISTRATION);

    EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, ConnectionIndex::PILConn_Fu1App, &dummyBuffer[0], sizeof(dummyBuffer)));
    EXPECT_EQ(LSR_PIL_MBOX_INVALID, errorOdiSession.handleIncomingData(0));
}

TYPED_TEST(PilOdiComSessionTest, corruptedMessages)
{
    uint8_t dummyBuffer[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7 };
    uint8_t dummyBuffer_too_long[20000] = {0};

    MockInititalSenderRecevier regReceiver(MessageTypes::ODI, &dummyBuffer[0], sizeof(dummyBuffer));

    char buffer[255] = { 0 };
    OdiRecorder odiRecorder(static_cast<void*>(buffer), sizeof(buffer));
    this->m_engine.setOdiRecorder(&odiRecorder);
    this->m_fu.setOdiRecorder(&odiRecorder);

    pilInit();

    // Check that mbox are initialized successfully
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NO_ERROR == pilMailboxInit(i));
    }

    EXPECT_TRUE(this->m_engine.registerMsgReceiver(&regReceiver, MessageTypes::REGISTRATION) == LSR_NO_ERROR);

    // Send message from undefined fuId
    dummyBuffer[0] = MessageTypes::REGISTRATION;
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, 252, &dummyBuffer[0], sizeof(dummyBuffer)));
    EXPECT_EQ(LSR_SESSION_UNDEFINED_TRANSMITTER, this->m_engine.handleIncomingData(0));

    // Send wrong message type. handleIncomingData() should return LSR_NO_ERROR.
    dummyBuffer[0] = MessageTypes::UNKNOWN - 1;
    ASSERT_TRUE(dummyBuffer[0] > MessageTypes::LAST);
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, ConnectionIndex::PILConn_Fu1App, &dummyBuffer[0], sizeof(dummyBuffer)));
    EXPECT_EQ(LSR_COMM_INVALID_FIELD_IN_MSG, this->m_engine.handleIncomingData(0));

    // Too long message
    dummyBuffer_too_long[0] = MessageTypes::ODI;
    EXPECT_EQ(PIL_UNKNOWN_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, ConnectionIndex::PILConn_Fu1App, &dummyBuffer_too_long[0], sizeof(dummyBuffer_too_long)));
    EXPECT_TRUE(this->m_engine.handleIncomingData(0) == LSR_NO_ERROR);

    // Empty message
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, 253, NULL, 0));
    EXPECT_EQ(LSR_SESSION_UNDEFINED_TRANSMITTER, this->m_engine.handleIncomingData(0));

    // Empty message with non-zero empty pointer
    dummyBuffer[0] = MessageTypes::ODI;
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, 253, &dummyBuffer[0], 0));
    EXPECT_EQ(LSR_SESSION_UNDEFINED_TRANSMITTER, this->m_engine.handleIncomingData(0));

    // Null pointer buffer with non-zero size
    EXPECT_EQ(PIL_UNKNOWN_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, 253, NULL, sizeof(dummyBuffer)));

    // Too many messages
    for (U8 index = 0; index < 20; ++index)
    {
        dummyBuffer[0] = MessageTypes::ODI;
        EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, ConnectionIndex::PILConn_Fu1App, &dummyBuffer[0], sizeof(dummyBuffer)));
    }

    EXPECT_EQ(LSR_PIL_INVALID_MSG, this->m_engine.handleIncomingData(0));
}

TYPED_TEST(PilOdiComSessionTest, unregisterMsgReceiverUnavailableBranchCoverage)
{
    pilInit();

    // Check that mbox are initialized successfully
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NO_ERROR == pilMailboxInit(i));
    }

    EXPECT_TRUE(this->m_engine.unregisterMsgReceiver(NULL, MessageTypes::UNKNOWN)== LSR_UNKNOWN_ERROR);
    EXPECT_TRUE(this->m_fu.unregisterMsgReceiver(NULL, MessageTypes::UNKNOWN)== LSR_UNKNOWN_ERROR);

    PilComSessionWithError errorOdiSession(ConnectionIndex::PILConn_Lsr, true);

    errorOdiSession.SetDummyError(LSR_SESSION_TOO_MANY_RECEIVERS);
    errorOdiSession.SetDummyTransmitter(NULL);
    errorOdiSession.SetDummyReceiver(reinterpret_cast<IMsgReceiver*>(0x12345678));
    errorOdiSession.SetDummyMessageType(12);
    EXPECT_FALSE(errorOdiSession.unregisterMsgReceiver(reinterpret_cast<IMsgReceiver*>(0x12345678), 12) == LSR_NO_ERROR);

    errorOdiSession.SetDummyError(LSR_SESSION_TOO_MANY_RECEIVERS);
    errorOdiSession.SetDummyTransmitter(NULL);
    errorOdiSession.SetDummyReceiver(reinterpret_cast<IMsgReceiver*>(0x12345678));
    errorOdiSession.SetDummyMessageType(12);
    EXPECT_FALSE(errorOdiSession.unregisterMsgReceiver(reinterpret_cast<IMsgReceiver*>(0x12345678), 13) == LSR_NO_ERROR);

    errorOdiSession.SetDummyError(LSR_SESSION_TOO_MANY_RECEIVERS);
    errorOdiSession.SetDummyTransmitter(NULL);
    errorOdiSession.SetDummyReceiver(reinterpret_cast<IMsgReceiver*>(0x12345678));
    errorOdiSession.SetDummyMessageType(12);
    EXPECT_FALSE(errorOdiSession.unregisterMsgReceiver(reinterpret_cast<IMsgReceiver*>(0x11111111), 12) == LSR_NO_ERROR);

    errorOdiSession.SetDummyError(LSR_SESSION_TOO_MANY_RECEIVERS);
    errorOdiSession.SetDummyTransmitter(NULL);
    errorOdiSession.SetDummyReceiver(reinterpret_cast<IMsgReceiver*>(0x12345678));
    errorOdiSession.SetDummyMessageType(12);
    EXPECT_TRUE(errorOdiSession.handleIncomingData(0) == LSR_PIL_MBOX_INVALID);
}

template <class T>
class PilOdiComSessionZeroReceiversTest : public ::testing::Test
{
public:
    PilOdiComSessionZeroReceiversTest()
        : m_engine(ConnectionIndex::PILConn_Lsr, true)
        , m_fu(ConnectionIndex::PILConn_Fu1App, false)
    {
    }

    virtual ~PilOdiComSessionZeroReceiversTest()
    {
    }

protected:
    void SetUp()
    {
        pilClose();
    }
    void TearDown()
    {
        pilClose();
    }

protected:
    PilOdiComSession<T::ReceiversNumber, T::TransmittersNumber> m_engine;
    PilOdiComSession<T::ReceiversNumber, T::TransmittersNumber> m_fu;
};

typedef ::testing::Types < RangeDefinitions<0, 2> > ZeroValuesSet;

TYPED_TEST_CASE(PilOdiComSessionZeroReceiversTest, ZeroValuesSet);

TYPED_TEST(PilOdiComSessionZeroReceiversTest, dynamicAllocation)
{
    dynamicAllocationTest<TypeParam::ReceiversNumber, TypeParam::TransmittersNumber>();
}

TYPED_TEST(PilOdiComSessionZeroReceiversTest, nonInitializedPilLibrary)
{
    nonInitializedPilLibraryTest<TypeParam::ReceiversNumber, TypeParam::TransmittersNumber>(&this->m_engine, &this->m_fu);
}

TYPED_TEST(PilOdiComSessionZeroReceiversTest, defaultCopyConstructor)
{
    defaultCopyConstructorTest<TypeParam::ReceiversNumber, TypeParam::TransmittersNumber>(&this->m_engine, &this->m_fu);
}

TYPED_TEST(PilOdiComSessionZeroReceiversTest, receiverRegistration)
{
    MockDummyRecevier receiver;

    // Register too many receivers
    EXPECT_TRUE(this->m_engine.registerMsgReceiver(&receiver, MessageTypes::REGISTRATION + TypeParam::ReceiversNumber) == LSR_SESSION_TOO_MANY_RECEIVERS);
    EXPECT_TRUE(this->m_fu.registerMsgReceiver(&receiver, MessageTypes::REGISTRATION + TypeParam::ReceiversNumber) == LSR_SESSION_TOO_MANY_RECEIVERS);
}

TYPED_TEST(PilOdiComSessionZeroReceiversTest, activateFUConnectionTest)
{
    U8 dummyBuffer[] = { 0, 0, 0, 0, 0 };
    TestBroadcastFuConnection fuConn(&dummyBuffer[0], sizeof(dummyBuffer));

    // Check that mbox cannot be initialized without pilInit()
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NOT_INITIALIZED == pilMailboxInit(i));
    }

    // Check that ActivateFuConnection returns error without pilInit()
    EXPECT_TRUE(this->m_engine.activateFUConnection(&fuConn) == LSR_UNKNOWN_ERROR);
    EXPECT_TRUE(this->m_fu.activateFUConnection(&fuConn) == LSR_PIL_NOT_INITIALIZED);
    EXPECT_TRUE(this->m_engine.activateFUConnection(NULL) == LSR_INVALID_PARAMETER);
    EXPECT_TRUE(this->m_fu.activateFUConnection(NULL) == LSR_INVALID_PARAMETER);

    pilInit();

    // Check that mbox are initialized successfully
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NO_ERROR == pilMailboxInit(i));
    }

    // Check that FU activation doesn't work for NULL IFuConnection* argument
    EXPECT_TRUE(this->m_engine.activateFUConnection(NULL) == LSR_INVALID_PARAMETER);
    EXPECT_TRUE(this->m_fu.activateFUConnection(NULL) == LSR_INVALID_PARAMETER);

    // Check that FU activation doesn't work for engine side
    EXPECT_TRUE(this->m_engine.activateFUConnection(&fuConn) == LSR_UNKNOWN_ERROR);

    // Check activation success on fu side
    EXPECT_TRUE(this->m_fu.activateFUConnection(&fuConn) == LSR_NO_ERROR);

    const U8 maxTransmittersNumber = std::min<U8>(ConnectionIndex::PILConn_Last - 1, TypeParam::TransmittersNumber);

    for (U8 i = ConnectionIndex::PILConn_Lsr; i < maxTransmittersNumber; ++i)
    {
        EXPECT_EQ(true, readMsgAndCheckFormat(i, ConnectionIndex::PILConn_Fu1App, &dummyBuffer[0], sizeof(dummyBuffer)));
    }
}

TYPED_TEST(PilOdiComSessionZeroReceiversTest, handleIncomingDataTest)
{
    char buffer[255] = { 0 };

    U8 dummyBuffer[] = { 0, 0, 0, 0, 0 };
    TestFuConnection fuConn(&dummyBuffer[0], sizeof(dummyBuffer));
    MockInititalSenderRecevier regReceiver(MessageTypes::ODI, &dummyBuffer[0], sizeof(dummyBuffer));

    EXPECT_TRUE(this->m_engine.handleIncomingData(0) == LSR_PIL_NOT_INITIALIZED);

    pilInit();
    EXPECT_TRUE(this->m_engine.handleIncomingData(0) == LSR_PIL_MBOX_NOT_INITIALIZED);

    // Check that mbox are initialized successfully
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NO_ERROR == pilMailboxInit(i));
    }

    OdiRecorder odiRecorder(static_cast<void*>(buffer), sizeof(buffer));

    this->m_engine.setOdiRecorder(&odiRecorder);
    this->m_fu.setOdiRecorder(&odiRecorder);

    EXPECT_TRUE(this->m_engine.registerMsgReceiver(&regReceiver, MessageTypes::REGISTRATION) == LSR_SESSION_TOO_MANY_RECEIVERS);

    EXPECT_TRUE(this->m_fu.activateFUConnection(&fuConn) == LSR_NO_ERROR);
    EXPECT_EQ(LSR_SESSION_UNDEFINED_RECEIVER, this->m_engine.handleIncomingData(0));


    this->m_engine.setOdiRecorder(NULL);
    this->m_fu.setOdiRecorder(NULL);

    EXPECT_TRUE(this->m_fu.activateFUConnection(&fuConn) == LSR_NO_ERROR);
    EXPECT_EQ(LSR_SESSION_UNDEFINED_RECEIVER, this->m_engine.handleIncomingData(0));
}

TYPED_TEST(PilOdiComSessionZeroReceiversTest, corruptedMessages)
{
    uint8_t dummyBuffer[] = { 0, 0, 1, 2, 3, 4, 5, 6, 7 };
    uint8_t dummyBuffer_too_long[20000] = { 0 };

    MockInititalSenderRecevier regReceiver(MessageTypes::ODI, &dummyBuffer[0], sizeof(dummyBuffer));

    char buffer[255] = { 0 };
    OdiRecorder odiRecorder(static_cast<void*>(buffer), sizeof(buffer));
    this->m_engine.setOdiRecorder(&odiRecorder);
    this->m_fu.setOdiRecorder(&odiRecorder);

    pilInit();

    // Check that mbox are initialized successfully
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NO_ERROR == pilMailboxInit(i));
    }

    EXPECT_TRUE(this->m_engine.registerMsgReceiver(&regReceiver, MessageTypes::REGISTRATION) == LSR_SESSION_TOO_MANY_RECEIVERS);

    // Send message from undefined fuId
    dummyBuffer[0] = MessageTypes::REGISTRATION;
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, 252, &dummyBuffer[0], sizeof(dummyBuffer)));
    EXPECT_EQ(LSR_SESSION_UNDEFINED_TRANSMITTER, this->m_engine.handleIncomingData(0));

    // Send wrong message type. handleIncomingData() should return LSR_NO_ERROR.
    dummyBuffer[0] = MessageTypes::UNKNOWN - 1;
    ASSERT_TRUE(MessageTypes::UNKNOWN - 1 > MessageTypes::LAST);
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, ConnectionIndex::PILConn_Fu1App, &dummyBuffer[0], sizeof(dummyBuffer)));
    EXPECT_EQ(LSR_COMM_INVALID_FIELD_IN_MSG, this->m_engine.handleIncomingData(0));

    // Too long message
    dummyBuffer_too_long[0] = MessageTypes::ODI;
    EXPECT_EQ(PIL_UNKNOWN_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, ConnectionIndex::PILConn_Fu1App, &dummyBuffer_too_long[0], sizeof(dummyBuffer_too_long)));
    EXPECT_EQ(LSR_NO_ERROR, this->m_engine.handleIncomingData(0));

    // Empty message
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, 253, NULL, 0));
    EXPECT_EQ(LSR_SESSION_UNDEFINED_TRANSMITTER, this->m_engine.handleIncomingData(0));

    // Empty message with non-zero empty pointer
    dummyBuffer[0] = MessageTypes::ODI;
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, 253, &dummyBuffer[0], 0));
    EXPECT_EQ(LSR_SESSION_UNDEFINED_TRANSMITTER, this->m_engine.handleIncomingData(0));

    // Null pointer buffer with non-zero size
    EXPECT_EQ(PIL_UNKNOWN_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, 253, NULL, sizeof(dummyBuffer)));

    // Too many messages
    for (U8 index = 0; index < 20; ++index)
    {
        dummyBuffer[0] = MessageTypes::ODI;
        EXPECT_EQ(PIL_NO_ERROR, pilMailboxWrite(ConnectionIndex::PILConn_Lsr, ConnectionIndex::PILConn_Fu1App, &dummyBuffer[0], sizeof(dummyBuffer)));
    }

    EXPECT_EQ(LSR_PIL_INVALID_MSG, this->m_engine.handleIncomingData(0));
}

TYPED_TEST(PilOdiComSessionZeroReceiversTest, unavailableBranchCoverage)
{
    pilInit();

    // Check that mbox are initialized successfully
    for (int i = ConnectionIndex::PILConn_Lsr; i < ConnectionIndex::PILConn_Last - 1; ++i)
    {
        EXPECT_TRUE(PIL_NO_ERROR == pilMailboxInit(i));
    }

    EXPECT_TRUE(this->m_engine.unregisterMsgReceiver(NULL, MessageTypes::UNKNOWN)== LSR_UNKNOWN_ERROR);
    EXPECT_TRUE(this->m_fu.unregisterMsgReceiver(NULL, MessageTypes::UNKNOWN)== LSR_UNKNOWN_ERROR);

    PilComSessionWithError errorOdiSession(ConnectionIndex::PILConn_Lsr, true);

    errorOdiSession.SetDummyError(LSR_SESSION_TOO_MANY_RECEIVERS);
    errorOdiSession.SetDummyTransmitter(NULL);
    errorOdiSession.SetDummyReceiver(reinterpret_cast<IMsgReceiver*>(0x12345678));
    errorOdiSession.SetDummyMessageType(12);

    EXPECT_TRUE(errorOdiSession.handleIncomingData(0) == LSR_PIL_MBOX_INVALID);
}

}
