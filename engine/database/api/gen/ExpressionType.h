#ifndef _LSR_EXPRESSIONTYPE_H_
#define _LSR_EXPRESSIONTYPE_H_

/******************************************************************************
**
**   File:        ExpressionType.h
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

#include "ddh_defs.h"

namespace lsr
{
struct ExpressionTermType;

struct ExpressionType
{
    const ExpressionOperatorEnumeration _operator;
    const ExpressionTermType* const *term;
    const U16 termCount;


    /**
     * Returns the value of the operator attribute
     */
    ExpressionOperatorEnumeration GetOperator() const
    {
        return _operator;
    }

    /**
     * Returns the number of term elements.
     */
    U16 GetTermCount() const
    {
        return termCount;
    }

    /**
     * Returns a pointer to the term child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    const ExpressionTermType* GetTerm(const U16 i) const
    {
        return (i < termCount) ? term[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_EXPRESSIONTYPE_H_
