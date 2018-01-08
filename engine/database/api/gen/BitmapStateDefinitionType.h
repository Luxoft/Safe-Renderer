#ifndef _BITMAPSTATEDEFINITIONTYPE_H_
#define _BITMAPSTATEDEFINITIONTYPE_H_

/******************************************************************************
**
**   File:        BitmapStateDefinitionType.h
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

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct BitmapStateDefinitionType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the BitmapStateDefinitionType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 stateBitmapId :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the stateBitmapId attribute
     */
    U16 GetStateBitmapId() const;
};

P_STATIC_ASSERT((sizeof(BitmapStateDefinitionType)) == 2, "BitmapStateDefinitionType size")


inline U16 BitmapStateDefinitionType::GetStateBitmapId() const
{
    return stateBitmapId;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _BITMAPSTATEDEFINITIONTYPE_H_
