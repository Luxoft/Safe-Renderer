/******************************************************************************
**
**   File:        ExpressionBooleanOperatorsTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

using namespace psc;

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

    void addOperands(U32 value)
    {
        ExpressionTypeFactory exprFactory;
        exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 1U);

        ExpressionTermTypeFactory term;
        term.createIntegerExprTerm(value);

        exprFactory.addExprTerm(term.getDdh(), term.getSize());

        m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());
    }

    void addOperands(bool value)
    {
        ExpressionTypeFactory exprFactory;
        exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 1U);

        ExpressionTermTypeFactory term;
        term.createBoolExprTerm(value);

        exprFactory.addExprTerm(term.getDdh(), term.getSize());

        m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());
    }

    void addOperands(U32 value1, U32 value2)
    {
        ExpressionTypeFactory exprFactory;
        exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

        ExpressionTermTypeFactory term1;
        term1.createIntegerExprTerm(value1);

        ExpressionTermTypeFactory term2;
        term2.createIntegerExprTerm(value2);

        exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
        exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

        m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());
    }

    void addOperands(bool value1, bool value2)
    {
        ExpressionTypeFactory exprFactory;
        exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

        ExpressionTermTypeFactory term1;
        term1.createBoolExprTerm(value1);

        ExpressionTermTypeFactory term2;
        term2.createBoolExprTerm(value2);

        exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
        exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

        m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());
    }

    void testOperator(TestingOperator op,
                      const DataStatus expectedStatus,
                      const Number expectedValue)
    {
        Number actualValue;
        DataStatus actualStatus = (*op)(m_termFactory.getDdh()->GetExpression(),
                                                     &m_context,
                                                     actualValue);

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
    addOperands(5U, 5U);

    testOperator(&expressionoperators::equals,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::notEquals,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::lessThan,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::lessThanOrEquals,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::greaterThan,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::greaterThanOrEquals,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, IntOperatorsWithValue1LessValue2Test)
{
    addOperands(3U, 5U);

    testOperator(&expressionoperators::equals,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::notEquals,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::lessThan,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::lessThanOrEquals,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::greaterThan,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::greaterThanOrEquals,
                 DataStatus::VALID,
                 m_expectedFalse);
}

TEST_F(ExpressionBooleanOpFixture, IntOperatorsWithValue1GreaterValue2Test)
{
    addOperands(5U, 3U);

    testOperator(&expressionoperators::equals,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::notEquals,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::lessThan,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::lessThanOrEquals,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::greaterThan,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::greaterThanOrEquals,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, NotOperatorTest1)
{
    addOperands(true);

    testOperator(&expressionoperators::booleanNot,
                 DataStatus::VALID,
                 m_expectedFalse);
}

TEST_F(ExpressionBooleanOpFixture, NotOperatorTest2)
{
    addOperands(false);

    testOperator(&expressionoperators::booleanNot,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithEqualValuesTest)
{
    addOperands(true, true);

    testOperator(&expressionoperators::booleanAnd,
                 DataStatus::VALID,
                 m_expectedTrue);

    testOperator(&expressionoperators::booleanOr,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithNotEqualValuesTest1)
{
    addOperands(true, false);

    testOperator(&expressionoperators::booleanAnd,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::booleanOr,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithNotEqualValuesTest2)
{
    addOperands(false, true);

    testOperator(&expressionoperators::booleanAnd,
                 DataStatus::VALID,
                 m_expectedFalse);

    testOperator(&expressionoperators::booleanOr,
                 DataStatus::VALID,
                 m_expectedTrue);
}

TEST_F(ExpressionBooleanOpFixture, IntOperatorsWithWrongTermTest1)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createWrongExprTerm(5U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    testOperator(&expressionoperators::equals,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::notEquals,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::lessThan,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::lessThanOrEquals,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::greaterThan,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::greaterThanOrEquals,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, IntOperatorsWithWrongTermTest2)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term2;
    term2.createWrongExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    testOperator(&expressionoperators::equals,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::notEquals,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::lessThan,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::lessThanOrEquals,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::greaterThan,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::greaterThanOrEquals,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithWrongTermTest1)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createWrongExprTerm(5U);

    ExpressionTermTypeFactory term2;
    term2.createBoolExprTerm(true);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    testOperator(&expressionoperators::booleanAnd,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::booleanOr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithWrongTermTest2)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createBoolExprTerm(true);

    ExpressionTermTypeFactory term2;
    term2.createWrongExprTerm(false);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    testOperator(&expressionoperators::booleanAnd,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::booleanOr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, NotOperatorsWithWrongTermTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 1U);

    ExpressionTermTypeFactory term;
    term.createWrongExprTerm(5U);

    exprFactory.addExprTerm(term.getDdh(), term.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    testOperator(&expressionoperators::booleanNot,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithWrongTermTypeTest1)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term2;
    term2.createBoolExprTerm(true);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    testOperator(&expressionoperators::booleanAnd,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::booleanOr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, BoolOperatorsWithWrongTermTypeTest2)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createBoolExprTerm(true);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    testOperator(&expressionoperators::booleanAnd,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);

    testOperator(&expressionoperators::booleanOr,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

TEST_F(ExpressionBooleanOpFixture, NotOperatorsWithWrongTermTypeTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 1U);

    ExpressionTermTypeFactory term;
    term.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term.getDdh(), term.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    testOperator(&expressionoperators::booleanNot,
                 DataStatus::INCONSISTENT,
                 m_notIntersting);
}

