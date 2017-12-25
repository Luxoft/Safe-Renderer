/******************************************************************************
**
**   File:        ExpressionMinMaxOperatorTest.cpp
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

class ExpressionMinMaxOpFixture : public ExpressionTestFixture
{
protected:
    ExpressionMinMaxOpFixture()
    {
    }

    void prepareExpression(U32 value, U32 minValue, U32 maxValue)
    {
        ExpressionTypeFactory exprFactory;
        exprFactory.createExpr(psc::EXPRESSION_OPERATOR_MIN_MAX, 3U);

        ExpressionTermTypeFactory termValue;
        termValue.createIntegerExprTerm(value);

        ExpressionTermTypeFactory termMin;
        termMin.createIntegerExprTerm(minValue);

        ExpressionTermTypeFactory termMax;
        termMax.createIntegerExprTerm(maxValue);

        exprFactory.addExprTerm(termValue.getDdh(), termValue.getSize());
        exprFactory.addExprTerm(termMin.getDdh(), termMin.getSize());
        exprFactory.addExprTerm(termMax.getDdh(), termMax.getSize());

        m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());
    }
};


TEST_F(ExpressionMinMaxOpFixture, MinMaxReturnValueTest)
{
    U32 expected = 32U;
    prepareExpression(expected, 5U, 100U);

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    const psc::DataStatus expectedStatus = psc::DataStatus::VALID;
    psc::Number actualValue;

    psc::DataStatus actualStatus =
        psc::expressionoperators::minMax(m_termFactory.getDdh()->GetExpression(),
                                                 &m_context,
                                                 actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxReturnMinTest)
{
    U32 expected = 32U;
    prepareExpression(1U, expected, 100U);

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    const psc::DataStatus expectedStatus = psc::DataStatus::VALID;
    psc::Number actualValue;

    psc::DataStatus actualStatus =
        psc::expressionoperators::minMax(m_termFactory.getDdh()->GetExpression(),
                                                 &m_context,
                                                 actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxReturnMaxTest)
{
    U32 expected = 100U;
    prepareExpression(200U, 5U, expected);

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    const psc::DataStatus expectedStatus = psc::DataStatus::VALID;
    psc::Number actualValue;

    psc::DataStatus actualStatus =
        psc::expressionoperators::minMax(m_termFactory.getDdh()->GetExpression(),
                                                 &m_context,
                                                 actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxWithWrongFirstTermTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_MIN_MAX, 3U);

    ExpressionTermTypeFactory termValue;
    termValue.createWrongExprTerm(200U);

    ExpressionTermTypeFactory termMin;
    termMin.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory termMax;
    termMax.createIntegerExprTerm(100U);

    exprFactory.addExprTerm(termValue.getDdh(), termValue.getSize());
    exprFactory.addExprTerm(termMin.getDdh(), termMin.getSize());
    exprFactory.addExprTerm(termMax.getDdh(), termMax.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const psc::DataStatus expectedStatus = psc::DataStatus::INCONSISTENT;
    psc::Number actualValue;

    psc::DataStatus actualStatus =
        psc::expressionoperators::minMax(m_termFactory.getDdh()->GetExpression(),
                                                 &m_context,
                                                 actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxWithWrongSecondTermTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_MIN_MAX, 3U);

    ExpressionTermTypeFactory termValue;
    termValue.createIntegerExprTerm(200U);

    ExpressionTermTypeFactory termMin;
    termMin.createWrongExprTerm(5U);

    ExpressionTermTypeFactory termMax;
    termMax.createIntegerExprTerm(100U);

    exprFactory.addExprTerm(termValue.getDdh(), termValue.getSize());
    exprFactory.addExprTerm(termMin.getDdh(), termMin.getSize());
    exprFactory.addExprTerm(termMax.getDdh(), termMax.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const psc::DataStatus expectedStatus = psc::DataStatus::INCONSISTENT;
    psc::Number actualValue;

    psc::DataStatus actualStatus =
        psc::expressionoperators::minMax(m_termFactory.getDdh()->GetExpression(),
                                                 &m_context,
                                                 actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
}

TEST_F(ExpressionMinMaxOpFixture, MinMaxWithWrongThirdTermTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_MIN_MAX, 3U);

    ExpressionTermTypeFactory termValue;
    termValue.createIntegerExprTerm(200U);

    ExpressionTermTypeFactory termMin;
    termMin.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory termMax;
    termMax.createWrongExprTerm(100U);

    exprFactory.addExprTerm(termValue.getDdh(), termValue.getSize());
    exprFactory.addExprTerm(termMin.getDdh(), termMin.getSize());
    exprFactory.addExprTerm(termMax.getDdh(), termMax.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const psc::DataStatus expectedStatus = psc::DataStatus::INCONSISTENT;
    psc::Number actualValue;

    psc::DataStatus actualStatus =
        psc::expressionoperators::minMax(m_termFactory.getDdh()->GetExpression(),
                                                 &m_context,
                                                 actualValue);

    EXPECT_EQ(expectedStatus, actualStatus);
}
