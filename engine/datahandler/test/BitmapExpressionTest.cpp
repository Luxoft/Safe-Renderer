/******************************************************************************
**
**   File:        BitmapExpressionTest.cpp
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
#include <BitmapExpression.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;

TEST_F(ExpressionTestFixture, BitmapExprGetValueTest)
{
    const lsr::DynamicData expected(0xAABB, 0xBBAA);

    lsr::DynamicDataType dataType = { expected.getCombined(), lsr::DATATYPE_INTEGER };
    lsr::ExpressionTermType term = { lsr::ExpressionTermType::DYNAMICDATA_CHOICE, 0, &dataType };

    const lsr::BitmapId expectedId = 5U;
    const lsr::Number expectedValue(static_cast<U32>(expectedId), lsr::DATATYPE_INTEGER);

    m_dataHandler.setNumber(expectedValue);

    lsr::BitmapExpression expr;
    expr.setup(&term, &m_context);

    lsr::BitmapId actualId;
    EXPECT_EQ(lsr::DataStatus::VALID, expr.getValue(actualId));
    EXPECT_EQ(expectedId, actualId);

    // Let's check that the request to datahandler was correct.
    EXPECT_EQ(expected.getFUClassId(), m_dataHandler.getLastFuId());
    EXPECT_EQ(expected.getDataId(), m_dataHandler.getLastDataId());
}

TEST_F(ExpressionTestFixture, BitmapExprGetValueFailedTest)
{
    lsr::ExpressionTermType term = { lsr::ExpressionTermType::NONE, 55U, NULL };

    lsr::BitmapExpression expr;
    expr.setup(&term, &m_context);

    lsr::BitmapId actualId;
    EXPECT_EQ(lsr::DataStatus::INCONSISTENT, expr.getValue(actualId));
}
