/******************************************************************************
**
**   File:        ExpressionTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "ExpressionTestFixture.h"

#include <Expression.h>

#include <gtest/gtest.h>

using namespace psc;

TEST_F(ExpressionTestFixture, GetBoolTest)
{
    bool expectedValue = true;
    m_termFactory.createBoolExprTerm(expectedValue);

    bool actualValue = false;
    DataStatus actualStatus =
        Expression::getBool(m_termFactory.getDdh(),
                                         &m_context,
                                         actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);

    expectedValue = false;
    m_termFactory.createBoolExprTerm(expectedValue);

    actualStatus =
        Expression::getBool(m_termFactory.getDdh(),
                                         &m_context,
                                         actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetDynamicDataNumberTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    const Number expectedValue(5U, DATATYPE_INTEGER);
    m_dataHandler.setNumber(expectedValue);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetDynamicDataNumberWithOutDatedDataTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    const Number expectedValue;
    m_dataHandler.setOutDatedNumber(expectedValue);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::NOT_AVAILABLE, actualStatus);
}

TEST_F(ExpressionTestFixture, GetDynamicDataNumberWithInvalidDataTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    const Number expectedValue;
    m_dataHandler.setInvalidNumber(expectedValue);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::INVALID, actualStatus);
}

TEST_F(ExpressionTestFixture, GetDynamicDataNumberWithWrongContextTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           NULL,
                                           actualValue);

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}

TEST_F(ExpressionTestFixture, GetDynamicDataNumberWithWrongDataHandlerTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    corruptHandler();

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}

TEST_F(ExpressionTestFixture, GetIntegerNumberTest)
{
    U32 expectedValue = 5U;
    m_termFactory.createIntegerExprTerm(expectedValue);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue.getU32());
}

TEST_F(ExpressionTestFixture, GetNumberWithInfiniteExpressionsTest)
{
    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    ExpressionTypeFactory exprFactory;
    exprFactory.createInfiniteExpr(dataType);

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithEqualsOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(true);
    Number actualValue;

    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithMinMaxOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_MIN_MAX, 3U);

    U32 expected = 32U;
    ExpressionTermTypeFactory termValue;
    termValue.createIntegerExprTerm(expected);

    ExpressionTermTypeFactory termMin;
    termMin.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory termMax;
    termMax.createIntegerExprTerm(100U);

    exprFactory.addExprTerm(termValue.getDdh(), termValue.getSize());
    exprFactory.addExprTerm(termMin.getDdh(), termMin.getSize());
    exprFactory.addExprTerm(termMax.getDdh(), termMax.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(expected, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithNotEqualsOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_NOT_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(6U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithLessThanOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_LESS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(3U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithLessThanOrEqualsOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_LESS_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(3U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithGreaterThanOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_GREATER, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(10U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithGreaterThanOrequalsOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_GREATER_EQUALS, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(10U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithItemAtOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_ITEM_AT, 2U);

    ExpressionTermTypeFactory keyValue;
    keyValue.createIntegerExprTerm(39U);

    exprFactory.addExprTerm(keyValue.getDdh(), keyValue.getSize());

    BitmapIdTableTypeFactory tableFactory;
    tableFactory.createExpr(2U);

    EnumerationBitmapMapTypeFactory row1;
    row1.create(23U, true, 29U);
    EnumerationBitmapMapTypeFactory row2;
    row2.create(33U, true, 39U);

    tableFactory.addRow(row1.getDdh(), row1.getSize());
    tableFactory.addRow(row2.getDdh(), row2.getSize());

    ExpressionTermTypeFactory tableTerm;
    tableTerm.createBitmapIdTableExprTerm(tableFactory.getDdh(), tableFactory.getSize());

    exprFactory.addExprTerm(tableTerm.getDdh(), tableTerm.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(33U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithAndOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_AND, 2U);

    ExpressionTermTypeFactory term1;
    term1.createBoolExprTerm(true);

    ExpressionTermTypeFactory term2;
    term2.createBoolExprTerm(false);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(false);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithOrOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_OR, 2U);

    ExpressionTermTypeFactory term1;
    term1.createBoolExprTerm(true);

    ExpressionTermTypeFactory term2;
    term2.createBoolExprTerm(false);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(true);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithNotOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_NOT, 1U);

    ExpressionTermTypeFactory term;
    term.createBoolExprTerm(true);

    exprFactory.addExprTerm(term.getDdh(), term.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(false);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithFallbackOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_FALLBACK, 2U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(10U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(10U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithFallback2OperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_FALLBACK2, 3U);

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

    const Number expectedValue(10U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithFallback3OperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_FALLBACK3, 4U);

    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(10U);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(5U);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(7U);

    ExpressionTermTypeFactory term4;
    term4.createIntegerExprTerm(70U);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());
    exprFactory.addExprTerm(term4.getDdh(), term4.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(10U, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithRedundancyOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_REDUNDANCY, 3U);

    const U32 expected = 5U;
    ExpressionTermTypeFactory term1;
    term1.createIntegerExprTerm(expected);

    ExpressionTermTypeFactory term2;
    term2.createIntegerExprTerm(expected);

    ExpressionTermTypeFactory term3;
    term3.createIntegerExprTerm(expected);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());
    exprFactory.addExprTerm(term3.getDdh(), term3.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    const Number expectedValue(expected, DATATYPE_INTEGER);
    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetExpressionNumberWithWrongOperatorTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_PLUS, 1U);

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}

TEST_F(ExpressionTestFixture, GetIndicationNumberTest)
{
    DynamicIndicationIdType dataType;
    m_termFactory.createIndicationExprTerm(dataType);

    const Number expectedValue(true);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::VALID, actualStatus);
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, GetIndicationNumberWithoutDataHandlerTest)
{
    DynamicIndicationIdType dataType;
    m_termFactory.createIndicationExprTerm(dataType);

    corruptHandler();

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}

TEST_F(ExpressionTestFixture, GetUnknownNumberTest)
{
    m_termFactory.createWrongExprTerm(5U);

    Number actualValue;
    DataStatus actualStatus =
        Expression::getNumber(m_termFactory.getDdh(),
                                           &m_context,
                                           actualValue);

    EXPECT_EQ(DataStatus::INCONSISTENT, actualStatus);
}
