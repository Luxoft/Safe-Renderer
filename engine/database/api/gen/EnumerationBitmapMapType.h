#ifndef _ENUMERATIONBITMAPMAPTYPE_H_
#define _ENUMERATIONBITMAPMAPTYPE_H_

/******************************************************************************
**
**   File:        EnumerationBitmapMapType.h
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
struct EnumerationValueType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct EnumerationBitmapMapType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the EnumerationBitmapMapType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 bitmapId :16;
    U16 enumerationValueOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the bitmapId attribute
     */
    U16 GetBitmapId() const;

    /**
     * Returns a pointer to the enumerationValue child reference.
     */
    const EnumerationValueType* GetEnumerationValue() const;
};

P_STATIC_ASSERT((sizeof(EnumerationBitmapMapType)) == 4, "EnumerationBitmapMapType size")


inline U16 EnumerationBitmapMapType::GetBitmapId() const
{
    return bitmapId;
}

inline const EnumerationValueType* EnumerationBitmapMapType::GetEnumerationValue() const
{
    const EnumerationValueType* pResult = NULL;
    if (enumerationValueOffset != 0)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const EnumerationValueType*>(pThis + enumerationValueOffset * 4);
    }
    return pResult;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _ENUMERATIONBITMAPMAPTYPE_H_
