#ifndef _FUCLASSTYPE_H_
#define _FUCLASSTYPE_H_

/******************************************************************************
**
**   File:        FUClassType.h
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
struct DynamicDataEntryType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct FUClassType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the FUClassType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 fUClassId :16;
    U8  internalFU :8;
    U8  PADDING1 :8;
    U16 dynamicDataEntryCount :16;
    U16 dynamicDataEntryOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the fUClassId attribute
     */
    U16 GetFUClassId() const;

    /**
     * Returns the value of the internalFU attribute
     */
    bool GetInternalFU() const;

    /**
     * Returns the number of dynamicDataEntry child elements.
     */
    U16 GetDynamicDataEntryCount() const;

    /**
     * Returns a pointer to the dynamicDataEntry child reference at index item.
     * This method checks the index and returns null if there are no
     * DynamicDataEntryType elements or the 'item' index exceeds the element
     * count.
     */
    const DynamicDataEntryType* GetDynamicDataEntry(const U16 item) const;
};

P_STATIC_ASSERT((sizeof(FUClassType)) == 8, "FUClassType size")


inline U16 FUClassType::GetFUClassId() const
{
    return fUClassId;
}

inline bool FUClassType::GetInternalFU() const
{
    return internalFU != 0U;
}

inline U16 FUClassType::GetDynamicDataEntryCount() const
{
    return dynamicDataEntryCount;
}

inline const DynamicDataEntryType* FUClassType::GetDynamicDataEntry(const U16 item) const
{
    const DynamicDataEntryType* pResult = NULL;
    if (item < GetDynamicDataEntryCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U16* childRefROMPtr = reinterpret_cast<const U16*>(pThis + dynamicDataEntryOffset);
        pResult = reinterpret_cast<const DynamicDataEntryType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _FUCLASSTYPE_H_
