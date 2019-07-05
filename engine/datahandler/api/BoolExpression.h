#ifndef POPULSSC_BOOLEXPRESSION_H
#define POPULSSC_BOOLEXPRESSION_H

/******************************************************************************
**
**   File:        BoolExpression.h
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
#include "IDataHandler.h"
#include "DataContext.h"

#include <ExpressionTermType.h>

namespace lsr
{

/**
 * Represents an expression of type Boolean
 *
 * Boolean expressions can be Guards, Indications or static Boolean values,
 * but also comparisons or nested Boolean expressions.
 *
 * @reqid SW_ENG_048
 */
class BoolExpression P_FINAL : public Expression
{
public:
    BoolExpression();

    /**
     * Initializes the object and registers data subscriptions in the @c lsr::DataHandler
     * without listener (see @c lsr::IListener).
     *
     * @param[in] pExpr    expression configuration from database.
     * @param[in] pContext data context, which shall be used for evaluation.
     */
    void setup(const lsr::ExpressionTermType* pExpr, DataContext* pContext);

    /**
     * Returns the current value.
     *
     * @param[out] value the output value.
     *
     * @return status of @c value, see @c DataStatus.
     */
    DataStatus getValue(bool& value) const;

    /**
     * Frees all resources associated with this object.
     */
    void dispose();

    virtual ~BoolExpression() P_OVERRIDE;

private:
    BoolExpression(const BoolExpression&);
    BoolExpression& operator=(const BoolExpression&);

    virtual void update() P_OVERRIDE;

    const lsr::ExpressionTermType* m_pTerm;
    DataContext* m_pContext;
    mutable bool m_value;
};

} // namespace lsr

#endif // POPULSSC_BOOLEXPRESSION_H
