/******************************************************************************
**
**   File:        ExpressionRedundancyTest.cpp
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

#include "ExpressionTestFixture.h"

#include <ExpressionOperators.h>
#include <Expression.h>

#include <gtest/gtest.h>
using namespace lsr;

class ExpressionRedundancyTest : public ExpressionTestFixture
{
};

TEST_F(ExpressionRedundancyTest, RedundancyReturnValidValueTest)
{
    ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const U32 expected = 5U;
    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest1)
{
    ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 10U, NULL };
    ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const U32 expected = 5U;
    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest2)
{
    ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 10U, NULL };
    ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const U32 expected = 5U;

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest3)
{
    ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 10U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const U32 expected = 5U;

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest4)
{
    ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 6U, NULL };
    ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 7U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest5)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    ExpressionTermType t1 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    m_dataHandler.setInvalidNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const U32 expected = 5U;
    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest6)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    ExpressionTermType t1 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    ExpressionTermType t2 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const U32 expected = 10U;
    m_dataHandler.setInvalidNumber(lsr::Number(expected, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest7)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    ExpressionTermType t1 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    ExpressionTermType t2 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    ExpressionTermType t3 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const U32 expected = 10U;
    m_dataHandler.setInvalidNumber(lsr::Number(expected, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest8)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType t1 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    m_dataHandler.setOutDatedNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const U32 expected = 5U;
    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest9)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType t1 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    const ExpressionTermType t2 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    const ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const U32 expected = 10U;
    m_dataHandler.setOutDatedNumber(lsr::Number(expected, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest10)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType t1 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    const ExpressionTermType t2 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    const ExpressionTermType t3 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const U32 expected = 10U;
    m_dataHandler.setOutDatedNumber(lsr::Number(expected, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInconsistentFlagTest1)
{
    const ExpressionTermType t1 = { ExpressionTermType::NONE, 10U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::NONE, 5U, NULL };
    const ExpressionTermType t3 = { ExpressionTermType::NONE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::INCONSISTENT, actualStatus);
}
