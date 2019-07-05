#ifndef _SKINTYPE_H_
#define _SKINTYPE_H_

/******************************************************************************
**
**   File:        SkinType.h
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
struct ColorMapType;
struct BitmapDefinitionType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct SkinType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the SkinType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 colorMapCount :16;
    U16 bitmapCount :16;
    U16 colorMapOffset :16;
    U16 bitmapOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the number of colorMap child elements.
     */
    U16 GetColorMapCount() const;

    /**
     * Returns a pointer to the colorMap child reference at index item.
     * This method checks the index and returns null if there are no
     * ColorMapType elements or the 'item' index exceeds the element count.
     */
    const ColorMapType* GetColorMap(const U16 item) const;

    /**
     * Returns the number of bitmap child elements.
     */
    U16 GetBitmapCount() const;

    /**
     * Returns a pointer to the bitmap child reference at index item.
     * This method checks the index and returns null if there are no
     * BitmapDefinitionType elements or the 'item' index exceeds the element
     * count.
     */
    const BitmapDefinitionType* GetBitmap(const U16 item) const;
};

P_STATIC_ASSERT((sizeof(SkinType)) == 8, "SkinType size")


inline U16 SkinType::GetColorMapCount() const
{
    return colorMapCount;
}

inline const ColorMapType* SkinType::GetColorMap(const U16 item) const
{
    const ColorMapType* pResult = NULL;
    if (item < GetColorMapCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U16* childRefROMPtr = reinterpret_cast<const U16*>(pThis + colorMapOffset);
        pResult = reinterpret_cast<const ColorMapType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

inline U16 SkinType::GetBitmapCount() const
{
    return bitmapCount;
}

inline const BitmapDefinitionType* SkinType::GetBitmap(const U16 item) const
{
    const BitmapDefinitionType* pResult = NULL;
    if (item < GetBitmapCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U16* childRefROMPtr = reinterpret_cast<const U16*>(pThis + bitmapOffset);
        pResult = reinterpret_cast<const BitmapDefinitionType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _SKINTYPE_H_
