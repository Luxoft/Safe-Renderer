#ifndef _PAGETYPE_H_
#define _PAGETYPE_H_

/******************************************************************************
**
**   File:        PageType.h
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

struct PageType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the PageType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 panelIdSize :16;
    U16 panelIdOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns the number of elements panelId attribute list has
     */
    U16 GetSizeOfPanelIdList() const;

    /**
     * Returns the selected index of the panelId attribute list
     */
    U16 GetPanelIdItem(const U16 index) const;

    /**
     * Returns a pointer to the content of the panelId attribute list
     */
     const U16* GetPanelIdPointer() const;
};

P_STATIC_ASSERT((sizeof(PageType)) == 4, "PageType size")


inline U16 PageType::GetSizeOfPanelIdList() const
{
    return panelIdSize;
}

inline U16 PageType::GetPanelIdItem(const U16 index) const
{
    U16 result = 0;
    if (index < GetSizeOfPanelIdList())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U16* arr = reinterpret_cast<const U16*>(pThis + panelIdOffset);
        result = arr[index];
    }
    return result;
}

inline const U16* PageType::GetPanelIdPointer() const
{
    const U8* pThis = reinterpret_cast<const U8*>(this);
    const U16* arr = reinterpret_cast<const U16*>(pThis + panelIdOffset);
    return arr;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _PAGETYPE_H_
