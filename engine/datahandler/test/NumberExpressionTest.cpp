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

#include "MockListener.h"
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
    FUClassId expectedFuId = 0xAABB;
    DataId expectedDataId = 0xBBAA;

    DynamicDataType dataType;
    dataType.fUClassId = expectedFuId;
    dataType.dataId = expectedDataId;

    m_termFactory.createDynamicDataExprTerm(dataType);

    const Number expectedValue(5U, DATATYPE_INTEGER);

    m_dataHandler.setNumber(expectedValue);

    NumberExpression expr;
    expr.setup(m_termFactory.getDdh(), &m_context, NULL);

    Number actualValue;
    EXPECT_EQ(DataStatus::VALID, expr.getValue(actualValue));
    EXPECT_EQ(expectedValue, actualValue);

    // Let's check that the request to lsr was correct.
    EXPECT_EQ(expectedFuId, m_dataHandler.getLastFuId());
    EXPECT_EQ(expectedDataId, m_dataHandler.getLastDataId());
}

TEST_F(ExpressionTestFixture, NumberExprGetValueWithListenerTest)
{
    FUClassId expectedFuId = 0xAABB;
    DataId expectedDataId = 0xBBAA;

    DynamicDataType dataType;
    dataType.fUClassId = expectedFuId;
    dataType.dataId = expectedDataId;

    m_termFactory.createDynamicDataExprTerm(dataType);

    const Number expectedValue(5U, DATATYPE_INTEGER);
    m_dataHandler.setNumber(expectedValue);

    NumberExpression expr;
    MockListener listener;
    expr.setup(m_termFactory.getDdh(), &m_context, &listener);

    // As there is listener, there will be no request to lsr about new value
    Number actualValue;
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, expr.getValue(actualValue));
    EXPECT_NE(expectedValue.getU32(), actualValue.getU32());

    // emit signal about updated value
    IDataHandler::IListener* changeListener = &expr;
    changeListener->onDataChange();

    // Lets check the request to lsr was correct.
    EXPECT_EQ(expectedFuId, m_dataHandler.getLastFuId());
    EXPECT_EQ(expectedDataId, m_dataHandler.getLastDataId());

    // value should be updated
    EXPECT_EQ(DataStatus::VALID, expr.getValue(actualValue));
    EXPECT_EQ(expectedValue, actualValue);
}

TEST_F(ExpressionTestFixture, NumberExprGetValueFailedTest)
{
    m_termFactory.createWrongExprTerm(55U);

    NumberExpression expr;
    expr.setup(m_termFactory.getDdh(), &m_context, NULL);

    Number actualValue;
    EXPECT_EQ(DataStatus::INCONSISTENT, expr.getValue(actualValue));
}

TEST_F(ExpressionTestFixture, NumberExprSubscriptionTest)
{
    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    m_termFactory.createDynamicDataExprTerm(dataType);

    MockListener listener;
    NumberExpression expr;

    EXPECT_CALL(m_dataHandler, subscribeData(dataType.GetFUClassId(),
                                             dataType.GetDataId(),
                                             static_cast<IDataHandler::IListener*>(&expr)))
        .WillOnce(Return(true));

    // Here should be subscription
    expr.setup(m_termFactory.getDdh(), &m_context, &listener);
}

TEST_F(ExpressionTestFixture, NumberExprUnsubscriptionTest)
{
    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    m_termFactory.createDynamicDataExprTerm(dataType);

    MockListener listener;
    NumberExpression expr;

    expr.setup(m_termFactory.getDdh(), &m_context, &listener);

    EXPECT_CALL(m_dataHandler, unsubscribeData(dataType.GetFUClassId(),
                                               dataType.GetDataId(),
                                               static_cast<IDataHandler::IListener*>(&expr)))
        .Times(1);

    // Here should be unsubscription
    expr.dispose();
}

TEST_F(ExpressionTestFixture, NumberExprNotificationTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    MockListener listener;
    NumberExpression expr;

    expr.setup(m_termFactory.getDdh(), &m_context, &listener);

    EXPECT_CALL(listener, notifyDataChange(_))
        .Times(1);

    // Here should be notification
    IDataHandler::IListener* changeListener = &expr;
    changeListener->onDataChange();
}

TEST_F(ExpressionTestFixture, NumberExprNotificationTestWithoutListener)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    MockListener listener;
    NumberExpression expr;

    expr.setup(m_termFactory.getDdh(), &m_context, NULL);

    EXPECT_CALL(listener, notifyDataChange(_))
        .Times(0);

    // Here should be no notification
    IDataHandler::IListener* changeListener = &expr;
    changeListener->onDataChange();
}
