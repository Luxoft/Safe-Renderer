#ifndef _LSR_STATICBITMAPFIELDTYPE_H_
#define _LSR_STATICBITMAPFIELDTYPE_H_

/******************************************************************************
**
**   File:        StaticBitmapFieldType.h
**   Description:
**   Generator:   7db08a476f8107a993e0bf7183b0cf60031dad3e
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "ddh_defs.h"

namespace lsr
{

/**
 * StaticBitmapFieldType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct StaticBitmapFieldType
{
    const AreaType* const m_area;
    const ExpressionTermType* const m_visible;
    const ExpressionTermType* const m_bitmap;


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

#endif // #ifndef _LSR_STATICBITMAPFIELDTYPE_H_
