#ifndef _LSR_REFERENCEBITMAPFIELDTYPE_H_
#define _LSR_REFERENCEBITMAPFIELDTYPE_H_

/******************************************************************************
**
**   File:        ReferenceBitmapFieldType.h
**   Description:
**   Generator:   c78c5138ac2e7c6506a52bfc6fbc0ef05f7ad869
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

/**
 * ReferenceBitmapFieldType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct ReferenceBitmapFieldType
{
    const U32 m_errorCounterFUDataId;
    const AreaType* const m_area;
    const ExpressionTermType* const m_visible;
    const ExpressionTermType* const m_bitmap;


    /**
     * Returns the value of the errorCounterFUDataId attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U32 GetErrorCounterFUDataId() const
    {
        return m_errorCounterFUDataId;
    }

    /**
     * Returns a pointer to the area child reference.
     * Defines the area of the element relative to the upper left corner of its parent
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const AreaType* GetArea() const
    {
        return m_area;
    }

    /**
     * Returns a pointer to the visible child reference.
     * Controls the visibility of the element. It can make sense to have a field invisible if it is also enabled because when it receives focus, it becomes visible and when it loses focus, it becomes invisible again
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const ExpressionTermType* GetVisible() const
    {
        return m_visible;
    }

    /**
     * Returns a pointer to the bitmap child reference.
     * The locally unique ID of a bitmap in the Bitmaps Database or a more complex expression
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const ExpressionTermType* GetBitmap() const
    {
        return m_bitmap;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_REFERENCEBITMAPFIELDTYPE_H_
