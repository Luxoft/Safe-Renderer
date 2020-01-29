#ifndef LUXOFTSAFERENDERER_NUMBEREXPRESSION_H
#define LUXOFTSAFERENDERER_NUMBEREXPRESSION_H

/******************************************************************************
**
**   File:        NumberExpression.h
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
#include "DataContext.h"

#include <ExpressionTermType.h>

namespace lsr
{

/**
 * Represents an expression of type @c Number.
 *
 * Number expressions can get dynamic data, constants or calculate nested expressions.
 *
 * @reqid SW_ENG_064
 */
class NumberExpression: public Expression
{
public:
    NumberExpression();
    virtual ~NumberExpression() P_OVERRIDE;
    //NumberExpression(const NumberExpression&);  Base class NonCopyable hides copy constructor
    //NumberExpression& operator=(const NumberExpression&);  Base class NonCopyable hides assignment operator

    /**
     * Initializes the object and registers data subscriptions if needed.
     *
     * @param[in] pTerm     expression configuration from database.
     * @param[in] pContext  data context, which shall be used for evaluation.
     */
    void setup(const ExpressionTermType* const pTerm, DataContext* const pContext);

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
    const ExpressionTermType* m_pTerm;
    DataContext* m_pContext;
    mutable Number m_value;
    mutable DataStatus m_status;
};

} // namespace lsr


#endif // LUXOFTSAFERENDERER_NUMBEREXPRESSION_H
