#ifndef _BITMAPIDTABLETYPE_H_
#define _BITMAPIDTABLETYPE_H_

/******************************************************************************
**
**   File:        BitmapIdTableType.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

#include "ddh_defs.h"
#include "PscTypes.h"  // for P_STATIC_ASSERT


namespace psc
{
struct EnumerationBitmapMapType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct BitmapIdTableType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the BitmapIdTableType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 itemCount :16;
    U16 itemOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the number of item child elements.
     */
    U16 GetItemCount() const;

    /**
     * Returns a pointer to the item child reference at index item.
     * This method checks the index and returns null if there are no
     * EnumerationBitmapMapType elements or the 'item' index exceeds the
     * element count.
     */
    const EnumerationBitmapMapType* GetItem(const U16 item) const;
};

P_STATIC_ASSERT((sizeof(BitmapIdTableType)) == 4, "BitmapIdTableType size")


inline U16 BitmapIdTableType::GetItemCount() const
{
    return itemCount;
}

inline const EnumerationBitmapMapType* BitmapIdTableType::GetItem(const U16 item) const
{
    const EnumerationBitmapMapType* pResult = NULL;
    if (item < GetItemCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U16* childRefROMPtr = reinterpret_cast<const U16*>(pThis + itemOffset);
        pResult = reinterpret_cast<const EnumerationBitmapMapType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _BITMAPIDTABLETYPE_H_
