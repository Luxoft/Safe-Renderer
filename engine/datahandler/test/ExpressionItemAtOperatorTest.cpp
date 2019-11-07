/******************************************************************************
**
**   File:        ExpressionItemAtOperatorTest.cpp
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

#include <gtest/gtest.h>

using namespace lsr;

class ExpressionItemAtOpFixture : public ExpressionTestFixture
{
};

namespace
{
    const EnumerationBitmapMapType map1 = { 29U, 23U };
    const EnumerationBitmapMapType map2 = { 39U, 33U };
    const EnumerationBitmapMapType* tableEntries[] = { &map1, &map2, };
    const BitmapIdTableType bitmapTable = { tableEntries, 2 };
}

TEST_F(ExpressionItemAtOpFixture, ItemAtTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 39U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::BITMAPIDTABLE_CHOICE, 0U, &bitmapTable };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ITEM_AT, parameters, 2 };

    const lsr::Number expectedValue(33U, lsr::DATATYPE_INTEGER);
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    lsr::Number actualValue;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::itemAt(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionItemAtOpFixture, ItemAtUseDefaultValueTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 40U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::BITMAPIDTABLE_CHOICE, 0U, &bitmapTable };
    const ExpressionTermType defaultVal = { ExpressionTermType::INTEGER_CHOICE, 55U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &defaultVal };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ITEM_AT, parameters, 3 };

    const lsr::Number expectedValue(55U, lsr::DATATYPE_INTEGER);
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;

    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::expressionoperators::itemAt(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionItemAtOpFixture, ItemAtWithoutDefaultValueTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 40U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::BITMAPIDTABLE_CHOICE, 0U, &bitmapTable };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ITEM_AT, parameters, 2 };

    const lsr::DataStatus expectedStatus = lsr::DataStatus::INVALID;
    lsr::Number actualValue;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::itemAt(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
}

TEST_F(ExpressionItemAtOpFixture, ItemAtWithWrongDefaultValueTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 40U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::BITMAPIDTABLE_CHOICE, 0U, &bitmapTable };
    const ExpressionTermType defaultVal = { ExpressionTermType::NONE, 55U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &defaultVal };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ITEM_AT, parameters, 3 };

    const lsr::DataStatus expectedStatus = lsr::DataStatus::INCONSISTENT;
    lsr::Number actualValue;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::itemAt(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
}

TEST_F(ExpressionItemAtOpFixture, ItemAtWithWrongFirstTermTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::NONE, 39U, NULL };
    const ExpressionTermType t2 = { ExpressionTermType::BITMAPIDTABLE_CHOICE, 0U, &bitmapTable };
    const ExpressionTermType defaultVal = { ExpressionTermType::INTEGER_CHOICE, 55U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &defaultVal };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ITEM_AT, parameters, 3 };

    lsr::Number actualValue;
    const lsr::DataStatus expectedStatus = lsr::DataStatus::INCONSISTENT;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::itemAt(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
}

TEST_F(ExpressionItemAtOpFixture, ItemAtWithEmptyBitmapTableTest1)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 39U, NULL };
    BitmapIdTableType emptyTable = { NULL, 0U, };
    const ExpressionTermType t2 = { ExpressionTermType::BITMAPIDTABLE_CHOICE, 0U, &emptyTable };
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ITEM_AT, parameters, 2 };

    lsr::Number actualValue;
    const lsr::DataStatus expectedStatus = lsr::DataStatus::INVALID;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::itemAt(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
}

