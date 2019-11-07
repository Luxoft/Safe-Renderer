#ifndef _LSR_STATICBITMAPFIELDTYPE_H_
#define _LSR_STATICBITMAPFIELDTYPE_H_

/******************************************************************************
**
**   File:        StaticBitmapFieldType.h
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
struct AreaType;
struct ExpressionTermType;

struct StaticBitmapFieldType
{
    const AreaType* const area;
    const ExpressionTermType* const visible;
    const ExpressionTermType* const bitmap;


    /**
     * Returns a pointer to the area child reference.
     * Defines the area of the element relative to the upper left corner of its parent
     */
    const AreaType* GetArea() const
    {
        return area;
    }

    /**
     * Returns a pointer to the visible child reference.
     * Controls the visibility of the element. It can make sense to have a field invisible if it is also enabled because when it receives focus, it becomes visible and when it loses focus, it becomes invisible again
     */
    const ExpressionTermType* GetVisible() const
    {
        return visible;
    }

    /**
     * Returns a pointer to the bitmap child reference.
     * The locally unique ID of a bitmap in the Bitmaps Database or a more complex expression
     */
    const ExpressionTermType* GetBitmap() const
    {
        return bitmap;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_STATICBITMAPFIELDTYPE_H_
