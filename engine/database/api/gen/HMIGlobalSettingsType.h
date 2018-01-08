#ifndef _HMIGLOBALSETTINGSTYPE_H_
#define _HMIGLOBALSETTINGSTYPE_H_

/******************************************************************************
**
**   File:        HMIGlobalSettingsType.h
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
struct DisplaySizeType;
struct ColorSetType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct HMIGlobalSettingsType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the HMIGlobalSettingsType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 displaySizeOffset :16;
    U16 colorSetOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns a pointer to the displaySize child reference.
     * The size of the display in pixels
     */
    const DisplaySizeType* GetDisplaySize() const;

    /**
     * Returns a pointer to the colorSet child reference.
     * Defines which colors shall be used for backgrounds, field types, specific
     * fields, etc.
     */
    const ColorSetType* GetColorSet() const;
};

P_STATIC_ASSERT((sizeof(HMIGlobalSettingsType)) == 4, "HMIGlobalSettingsType size")


inline const DisplaySizeType* HMIGlobalSettingsType::GetDisplaySize() const
{
    const DisplaySizeType* pResult = NULL;
    if (displaySizeOffset != 0)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const DisplaySizeType*>(pThis + displaySizeOffset * 4);
    }
    return pResult;
}

inline const ColorSetType* HMIGlobalSettingsType::GetColorSet() const
{
    const ColorSetType* pResult = NULL;
    if (colorSetOffset != 0)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const ColorSetType*>(pThis + colorSetOffset * 4);
    }
    return pResult;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _HMIGLOBALSETTINGSTYPE_H_
