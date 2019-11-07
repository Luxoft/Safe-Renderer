/******************************************************************************
**
**   File:        NumberExpressionTest.cpp
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

#include "MockDataHandler.h"
#include "ExpressionTestFixture.h"

#include <IDataHandler.h>
#include <NumberExpression.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace lsr;

using ::testing::_;
using ::testing::Return;

TEST_F(ExpressionTestFixture, NumberExprGetValueTest)
{
    const DynamicData expected(0xAABB, 0xBBAA);

    const DynamicDataType dataType = { expected.getCombined(), DATATYPE_INTEGER };
    const ExpressionTermType term = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };

    const Number expectedValue(5U, DATATYPE_INTEGER);

    m_dataHandler.setNumber(expectedValue);

    NumberExpression expr;
    expr.setup(&term, &m_context);

    Number actualValue;
    EXPECT_EQ(DataStatus::VALID, expr.getValue(actualValue));
    EXPECT_EQ(expectedValue, actualValue);

    // Let's check that the request to lsr was correct.
    EXPECT_EQ(expected.getFUClassId(), m_dataHandler.getLastFuId());
    EXPECT_EQ(expected.getDataId(), m_dataHandler.getLastDataId());
}

TEST_F(ExpressionTestFixture, NumberExprGetValueFailedTest)
{
    const ExpressionTermType term = { ExpressionTermType::NONE, 55U, NULL };

    NumberExpression expr;
    expr.setup(&term, &m_context);

    Number actualValue;
    EXPECT_EQ(DataStatus::INCONSISTENT, expr.getValue(actualValue));
}
