#ifndef _AREATYPE_H_
#define _AREATYPE_H_

/******************************************************************************
**
**   File:        AreaType.h
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

struct AreaType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the AreaType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 xCoord :16;
    U16 yCoord :16;
    U16 width :16;
    U16 height :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the xCoord attribute
     */
    I16 GetXCoord() const;

    /**
     * Returns the value of the yCoord attribute
     */
    I16 GetYCoord() const;

    /**
     * Returns the value of the width attribute
     */
    I16 GetWidth() const;

    /**
     * Returns the value of the height attribute
     */
    I16 GetHeight() const;
};

P_STATIC_ASSERT((sizeof(AreaType)) == 8, "AreaType size")


inline I16 AreaType::GetXCoord() const
{
    return xCoord;
}

inline I16 AreaType::GetYCoord() const
{
    return yCoord;
}

inline I16 AreaType::GetWidth() const
{
    return width;
}

inline I16 AreaType::GetHeight() const
{
    return height;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _AREATYPE_H_
