#ifndef POPULUSSC_NUMBEREXPRESSION_H
#define POPULUSSC_NUMBEREXPRESSION_H

/******************************************************************************
**
**   File:        NumberExpression.h
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

#include "Expression.h"
#include "DataContext.h"

#include <ExpressionTermType.h>

namespace psc
{

/**
 * Represents an expression of type @c Number.
 *
 * Number expressions can get dynamic data, constants or calculate nested expressions.
 *
 * @reqid SW_ENG_051
 */
class NumberExpression: public Expression
{
public:
    NumberExpression();
    virtual ~NumberExpression() P_OVERRIDE;

    /**
     * Initializes the object and registers data subscriptions if needed.
     *
     * @param[in] pExpr     expression configuration from database.
     * @param[in] pContext  data context, which shall be used for evaluation.
     * @param[in] pListener an optional listener object that shall be notified for
     *                      data changes. This notification will be evaluated even if
     *                      current value is incorrect.
     */
    void setup(const ExpressionTermType* pExpr,
               DataContext* pContext,
               Expression::IListener* pListener);

    /**
     * Returns the current value.
     *
     * @param[out] value the output value.
     *
     * @return status of @c value, see @c DataStatus.
     */
    DataStatus getValue(Number& value) const;

    /**
     * Frees all resources associated with this object (e.g. subscription listeners)
     */
    void dispose();

private:
    NumberExpression(const NumberExpression&);
    NumberExpression& operator=(const NumberExpression&);

    virtual void update() P_OVERRIDE;

    const ExpressionTermType* m_pTerm;
    Expression::IListener* m_pListener;
    DataContext* m_pContext;
    mutable Number m_value;
    mutable DataStatus m_status;
};

} // namespace psc


#endif // POPULUSSC_NUMBEREXPRESSION_H
