#ifndef _FIELDSTYPE_H_
#define _FIELDSTYPE_H_

/******************************************************************************
**
**   File:        FieldsType.h
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
struct FieldType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct FieldsType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the FieldsType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 fieldCount :16;
    U16 fieldOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the number of field child elements.
     */
    U16 GetFieldCount() const;

    /**
     * Returns a pointer to the field child reference at index item.
     * This method checks the index and returns null if there are no FieldType
     * elements or the 'item' index exceeds the element count.
     */
    const FieldType* GetField(const U16 item) const;
};

P_STATIC_ASSERT((sizeof(FieldsType)) == 4, "FieldsType size")


inline U16 FieldsType::GetFieldCount() const
{
    return fieldCount;
}

inline const FieldType* FieldsType::GetField(const U16 item) const
{
    const FieldType* pResult = NULL;
    if (item < GetFieldCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U16* childRefROMPtr = reinterpret_cast<const U16*>(pThis + fieldOffset);
        pResult = reinterpret_cast<const FieldType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _FIELDSTYPE_H_
