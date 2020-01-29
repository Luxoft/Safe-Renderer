/******************************************************************************
**
**   File:        RegistrationMsgBuilderTest.cpp
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

#include <RegistrationMsgBuilder.h>
#include <OdiTypes.h>

#include "RegistrationMsgBuffer.h"

using namespace lsr;

class RegistrationMsgBuilderTest : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_mode = RegistrationMode::APPEND;
        m_uid = 0x01020304;
        m_number = 32;

        m_fuList = new FUClassId[UINT8_MAX];
        FUClassId fuId = 0x8118;
        for (U8 index=0; index < UINT8_MAX; ++index, ++fuId)
        {
            m_fuList[index] = fuId;
        }
    }

    void TearDown()
    {
        delete[] m_fuList;
    }

    void CheckMsg(const RegistrationMsgBuilder& msg,
                  const RegistrationMsgBuffer& expBuffer)
    {
        U8 buffer[1024] = {0};
        OutputStream stream(buffer, sizeof(buffer));

        stream << msg;

        EXPECT_EQ(COM_NO_ERROR, stream.getError());

        const U16 expectedMsgSize = msg.getSize();
        EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

        for (U16 index=0; index < expectedMsgSize; ++index)
        {
            EXPECT_EQ(expBuffer.getBuffer()[index], buffer[index]);
        }
    }

    void CheckMsg(const RegistrationMsgBuilder& msg,
                  const RegistrationMsgBuffer& expBuffer,
                  U16 expMsgSize)
    {
        U8 buffer[1024] = {0};
        OutputStream stream(buffer, sizeof(buffer));

        stream << msg;

        EXPECT_EQ(COM_NO_ERROR, stream.getError());

        const U16 expectedMsgSize = msg.getSize();
        EXPECT_EQ(expectedMsgSize, stream.bytesWritten());
        EXPECT_EQ(expMsgSize, stream.bytesWritten());

        for (U8 index=0; index < expectedMsgSize; ++index)
        {
            EXPECT_EQ(expBuffer.getBuffer()[index], buffer[index]);
        }
    }

    RegistrationMode::Val m_mode;
    U32 m_uid;
    U8 m_number;
    FUClassId* m_fuList;
};

TEST_F(RegistrationMsgBuilderTest, TestInitializing)
{
    RegistrationMsgBuilder msg;
    RegistrationMsgBuffer expBuffer;

    CheckMsg(msg, expBuffer);
}

TEST_F(RegistrationMsgBuilderTest, TestGetType)
{
    RegistrationMsgBuilder msg;
    const MessageTypes::Val expectedType = MessageTypes::REGISTRATION;
    EXPECT_EQ(expectedType, msg.getType());
}

TEST_F(RegistrationMsgBuilderTest, TestSetRegistrationMode)
{
    RegistrationMsgBuilder msg;
    msg.setRegistrationMode(m_mode);

    RegistrationMsgBuffer expBuffer;
    expBuffer.setRegistrationMode(m_mode);

    CheckMsg(msg, expBuffer);
}

TEST_F(RegistrationMsgBuilderTest, TestSetRemoteUid)
{
    RegistrationMsgBuilder msg;
    msg.setRemoteUid(m_uid);

    RegistrationMsgBuffer expBuffer;
    expBuffer.setRemoteUid(m_uid);

    CheckMsg(msg, expBuffer);
}

TEST_F(RegistrationMsgBuilderTest, TestAddFu)
{
    RegistrationMsgBuilder msg;
    RegistrationMsgBuffer expBuffer;
    expBuffer.setFuCount(UINT8_MAX);
    for (U8 index=0; index < UINT8_MAX; ++index)
    {
        EXPECT_TRUE(msg.addFu(m_fuList[index]));
        expBuffer.addFu(m_fuList[index]);
    }

    CheckMsg(msg, expBuffer);

    for (U8 index=0; index < UINT8_MAX; ++index)
    {
        EXPECT_FALSE(msg.addFu(m_fuList[index]));
    }

    CheckMsg(msg, expBuffer);
}

TEST_F(RegistrationMsgBuilderTest, TestGetSizeNotInitialized)
{
    RegistrationMsgBuilder msg;
    RegistrationMsgBuffer expBuffer;

    CheckMsg(msg, expBuffer, 8u);
}

TEST_F(RegistrationMsgBuilderTest, TestGetSize)
{
    RegistrationMsgBuilder msg;
    RegistrationMsgBuffer expBuffer;
    expBuffer.setFuCount(m_number);
    for (U8 index=0; index < m_number; ++index)
    {
        EXPECT_TRUE(msg.addFu(m_fuList[index]));
        expBuffer.addFu(m_fuList[index]);
    }
    const U16 expectedSize = 8u + m_number * sizeof(FUClassId);
    CheckMsg(msg, expBuffer, expectedSize);
}

TEST_F(RegistrationMsgBuilderTest, TestSerialize)
{
    RegistrationMsgBuilder msg;
    msg.setRegistrationMode(m_mode);
    msg.setRemoteUid(m_uid);

    RegistrationMsgBuffer expBuffer;
    expBuffer.setRegistrationMode(m_mode);
    expBuffer.setRemoteUid(m_uid);
    expBuffer.setFuCount(m_number);
    for (U8 index=0; index < m_number; ++index)
    {
        EXPECT_TRUE(msg.addFu(m_fuList[index]));
        expBuffer.addFu(m_fuList[index]);
    }

    const U16 expectedSize = 8u + m_number * sizeof(FUClassId);
    CheckMsg(msg, expBuffer, expectedSize);
}

TEST_F(RegistrationMsgBuilderTest, TestSerializeWithNotEnoughBuffer)
{
    RegistrationMsgBuilder msg;
    msg.setRegistrationMode(m_mode);
    msg.setRemoteUid(m_uid);
    for (U8 index=0; index < m_number; ++index)
    {
        EXPECT_TRUE(msg.addFu(m_fuList[index]));
    }

    U8 buffer[5] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    stream << msg;
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST_F(RegistrationMsgBuilderTest, TestSerializeWithWrongBuffer)
{
    RegistrationMsgBuilder msg;
    msg.setRegistrationMode(m_mode);
    msg.setRemoteUid(m_uid);
    for (U8 index=0; index < m_number; ++index)
    {
        EXPECT_TRUE(msg.addFu(m_fuList[index]));
    }

    U8 buffer[1024] = {0};
    OutputStream stream1(NULL, sizeof(buffer));
    stream1 << msg;

    EXPECT_EQ(0u, stream1.bytesWritten());
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream1.getError());

    OutputStream stream2(buffer, 0u);
    stream2 << msg;

    EXPECT_EQ(0u, stream2.bytesWritten());
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream2.getError());
}

