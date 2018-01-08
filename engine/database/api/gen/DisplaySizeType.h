#ifndef _DISPLAYSIZETYPE_H_
#define _DISPLAYSIZETYPE_H_

/******************************************************************************
**
**   File:        DisplaySizeType.h
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

struct DisplaySizeType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the DisplaySizeType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 width :16;
    U16 height :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the width attribute
     */
    U16 GetWidth() const;

    /**
     * Returns the value of the height attribute
     */
    U16 GetHeight() const;
};

P_STATIC_ASSERT((sizeof(DisplaySizeType)) == 4, "DisplaySizeType size")


inline U16 DisplaySizeType::GetWidth() const
{
    return width;
}

inline U16 DisplaySizeType::GetHeight() const
{
    return height;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _DISPLAYSIZETYPE_H_
