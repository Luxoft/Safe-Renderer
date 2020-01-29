/******************************************************************************
**
**   File:        RegistrationMsgReaderTest.cpp
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

#include <RegistrationMsgReader.h>
#include <OdiTypes.h>

using namespace lsr;

class RegistrationMsgReaderTest : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_majorVersion = OdiVersion::VERSION_MAJOR;
        m_minorVersion = OdiVersion::VERSION_MINOR;
        m_mode = RegistrationMode::APPEND;
        m_uid = 0x01020304;
        m_number = 32;
        m_msgSize = 8 + m_number * sizeof(FUClassId);

        m_fuList = new FUClassId[UINT8_MAX];
        FUClassId fuId = 0x8118;
        for (U8 index=0; index < UINT8_MAX; ++index, ++fuId)
        {
            m_fuList[index] = fuId;
        }

        m_bufferSize = m_msgSize;
        m_buffer = new U8[m_bufferSize];
        memset(m_buffer, 0, m_bufferSize);

        m_buffer[0] = m_majorVersion;
        m_buffer[1] = m_minorVersion;
        m_buffer[2] = static_cast<U8>(m_mode);
        m_buffer[3] = static_cast<U8>(m_uid >> 24);
        m_buffer[4] = static_cast<U8>(m_uid >> 16);
        m_buffer[5] = static_cast<U8>(m_uid >> 8);
        m_buffer[6] = static_cast<U8>(m_uid);
        m_buffer[7] = m_number;

        for (U8 index=8, fuCount=0; fuCount < m_number; ++fuCount, index += 2)
        {
            m_buffer[index] = static_cast<U8>(m_fuList[fuCount] >> 8);
            m_buffer[index + 1] = static_cast<U8>(m_fuList[fuCount]);
        }
    }

    void TearDown()
    {
        delete[] m_buffer;
        delete[] m_fuList;
    }

    U8 m_majorVersion;
    U8 m_minorVersion;
    RegistrationMode::Val m_mode;
    U32 m_uid;
    U8 m_number;
    U16 m_msgSize;
    FUClassId* m_fuList;

    U16 m_bufferSize;
    U8* m_buffer;
};

TEST_F(RegistrationMsgReaderTest, TestGetMajorVersion)
{
    InputStream stream(m_buffer, m_bufferSize);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(m_majorVersion, reader.getMajorVersion());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetMinorVersion)
{
    InputStream stream(m_buffer, m_bufferSize);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(m_minorVersion, reader.getMinorVersion());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetRegistrationMode)
{
    InputStream stream(m_buffer, m_bufferSize);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(m_mode, reader.getRegistrationMode());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetWrongRegistration1)
{
    U8 expectedMode = RegistrationMode::UNKNOWN - 1;
    m_buffer[2] = expectedMode;

    InputStream stream(m_buffer, m_bufferSize);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(RegistrationMode::UNKNOWN, reader.getRegistrationMode());
    EXPECT_EQ(COM_INVALID_FIELD_IN_MSG, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetWrongRegistration2)
{
    U8 expectedMode = RegistrationMode::UNKNOWN;
    m_buffer[2] = expectedMode;

    InputStream stream(m_buffer, m_bufferSize);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(static_cast<RegistrationMode::Val>(expectedMode), reader.getRegistrationMode());
    EXPECT_EQ(COM_INVALID_FIELD_IN_MSG, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetRemoteUid)
{
    InputStream stream(m_buffer, m_bufferSize);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(m_uid, reader.getRemoteUid());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetRemoteUidtWithNotEnougthBuffer1)
{
    InputStream stream(m_buffer, m_bufferSize - 1);
    RegistrationMsgReader reader(stream);
    reader.getRemoteUid();
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetRemoteUidWithNotEnougthBuffer2)
{
    InputStream stream(m_buffer, 7);
    RegistrationMsgReader reader(stream);
    reader.getRemoteUid();
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetRemoteUidWithNotEnougthBuffer3)
{
    InputStream stream(m_buffer, 8);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(m_uid, reader.getRemoteUid());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetFuCount)
{
    InputStream stream(m_buffer, m_bufferSize);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(m_number, reader.getFuCount());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetFuCountWithNotEnougthBuffer1)
{
    InputStream stream(m_buffer, m_bufferSize - 1);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(m_number, reader.getFuCount());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetFuCountWithNotEnougthBuffer2)
{
    InputStream stream(m_buffer, 7);
    RegistrationMsgReader reader(stream);
    reader.getFuCount();
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetFuCountWithNotEnougthBuffer3)
{
    InputStream stream(m_buffer, 8);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(m_number, reader.getFuCount());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetNextFu)
{
    InputStream stream(m_buffer, m_bufferSize);
    RegistrationMsgReader reader(stream);
    U8 fuCount = reader.getFuCount();
    EXPECT_EQ(m_number, fuCount);
    EXPECT_EQ(COM_NO_ERROR, stream.getError());

    for (U8 index=0; index < fuCount; ++index)
    {
        EXPECT_EQ(m_fuList[index], reader.getNextFu());
        EXPECT_EQ(COM_NO_ERROR, stream.getError());
    }

    reader.getNextFu();
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetFuWithNotEnougthBuffer1)
{
    InputStream stream(m_buffer, m_bufferSize - 1);
    RegistrationMsgReader reader(stream);

    for (U8 index=0; index < m_number - 1; ++index)
    {
        reader.getNextFu();
        EXPECT_EQ(COM_NO_ERROR, stream.getError());
    }

    reader.getNextFu();
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetFuWithNotEnougthBuffer3)
{
    InputStream stream(m_buffer, 7);
    RegistrationMsgReader reader(stream);
    reader.getNextFu();
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetFuWithLargeNumber)
{
    U8 expectedCount = m_number + 1;
    m_buffer[7] = expectedCount;

    InputStream stream(m_buffer, m_bufferSize);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(expectedCount, reader.getFuCount());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}

TEST_F(RegistrationMsgReaderTest, TestGetFuWithZeroFu)
{
    m_buffer[7] = U8(0u);

    InputStream stream(m_buffer, 8u);
    RegistrationMsgReader reader(stream);
    EXPECT_EQ(0u, reader.getFuCount());
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
}


TEST_F(RegistrationMsgReaderTest, TestDeserializeWithWrongBuffer)
{
    InputStream stream1(NULL, m_bufferSize);
    RegistrationMsgReader reader1(stream1);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream1.getError());

    InputStream stream2(m_buffer, 0u);
    RegistrationMsgReader reader2(stream2);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream2.getError());
}

TEST_F(RegistrationMsgReaderTest, TestSerializeDeserialize)
{
    RegistrationMsgBuilder msg;

    msg.setRegistrationMode(m_mode);
    msg.setRemoteUid(m_uid);

    for (U8 index=0; index < m_number; ++index)
    {
        msg.addFu(m_fuList[index]);
    }

    U8 buffer[1024] = {0};
    OutputStream outStream(buffer, sizeof(buffer));

    const U16 expectedMsgSize = msg.getSize();
    outStream << msg;
    EXPECT_EQ(COM_NO_ERROR, outStream.getError());
    EXPECT_EQ(expectedMsgSize, outStream.bytesWritten());

    InputStream inStream(buffer, sizeof(buffer));
    RegistrationMsgReader reader(inStream);

    EXPECT_EQ(m_majorVersion, reader.getMajorVersion());
    EXPECT_EQ(m_minorVersion, reader.getMinorVersion());
    EXPECT_EQ(m_mode, reader.getRegistrationMode());
    EXPECT_EQ(m_uid, reader.getRemoteUid());
    U8 count = reader.getFuCount();
    EXPECT_EQ(m_number, count);

    for (U8 index=0; index < count; ++index)
    {
        EXPECT_EQ(m_fuList[index], reader.getNextFu());
    }

    EXPECT_EQ(COM_NO_ERROR, inStream.getError());
}
