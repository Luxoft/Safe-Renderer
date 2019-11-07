#ifndef LUXOFTSAFERENDERER_EXPRESSION_H
#define LUXOFTSAFERENDERER_EXPRESSION_H

/******************************************************************************
**
**   File:        Expression.h
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

#include "IDataHandler.h"
#include "DataContext.h"
#include "Number.h"
#include "DataStatus.h"

#include <ExpressionTermType.h>

namespace lsr
{

/**
 * Expression provides functionality for getting value which can be stored inside @c DataHandler
 * or can be calculated with nested expressions.
 *
 * Expressions are configured by @c lsr::ExpressionTermType objects,
 * which are stored inside database. With these objects @c Expression understands
 * where value is stored, what the type of value is, how it can be calculated, etc.
 *
 * Most of the @c Expression methods are static, which provides evaluating nested expressions.
 *
 * Also, Expressions provide functionality for subscription to data changes.
 * If data was changed inside the @c DataHandler, the @c IDataHandler::IListener will be notified
 * with reference to @c Expression object, with this changed data.
 *
 * @reqid SW_ENG_048, SW_ENG_049, SW_ENG_051, SW_ENG_053, SW_ENG_064
 */
class Expression
{
public:
    /**
     * Evaluates the given expression as a Boolean value
     *
     * @param[in]  pTerm    lsr expression configuration
     * @param[in]  pContext data context, which shall be used for evaluation.
     * @param[out] value    the output value.
     *
     * @return status of @c value, see @c DataStatus.
     */
    static DataStatus getBool(const lsr::ExpressionTermType* const pTerm,
                              DataContext* const pContext,
                              bool& value);

    /**
     * Evaluates the given expression as a numerical value
     *
     * @param[in]  pTerm    lsr expression configuration
     * @param[in]  pContext data context, which shall be used for evaluation.
     * @param[out] value    the output value.
     *
     * @return status of @c value, see @c DataStatus.
     */
    static DataStatus getNumber(const lsr::ExpressionTermType* const pTerm,
                                DataContext* const pContext,
                                Number& value);

    virtual ~Expression() {}

protected:
    Expression() {}

private:
    /**
     * Calculates new value of the expression, according to its operation type.
     *
     * @param[in]  pExpression pointer to @c lsr::ExpressionType object.
     *                         It is the owner of objects, that need to be handled.
     * @param[in]  pContext    data context, which shall be used for evaluation.
     * @param[out] value       the output value. It will contain the result of operation.
     *
     * @return status of @c value, see @c DataStatus.
     */
    static DataStatus calcNumber(const lsr::ExpressionType* const pExpression,
                                 DataContext* const pContext,
                                 Number& value);
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_EXPRESSION_H
