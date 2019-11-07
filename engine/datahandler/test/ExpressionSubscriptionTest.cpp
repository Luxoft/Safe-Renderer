/******************************************************************************
**
**   File:        ExpressionSubscriptionTest.cpp
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

#include <Expression.h>
#include <IDataHandler.h>

#include <DynamicDataType.h>
#include <ExpressionType.h>
#include <LsrLimits.h>

#include <gtest/gtest.h>

using namespace lsr;

using ::testing::_;
using ::testing::Return;
using ::testing::Ref;
using ::testing::TypedEq;

class DummyExpression: public Expression
{
public:
    DummyExpression() {}
};

namespace infinite
{
    const DynamicDataType dynamicData = { ((13U << 16U | 52U)), DATATYPE_INTEGER };
    const ExpressionTermType tdyn = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dynamicData };

    const ExpressionTermType* para11[] = { &tdyn, &tdyn, };
    const ExpressionType e11 = { EXPRESSION_OPERATOR_EQUALS, para11, 2U };
    const ExpressionTermType te11 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e11 };

    const ExpressionTermType* para10[] = { &tdyn, &te11, };
    const ExpressionType e10 = { EXPRESSION_OPERATOR_EQUALS, para10, 2U };
    const ExpressionTermType te10 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e10 };

    const ExpressionTermType* para9[] = { &tdyn, &te10, };
    const ExpressionType e9 = { EXPRESSION_OPERATOR_EQUALS, para9, 2U };
    const ExpressionTermType te9 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e9 };

    const ExpressionTermType* para8[] = { &tdyn, &te9, };
    const ExpressionType e8 = { EXPRESSION_OPERATOR_EQUALS, para8, 2U };
    const ExpressionTermType te8 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e8 };

    const ExpressionTermType* para7[] = { &tdyn, &te8, };
    const ExpressionType e7 = { EXPRESSION_OPERATOR_EQUALS, para7, 2U };
    const ExpressionTermType te7 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e7 };

    const ExpressionTermType* para6[] = { &tdyn, &te7, };
    const ExpressionType e6 = { EXPRESSION_OPERATOR_EQUALS, para6, 2U };
    const ExpressionTermType te6 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e6 };

    const ExpressionTermType* para5[] = { &tdyn, &te6, };
    const ExpressionType e5 = { EXPRESSION_OPERATOR_EQUALS, para5, 2U };
    const ExpressionTermType te5 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e5 };

    const ExpressionTermType* para4[] = { &tdyn, &te5, };
    const ExpressionType e4 = { EXPRESSION_OPERATOR_EQUALS, para4, 2U };
    const ExpressionTermType te4 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e4 };

    const ExpressionTermType* para3[] = { &tdyn, &te4, };
    const ExpressionType e3 = { EXPRESSION_OPERATOR_EQUALS, para3, 2U };
    const ExpressionTermType te3 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e3 };

    const ExpressionTermType* para2[] = { &tdyn, &te3, };
    const ExpressionType e2 = { EXPRESSION_OPERATOR_EQUALS, para2, 2U };
    const ExpressionTermType te2 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e2 };

    const ExpressionTermType* para1[] = { &tdyn, &te2, };
    const ExpressionType e1 = { EXPRESSION_OPERATOR_EQUALS, para1, 2U };
    const ExpressionTermType te1 = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &e1 };

    const ExpressionTermType* parameters[] = { &tdyn, &te1, };
    const ExpressionType exp = { EXPRESSION_OPERATOR_EQUALS, parameters, 2U };
    const ExpressionTermType term = { ExpressionTermType::EXPRESSION_CHOICE, 0U, &exp };
}
