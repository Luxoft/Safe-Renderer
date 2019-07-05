#ifndef _ENUMERATIONVALUETYPE_H_
#define _ENUMERATIONVALUETYPE_H_

/******************************************************************************
**
**   File:        EnumerationValueType.h
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

struct EnumerationValueType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the EnumerationValueType.
     * Each element of this type has this exact image in ROM memory.
     */
    U8  valueSet :8;
    U8  PADDING1 :8;
    U16 value :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns >0 if the value attribute has been set,
     * returns 0 if value has not been set on this instance.
     */
    bool IsValueSet() const;

    /**
     * Returns the value of the value attribute
     */
    U16 GetValue() const;
};

P_STATIC_ASSERT((sizeof(EnumerationValueType)) == 4, "EnumerationValueType size")


inline bool EnumerationValueType::IsValueSet() const
{
    return valueSet != 0U;
}

inline U16 EnumerationValueType::GetValue() const
{
    return value;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _ENUMERATIONVALUETYPE_H_
