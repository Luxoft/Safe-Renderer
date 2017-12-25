#ifndef _DYNAMICDATAENTRYTYPE_H_
#define _DYNAMICDATAENTRYTYPE_H_

/******************************************************************************
**
**   File:        DynamicDataEntryType.h
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

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct DynamicDataEntryType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the DynamicDataEntryType.
     * Each element of this type has this exact image in ROM memory.
     */
    U8  minimumSet :8;
    U8  maximumSet :8;
    U16 dataId :16;
    U16 dataType :16;
    U32 minimum :32;
    U32 maximum :32;
    U16 repeatTimeout :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the dataId attribute
     */
    U16 GetDataId() const;

    /**
     * Returns the value of the dataType attribute
     */
    DynamicDataTypeEnumeration GetDataType() const;

    /**
     * Returns >0 if the minimum attribute has been set,
     * returns 0 if minimum has not been set on this instance.
     */
    bool IsMinimumSet() const;

    /**
     * Returns the value of the minimum attribute
     */
    I32 GetMinimum() const;

    /**
     * Returns >0 if the maximum attribute has been set,
     * returns 0 if maximum has not been set on this instance.
     */
    bool IsMaximumSet() const;

    /**
     * Returns the value of the maximum attribute
     */
    I32 GetMaximum() const;

    /**
     * Returns the value of the repeatTimeout attribute
     */
    U16 GetRepeatTimeout() const;
};

P_STATIC_ASSERT((sizeof(DynamicDataEntryType)) == 16, "DynamicDataEntryType size")


inline U16 DynamicDataEntryType::GetDataId() const
{
    return dataId;
}

inline DynamicDataTypeEnumeration DynamicDataEntryType::GetDataType() const
{
    return static_cast<DynamicDataTypeEnumeration>(dataType);
}

inline bool DynamicDataEntryType::IsMinimumSet() const
{
    return minimumSet != 0;
}

inline I32 DynamicDataEntryType::GetMinimum() const
{
    return minimum;
}

inline bool DynamicDataEntryType::IsMaximumSet() const
{
    return maximumSet != 0;
}

inline I32 DynamicDataEntryType::GetMaximum() const
{
    return maximum;
}

inline U16 DynamicDataEntryType::GetRepeatTimeout() const
{
    return repeatTimeout;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _DYNAMICDATAENTRYTYPE_H_
