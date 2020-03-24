/******************************************************************************
**
**   File:        RegistrationMsgBufferTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <OdiTypes.h>
#include <LsrTypes.h>

#include "RegistrationMsgBuffer.h"

using lsr::FUClassId;


TEST(RegistrationMessageTest, TestInitializing)
{
    RegistrationMsgBuffer expBuffer;

    U8 expectedBuffer[8] = {0u};
    expectedBuffer[0] = static_cast<U8>(OdiVersion::VERSION_MAJOR);
    expectedBuffer[1] = static_cast<U8>(OdiVersion::VERSION_MINOR);
    expectedBuffer[2] = static_cast<U8>(RegistrationMode::UNKNOWN);
    expectedBuffer[3] = static_cast<U8>(0);
    expectedBuffer[4] = static_cast<U8>(0);
    expectedBuffer[5] = static_cast<U8>(0);
    expectedBuffer[6] = static_cast<U8>(0);
    expectedBuffer[7] = 0;

    for (U8 index=0; index < 8; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], expBuffer.getBuffer()[index]);
    }
}

TEST(RegistrationMessageTest, TestSetRegistrationMode)
{
    RegistrationMode::Val mode = RegistrationMode::REMOVE;
    RegistrationMsgBuffer expBuffer;
    expBuffer.setRegistrationMode(mode);

    U8 expectedBuffer[8] = {0u};
    expectedBuffer[0] = static_cast<U8>(OdiVersion::VERSION_MAJOR);
    expectedBuffer[1] = static_cast<U8>(OdiVersion::VERSION_MINOR);
    expectedBuffer[2] = static_cast<U8>(mode);
    expectedBuffer[3] = static_cast<U8>(0);
    expectedBuffer[4] = static_cast<U8>(0);
    expectedBuffer[5] = static_cast<U8>(0);
    expectedBuffer[6] = static_cast<U8>(0);
    expectedBuffer[7] = 0;

    for (U8 index=0; index < 8; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], expBuffer.getBuffer()[index]);
    }
}

TEST(RegistrationMessageTest, TestSetRemoteUid)
{
    U32 id = 0x01020304;
    RegistrationMsgBuffer expBuffer;
    expBuffer.setRemoteUid(id);

    U8 expectedBuffer[8] = {0u};
    expectedBuffer[0] = static_cast<U8>(OdiVersion::VERSION_MAJOR);
    expectedBuffer[1] = static_cast<U8>(OdiVersion::VERSION_MINOR);
    expectedBuffer[2] = static_cast<U8>(RegistrationMode::UNKNOWN);
    expectedBuffer[3] = static_cast<U8>(id >> 24);
    expectedBuffer[4] = static_cast<U8>(id >> 16);
    expectedBuffer[5] = static_cast<U8>(id >> 8);
    expectedBuffer[6] = static_cast<U8>(id);
    expectedBuffer[7] = 0;

    for (U8 index=0; index < 8; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], expBuffer.getBuffer()[index]);
    }
}

TEST(RegistrationMessageTest, TestSetFuCount)
{
    U8 count = 19;
    RegistrationMsgBuffer expBuffer;
    expBuffer.setFuCount(count);

    U8 expectedBuffer[8] = {0u};
    expectedBuffer[0] = static_cast<U8>(OdiVersion::VERSION_MAJOR);
    expectedBuffer[1] = static_cast<U8>(OdiVersion::VERSION_MINOR);
    expectedBuffer[2] = static_cast<U8>(RegistrationMode::UNKNOWN);
    expectedBuffer[3] = static_cast<U8>(0);
    expectedBuffer[4] = static_cast<U8>(0);
    expectedBuffer[5] = static_cast<U8>(0);
    expectedBuffer[6] = static_cast<U8>(0);
    expectedBuffer[7] = count;

    for (U8 index=0; index < 8; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], expBuffer.getBuffer()[index]);
    }
}

TEST(RegistrationMessageTest, TestAddFu)
{
    RegistrationMsgBuffer expBuffer;

    U8 expectedBuffer[1024] = {0u};
    expectedBuffer[0] = static_cast<U8>(OdiVersion::VERSION_MAJOR);
    expectedBuffer[1] = static_cast<U8>(OdiVersion::VERSION_MINOR);
    expectedBuffer[2] = static_cast<U8>(RegistrationMode::UNKNOWN);
    expectedBuffer[3] = static_cast<U8>(0);
    expectedBuffer[4] = static_cast<U8>(0);
    expectedBuffer[5] = static_cast<U8>(0);
    expectedBuffer[6] = static_cast<U8>(0);
    expectedBuffer[7] = 0;

    U8 count = 19;
    FUClassId fuId = 0x8118;
    for (U16 index=0; index < count; ++fuId)
    {
        expectedBuffer[8 + index++] = static_cast<U8>(fuId >> 8);
        expectedBuffer[8 + index++] = static_cast<U8>(fuId);
        expBuffer.addFu(fuId);
    }

    U16 msgSize = 8 + count * sizeof(FUClassId);
    for (U8 index=0; index < msgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], expBuffer.getBuffer()[index]);
    }
}

