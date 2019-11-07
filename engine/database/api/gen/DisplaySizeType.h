#ifndef _LSR_DISPLAYSIZETYPE_H_
#define _LSR_DISPLAYSIZETYPE_H_

/******************************************************************************
**
**   File:        DisplaySizeType.h
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

struct DisplaySizeType
{
    const U16 width;
    const U16 height;


    /**
     * Returns the value of the width attribute
     */
    U16 GetWidth() const
    {
        return width;
    }

    /**
     * Returns the value of the height attribute
     */
    U16 GetHeight() const
    {
        return height;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_DISPLAYSIZETYPE_H_
