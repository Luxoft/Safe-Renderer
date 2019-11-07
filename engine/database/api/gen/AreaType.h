#ifndef _LSR_AREATYPE_H_
#define _LSR_AREATYPE_H_

/******************************************************************************
**
**   File:        AreaType.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   Luxoft Safe Renderer is free software: you can redistribute it and/or
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

namespace lsr
{

struct AreaType
{
    const I16 xCoord;
    const I16 yCoord;
    const I16 width;
    const I16 height;


    /**
     * Returns the value of the xCoord attribute
     */
    I16 GetXCoord() const
    {
        return xCoord;
    }

    /**
     * Returns the value of the yCoord attribute
     */
    I16 GetYCoord() const
    {
        return yCoord;
    }

    /**
     * Returns the value of the width attribute
     */
    I16 GetWidth() const
    {
        return width;
    }

    /**
     * Returns the value of the height attribute
     */
    I16 GetHeight() const
    {
        return height;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_AREATYPE_H_
