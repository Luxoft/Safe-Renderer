/******************************************************************************
**
**   File:        Expression.cpp
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

#include "Expression.h"
#include "ExpressionOperators.h"

#include <Assertion.h>
#include <LsrLimits.h>

#include <ExpressionType.h>

#include <algorithm>

namespace lsr
{
namespace
{

/**
 * NestingCounterHelper is a helper class which provides RAII idiom
 * for nesting counter variable.
 */
class NestingCounterHelper
{
public:
    /**
     * Construct the object and execute @c DataContext::increaseNesting method.
     *
     * @param[in] context reference to the context, which is owner of nesting counter
     *                    variable.
     */
    NestingCounterHelper(DataContext& context)
        : m_context(context)
    {
        m_context.increaseNesting();
    }

    /**
     * Destruct the object and execute @c DataContext::decreaseNesting method.
     */
    ~NestingCounterHelper()
    {
        m_context.decreaseNesting();
    }

private:
    DataContext& m_context;
};

} // namespace

DataStatus Expression::getNumber(const ExpressionTermType* const pTerm,
                                 DataContext* const pContext,
                                 Number& value)
{
    DataStatus status = DataStatus::INCONSISTENT;

    if ((NULL != pContext) && (MAX_EXPRESSION_NESTING > pContext->getNestingCounter()))
    {
        NestingCounterHelper nestingCounter(*pContext);

        ASSERT(NULL != pTerm);
        switch (pTerm->GetExpressionTermTypeChoice())
        {
        case ExpressionTermType::DYNAMICDATA_CHOICE:
        {
            const IDataHandler& dh = pContext->getDataHandler();
            const DynamicDataType* const pData = pTerm->GetDynamicData();

            ASSERT(NULL != pData);
            status = dh.getNumber(pData, value);
            break;
        }
        case ExpressionTermType::EXPRESSION_CHOICE:
        {
            /*
             We are not able to check pTerm->GetExpression() == NULL:
             this work will be done by @c calcNumber.
             */
            status = calcNumber(pTerm->GetExpression(), pContext, value);
            break;
        }
        case ExpressionTermType::INTEGER_CHOICE:
        {
            status = DataStatus::VALID;
            value = Number(static_cast<U32>(pTerm->GetInteger()), DATATYPE_INTEGER);
            break;
        }
        case ExpressionTermType::BOOLEAN_CHOICE:
        {
            status = DataStatus::VALID;
            value = Number(pTerm->GetBoolean());
            break;
        }
        case ExpressionTermType::BITMAPID_CHOICE:
        {
            status = DataStatus::VALID;
            value = Number(pTerm->GetBitmapId(), DATATYPE_BITMAP_ID);
            break;
        }
        default:
        {
            break;
        }
        }
    }

    return status;
}

DataStatus Expression::getBool(const ExpressionTermType* const pTerm,
                               DataContext* const pContext,
                               bool& value)
{
    Number tmpValue;
    const DataStatus status = getNumber(pTerm, pContext, tmpValue);
    value = tmpValue.getBool();
    return status;
}

DataStatus Expression::calcNumber(const ExpressionType* const pExpression,
                                  DataContext* const pContext,
                                  Number& value)
{
    DataStatus status = DataStatus::INCONSISTENT;

    ASSERT(NULL != pExpression);
    switch (pExpression->GetOperator())
    {
    case EXPRESSION_OPERATOR_MIN_MAX:
    {
        status = expressionoperators::minMax(pExpression,
                                             pContext,
                                             value);
        break;
    }
    case EXPRESSION_OPERATOR_EQUALS:
    {
        status = expressionoperators::equals(pExpression,
                                             pContext,
                                             value);
        break;
    }
    case EXPRESSION_OPERATOR_NOT_EQUALS:
    {
        status = expressionoperators::notEquals(pExpression,
                                                pContext,
                                                value);
        break;
    }
    case EXPRESSION_OPERATOR_LESS:
    {
        status = expressionoperators::lessThan(pExpression,
                                               pContext,
                                               value);
        break;
    }
    case EXPRESSION_OPERATOR_LESS_EQUALS:
    {
        status = expressionoperators::lessThanOrEquals(pExpression,
                                                       pContext,
                                                       value);
        break;
    }
    case EXPRESSION_OPERATOR_GREATER:
    {
        status = expressionoperators::greaterThan(pExpression,
                                                  pContext,
                                                  value);
        break;
    }
    case EXPRESSION_OPERATOR_GREATER_EQUALS:
    {
        status = expressionoperators::greaterThanOrEquals(pExpression,
                                                          pContext,
                                                          value);
        break;
    }
    case EXPRESSION_OPERATOR_ITEM_AT:
    {
        status = expressionoperators::itemAt(pExpression,
                                             pContext,
                                             value);
        break;
    }
    case EXPRESSION_OPERATOR_AND:
    {
        status = expressionoperators::booleanAnd(pExpression,
                                                 pContext,
                                                 value);
        break;
    }
    case EXPRESSION_OPERATOR_OR:
    {
        status = expressionoperators::booleanOr(pExpression,
                                                pContext,
                                                value);
        break;
    }
    case EXPRESSION_OPERATOR_NOT:
    {
        status = expressionoperators::booleanNot(pExpression,
                                                 pContext,
                                                 value);
        break;
    }
    case EXPRESSION_OPERATOR_REDUNDANCY:
    {
        status = expressionoperators::redundancy(pExpression,
                                                pContext,
                                                value);
        break;
    }
    case EXPRESSION_OPERATOR_FALLBACK:
    {
        status = expressionoperators::fallback(pExpression,
                                               pContext,
                                               value);
        break;
    }
    case EXPRESSION_OPERATOR_FALLBACK2:
    {
        status = expressionoperators::fallback2(pExpression,
                                                pContext,
                                                value);
        break;
    }
    case EXPRESSION_OPERATOR_FALLBACK3:
    {
        status = expressionoperators::fallback3(pExpression,
                                                pContext,
                                                value);
        break;
    }
    default:
    {
        break;
    }
    }

    return status;
}

} // namespace lsr
