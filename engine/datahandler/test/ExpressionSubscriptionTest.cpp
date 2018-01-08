/******************************************************************************
**
**   File:        ExpressionSubscriptionTest.cpp
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
#include <IDataHandler.h>

#include <DynamicDataType.h>

#include <gtest/gtest.h>

using namespace psc;

using ::testing::_;
using ::testing::Return;
using ::testing::Ref;
using ::testing::TypedEq;

class DummyExpression: public Expression
{
public:
    DummyExpression()
    {}

    void proxySubscribe(const ExpressionTermType* pTerm,
                        DataContext* dataContex,
                        IDataHandler::IListener* pListener)
    {
        Expression::subscribe(pTerm,
                                           dataContex,
                                           pListener);
    }

    void proxyUnsubscribe(const ExpressionTermType* pTerm,
                          DataContext* dataContex,
                          IDataHandler::IListener* pListener)
    {
        Expression::unsubscribe(pTerm,
                                             dataContex,
                                             pListener);
    }

private:
    virtual void update() P_OVERRIDE
    {}
};

TEST_F(ExpressionTestFixture, SubscribeDynamicDataTest)
{
    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    m_termFactory.createDynamicDataExprTerm(dataType);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, subscribeData(dataType.fUClassId,
                                             dataType.dataId,
                                             static_cast<IDataHandler::IListener*>(&expr)))
        .WillOnce(Return(true));

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeIntegerTest)
{
    m_termFactory.createIntegerExprTerm(5U);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeBoolTest)
{
    m_termFactory.createBoolExprTerm(true);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeExpressionTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(dataType);

    ExpressionTermTypeFactory term2;
    term2.createDynamicDataExprTerm(dataType);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, subscribeData(dataType.GetFUClassId(),
                                             dataType.GetDataId(),
                                             static_cast<IDataHandler::IListener*>(&expr)))
        .Times(2)
        .WillRepeatedly(Return(true));

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeInfiniteExpressionTest)
{
    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    ExpressionTypeFactory exprFactory;
    exprFactory.createInfiniteExpr(dataType);
    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, subscribeData(dataType.GetFUClassId(),
                                             dataType.GetDataId(),
                                             static_cast<IDataHandler::IListener*>(&expr)))
        .Times(MAX_EXPRESSION_NESTING - 1)
        .WillRepeatedly(Return(true));

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeIndicationTest)
{
    DynamicIndicationIdType type;
    type.fUClassId = 45U;
    type.indicationId = 25U;

    m_termFactory.createIndicationExprTerm(type);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, subscribeIndication(type.GetFUClassId(),
                                                   type.GetIndicationId(),
                                                   static_cast<IDataHandler::IListener*>(&expr)))
        .WillOnce(Return(true));

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeIndicationWithoutListenerTest)
{
    DynamicIndicationIdType type;
    m_termFactory.createIndicationExprTerm(type);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, NULL);
}

TEST_F(ExpressionTestFixture, SubscribeIndicationWithWrongHandlerTest)
{
    DynamicIndicationIdType type;
    m_termFactory.createIndicationExprTerm(type);

    DummyExpression expr;

    corruptHandler();

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeWrongDataTest)
{
    m_termFactory.createWrongExprTerm(5U);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeWithWrongContextTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxySubscribe(m_termFactory.getDdh(), NULL, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeWithWrongDataHandlerTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    DummyExpression expr;

    corruptHandler();

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, SubscribeWithWrongTermTest)
{
    m_termFactory.createWrongExprTerm(5U);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxySubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeDynamicDataTest)
{
    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;
    m_termFactory.createDynamicDataExprTerm(dataType);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(dataType.GetFUClassId(),
                                               dataType.GetDataId(),
                                               static_cast<IDataHandler::IListener*>(&expr)))
        .Times(1);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeExpressionTest)
{
    ExpressionTypeFactory exprFactory;
    exprFactory.createExpr(EXPRESSION_OPERATOR_EQUALS, 2U);

    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    ExpressionTermTypeFactory term1;
    term1.createDynamicDataExprTerm(dataType);

    ExpressionTermTypeFactory term2;
    term2.createDynamicDataExprTerm(dataType);

    exprFactory.addExprTerm(term1.getDdh(), term1.getSize());
    exprFactory.addExprTerm(term2.getDdh(), term2.getSize());

    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(dataType.GetFUClassId(),
                                               dataType.GetDataId(),
                                               static_cast<IDataHandler::IListener*>(&expr)))
        .Times(2);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeInfiniteExpressionTest)
{
    DynamicDataType dataType;
    dataType.fUClassId = 13U;
    dataType.dataId = 52U;

    ExpressionTypeFactory exprFactory;
    exprFactory.createInfiniteExpr(dataType);
    m_termFactory.createExpressionExprTerm(exprFactory.getDdh(), exprFactory.getSize());

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(dataType.GetFUClassId(),
                                               dataType.GetDataId(),
                                               static_cast<IDataHandler::IListener*>(&expr)))
        .Times(MAX_EXPRESSION_NESTING - 1);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeIndicationTest)
{
    DynamicIndicationIdType type;
    type.fUClassId = 32U;
    type.indicationId = 26U;

    m_termFactory.createIndicationExprTerm(type);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeIndication(type.GetFUClassId(),
                                                     type.GetIndicationId(),
                                                     static_cast<IDataHandler::IListener*>(&expr)))
        .Times(1);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeIndicationWithoutListenerTest)
{
    DynamicIndicationIdType type;
    m_termFactory.createIndicationExprTerm(type);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, NULL);
}

TEST_F(ExpressionTestFixture, UnsubscribeIndicationWithWrongContextTest)
{
    DynamicIndicationIdType type;
    m_termFactory.createIndicationExprTerm(type);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), NULL, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeIndicationWithWrongHandlerTest)
{
    DynamicIndicationIdType type;
    m_termFactory.createIndicationExprTerm(type);

    DummyExpression expr;

    corruptHandler();

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeIntegerTest)
{
    m_termFactory.createIntegerExprTerm(5U);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeBoolTest)
{
    m_termFactory.createBoolExprTerm(true);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeWrongDataTest)
{
    m_termFactory.createWrongExprTerm(5U);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeWithWrongDataHandlerTest)
{
    DynamicDataType dataType;
    m_termFactory.createDynamicDataExprTerm(dataType);

    DummyExpression expr;

    corruptHandler();

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}

TEST_F(ExpressionTestFixture, UnsubscribeWithWrongTermTest)
{
    m_termFactory.createWrongExprTerm(5U);

    DummyExpression expr;

    EXPECT_CALL(m_dataHandler, unsubscribeData(_, _, _))
        .Times(0);
    EXPECT_CALL(m_dataHandler, unsubscribeIndication(_, _, _))
        .Times(0);

    expr.proxyUnsubscribe(m_termFactory.getDdh(), &m_context, &expr);
}
