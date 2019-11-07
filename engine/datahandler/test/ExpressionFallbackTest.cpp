/******************************************************************************
**
**   File:        ExpressionFallbackTest.cpp
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

class ExpressionFallbackTest : public ExpressionTestFixture
{
protected:
    ExpressionFallbackTest()
    {
    }
};

TEST_F(ExpressionFallbackTest, FallbackReturnValidValueTest)
{
    ExpressionTermType t1 = {ExpressionTermType::INTEGER_CHOICE, 10U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const Number expectedValue(10U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus = Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, FallbackReturnInValidValueTest)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType t1 = {ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData};
    const ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    m_dataHandler.setInvalidNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, FallbackReturnOtherCasesValueTest1)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType t1 = {ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData};
    const ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    m_dataHandler.setOutDatedNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, FallbackReturnOtherCasesValueTest2)
{
    ExpressionTermType t1 = {ExpressionTermType::NONE, 7U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK, parameters, 2 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}


TEST_F(ExpressionFallbackTest, Fallback2ReturnValidValueTest)
{
    ExpressionTermType t1 = {ExpressionTermType::INTEGER_CHOICE, 10U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    ExpressionTermType t3 = {ExpressionTermType::INTEGER_CHOICE, 7U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK2, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const lsr::Number expectedValue(10U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback2ReturnInValidValueTest)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType t1 = {ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData};
    const ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType t3 = {ExpressionTermType::INTEGER_CHOICE, 7U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK2, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    m_dataHandler.setInvalidNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback2ReturnNotAvailableValueTest)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType t1 = {ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData};
    const ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType t3 = {ExpressionTermType::INTEGER_CHOICE, 7U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK2, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    m_dataHandler.setOutDatedNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(7U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback2ReturnOtherCasesValueTest)
{
    ExpressionTermType t1 = {ExpressionTermType::NONE, 3U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    ExpressionTermType t3 = {ExpressionTermType::INTEGER_CHOICE, 7U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK2, parameters, 3 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const lsr::Number expectedValue(7U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback3ReturnValidValueTest)
{
    ExpressionTermType t1 = {ExpressionTermType::INTEGER_CHOICE, 10U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    ExpressionTermType t3 = {ExpressionTermType::INTEGER_CHOICE, 7U, NULL};
    ExpressionTermType t4 = {ExpressionTermType::INTEGER_CHOICE, 9U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3, &t4 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK3, parameters, 4 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const lsr::Number expectedValue(10U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback3ReturnInValidValueTest)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType t1 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 7U, NULL };
    const ExpressionTermType t4 = { ExpressionTermType::INTEGER_CHOICE, 9U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3, &t4 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK3, parameters, 4 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    m_dataHandler.setInvalidNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback3ReturnNotAvailableValueTest)
{
    const DynamicDataType dynData = { 0U, DATATYPE_INTEGER };
    const ExpressionTermType t1 = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynData };
    const ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 7U, NULL };
    const ExpressionTermType t4 = { ExpressionTermType::INTEGER_CHOICE, 9U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3, &t4 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK3, parameters, 4 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    m_dataHandler.setOutDatedNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const lsr::Number expectedValue(7U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback3ReturnInconsistentValueTest)
{
    ExpressionTermType t1 = { ExpressionTermType::NONE, 3U, NULL };
    ExpressionTermType t2 = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType t3 = { ExpressionTermType::INTEGER_CHOICE, 7U, NULL };
    ExpressionTermType t4 = { ExpressionTermType::INTEGER_CHOICE, 9U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &t2, &t3, &t4 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_FALLBACK3, parameters, 4 };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &expr };

    const lsr::Number expectedValue(9U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(&term, &m_context, actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}
