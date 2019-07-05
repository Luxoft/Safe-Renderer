#ifndef _DYNAMICDATATYPE_H_
#define _DYNAMICDATATYPE_H_

/******************************************************************************
**
**   File:        DynamicDataType.h
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

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct DynamicDataType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the DynamicDataType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 type :16;
    U16 fUClassId :16;
    U16 dataId :16;
    U8  PADDING1 :8;
    U8  PADDING2 :8;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the type attribute
     */
    DynamicDataTypeEnumeration GetType() const;

    /**
     * Returns the value of the fUClassId attribute
     */
    U16 GetFUClassId() const;

    /**
     * Returns the value of the dataId attribute
     */
    U16 GetDataId() const;
};

P_STATIC_ASSERT((sizeof(DynamicDataType)) == 8, "DynamicDataType size")


inline DynamicDataTypeEnumeration DynamicDataType::GetType() const
{
    return static_cast<DynamicDataTypeEnumeration>(type);
}

inline U16 DynamicDataType::GetFUClassId() const
{
    return fUClassId;
}

inline U16 DynamicDataType::GetDataId() const
{
    return dataId;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _DYNAMICDATATYPE_H_
