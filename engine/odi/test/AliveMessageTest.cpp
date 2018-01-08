/******************************************************************************
**
**   File:        AliveMessageTest.cpp
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

#include <AliveMessage.h>
#include <OdiTypes.h>
#include <InputStream.h>
#include <OutputStream.h>

using namespace psc;

class AliveMessageTest : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_msgSize = 1;
        m_id = 43;
        m_msg = new AliveMessage(m_id);
    }

    void TearDown()
    {
        delete m_msg;
    }

    U16 m_msgSize;
    U8 m_id;
    AliveMessage* m_msg;
};

TEST_F(AliveMessageTest, TestInitializing)
{
    const MessageTypes::Val expectedType = MessageTypes::ALIVE;
    const U16 expectedSize = m_msgSize;
    const U8 expectedId = 43;

    EXPECT_EQ(expectedType, m_msg->getType());
    EXPECT_EQ(expectedSize, m_msg->getSize());
    EXPECT_EQ(expectedId, m_msg->getId());
}

TEST_F(AliveMessageTest, TestConstrFromStream)
{
    U8 buffer[1] = {0};
    buffer[0] = m_id;

    InputStream stream(buffer, sizeof(buffer));
    AliveMessage msg = AliveMessage::fromStream(stream);

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(m_id, msg.getId());
}

TEST_F(AliveMessageTest, TestGetType)
{
    const MessageTypes::Val expectedType = MessageTypes::ALIVE;
    EXPECT_EQ(expectedType, m_msg->getType());
}

TEST_F(AliveMessageTest, TestGetId)
{
    U8 expectedId = 0;
    AliveMessage msg1(expectedId);
    EXPECT_EQ(expectedId, msg1.getId());

    expectedId = 34;
    AliveMessage msg2(expectedId);
    EXPECT_EQ(expectedId, msg2.getId());

    expectedId = UINT8_MAX;
    AliveMessage msg3(expectedId);
    EXPECT_EQ(expectedId, msg3.getId());
}

TEST_F(AliveMessageTest, TestSerialize)
{
    U8 buffer[1024] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    U16 expectedMsgSize = m_msg->getSize();
    stream << *m_msg;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

    U8* expectedBuffer = new U8[expectedMsgSize];
    memset(expectedBuffer, 0, expectedMsgSize);

    expectedBuffer[0] = m_id;

    for (U8 index=0; index < expectedMsgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], buffer[index]);
    }

    delete[] expectedBuffer;
}

TEST_F(AliveMessageTest, TestSerializeWithZeroBuffer1)
{
    U8 buffer[1024] = {0};
    OutputStream stream(buffer, 0);
    stream << (*m_msg);
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
    EXPECT_EQ(0u, stream.bytesWritten());
}

TEST_F(AliveMessageTest, TestSerializeWithZeroBuffer2)
{
    U8* buffer = NULL;
    OutputStream stream(buffer, 1024);
    stream << *m_msg;
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
    EXPECT_EQ(0u, stream.bytesWritten());
}

TEST_F(AliveMessageTest, TestSerializeWithNotEnoughBuffer)
{
    U8 buffer[2] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    // Emulate not enough buffer
    U8 someVariable = 9;
    stream << someVariable << someVariable;

    stream << *m_msg;
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(AliveMessageTest, TestDeserialize)
{
    U8 buffer[1] = { 0 };
    buffer[0] = m_id;

    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_msg;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(m_id, m_msg->getId());
}

TEST_F(AliveMessageTest, TestSerializeDeserialize)
{
    U8 buffer[1024] = {0};
    OutputStream inStream(buffer, sizeof(buffer));
    inStream << *m_msg;
    EXPECT_EQ(PSCError(PSC_NO_ERROR),  inStream.getError());

    InputStream outStream(buffer, sizeof(buffer));
    AliveMessage msg(m_id + 56);
    outStream >> msg;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), outStream.getError());

    EXPECT_EQ(m_id, m_msg->getId());
}

TEST_F(AliveMessageTest, TestDeserializeWIthZeroMessage1)
{
    U8 buffer[1] = {0};
    buffer[0] = m_id;

    InputStream stream(buffer, 0);
    stream >> *m_msg;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(AliveMessageTest, TestDeserializeWIthZeroMessage2)
{
    const U16 bufferSize = 1024;
    const U8* buffer = NULL;

    InputStream stream(buffer, bufferSize);
    stream >> *m_msg;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(AliveMessageTest, TestDeserializeWithNotEnoughBuffer)
{
    U8 buffer[2] = {0};
    buffer[0] = m_id;

    InputStream stream(buffer, sizeof(buffer));

    // Emulate not enough buffer
    U8 someVariable = 0;
    stream >> someVariable >> someVariable;

    stream >> *m_msg;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

