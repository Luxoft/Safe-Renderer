/******************************************************************************
**
**   File:        NumberTest.cpp
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

#include <Number.h>

#include <gtest/gtest.h>

using namespace lsr;

TEST(NumberTest, TestDefaultValue)
{
    Number number;
    EXPECT_EQ(0U, number.getU32());
    EXPECT_EQ(DATATYPE_ENUM_SIZE, number.getType());
}

TEST(NumberTest, CobnstructorTest)
{
    const U32 expectedValue = 45U;
    const DynamicDataTypeEnumeration expectedType = DATATYPE_DECIMAL;
    Number number(expectedValue, expectedType);

    EXPECT_EQ(expectedValue, number.getU32());
    EXPECT_EQ(expectedType, number.getType());
}

TEST(NumberTest, ConstructorWithBoolTest)
{
    const U32 expectedValue = 1U;
    const DynamicDataTypeEnumeration expectedType = DATATYPE_BOOLEAN;
    const bool value = true;
    Number number(value);

    EXPECT_EQ(value, number.getBool());
    EXPECT_EQ(expectedValue, number.getU32());
    EXPECT_EQ(expectedType, number.getType());
}

TEST(NumberTest, CopyConstructorTest)
{
    const U32 expectedValue = 45U;
    const DynamicDataTypeEnumeration expectedType = DATATYPE_DECIMAL;
    const Number number1(expectedValue, expectedType);
    const Number number2(number1);

    EXPECT_EQ(expectedValue, number2.getU32());
    EXPECT_EQ(expectedType, number2.getType());
}

TEST(NumberTest, OperatorAssignmentTest)
{
    const U32 expectedValue = 45U;
    const DynamicDataTypeEnumeration expectedType = DATATYPE_DECIMAL;
    Number number1(expectedValue, expectedType);
    Number number2(expectedValue + 2, DATATYPE_INTEGER);
    number2 = number1;

    EXPECT_TRUE(number1 == number2);

    // Do nothing
    number2 = number2;
}

TEST(NumberTest, OperatorLessTest)
{
    const Number number1(45U, DATATYPE_INTEGER);
    const Number number2(32U, DATATYPE_DECIMAL);

    EXPECT_TRUE(number2 < number1);
    EXPECT_FALSE(number1 < number2);
}

TEST(NumberTest, OperatorEqualTest)
{
    const Number number1(45U, DATATYPE_INTEGER);
    const Number number2(32U, DATATYPE_DECIMAL);

    EXPECT_FALSE(number1 == number2);

    const Number number3(45U, DATATYPE_DECIMAL);

    EXPECT_FALSE(number1 == number3);

    const Number number4(45U, DATATYPE_INTEGER);

    EXPECT_TRUE(number1 == number4);
}

TEST(NumberTest, OperatorNotEqualTest)
{
    const Number number1(45U, DATATYPE_INTEGER);
    const Number number2(32U, DATATYPE_DECIMAL);

    EXPECT_TRUE(number1 != number2);

    const Number number3(45U, DATATYPE_DECIMAL);

    EXPECT_TRUE(number1 != number3);

    const Number number4(45U, DATATYPE_INTEGER);

    EXPECT_FALSE(number1 != number4);
}

