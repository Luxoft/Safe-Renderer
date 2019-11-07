/******************************************************************************
**
**   File:        ExpressionBooleanOperatorsTest.cpp
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

class ExpressionBooleanOpFixture : public ExpressionTestFixture
{
protected:
    typedef DataStatus(*TestingOperator)(const ExpressionType* pExpression,
                                                      DataContext* pContext,
                                                      Number& value);

    ExpressionBooleanOpFixture()
        : m_expectedTrue(true)
        , m_expectedFalse(false)
        , m_notIntersting(0xFF, DATATYPE_INTEGER)
    {
    }

    void testOperator(TestingOperator op, const ExpressionType* expr,
                      const DataStatus expectedStatus,
                      const Number expectedValue)
    {
        Number actualValue;
        DataStatus actualStatus = (*op)(expr, &m_context, actualValue);

        EXPECT_EQ(expectedStatus, actualStatus);

        if (m_notIntersting != expectedValue)
        {
            EXPECT_EQ(expectedValue, actualValue);
        }
    }

    const Number m_expectedTrue;
    const Number m_expectedFalse;
    const Number m_notIntersting;
};

TEST_F(ExpressionBooleanOpFixture, IntOperatorsWithEqualValuesTest)
{
    ExpressionTermType t1 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 2 };

    testOperator(&expressionoperators::equals, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::notEquals, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::lessThan, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::lessThanOrEquals, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::greaterThan, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::greaterThanOrEquals, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);
}


TEST_F(ExpressionBooleanOpFixture, IntOperatorsWithValue1LessValue2Test)
{
    ExpressionTermType t1 = {ExpressionTermType::INTEGER_CHOICE, 3U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 2 };

    testOperator(&expressionoperators::equals, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::notEquals, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::lessThan, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::lessThanOrEquals, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::greaterThan, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::greaterThanOrEquals, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);
}

TEST_F(ExpressionBooleanOpFixture, IntOperatorsWithValue1GreaterValue2Test)
{
    ExpressionTermType t1 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 3U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 2 };

    testOperator(&expressionoperators::equals, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::notEquals, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::lessThan, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::lessThanOrEquals, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::greaterThan, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::greaterThanOrEquals, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, NotOperatorTest1)
{
    ExpressionTermType t1 = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    const ExpressionTermType* parameters[] = { &t1, };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 1 };

    testOperator(&expressionoperators::booleanNot, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);
}

TEST_F(ExpressionBooleanOpFixture, NotOperatorTest2)
{
    ExpressionTermType t1 = {ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL};
    const ExpressionTermType* parameters[] = { &t1, };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 1 };

    testOperator(&expressionoperators::booleanNot, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithEqualValuesTest)
{
    ExpressionTermType t1 = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 2 };

    testOperator(&expressionoperators::booleanAnd, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::booleanOr, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithNotEqualValuesTest1)
{
    ExpressionTermType t1 = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 2 };

    testOperator(&expressionoperators::booleanAnd, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::booleanOr, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithNotEqualValuesTest2)
{
    ExpressionTermType t1 = {ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_ENUM_SIZE, parameters, 2 };

    testOperator(&expressionoperators::booleanAnd, &expr,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::booleanOr, &expr,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, IntOperatorsWithWrongTermTest1)
{
    ExpressionTermType t1 = {ExpressionTermType::NONE, 5U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_EQUALS, parameters, 2 };

    testOperator(&expressionoperators::equals, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::notEquals, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::lessThan, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::lessThanOrEquals, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::greaterThan, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::greaterThanOrEquals, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, IntOperatorsWithWrongTermTest2)
{
    ExpressionTermType t1 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::NONE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_EQUALS, parameters, 2 };

    testOperator(&expressionoperators::equals, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::notEquals, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::lessThan, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::lessThanOrEquals, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::greaterThan, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::greaterThanOrEquals, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithWrongTermTest1)
{
    ExpressionTermType t1 = {ExpressionTermType::NONE, 5U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_EQUALS, parameters, 2 };

    testOperator(&expressionoperators::booleanAnd, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::booleanOr, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithWrongTermTest2)
{
    ExpressionTermType t1 = {ExpressionTermType::BOOLEAN_CHOICE, 5U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::NONE, 0U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_EQUALS, parameters, 2 };

    testOperator(&expressionoperators::booleanAnd, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::booleanOr, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, NotOperatorsWithWrongTermTest)
{
    ExpressionTermType t1 = {ExpressionTermType::NONE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1,};
    const ExpressionType expr = { EXPRESSION_OPERATOR_EQUALS, parameters, 1 };

    testOperator(&expressionoperators::booleanNot, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithWrongTermTypeTest1)
{
    ExpressionTermType t1 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_EQUALS, parameters, 2 };

    testOperator(&expressionoperators::booleanAnd, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::booleanOr, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithWrongTermTypeTest2)
{
    ExpressionTermType t1 = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    ExpressionTermType t2 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, &t2 };
    const ExpressionType expr = { EXPRESSION_OPERATOR_EQUALS, parameters, 2 };

    testOperator(&expressionoperators::booleanAnd, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::booleanOr, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, NotOperatorsWithWrongTermTypeTest)
{
    ExpressionTermType t1 = {ExpressionTermType::INTEGER_CHOICE, 5U, NULL};
    const ExpressionTermType* parameters[] = { &t1, };
    const ExpressionType expr = { EXPRESSION_OPERATOR_EQUALS, parameters, 1 };

    testOperator(&expressionoperators::booleanNot, &expr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

