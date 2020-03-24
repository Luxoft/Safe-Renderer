/******************************************************************************
**
**   File:        OdiMessageUtilsTest.cpp
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

#include <OdiMessageUtils.h>
#include <OdiTypes.h>
#include <LsrTypes.h>

using namespace lsr;

TEST(OdiMessageUtilsTest, TestCheckMsgTypeReturnTrue)
{
    EXPECT_TRUE(messageutils::checkMsgType(MessageTypes::REGISTRATION));
    EXPECT_TRUE(messageutils::checkMsgType(MessageTypes::ODI));
    EXPECT_TRUE(messageutils::checkMsgType(MessageTypes::ALIVE));
}

TEST(OdiMessageUtilsTest, TestCheckMsgTypeReturnFalse)
{
    for (U8 cur = MessageTypes::LAST; cur < MessageTypes::UNKNOWN; ++cur)
    {
        EXPECT_FALSE(messageutils::checkMsgType(cur));
    }

    EXPECT_FALSE(messageutils::checkMsgType(MessageTypes::UNKNOWN));
}

TEST(OdiMessageUtilsTest, TestCheckOdiMsgTypeReturnTrue)
{
    EXPECT_TRUE(messageutils::checkOdiMsgType(DataMessageTypes::DYN_DATA_RESP));
    EXPECT_TRUE(messageutils::checkOdiMsgType(DataMessageTypes::EVENT));
    EXPECT_TRUE(messageutils::checkOdiMsgType(DataMessageTypes::INDICATION));
}

TEST(OdiMessageUtilsTest, TestCheckOdiMsgTypeReturnFalse)
{
    EXPECT_FALSE(messageutils::checkOdiMsgType(1));
    for (U8 cur = DataMessageTypes::LAST; cur < DataMessageTypes::UNKNOWN; ++cur)
    {
        EXPECT_FALSE(messageutils::checkOdiMsgType(cur));
    }
    EXPECT_FALSE(messageutils::checkMsgType(DataMessageTypes::UNKNOWN));
}

TEST(OdiMessageUtilsTest, TestCheckRegistrationModeReturnTrue)
{
    for (U8 cur = RegistrationMode::REPLACE; cur < RegistrationMode::LAST; ++cur)
    {
        EXPECT_TRUE(messageutils::checkRegistrationMode(cur));
    }
}

TEST(OdiMessageUtilsTest, TestCheckRegistrationModeReturnFalse)
{
    for (U8 cur = RegistrationMode::LAST; cur < RegistrationMode::UNKNOWN; ++cur)
    {
        EXPECT_FALSE(messageutils::checkRegistrationMode(cur));
    }

    EXPECT_FALSE(messageutils::checkRegistrationMode(RegistrationMode::UNKNOWN));
}
