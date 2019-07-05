/******************************************************************************
**
**   File:        AssertionTest.cpp
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

#include <Assertion.h>

#include "gtest/gtest.h"

static const char* gMessage = NULL;

extern "C"
{
    void pilAssert(const char* msg, const char* file, int lineNo)
    {
        gMessage = msg;
    }
}

#ifndef NDEBUG

TEST(AssertionTest, assertions)
{
    int i = 0;
    (void)i; //suppress compiler warning

    gMessage = NULL;
    ASSERT(i == 0);
    EXPECT_EQ(NULL, gMessage);

    gMessage = NULL;
    ASSERT(i > 5);
    EXPECT_EQ(std::string("i > 5"), gMessage);

    gMessage = NULL;
    ASSERT_MSG(i > 5, "Index out of bounds");
    EXPECT_EQ(std::string("Index out of bounds"), gMessage);
}

TEST(AssertionTest, require)
{
    int i = 0;
    gMessage = NULL;
    if (REQUIRE(i < 10))
    {
        EXPECT_EQ(NULL, gMessage);
    }
    else
    {
        FAIL();
    }

    if (REQUIRE(i == 100))
    {
        FAIL();
    }
    else
    {
        EXPECT_EQ(std::string("i == 100"), gMessage);
    }

    if (REQUIRE_MSG(i == 100, "i should be 100"))
    {
        FAIL();
    }
    else
    {
        EXPECT_EQ(std::string("i should be 100"), gMessage);
    }
}

#else // NDEBUG

TEST(AssertionTest, noAssertions)
{
    int i = 0;
    (void)i; //supress compiler warning

    gMessage = NULL;
    ASSERT(i == 0);
    EXPECT_EQ(NULL, gMessage);

    ASSERT(i > 5);
    EXPECT_EQ(NULL, gMessage);

    ASSERT_MSG(i > 5, "Index out of bounds");
    EXPECT_EQ(NULL, gMessage);
}

TEST(AssertionTest, noRequire)
{
    int i = 0;
    gMessage = NULL;
    if (REQUIRE(i < 10))
    {
        EXPECT_EQ(NULL, gMessage);
    }
    else
    {
        FAIL();
    }

    if (REQUIRE(i == 100))
    {
        FAIL();
    }
    else
    {
        EXPECT_EQ(NULL, gMessage);
    }

    if (REQUIRE_MSG(i == 100, "i should be 100"))
    {
        FAIL();
    }
    else
    {
        EXPECT_EQ(NULL, gMessage);
    }
}

#endif // NDEBUG
