/******************************************************************************
**
**   File:        LongTermPtrTest.cpp
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

#include "LongTermPtrCorrupter.h"

#include <LongTermPtr.h>
#include <PscTypes.h>

#include <gtest/gtest.h>

using namespace psc;

TEST(LongTermPtrTest, Constructor1Test)
{
    U8 someValue = 0U;

    LongTermPtr<U8> ptr(&someValue);

    EXPECT_EQ(&someValue, ptr.getPtr());
}

TEST(LongTermPtrTest, Constructor2Test)
{
    LongTermPtr<U8> ptr;

    EXPECT_EQ(NULL, ptr.getPtr());
}

TEST(LongTermPtrTest, ConstructorWithNullTest)
{
    LongTermPtr<U8> ptr(NULL);

    EXPECT_EQ(NULL, ptr.getPtr());
}

TEST(LongTermPtrTest, CopyConstructorTest)
{
    U8 someValue = 0U;

    LongTermPtr<U8> ptr(&someValue);

    LongTermPtr<U8> ptr2(ptr);

    EXPECT_EQ(&someValue, ptr2.getPtr());
}

TEST(LongTermPtrTest, GetPtrTest)
{
    U8 someValue = 0U;
    U8 anotherValue = 5U;

    LongTermPtr<U8> ptr1(&someValue);

    LongTermPtr<U8> ptr2(&anotherValue);

    ptr2 = ptr1;

    EXPECT_EQ(&someValue, ptr2.getPtr());

    // to fulfill code coverage
    ptr2 = ptr2;
    EXPECT_EQ(&someValue, ptr2.getPtr());
}

TEST(LongTermPtrTest, GetPtrReturnNullTest1)
{
    U8 someValue = 0U;
    U8 anotherValue = 5U;

    LongTermPtr<U8> ptr(&someValue);

    LongTermPtrCorrupter<U8>& corrupter =
        reinterpret_cast<LongTermPtrCorrupter<U8>&>(ptr);

    corrupter.setPtr(&anotherValue);

    EXPECT_EQ(NULL, ptr.getPtr());
}

TEST(LongTermPtrTest, GetPtrReturnNullTest2)
{
    U8 someValue = 0U;

    LongTermPtr<U8> ptr(&someValue);

    LongTermPtrCorrupter<U8>* corrupter =
        reinterpret_cast<LongTermPtrCorrupter<U8>* >(&ptr);

    corrupter->setInvertedPtr(0xFFAABBCC);

    EXPECT_EQ(NULL, ptr.getPtr());
}

TEST(LongTermPtrTest, CheckPtrReturnTrueTest)
{
    U8 someValue = 0U;
    LongTermPtr<U8> ptr(&someValue);

    EXPECT_TRUE(ptr.checkPtr(&someValue));
}

TEST(LongTermPtrTest, CheckPtrReturnFalseTest1)
{
    U8 someValue = 0U;
    U8 anotherValue = 0U;
    LongTermPtr<U8> ptr(&someValue);

    EXPECT_FALSE(ptr.checkPtr(&anotherValue));
}

TEST(LongTermPtrTest, CheckPtrReturnFalseTest2)
{
    U8 someValue = 0U;
    U8 anotherValue = 0U;
    LongTermPtr<U8> ptr(&someValue);

    LongTermPtrCorrupter<U8>* corrupter =
        reinterpret_cast<LongTermPtrCorrupter<U8>* >(&ptr);

    corrupter->setPtr(&anotherValue);

    EXPECT_FALSE(ptr.checkPtr(&someValue));
}

TEST(LongTermPtrTest, CheckPtrReturnFalseTest3)
{
    U8 someValue = 0U;
    LongTermPtr<U8> ptr(&someValue);

    LongTermPtrCorrupter<U8>* corrupter =
        reinterpret_cast<LongTermPtrCorrupter<U8>* >(&ptr);

    corrupter->setInvertedPtr(0x11223344);

    EXPECT_FALSE(ptr.checkPtr(&someValue));
}
