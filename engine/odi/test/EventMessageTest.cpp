/******************************************************************************
**
**   File:        EventMessageTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <EventMessage.h>
#include <OdiTypes.h>

using namespace psc;

class EventMessageTest : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_fuId = 0x8118;
        m_eventId = 0x1881;
        m_msgSize = 4;

        m_msg = new EventMessage();
    }

    void TearDown()
    {
        delete m_msg;
    }

    void InitMessage()
    {
        m_msg->setFuId(m_fuId);
        m_msg->setEvent(m_eventId);
    }

    FUClassId m_fuId;
    EventId m_eventId;
    U16 m_msgSize;
    EventMessage* m_msg;
};

TEST_F(EventMessageTest, TestInitializing)
{
    const MessageTypes::Val expectedType = MessageTypes::ODI;
    const U16 expectedSize = m_msgSize;
    const FUClassId expectedFuId = 0;
    const EventId expectedEventId = 0;

    EXPECT_EQ(expectedType, m_msg->getType());
    EXPECT_EQ(expectedSize, m_msg->getSize());
    EXPECT_EQ(expectedFuId, m_msg->getFuId());
    EXPECT_EQ(expectedEventId, m_msg->getEventId());
}

TEST_F(EventMessageTest, TestConstrFromStream)
{
    U8 buffer[4] = {0};

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = static_cast<U8>(m_eventId >> 8);
    buffer[3] = static_cast<U8>(m_eventId);

    InputStream stream(buffer, sizeof(buffer));
    EventMessage msg = EventMessage::fromStream(stream);

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(m_fuId, msg.getFuId());
    EXPECT_EQ(m_eventId, msg.getEventId());
}

TEST_F(EventMessageTest, TestGetType)
{
    const MessageTypes::Val expectedType = MessageTypes::ODI;
    EXPECT_EQ(expectedType, m_msg->getType());
}

TEST_F(EventMessageTest, TestSetFuId)
{
    InitMessage();
    EXPECT_EQ(m_fuId, m_msg->getFuId());
}

TEST_F(EventMessageTest, TestSetEventId)
{
    InitMessage();
    EXPECT_EQ(m_eventId, m_msg->getEventId());
}

TEST_F(EventMessageTest, TestGetPackedMsgSizeAfterInit)
{
    InitMessage();
    EXPECT_EQ(m_msgSize, m_msg->getSize());
}

TEST_F(EventMessageTest, TestSerialize)
{
    InitMessage();

    U8 buffer[1024] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    const U16 expectedMsgSize = m_msg->getSize();
    stream << *m_msg;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());
    EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

    U8* expectedBuffer = new U8[expectedMsgSize];
    memset(expectedBuffer, 0, expectedMsgSize);

    expectedBuffer[0] = static_cast<U8>(m_fuId >> 8);
    expectedBuffer[1] = static_cast<U8>(m_fuId);
    expectedBuffer[2] = static_cast<U8>(m_eventId >> 8);
    expectedBuffer[3] = static_cast<U8>(m_eventId);

    for (U8 index=0; index < expectedMsgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], buffer[index]);
    }

    delete[] expectedBuffer;
}

TEST_F(EventMessageTest, TestSerializeNotInitedObject)
{
    U8 buffer[1024] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    const U16 expectedMsgSize = m_msg->getSize();
    stream << *m_msg;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());
    EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

    U8* expectedBuffer = new U8[expectedMsgSize];
    memset(expectedBuffer, 0, expectedMsgSize);

    expectedBuffer[0] = U8(0);
    expectedBuffer[1] = U8(0);
    expectedBuffer[2] = U8(0);
    expectedBuffer[3] = U8(0);

    for (U8 index=0; index < expectedMsgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], buffer[index]);
    }

    delete[] expectedBuffer;
}

TEST_F(EventMessageTest, TestSerializeWithNotEnoughBuffer)
{
    InitMessage();

    U8 buffer[3] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    stream << *m_msg;
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(EventMessageTest, TestSerializeWithWrongBuffer)
{
    InitMessage();

    U8 buffer[4] = {0};
    OutputStream stream1(NULL, sizeof(buffer));
    stream1 << *m_msg;

    EXPECT_EQ(0u, stream1.bytesWritten());
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    OutputStream stream2(buffer, 0u);
    stream2 << *m_msg;

    EXPECT_EQ(0u, stream2.bytesWritten());
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}

TEST_F(EventMessageTest, TestDeserialize)
{
    U8 buffer[4] = { 0 };

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = static_cast<U8>(m_eventId >> 8);
    buffer[3] = static_cast<U8>(m_eventId);

    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_msg;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(m_fuId, m_msg->getFuId());
    EXPECT_EQ(m_eventId, m_msg->getEventId());
}

TEST_F(EventMessageTest, TestSerializeDeserialize)
{
    InitMessage();

    U8 buffer[1024] = {0};
    OutputStream outStream(buffer, sizeof(buffer));

    outStream << *m_msg;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), outStream.getError());

    EventMessage msg;

    InputStream inStream(buffer, sizeof(buffer));
    inStream >> msg;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), inStream.getError());

    EXPECT_EQ(m_fuId, msg.getFuId());
    EXPECT_EQ(m_eventId, msg.getEventId());
}

TEST_F(EventMessageTest, TestDeserializeWithNotFullSize)
{
    U8 buffer[3] = { 0 };

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = static_cast<U8>(m_eventId >> 8);

    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_msg;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(EventMessageTest, TestDeserializeWithWrongBuffer)
{
    U8 buffer[4] = {0};

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = static_cast<U8>(m_eventId >> 8);
    buffer[3] = static_cast<U8>(m_eventId);

    const MessageTypes::Val expectedType = MessageTypes::ODI;
    const U16 expectedSize = m_msgSize;
    const FUClassId expectedFuId = 0;
    const EventId expectedEventId = 0;

    InputStream stream1(NULL, sizeof(buffer));
    EventMessage msg1;
    stream1 >> msg1;

    EXPECT_EQ(expectedType, msg1.getType());
    EXPECT_EQ(expectedSize, msg1.getSize());
    EXPECT_EQ(expectedFuId, msg1.getFuId());
    EXPECT_EQ(expectedEventId, msg1.getEventId());

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    InputStream stream2(buffer, 0u);
    EventMessage msg2;
    stream2 >> msg2;

    EXPECT_EQ(expectedType, msg2.getType());
    EXPECT_EQ(expectedSize, msg2.getSize());
    EXPECT_EQ(expectedFuId, msg2.getFuId());
    EXPECT_EQ(expectedEventId, msg2.getEventId());

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}
