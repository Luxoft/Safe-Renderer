/******************************************************************************
**
**   File:        ExpressionMinMaxOperatorTest.cpp
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

class ExpressionMinMaxOpFixture : public ExpressionTestFixture
{
};


TEST_F(ExpressionMinMaxOpFixture, MinMaxReturnValueTest)
{
    ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 32U, NULL };
    ExpressionTermType tmin = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType tmax = { ExpressionTermType::INTEGER_CHOICE, 100U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &tmin, &tmax };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 3 };

    const lsr::Number expectedValue(32U, lsr::DATATYPE_INTEGER);
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    lsr::Number actualValue;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::minMax(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxReturnMinTest)
{
    ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 1U, NULL };
    ExpressionTermType tmin = { ExpressionTermType::INTEGER_CHOICE, 32U, NULL };
    ExpressionTermType tmax = { ExpressionTermType::INTEGER_CHOICE, 100U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &tmin, &tmax };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 3 };

    U32 expected = 32U;
    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    lsr::Number actualValue;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::minMax(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxReturnMaxTest)
{
    ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 200U, NULL };
    ExpressionTermType tmin = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType tmax = { ExpressionTermType::INTEGER_CHOICE, 100U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &tmin, &tmax };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 3 };

    U32 expected = 100U;
    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    lsr::Number actualValue;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::minMax(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxWithWrongFirstTermTest)
{
    ExpressionTermType t1 = { ExpressionTermType::NONE, 200U, NULL };
    ExpressionTermType tmin = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    ExpressionTermType tmax = { ExpressionTermType::INTEGER_CHOICE, 100U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &tmin, &tmax };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 3 };

    const lsr::DataStatus expectedStatus = lsr::DataStatus::INCONSISTENT;
    lsr::Number actualValue;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::minMax(&expr, &m_context, actualValue); 

    EXPECT_EQ(expectedStatus, actualStatus);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxWithWrongSecondTermTest)
{
    ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 200U, NULL };
    ExpressionTermType tmin = { ExpressionTermType::NONE, 5U, NULL };
    ExpressionTermType tmax = { ExpressionTermType::INTEGER_CHOICE, 100U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &tmin, &tmax };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 3 };

    const lsr::DataStatus expectedStatus = lsr::DataStatus::INCONSISTENT;
    lsr::Number actualValue;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::minMax(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxWithWrongThirdTermTest)
{
    const ExpressionTermType t1 = { ExpressionTermType::INTEGER_CHOICE, 200U, NULL };
    const ExpressionTermType tmin = { ExpressionTermType::INTEGER_CHOICE, 5U, NULL };
    const ExpressionTermType tmax = { ExpressionTermType::NONE, 100U, NULL };
    const ExpressionTermType* parameters[] = { &t1, &tmin, &tmax };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 3 };

    const lsr::DataStatus expectedStatus = lsr::DataStatus::INCONSISTENT;
    lsr::Number actualValue;

    lsr::DataStatus actualStatus =
        lsr::expressionoperators::minMax(&expr, &m_context, actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
}
