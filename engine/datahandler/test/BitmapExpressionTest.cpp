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

#include "ExpressionTermTypeFactory.h"
#include "MockListener.h"
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
    const FUClassId expectedFuId = 0xAABB;
    const DataId expectedDataId = 0xBBAA;

    lsr::DynamicDataType dataType;
    dataType.fUClassId = expectedFuId;
    dataType.dataId = expectedDataId;

    m_termFactory.createDynamicDataExprTerm(dataType);

    const lsr::BitmapId expectedId = 5U;
    const lsr::Number expectedValue(static_cast<U32>(expectedId), lsr::DATATYPE_INTEGER);

    m_dataHandler.setNumber(expectedValue);

    lsr::BitmapExpression expr;
    expr.setup(m_termFactory.getDdh(), &m_context, NULL);

    lsr::BitmapId actualId;
    EXPECT_EQ(lsr::DataStatus::VALID, expr.getValue(actualId));
    EXPECT_EQ(expectedId, actualId);

    // Let's check that the request to datahandler was correct.
    EXPECT_EQ(expectedFuId, m_dataHandler.getLastFuId());
    EXPECT_EQ(expectedDataId, m_dataHandler.getLastDataId());
}

TEST_F(ExpressionTestFixture, BitmapExprGetValueWithListenerTest)
{
    const FUClassId expectedFuId = 0xAABB;
    const DataId expectedDataId = 0xBBAA;

    lsr::DynamicDataType dataType;
    dataType.fUClassId = expectedFuId;
    dataType.dataId = expectedDataId;

    m_termFactory.createDynamicDataExprTerm(dataType);

    const lsr::BitmapId expectedId = 5U;
    const lsr::Number expectedValue(static_cast<U32>(expectedId), lsr::DATATYPE_INTEGER);
    m_dataHandler.setNumber(expectedValue);

    lsr::BitmapExpression expr;
    MockListener listener;
    expr.setup(m_termFactory.getDdh(), &m_context, &listener);

    // As there is listener, there will be no request to datahandler about new value
    lsr::BitmapId actualId = expectedId * 2; //to get some value differ to expectedId
    EXPECT_EQ(lsr::DataStatus::NOT_AVAILABLE, expr.getValue(actualId));
    EXPECT_NE(expectedId, actualId);

    // emit signal about updated value
    lsr::IDataHandler::IListener* changeListener = &expr;
    changeListener->onDataChange();

    // Lets check the request to datahandler was correct.
    EXPECT_EQ(expectedFuId, m_dataHandler.getLastFuId());
    EXPECT_EQ(expectedDataId, m_dataHandler.getLastDataId());

    // value should be updated
    EXPECT_EQ(lsr::DataStatus::VALID, expr.getValue(actualId));
    EXPECT_EQ(expectedId, actualId);
}

TEST_F(ExpressionTestFixture, BitmapExprGetValueFailedTest)
{
    m_termFactory.createWrongExprTerm(55U);

    lsr::BitmapExpression expr;
    expr.setup(m_termFactory.getDdh(), &m_context, NULL);

    lsr::BitmapId actualId;
    EXPECT_EQ(lsr::DataStatus::INCONSISTENT, expr.getValue(actualId));
}

TEST_F(ExpressionTestFixture, BitmapExprSubscriptionTest)
{
    lsr::DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    m_termFactory.createDynamicDataExprTerm(dataType);

    MockListener listener;
    lsr::BitmapExpression expr;

    EXPECT_CALL(m_dataHandler, subscribeData(dataType.GetFUClassId(),
                                             dataType.GetDataId(),
                                             static_cast<lsr::IDataHandler::IListener*>(&expr)))
        .WillOnce(Return(true));

    // Here should be subscription
    expr.setup(m_termFactory.getDdh(), &m_context, &listener);
}

TEST_F(ExpressionTestFixture, BitmapExprUnsubscriptionTest)
{
    lsr::DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    m_termFactory.createDynamicDataExprTerm(dataType);

    MockListener listener;
    lsr::BitmapExpression expr;

    expr.setup(m_termFactory.getDdh(), &m_context, &listener);

    EXPECT_CALL(m_dataHandler, unsubscribeData(dataType.GetFUClassId(),
                                               dataType.GetDataId(),
                                               static_cast<lsr::IDataHandler::IListener*>(&expr)))
        .Times(1);

    // Here should be unsubscription
    expr.dispose();
}

TEST_F(ExpressionTestFixture, BitmapExprNotificationTest)
{
    lsr::DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    MockListener listener;
    lsr::BitmapExpression expr;

    expr.setup(m_termFactory.getDdh(), &m_context, &listener);

    EXPECT_CALL(listener, notifyDataChange(_))
        .Times(1);

    // Here should be notification
    lsr::IDataHandler::IListener* changeListener = &expr;
    changeListener->onDataChange();
}

TEST_F(ExpressionTestFixture, BitmapExprNotificationTestWithoutListener)
{
    lsr::DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    MockListener listener;
    lsr::BitmapExpression expr;

    expr.setup(m_termFactory.getDdh(), &m_context, NULL);

    EXPECT_CALL(listener, notifyDataChange(_))
        .Times(0);

    // Here should be no notification
    lsr::IDataHandler::IListener* changeListener = &expr;
    changeListener->onDataChange();
}
