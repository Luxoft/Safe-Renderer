/******************************************************************************
**
**   File:        BoolExpressionTest.cpp
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
#include <BoolExpression.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace lsr;


TEST_F(ExpressionTestFixture, BoolExprGetValueTest)
{
    ExpressionTermType term = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };

    BoolExpression expr;
    expr.setup(&term, &m_context);

    bool actualValue = false;
    EXPECT_EQ(DataStatus::VALID, expr.getValue(actualValue));

    EXPECT_TRUE(actualValue);
}

TEST_F(ExpressionTestFixture, BoolExprGetValueWithWrongValueTest)
{
    ExpressionTermType term = { ExpressionTermType::NONE, 55U, NULL };

    BoolExpression expr;
    expr.setup(&term, &m_context);

    bool actualValue = false;
    EXPECT_EQ(DataStatus::INCONSISTENT, expr.getValue(actualValue));
}
