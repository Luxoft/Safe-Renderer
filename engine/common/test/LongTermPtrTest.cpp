/******************************************************************************
**
**   File:        LongTermPtrTest.cpp
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

#include "LongTermPtrCorrupter.h"

#include <LongTermPtr.h>
#include <LsrTypes.h>

#include <gtest/gtest.h>

using namespace lsr;

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
