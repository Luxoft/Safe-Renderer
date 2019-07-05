#ifndef _COLORDATABASETYPE_H_
#define _COLORDATABASETYPE_H_

/******************************************************************************
**
**   File:        ColorDatabaseType.h
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

struct ColorDatabaseType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the ColorDatabaseType.
     * Each element of this type has this exact image in ROM memory.
     */
    //----------------------------------------------------------------

public:
};

P_STATIC_ASSERT((sizeof(ColorDatabaseType)) == 0, "ColorDatabaseType size")


} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _COLORDATABASETYPE_H_
