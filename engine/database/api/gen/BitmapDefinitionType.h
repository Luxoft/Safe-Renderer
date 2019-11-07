#ifndef _LSR_BITMAPDEFINITIONTYPE_H_
#define _LSR_BITMAPDEFINITIONTYPE_H_

/******************************************************************************
**
**   File:        BitmapDefinitionType.h
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
struct BitmapStateDefinitionType;

struct BitmapDefinitionType
{
    const U16 bitmapId;
    const BitmapStateDefinitionType* const _default;


    /**
     * Returns the value of the bitmapId attribute
     */
    U16 GetBitmapId() const
    {
        return bitmapId;
    }

    /**
     * Returns a pointer to the default child reference.
     *
     */
    const BitmapStateDefinitionType* GetDefault() const
    {
        return _default;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_BITMAPDEFINITIONTYPE_H_
