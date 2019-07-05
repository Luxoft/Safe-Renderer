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

class ExpressionRedundancyTest : public ExpressionTestFixture
{
protected:
    ExpressionRedundancyTest()
    {
    }

    void prepareExpression(U32 value1, U32 value2, U32 value3)
    {
        ExpressionTypeFactory exprFactory;
        exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

        ExpressionTermTypeFactory term1;
        term1.createIntegerExprTerm(value1);

        ExpressionTermTypeFactory term2;
        term2.createIntegerExprTerm(value2);

        ExpressionTermTypeFactory term3;
        term3.createIntegerExprTerm(value3);

        exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
        exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
        exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

        m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());
    }
};

TEST_F(ExpressionRedundancyTest, RedundancyReturnValidValueTest)
{
    const U32 expected = 5U;
    prepareExpression(expected, expected, expected);

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest1)
{
    const U32 expected = 5U;
    prepareExpression(10U, expected, expected);

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest2)
{
    const U32 expected = 5U;
    prepareExpression(expected, 10U, expected);

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest3)
{
    const U32 expected = 5U;
    prepareExpression(expected, expected, 10U);

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest4)
{
    prepareExpression(5U, 6U, 7U);

    const lsr::Number expectedValue(5U, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest5)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    m_dataHandler.setInvalidNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const U32 expected = 5U;
    lsr::DynamicDataType type;

    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(expected);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(expected);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest6)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    const U32 expected = 10U;

    m_dataHandler.setInvalidNumber(lsr::Number(expected, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest7)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    const U32 expected = 10U;

    m_dataHandler.setInvalidNumber(lsr::Number(expected, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term3;
    term3.createDynamicDataExprTerm(type);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest8)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    m_dataHandler.setOutDatedNumber(lsr::Number(10U, lsr::DATATYPE_INTEGER));

    const U32 expected = 5U;
    lsr::DynamicDataType type;

    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(expected);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(expected);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest9)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    const U32 expected = 10U;

    m_dataHandler.setOutDatedNumber(lsr::Number(expected, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest10)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    const U32 expected = 10U;

    m_dataHandler.setOutDatedNumber(lsr::Number(expected, lsr::DATATYPE_INTEGER));

    lsr::DynamicDataType type;
    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term2;
    term2.createDynamicDataExprTerm(type);

    ExpressionTermTypeFactory term3;
    term3.createDynamicDataExprTerm(type);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const lsr::Number expectedValue(expected, lsr::DATATYPE_INTEGER);
    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInconsistentFlagTest1)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(lsr::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    ExpressionTermTypeFactory term1;
    term1.createWrongExprTerm(10U);

    ExpressionTermTypeFactory term2;
    term2.createWrongExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createWrongExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    lsr::Number actualValue;
    lsr::DataStatus actualStatus =
        lsr::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(lsr::DataStatus::INCONSISTENT, actualStatus);
}
