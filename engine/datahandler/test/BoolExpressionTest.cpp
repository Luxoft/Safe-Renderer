/******************************************************************************
**
**   File:        BoolExpressionTest.cpp
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

#include "MockListener.h"
#include "MockDataHandler.h"
#include "ExpressionTestFixture.h"

#include <IDataHandler.h>
#include <BoolExpression.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace psc;


TEST_F(ExpressionTestFixture, BoolExprGetValueTest)
{
    bool expectedValue = true;
    m_termFactory.createBoolExprTerm(expectedValue);

    BoolExpression expr;
    expr.setup(m_termFactory.getDdh(), &m_context);

    bool actualValue = false;
    EXPECT_EQ(DataStatus::VALID, expr.getValue(actualValue));

    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, BoolExprGetValueWithWrongValueTest)
{
    m_termFactory.createWrongExprTerm(55U);

    BoolExpression expr;
    expr.setup(m_termFactory.getDdh(), &m_context);

    bool actualValue = false;
    EXPECT_EQ(DataStatus::INCONSISTENT, expr.getValue(actualValue));
}

TEST_F(ExpressionTestFixture, BoolExprSubscriptionTest)
{
    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    m_termFactory.createDynamicDataExprTerm(dataType);

    BoolExpression expr;

    EXPECT_CALL(m_dataHandler, subscribeData(dataType.GetFUClassId(),
                                             dataType.GetDataId(),
                                             NULL))
        .Times(1);

    expr.setup(m_termFactory.getDdh(), &m_context);
}

TEST_F(ExpressionTestFixture, BoolExprUnsubscriptionTest)
{
    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    m_termFactory.createDynamicDataExprTerm(dataType);

    BoolExpression expr;
    expr.setup(m_termFactory.getDdh(), &m_context);

    EXPECT_CALL(m_dataHandler, unsubscribeData(dataType.GetFUClassId(),
                                               dataType.GetDataId(),
                                               NULL))
        .Times(1);

    expr.dispose();
}

// To fill gap of code coverage
TEST_F(ExpressionTestFixture, BoolExprNotificationTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    BoolExpression expr;
    expr.setup(m_termFactory.getDdh(), &m_context);

    // Here should be notification
    IDataHandler::IListener* changeListener = &expr;
    changeListener->onDataChange();
}
