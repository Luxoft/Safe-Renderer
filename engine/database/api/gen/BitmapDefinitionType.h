#ifndef _BITMAPDEFINITIONTYPE_H_
#define _BITMAPDEFINITIONTYPE_H_

/******************************************************************************
**
**   File:        BitmapDefinitionType.h
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
struct BitmapStateDefinitionType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct BitmapDefinitionType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the BitmapDefinitionType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 bitmapId :16;
    U16 _defaultOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the bitmapId attribute
     */
    U16 GetBitmapId() const;

    /**
     * Returns a pointer to the default child reference.
     */
    const BitmapStateDefinitionType* GetDefault() const;
};

P_STATIC_ASSERT((sizeof(BitmapDefinitionType)) == 4, "BitmapDefinitionType size")


inline U16 BitmapDefinitionType::GetBitmapId() const
{
    return bitmapId;
}

inline const BitmapStateDefinitionType* BitmapDefinitionType::GetDefault() const
{
    const BitmapStateDefinitionType* pResult = NULL;
    if (_defaultOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const BitmapStateDefinitionType*>(pThis + _defaultOffset * 4);
    }
    return pResult;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _BITMAPDEFINITIONTYPE_H_
