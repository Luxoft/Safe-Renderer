#ifndef _DYNAMICINDICATIONIDTYPE_H_
#define _DYNAMICINDICATIONIDTYPE_H_

/******************************************************************************
**
**   File:        DynamicIndicationIdType.h
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

struct DynamicIndicationIdType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the DynamicIndicationIdType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 fUClassId :16;
    U8  indicationId :8;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the fUClassId attribute
     */
    U16 GetFUClassId() const;

    /**
     * Returns the value of the indicationId attribute
     */
    U8 GetIndicationId() const;
};

P_STATIC_ASSERT((sizeof(DynamicIndicationIdType)) == 3, "DynamicIndicationIdType size")


inline U16 DynamicIndicationIdType::GetFUClassId() const
{
    return fUClassId;
}

inline U8 DynamicIndicationIdType::GetIndicationId() const
{
    return indicationId;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _DYNAMICINDICATIONIDTYPE_H_
