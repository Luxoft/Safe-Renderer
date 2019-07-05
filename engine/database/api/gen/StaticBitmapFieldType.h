#ifndef _STATICBITMAPFIELDTYPE_H_
#define _STATICBITMAPFIELDTYPE_H_

/******************************************************************************
**
**   File:        StaticBitmapFieldType.h
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

#include "ddh_defs.h"
#include "LsrTypes.h"  // for P_STATIC_ASSERT


namespace lsr
{
struct AreaType;
struct ExpressionTermType;
struct ExpressionTermType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct StaticBitmapFieldType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the StaticBitmapFieldType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 areaOffset :16;
    U16 visibleOffset :16;
    U16 bitmapOffset :16;
    U8  PADDING1 :8;
    U8  PADDING2 :8;
    //----------------------------------------------------------------

public:

    /**
     * Returns a pointer to the area child reference.
     * Defines the area of the element relative to the upper left corner of its
     * parent
     */
    const AreaType* GetArea() const;

    /**
     * Returns a pointer to the visible child reference.
     * Controls the visibility of the element. It can make sense to have a field
     * invisible if it is also enabled because when it receives focus, it
     * becomes visible and when it loses focus, it becomes invisible again
     */
    const ExpressionTermType* GetVisible() const;

    /**
     * Returns a pointer to the bitmap child reference.
     * The locally unique ID of a bitmap in the Bitmaps Database or a more
     * complex expression
     */
    const ExpressionTermType* GetBitmap() const;
};

P_STATIC_ASSERT((sizeof(StaticBitmapFieldType)) == 8, "StaticBitmapFieldType size")


inline const AreaType* StaticBitmapFieldType::GetArea() const
{
    const AreaType* pResult = NULL;
    if (areaOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const AreaType*>(pThis + areaOffset * 4);
    }
    return pResult;
}

inline const ExpressionTermType* StaticBitmapFieldType::GetVisible() const
{
    const ExpressionTermType* pResult = NULL;
    if (visibleOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const ExpressionTermType*>(pThis + visibleOffset * 4);
    }
    return pResult;
}

inline const ExpressionTermType* StaticBitmapFieldType::GetBitmap() const
{
    const ExpressionTermType* pResult = NULL;
    if (bitmapOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const ExpressionTermType*>(pThis + bitmapOffset * 4);
    }
    return pResult;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _STATICBITMAPFIELDTYPE_H_
