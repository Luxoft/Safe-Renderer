#ifndef _SKINDATABASETYPE_H_
#define _SKINDATABASETYPE_H_

/******************************************************************************
**
**   File:        SkinDatabaseType.h
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
#include "PscTypes.h"  // for P_STATIC_ASSERT


namespace psc
{
struct SkinType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct SkinDatabaseType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the SkinDatabaseType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 skinCount :16;
    U16 skinOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the number of skin child elements.
     */
    U16 GetSkinCount() const;

    /**
     * Returns a pointer to the skin child reference at index item.
     * This method checks the index and returns null if there are no SkinType
     * elements or the 'item' index exceeds the element count.
     */
    const SkinType* GetSkin(const U16 item) const;
};

P_STATIC_ASSERT((sizeof(SkinDatabaseType)) == 4, "SkinDatabaseType size")


inline U16 SkinDatabaseType::GetSkinCount() const
{
    return skinCount;
}

inline const SkinType* SkinDatabaseType::GetSkin(const U16 item) const
{
    const SkinType* pResult = NULL;
    if (item < GetSkinCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U16* childRefROMPtr = reinterpret_cast<const U16*>(pThis + skinOffset);
        pResult = reinterpret_cast<const SkinType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _SKINDATABASETYPE_H_
