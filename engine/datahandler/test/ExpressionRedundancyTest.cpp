/******************************************************************************
**
**   File:        ExpressionRedundancyTest.cpp
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
        exprFactory.createExpr(psc::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

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

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest1)
{
    const U32 expected = 5U;
    prepareExpression(10U, expected, expected);

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest2)
{
    const U32 expected = 5U;
    prepareExpression(expected, 10U, expected);

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest3)
{
    const U32 expected = 5U;
    prepareExpression(expected, expected, 10U);

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest4)
{
    prepareExpression(5U, 6U, 7U);

    const psc::Number expectedValue(5U, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest5)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    m_dataHandler.setInvalidNumber(psc::Number(10U, psc::DATATYPE_INTEGER));

    const U32 expected = 5U;
    psc::DynamicDataType type;

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

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest6)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    const U32 expected = 10U;

    m_dataHandler.setInvalidNumber(psc::Number(expected, psc::DATATYPE_INTEGER));

    psc::DynamicDataType type;
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

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest7)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    const U32 expected = 10U;

    m_dataHandler.setInvalidNumber(psc::Number(expected, psc::DATATYPE_INTEGER));

    psc::DynamicDataType type;
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

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest8)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    m_dataHandler.setOutDatedNumber(psc::Number(10U, psc::DATATYPE_INTEGER));

    const U32 expected = 5U;
    psc::DynamicDataType type;

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

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest9)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    const U32 expected = 10U;

    m_dataHandler.setOutDatedNumber(psc::Number(expected, psc::DATATYPE_INTEGER));

    psc::DynamicDataType type;
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

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInValidValueTest10)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    const U32 expected = 10U;

    m_dataHandler.setOutDatedNumber(psc::Number(expected, psc::DATATYPE_INTEGER));

    psc::DynamicDataType type;
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

    const psc::Number expectedValue(expected, psc::DATATYPE_INTEGER);
    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INVALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionRedundancyTest, RedundancyReturnInconsistentFlagTest1)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(psc::EXPRESSION_OPERATOR_REDUNDANCY, 3U);

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

    psc::Number actualValue;
    psc::DataStatus actualStatus =
        psc::Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(psc::DataStatus::INCONSISTENT, actualStatus);
}
