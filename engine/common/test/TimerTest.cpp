/******************************************************************************
**
**   File:        TimerTest.cpp
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Timer.h>

using ::testing::Return;

class IPIL
{
public:
    virtual U32 getMonotonicTime() const = 0;
};

class MockPIL
{
public:
    MOCK_CONST_METHOD0(getMonotonicTime, U32());
};

MockPIL* g_pil = NULL;

extern "C"
{
    U32 pilGetMonotonicTime()
    {
        return g_pil->getMonotonicTime();
    }
}

class TimerTest : public ::testing::Test
{
protected:
    void SetUp() P_OVERRIDE
    {
        g_pil = &m_pil;
    }

    void TearDown() P_OVERRIDE
    {
        g_pil = NULL;
    }

    ::testing::StrictMock<MockPIL> m_pil;
};


TEST_F(TimerTest, start)
{
    lsr::Timer tim;
    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(0U));
    tim.start();

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(0U));
    EXPECT_EQ(0U, tim.getElapsed());

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(100U));
    EXPECT_EQ(100U, tim.getElapsed());

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(100U));
    tim.start();

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(150U));
    EXPECT_EQ(50U, tim.getElapsed());
}

TEST_F(TimerTest, overflow)
{
    lsr::Timer tim;
    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(0xfffffffeU));
    tim.start();

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(0xfffffffeU));
    EXPECT_EQ(0U, tim.getElapsed());

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(0xffffffffU));
    EXPECT_EQ(1U, tim.getElapsed());

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(0U));
    EXPECT_EQ(2U, tim.getElapsed());

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(1U));
    EXPECT_EQ(3U, tim.getElapsed());
}

TEST_F(TimerTest, restart)
{
    lsr::Timer tim;
    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(2000U));
    tim.start();

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(2100U));
    EXPECT_EQ(100U, tim.restart());

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(2200U));
    EXPECT_EQ(100U, tim.restart());
}

TEST_F(TimerTest, hasExpired)
{
    lsr::Timer tim;
    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(2000U));
    tim.start();

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(2000U));
    EXPECT_FALSE(tim.hasExpired(100));

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(2099U));
    EXPECT_FALSE(tim.hasExpired(100));

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(2100U));
    EXPECT_TRUE(tim.hasExpired(100));

    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(2101U));
    EXPECT_TRUE(tim.hasExpired(100));
}

/**
 * getElapsed() is called before the timer was started
 */
TEST_F(TimerTest, invalid)
{
    lsr::Timer tim;
    EXPECT_CALL(m_pil, getMonotonicTime()).WillOnce(Return(42U));
    EXPECT_EQ(42U, tim.getElapsed()); // questionable, maybe return U32_MAX instead
}
