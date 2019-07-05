#ifndef _COLORSETTYPE_H_
#define _COLORSETTYPE_H_

/******************************************************************************
**
**   File:        ColorSetType.h
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

struct ColorSetType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the ColorSetType.
     * Each element of this type has this exact image in ROM memory.
     */
    U8  defaultDisplayBackgroundColorIdSet :8;
    U8  defaultPageBackgroundColorIdSet :8;
    U8  defaultPanelBackgroundColorIdSet :8;
    U8  PADDING1 :8;
    U16 defaultDisplayBackgroundColorId :16;
    U16 defaultPageBackgroundColorId :16;
    U16 defaultPanelBackgroundColorId :16;
    U8  PADDING2 :8;
    U8  PADDING3 :8;
    //----------------------------------------------------------------

public:

    /**
     * Returns >0 if the defaultDisplayBackgroundColorId attribute has been set,
     *
     * returns 0 if defaultDisplayBackgroundColorId has not been set on this
     * instance.
     */
    bool IsDefaultDisplayBackgroundColorIdSet() const;

    /**
     * Returns the value of the defaultDisplayBackgroundColorId attribute
     */
    U16 GetDefaultDisplayBackgroundColorId() const;

    /**
     * Returns >0 if the defaultPageBackgroundColorId attribute has been set,
     * returns 0 if defaultPageBackgroundColorId has not been set on this
     * instance.
     */
    bool IsDefaultPageBackgroundColorIdSet() const;

    /**
     * Returns the value of the defaultPageBackgroundColorId attribute
     */
    U16 GetDefaultPageBackgroundColorId() const;

    /**
     * Returns >0 if the defaultPanelBackgroundColorId attribute has been set,
     * returns 0 if defaultPanelBackgroundColorId has not been set on this
     * instance.
     */
    bool IsDefaultPanelBackgroundColorIdSet() const;

    /**
     * Returns the value of the defaultPanelBackgroundColorId attribute
     */
    U16 GetDefaultPanelBackgroundColorId() const;
};

P_STATIC_ASSERT((sizeof(ColorSetType)) == 12, "ColorSetType size")


inline bool ColorSetType::IsDefaultDisplayBackgroundColorIdSet() const
{
    return defaultDisplayBackgroundColorIdSet != 0U;
}

inline U16 ColorSetType::GetDefaultDisplayBackgroundColorId() const
{
    return defaultDisplayBackgroundColorId;
}

inline bool ColorSetType::IsDefaultPageBackgroundColorIdSet() const
{
    return defaultPageBackgroundColorIdSet != 0U;
}

inline U16 ColorSetType::GetDefaultPageBackgroundColorId() const
{
    return defaultPageBackgroundColorId;
}

inline bool ColorSetType::IsDefaultPanelBackgroundColorIdSet() const
{
    return defaultPanelBackgroundColorIdSet != 0U;
}

inline U16 ColorSetType::GetDefaultPanelBackgroundColorId() const
{
    return defaultPanelBackgroundColorId;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _COLORSETTYPE_H_
