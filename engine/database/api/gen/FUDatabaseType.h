#ifndef _FUDATABASETYPE_H_
#define _FUDATABASETYPE_H_

/******************************************************************************
**
**   File:        FUDatabaseType.h
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
struct FUClassType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct FUDatabaseType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the FUDatabaseType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 fUCount :16;
    U16 fUOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the number of fU child elements.
     * Documentation from xsd file:
     *
     * This is the list of all Functional Units known by the engine
     */
    U16 GetFUCount() const;

    /**
     * Returns a pointer to the fU child reference at index item.
     * This method checks the index and returns null if there are no FUClassType
     * elements or the 'item' index exceeds the element count.
     * This is the list of all Functional Units known by the engine
     */
    const FUClassType* GetFU(const U16 item) const;
};

P_STATIC_ASSERT((sizeof(FUDatabaseType)) == 4, "FUDatabaseType size")


inline U16 FUDatabaseType::GetFUCount() const
{
    return fUCount;
}

inline const FUClassType* FUDatabaseType::GetFU(const U16 item) const
{
    const FUClassType* pResult = NULL;
    if (item < GetFUCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U16* childRefROMPtr = reinterpret_cast<const U16*>(pThis + fUOffset);
        pResult = reinterpret_cast<const FUClassType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _FUDATABASETYPE_H_
