/******************************************************************************
**
**   File:        ExpressionTest.cpp
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

#include <Expression.h>
#include <ExpressionType.h>
#include <BitmapIdTableType.h>
#include <EnumerationBitmapMapType.h>

#include <gtest/gtest.h>

using namespace lsr;

TEST_F(ExpressionTestFixture, GetBoolTest)
{
    bool expectedValue = true;
    const ExpressionTermType term = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };

    bool actualValue = false;
    DataStatus actualStatus =
        Expression::getBool(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);

    expectedValue = false;
    const ExpressionTermType term1 = { ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL };

    actualStatus =
        Expression::getBool(&term1, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetDynamicDataNumberTest)
{
    const DynamicDataType dataType = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType term = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };

    const Number expectedValue(5U, DATATYPE_INTEGER);
    m_dataHandler.setNumber(expectedValue);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetDynamicDataNumberWithOutDatedDataTest)
{
    const DynamicDataType dataType = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType term = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };

    const Number expectedValue;
    m_dataHandler.setOutDatedNumber(expectedValue);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::NOT_AVAILABLE, actualStatus);
}

TEST_F(ExpressionTestFixture, GetDynamicDataNumberWithInvalidDataTest)
{
    const DynamicDataType dataType = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType term = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };

    const Number expectedValue;
    m_dataHandler.setInvalidNumber(expectedValue);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::INVALID, actualStatus);
}

TEST_F(ExpressionTestFixture, GetDynamicDataNumberWithWrongContextTest)
{
    const DynamicDataType dataType = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType term = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, NULL, actualValue);

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}

TEST_F(ExpressionTestFixture, GetIntegerNumberTest)
{
    U32 expectedValue = 5U;
    const ExpressionTermType term = { ExpressionTermType::INTEGER_CHOICE, expectedValue, NULL };

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue.getU32());
}

namespace infinite2 // TODO: baseclass?
{
    const DynamicDataType dynamicData = { ((13U << 16U) | 52U), DATATYPE_INTEGER };
    const ExpressionTermType tdyn = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynamicData };

    const ExpressionTermType* para11[] = { &tdyn, &tdyn, };
    const ExpressionType e11 = { EXPRESSION_OPERATOR_EQUALS, para11, 2U };
    const ExpressionTermType te11 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e11 };

    const ExpressionTermType* para10[] = { &tdyn, &te11, };
    const ExpressionType e10 = { EXPRESSION_OPERATOR_EQUALS, para10, 2U };
    const ExpressionTermType te10 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e10 };

    const ExpressionTermType* para9[] = { &tdyn, &te10, };
    const ExpressionType e9 = { EXPRESSION_OPERATOR_EQUALS, para9, 2U };
    const ExpressionTermType te9 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e9 };

    const ExpressionTermType* para8[] = { &tdyn, &te9, };
    const ExpressionType e8 = { EXPRESSION_OPERATOR_EQUALS, para8, 2U };
    const ExpressionTermType te8 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e8 };

    const ExpressionTermType* para7[] = { &tdyn, &te8, };
    const ExpressionType e7 = { EXPRESSION_OPERATOR_EQUALS, para7, 2U };
    const ExpressionTermType te7 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e7 };

    const ExpressionTermType* para6[] = { &tdyn, &te7, };
    const ExpressionType e6 = { EXPRESSION_OPERATOR_EQUALS, para6, 2U };
    const ExpressionTermType te6 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e6 };

    const ExpressionTermType* para5[] = { &tdyn, &te6, };
    const ExpressionType e5 = { EXPRESSION_OPERATOR_EQUALS, para5, 2U };
    const ExpressionTermType te5 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e5 };

    const ExpressionTermType* para4[] = { &tdyn, &te5, };
    const ExpressionType e4 = { EXPRESSION_OPERATOR_EQUALS, para4, 2U };
    const ExpressionTermType te4 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e4 };

    const ExpressionTermType* para3[] = { &tdyn, &te4, };
    const ExpressionType e3 = { EXPRESSION_OPERATOR_EQUALS, para3, 2U };
    const ExpressionTermType te3 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e3 };

    const ExpressionTermType* para2[] = { &tdyn, &te3, };
    const ExpressionType e2 = { EXPRESSION_OPERATOR_EQUALS, para2, 2U };
    const ExpressionTermType te2 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e2 };

    const ExpressionTermType* para1[] = { &tdyn, &te2, };
    const ExpressionType e1 = { EXPRESSION_OPERATOR_EQUALS, para1, 2U };
    const ExpressionTermType te1 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e1 };

    const ExpressionTermType* parameters[] = { &tdyn, &te1, };
    const ExpressionType exp = { EXPRESSION_OPERATOR_EQUALS, parameters, 2U };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };
    extern const ExpressionTermType term;
}

TEST_F(ExpressionTestFixture, GetNumberWithInfiniteExpressionsTest)
{
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&infinite2::term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithEqualsOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_EQUALS, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(true);
    Number actualValue;

    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithMinMaxOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 32U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 100U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_MIN_MAX, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(32U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithNotEqualsOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 6U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_NOT_EQUALS, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithLessThanOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 3U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_LESS, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithLessThanOrEqualsOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 3U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_LESS_EQUALS, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithGreaterThanOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 10U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_GREATER, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithGreaterThanOrequalsOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 10U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_GREATER_EQUALS, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithItemAtOperatorTest)
{
    const EnumerationBitmapMapType map1 = { 29U, 23U };
    const EnumerationBitmapMapType map2 = { 39U, 33U };
    const EnumerationBitmapMapType* tableEntries[] = { &map1, &map2, };
    const BitmapIdTableType bitmapTable = { tableEntries, 2 };

    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 39U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::BITMAPIDTABLE_CHOICE, 0U, &bitmapTable };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_ITEM_AT, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(33U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithAndOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_AND, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(false);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithOrOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_OR, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithNotOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType* parameters[] = { &t1 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_NOT, parameters, 1 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(false);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithFallbackOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 10U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_FALLBACK, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(10U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithFallback2OperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 10U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 7U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_FALLBACK2, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(10U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithFallback3OperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 10U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 7U, NULL };
    const ExpressionTermType t4 = { ExpressionTermType::INTEGER_CHOICE, 70U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3, &t4 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_FALLBACK3, parameters, 4 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(10U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithRedundancyOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType exp = { EXPRESSION_OPERATOR_REDUNDANCY, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    const Number expectedValue(5U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithWrongOperatorTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType* parameters[] = { &t1,};
    const ExpressionType exp = { EXPRESSION_OPERATOR_PLUS, parameters, 1 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}

TEST_F(ExpressionTestFixture, GetUnknownNumberTest)
{
    const ExpressionTermType term = { ExpressionTermType::NONE, 5U, NULL };

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(&term, &m_context, actualValue); 

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}
