/******************************************************************************
**
**   File:        MessageHeaderTest.cpp
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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>

#include <MessageHeader.h>
#include <OdiTypes.h>

using namespace psc;

class MessageHeaderTest : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_type = MessageTypes::ODI;
        m_dataSize = 0x1881;
        m_msgSize = 5;

        m_header = new MessageHeader(m_type, m_dataSize);
    }

    void TearDown()
    {
        delete m_header;
    }

    MessageTypes::Val m_type;
    U32 m_dataSize;
    U16 m_msgSize;
    MessageHeader* m_header;
};

TEST_F(MessageHeaderTest, TestInitializing)
{
    const MessageTypes::Val expectedType = m_type;
    const U32 expectedDataSize = m_dataSize;
    const U16 expectedSize = m_msgSize;

    EXPECT_EQ(expectedType, m_header->getType());
    EXPECT_EQ(expectedDataSize, m_header->getDataSize());
    EXPECT_EQ(expectedSize, m_header->getSize());
}

TEST_F(MessageHeaderTest, TestConstrFromStream)
{
    U8 buffer[5] = {0};

    const MessageTypes::Val expectedType = MessageTypes::ODI;
    const U32 expectedDataSize = 0x3451;

    buffer[0] = static_cast<U8>(expectedType);
    buffer[1] = static_cast<U8>(expectedDataSize >> 24);
    buffer[2] = static_cast<U8>(expectedDataSize >> 16);
    buffer[3] = static_cast<U8>(expectedDataSize >> 8);
    buffer[4] = static_cast<U8>(expectedDataSize & 0xFF);

    InputStream stream(buffer, sizeof(buffer));
    MessageHeader msg = MessageHeader::fromStream(stream);

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(expectedType, msg.getType());
    EXPECT_EQ(expectedDataSize, msg.getDataSize());
}

TEST_F(MessageHeaderTest, TestGetType)
{
    EXPECT_EQ(m_type, m_header->getType());
}

TEST_F(MessageHeaderTest, TestGetDataSize)
{
    EXPECT_EQ(m_dataSize, m_header->getDataSize());
}

TEST_F(MessageHeaderTest, TestSerialize)
{
    U8 buffer[5] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    const U16 expectedMsgSize = m_header->getSize();
    stream << *m_header;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());
    EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

    U8* expectedBuffer = new U8[expectedMsgSize];
    memset(expectedBuffer, 0, expectedMsgSize);

    expectedBuffer[0] = static_cast<U8>(m_type);
    expectedBuffer[1] = static_cast<U8>(m_dataSize >> 24);
    expectedBuffer[2] = static_cast<U8>(m_dataSize >> 16);
    expectedBuffer[3] = static_cast<U8>(m_dataSize >> 8);
    expectedBuffer[4] = static_cast<U8>(m_dataSize);

    for (U8 index=0; index < expectedMsgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], buffer[index]);
    }

    delete[] expectedBuffer;
}

TEST_F(MessageHeaderTest, TestSerializeWithNotEnoughBuffer)
{

    U8 buffer[4] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    stream << *m_header;
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(MessageHeaderTest, TestSerializeWithWrongBuffer)
{
    U8 buffer[5] = {0};
    OutputStream stream1(NULL, sizeof(buffer));
    stream1 << *m_header;

    EXPECT_EQ(0u, stream1.bytesWritten());
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    OutputStream stream2(buffer, 0u);
    stream2 << *m_header;

    EXPECT_EQ(0u, stream2.bytesWritten());
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}

TEST_F(MessageHeaderTest, TestDeserialize)
{
    U8 buffer[5] = { 0 };

    buffer[0] = static_cast<U8>(m_type);
    buffer[1] = static_cast<U8>(m_dataSize >> 24);
    buffer[2] = static_cast<U8>(m_dataSize >> 16);
    buffer[3] = static_cast<U8>(m_dataSize >> 8);
    buffer[4] = static_cast<U8>(m_dataSize);

    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_header;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(m_type, m_header->getType());
    EXPECT_EQ(m_dataSize, m_header->getDataSize());
}

TEST_F(MessageHeaderTest, TestSerializeDeserialize)
{
    U8 buffer[5] = {0};
    OutputStream outStream(buffer, sizeof(buffer));

    outStream << *m_header;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), outStream.getError());

    MessageHeader msg(MessageTypes::UNKNOWN, 0u);

    InputStream inStream(buffer, sizeof(buffer));
    inStream >> msg;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), inStream.getError());

    EXPECT_EQ(m_type, msg.getType());
    EXPECT_EQ(m_dataSize, msg.getDataSize());
}

TEST_F(MessageHeaderTest, TestDeserializeWithNotFullSize)
{
    U8 buffer[4] = { 0 };

    buffer[0] = static_cast<U8>(m_type);
    buffer[1] = static_cast<U8>(m_dataSize >> 24);
    buffer[2] = static_cast<U8>(m_dataSize >> 16);
    buffer[3] = static_cast<U8>(m_dataSize >> 8);

    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_header;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(MessageHeaderTest, TestDeserializeWithWrongMsgType)
{
    U8 buffer[5] = { 0 };

    buffer[0] = static_cast<U8>(MessageTypes::ALIVE + 1);
    buffer[1] = static_cast<U8>(m_dataSize >> 24);
    buffer[2] = static_cast<U8>(m_dataSize >> 16);
    buffer[3] = static_cast<U8>(m_dataSize >> 8);
    buffer[4] = static_cast<U8>(m_dataSize);

    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_header;

    EXPECT_EQ(PSCError(PSC_COMM_INVALID_FIELD_IN_MSG), stream.getError());
}

TEST_F(MessageHeaderTest, TestDeserializeWithWrongBuffer)
{
    U8 buffer[5] = {0};

    buffer[0] = static_cast<U8>(m_type);
    buffer[1] = static_cast<U8>(m_dataSize >> 24);
    buffer[2] = static_cast<U8>(m_dataSize >> 16);
    buffer[3] = static_cast<U8>(m_dataSize >> 8);
    buffer[4] = static_cast<U8>(m_dataSize);

    const MessageTypes::Val expectedType = m_type;
    const U32 expectedDataSize = m_dataSize;

    InputStream stream1(NULL, sizeof(buffer));
    MessageHeader msg1(expectedType, expectedDataSize);
    stream1 >> msg1;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    InputStream stream2(buffer, 0u);
    MessageHeader msg2(expectedType, expectedDataSize);
    stream2 >> msg2;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}
