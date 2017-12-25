#ifndef _COLORMAPTYPE_H_
#define _COLORMAPTYPE_H_

/******************************************************************************
**
**   File:        ColorMapType.h
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

struct ColorMapType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the ColorMapType.
     * Each element of this type has this exact image in ROM memory.
     */
    //----------------------------------------------------------------

public:
};

P_STATIC_ASSERT((sizeof(ColorMapType)) == 0, "ColorMapType size")


} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _COLORMAPTYPE_H_
