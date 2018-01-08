/******************************************************************************
**
**   File:        OdiMessageUtilsTest.cpp
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

#include <OdiMessageUtils.h>
#include <OdiTypes.h>
#include <PscTypes.h>

using namespace psc;

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
