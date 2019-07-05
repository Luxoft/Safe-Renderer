/******************************************************************************
**
**   File:        DataResponseMessageTest.cpp
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
#include "gmock/gmock.h"

#include <DataResponseMessage.h>
#include <OdiTypes.h>

using namespace lsr;

class DataResponseMessageTest : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_dataId = 0x1265;
        m_dataType = DATATYPE_INTEGER;
        m_fuId = 0x8118;
        m_invalidFlag = false;
        m_value = 0xAB05;
        m_msgSize = 10;

        m_msg = new DataResponseMessage();
    }

    void TearDown()
    {
        delete m_msg;
    }

    void InitMessage()
    {
        m_msg->setDataId(m_dataId);
        m_msg->setDataType(m_dataType);
        m_msg->setFuId(m_fuId);
        m_msg->setInvalidFlag(m_invalidFlag);
        m_msg->setDataValue(m_value);
    }

    DataId m_dataId;
    DynamicDataTypeEnumeration m_dataType;
    FUClassId m_fuId;
    bool m_invalidFlag;
    U32 m_value;
    U16 m_msgSize;
    DataResponseMessage* m_msg;
};

TEST_F(DataResponseMessageTest, TestInitializing)
{
    const MessageTypes::Val expectedType = MessageTypes::ODI;
    const U16 expectedSize = m_msgSize;
    const DataId expectedDataId = 0;
    const DynamicDataTypeEnumeration expectedDataType = lsr::DATATYPE_ENUM_SIZE;
    const FUClassId expectedFuId = 0;
    const bool expectedInvalidFlag = true;
    const U32 expectedValue = 0;

    EXPECT_EQ(expectedType, m_msg->getType());
    EXPECT_EQ(expectedSize, m_msg->getSize());
    EXPECT_EQ(expectedDataId, m_msg->getDataId());
    EXPECT_EQ(expectedDataType, m_msg->getDataType());
    EXPECT_EQ(expectedFuId, m_msg->getFuId());
    EXPECT_EQ(expectedInvalidFlag, m_msg->getInvalidFlag());
    EXPECT_EQ(expectedValue, m_msg->getDataValue());
}

TEST_F(DataResponseMessageTest, TestConstrFormStream)
{
    U8 buffer[10] = {0};

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = static_cast<U8>(m_dataId >> 8);
    buffer[3] = static_cast<U8>(m_dataId);
    buffer[4] = static_cast<U8>(m_dataType);
    buffer[5] = static_cast<U8>(m_invalidFlag ? 1 : 0);
    buffer[6] = static_cast<U8>(m_value >> 24);
    buffer[7] = static_cast<U8>(m_value >> 16);
    buffer[8] = static_cast<U8>(m_value >> 8);
    buffer[9] = static_cast<U8>(m_value);

    InputStream stream(buffer, sizeof(buffer));
    DataResponseMessage msg = DataResponseMessage::fromStream(stream);

    EXPECT_EQ(LSRError(LSR_NO_ERROR), stream.getError());

    EXPECT_EQ(m_dataId, msg.getDataId());
    EXPECT_EQ(m_dataType, msg.getDataType());
    EXPECT_EQ(m_fuId, msg.getFuId());
    EXPECT_EQ(m_invalidFlag, msg.getInvalidFlag());
    EXPECT_EQ(m_value, msg.getDataValue());
}

TEST_F(DataResponseMessageTest, TestGetType)
{
    const MessageTypes::Val expectedType = MessageTypes::ODI;
    EXPECT_EQ(expectedType, m_msg->getType());
}

TEST_F(DataResponseMessageTest, TestSetDataId)
{
    InitMessage();
    EXPECT_EQ(m_dataId, m_msg->getDataId());
}

TEST_F(DataResponseMessageTest, TestSetDataType)
{
    InitMessage();
    EXPECT_EQ(m_dataType, m_msg->getDataType());
}

TEST_F(DataResponseMessageTest, TestSetFuId)
{
    InitMessage();
    EXPECT_EQ(m_fuId, m_msg->getFuId());
}

TEST_F(DataResponseMessageTest, TestSetInvalidFlag)
{
    InitMessage();
    EXPECT_EQ(m_invalidFlag, m_msg->getInvalidFlag());
}

TEST_F(DataResponseMessageTest, TestSetDataValue)
{
    InitMessage();
    EXPECT_EQ(m_value, m_msg->getDataValue());
}

TEST_F(DataResponseMessageTest, TestGetPackedMsgSizeAfterInit)
{
    InitMessage();
    EXPECT_EQ(m_msgSize, m_msg->getSize());
}

TEST_F(DataResponseMessageTest, TestSerialize)
{
    InitMessage();

    U8 buffer[1024] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    const U16 expectedMsgSize = m_msg->getSize();
    stream << *m_msg;
    EXPECT_EQ(LSRError(LSR_NO_ERROR), stream.getError());
    EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

    U8* expectedBuffer = new U8[expectedMsgSize];
    memset(expectedBuffer, 0, expectedMsgSize);

    expectedBuffer[0] = static_cast<U8>(m_fuId >> 8);
    expectedBuffer[1] = static_cast<U8>(m_fuId);
    expectedBuffer[2] = static_cast<U8>(m_dataId >> 8);
    expectedBuffer[3] = static_cast<U8>(m_dataId);
    expectedBuffer[4] = static_cast<U8>(m_dataType);
    expectedBuffer[5] = static_cast<U8>(m_invalidFlag ? 1 : 0);
    expectedBuffer[6] = static_cast<U8>(m_value >> 24);
    expectedBuffer[7] = static_cast<U8>(m_value >> 16);
    expectedBuffer[8] = static_cast<U8>(m_value >> 8);
    expectedBuffer[9] = static_cast<U8>(m_value);

    for (U8 index=0; index < expectedMsgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], buffer[index]);
    }

    delete[] expectedBuffer;
}

TEST_F(DataResponseMessageTest, TestSerializeNotInitedObject)
{
    U8 buffer[1024] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    const U16 expectedMsgSize = m_msg->getSize();
    stream << *m_msg;
    EXPECT_EQ(LSRError(LSR_NO_ERROR), stream.getError());
    EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

    U8* expectedBuffer = new U8[expectedMsgSize];
    memset(expectedBuffer, 0, expectedMsgSize);

    expectedBuffer[0] = U8(0);
    expectedBuffer[1] = U8(0);
    expectedBuffer[2] = U8(0);
    expectedBuffer[3] = U8(0);
    expectedBuffer[4] = static_cast<U8>(DATATYPE_ENUM_SIZE);
    expectedBuffer[5] = U8(1);
    expectedBuffer[6] = U8(0);
    expectedBuffer[7] = U8(0);
    expectedBuffer[8] = U8(0);
    expectedBuffer[9] = U8(0);

    for (U8 index=0; index < expectedMsgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], buffer[index]);
    }

    delete[] expectedBuffer;
}

TEST_F(DataResponseMessageTest, TestSerializeWithNotEnoughBuffer)
{
    InitMessage();

    U8 buffer[5] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    stream << *m_msg;
    EXPECT_EQ(LSRError(LSR_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(DataResponseMessageTest, TestSerializeWithWrongBuffer)
{
    InitMessage();

    U8 buffer[11] = {0};
    OutputStream stream1(NULL, sizeof(buffer));
    stream1 << *m_msg;

    EXPECT_EQ(0u, stream1.bytesWritten());
    EXPECT_EQ(LSRError(LSR_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    OutputStream stream2(buffer, 0u);
    stream2 << *m_msg;

    EXPECT_EQ(0u, stream2.bytesWritten());
    EXPECT_EQ(LSRError(LSR_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}

TEST_F(DataResponseMessageTest, TestDeserialize)
{
    U8 buffer[10] = { 0 };

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = static_cast<U8>(m_dataId >> 8);
    buffer[3] = static_cast<U8>(m_dataId);
    buffer[4] = static_cast<U8>(m_dataType);
    buffer[5] = static_cast<U8>(m_invalidFlag ? 1 : 0);
    buffer[6] = static_cast<U8>(m_value >> 24);
    buffer[7] = static_cast<U8>(m_value >> 16);
    buffer[8] = static_cast<U8>(m_value >> 8);
    buffer[9] = static_cast<U8>(m_value);

    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_msg;

    EXPECT_EQ(LSRError(LSR_NO_ERROR), stream.getError());

    EXPECT_EQ(m_dataId, m_msg->getDataId());
    EXPECT_EQ(m_dataType, m_msg->getDataType());
    EXPECT_EQ(m_fuId, m_msg->getFuId());
    EXPECT_EQ(m_invalidFlag, m_msg->getInvalidFlag());
    EXPECT_EQ(m_value, m_msg->getDataValue());
}

TEST_F(DataResponseMessageTest, TestSerializeDeserialize)
{
    InitMessage();

    U8 buffer[1024] = {0};
    OutputStream outStream(buffer, sizeof(buffer));

    outStream << *m_msg;
    EXPECT_EQ(LSRError(LSR_NO_ERROR), outStream.getError());

    DataResponseMessage msg;
    InputStream inStream(buffer, sizeof(buffer));
    inStream >> msg;

    EXPECT_EQ(LSRError(LSR_NO_ERROR), inStream.getError());

    EXPECT_EQ(m_dataId, msg.getDataId());
    EXPECT_EQ(m_dataType, msg.getDataType());
    EXPECT_EQ(m_fuId, msg.getFuId());
    EXPECT_EQ(m_invalidFlag, msg.getInvalidFlag());
    EXPECT_EQ(m_value, msg.getDataValue());
}

TEST_F(DataResponseMessageTest, TestDeserializeWithNotFullSize)
{
    U8 buffer[6] = { 0 };

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = static_cast<U8>(m_dataId >> 8);
    buffer[3] = static_cast<U8>(m_dataId);
    buffer[4] = static_cast<U8>(m_dataType);
    buffer[5] = static_cast<U8>(m_invalidFlag ? 1 : 0);

    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_msg;

    EXPECT_EQ(LSRError(LSR_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(DataResponseMessageTest, TestDeserializeWithWrongBuffer)
{
    U8 buffer[10] = {0};

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = static_cast<U8>(m_dataId >> 8);
    buffer[3] = static_cast<U8>(m_dataId);
    buffer[4] = static_cast<U8>(m_dataType);
    buffer[5] = static_cast<U8>(m_invalidFlag ? 1 : 0);
    buffer[6] = static_cast<U8>(m_value >> 24);
    buffer[7] = static_cast<U8>(m_value >> 16);
    buffer[8] = static_cast<U8>(m_value >> 8);
    buffer[9] = static_cast<U8>(m_value);

    InputStream stream1(NULL, sizeof(buffer));
    DataResponseMessage msg1;
    stream1 >> msg1;

    EXPECT_EQ(LSRError(LSR_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    InputStream stream2(buffer, 0u);
    DataResponseMessage msg2;
    stream2 >> msg2;

    EXPECT_EQ(LSRError(LSR_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}
