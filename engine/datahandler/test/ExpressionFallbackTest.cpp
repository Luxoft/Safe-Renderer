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

class ExpressionFallbackTest : public ExpressionTestFixture
{
protected:
    ExpressionFallbackTest()
    {
    }
};

TEST_F(ExpressionFallbackTest, FallbackReturnValidValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(10U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(10U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, FallbackReturnInValidValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK, 2U);

    m_dataHandler.setInvalidNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, FallbackReturnOtherCasesValueTest1)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK, 2U);

    m_dataHandler.setOutDatedNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, FallbackReturnOtherCasesValueTest2)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK, 2U);

    ExpressionTermTypeFactory term1;
    term1.createWrongExprTerm(7U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}


TEST_F(ExpressionFallbackTest, Fallback2ReturnValidValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK2, 3U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(10U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(7U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(10U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback2ReturnInValidValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK2, 3U);

    m_dataHandler.setInvalidNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(7U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback2ReturnNotAvailableValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK2, 3U);

    m_dataHandler.setOutDatedNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(7U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(7U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback2ReturnOtherCasesValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK2, 3U);

    ExpressionTermTypeFactory term1;
    term1.createWrongExprTerm(3U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(7U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(7U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback3ReturnValidValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK3, 4U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(10U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(7U);

    ExpressionTermTypeFactory term4;
    term4.createIntegerExprTerm(9U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());
    exprFactory.addExprTerm(term4.getDdh(), term4.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(10U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback3ReturnInValidValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK3, 4U);

    m_dataHandler.setInvalidNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(7U);

    ExpressionTermTypeFactory term4;
    term4.createIntegerExprTerm(7U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());
    exprFactory.addExprTerm(term4.getDdh(), term4.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback3ReturnNotAvailableValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK3, 4U);

    m_dataHandler.setOutDatedNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(7U);

    ExpressionTermTypeFactory term4;
    term4.createIntegerExprTerm(9U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());
    exprFactory.addExprTerm(term4.getDdh(), term4.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(7U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionFallbackTest, Fallback3ReturnInconsistentValueTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_FALLBACK3, 4U);

    ExpressionTermTypeFactory term1;
    term1.createWrongExprTerm(3U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(7U);

    ExpressionTermTypeFactory term4;
    term4.createIntegerExprTerm(9U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());
    exprFactory.addExprTerm(term4.getDdh(), term4.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(9U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}
