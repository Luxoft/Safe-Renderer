#ifndef POPULSSC_BOOLEXPRESSION_H
#define POPULSSC_BOOLEXPRESSION_H

/******************************************************************************
**
**   File:        BoolExpression.h
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
#include "IDataHandler.h"
#include "DataContext.h"

#include <ExpressionTermType.h>

namespace psc
{

/**
 * Represents an expression of type Boolean
 *
 * Boolean expressions can be Guards, Indications or static Boolean values,
 * but also comparisons or nested Boolean expressions.
 *
 * @reqid SW_ENG_051
 */
class BoolExpression P_FINAL : public Expression
{
public:
    BoolExpression();

    /**
     * Initializes the object and registers data subscriptions in the @c psc::DataHandler
     * without listener (see @c psc::IListener).
     *
     * @param[in] pExpr    expression configuration from database.
     * @param[in] pContext data context, which shall be used for evaluation.
     */
    void setup(const psc::ExpressionTermType* pExpr, DataContext* pContext);

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

    const psc::ExpressionTermType* m_pTerm;
    DataContext* m_pContext;
    mutable bool m_value;
};

} // namespace psc

#endif // POPULSSC_BOOLEXPRESSION_H
