#ifndef _LSR_BITMAPSTATEDEFINITIONTYPE_H_
#define _LSR_BITMAPSTATEDEFINITIONTYPE_H_

/******************************************************************************
**
**   File:        BitmapStateDefinitionType.h
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
struct LsrImage;

struct BitmapStateDefinitionType
{
    const U16 stateBitmapId;
    const LsrImage* const file;


    /**
     * Returns the value of the stateBitmapId attribute
     */
    U16 GetStateBitmapId() const
    {
        return stateBitmapId;
    }

    /**
     * Returns the value of the file attribute
     */
    const LsrImage* GetFile() const
    {
        return file;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_BITMAPSTATEDEFINITIONTYPE_H_
