#ifndef _REFERENCEBITMAPFIELDTYPE_H_
#define _REFERENCEBITMAPFIELDTYPE_H_

/******************************************************************************
**
**   File:        ReferenceBitmapFieldType.h
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

struct ReferenceBitmapFieldType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the ReferenceBitmapFieldType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 errorCounter :16;
    U16 areaOffset :16;
    U16 visibleOffset :16;
    U16 bitmapOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the errorCounter attribute
     */
    U16 GetErrorCounter() const;

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

P_STATIC_ASSERT((sizeof(ReferenceBitmapFieldType)) == 8, "ReferenceBitmapFieldType size")


inline U16 ReferenceBitmapFieldType::GetErrorCounter() const
{
    return errorCounter;
}

inline const AreaType* ReferenceBitmapFieldType::GetArea() const
{
    const AreaType* pResult = NULL;
    if (areaOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const AreaType*>(pThis + areaOffset * 4);
    }
    return pResult;
}

inline const ExpressionTermType* ReferenceBitmapFieldType::GetVisible() const
{
    const ExpressionTermType* pResult = NULL;
    if (visibleOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const ExpressionTermType*>(pThis + visibleOffset * 4);
    }
    return pResult;
}

inline const ExpressionTermType* ReferenceBitmapFieldType::GetBitmap() const
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

#endif  // #ifndef _REFERENCEBITMAPFIELDTYPE_H_
