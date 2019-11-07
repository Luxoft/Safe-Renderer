#ifndef _LSR_HMIGLOBALSETTINGSTYPE_H_
#define _LSR_HMIGLOBALSETTINGSTYPE_H_

/******************************************************************************
**
**   File:        HMIGlobalSettingsType.h
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
struct DisplaySizeType;
struct ColorSetType;

struct HMIGlobalSettingsType
{
    const DisplaySizeType* const displaySize;
    const ColorSetType* const colorSet;


    /**
     * Returns a pointer to the displaySize child reference.
     * The size of the display in pixels
     */
    const DisplaySizeType* GetDisplaySize() const
    {
        return displaySize;
    }

    /**
     * Returns a pointer to the colorSet child reference.
     * Defines which colors shall be used for backgrounds, field types, specific fields, etc.
     */
    const ColorSetType* GetColorSet() const
    {
        return colorSet;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_HMIGLOBALSETTINGSTYPE_H_
