#ifndef _PANELDATABASETYPE_H_
#define _PANELDATABASETYPE_H_

/******************************************************************************
**
**   File:        PanelDatabaseType.h
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
struct PanelType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct PanelDatabaseType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the PanelDatabaseType.
     * Each element of this type has this exact image in ROM memory.
     */
    U32 panelCount :32;
    U32 panelOffset :32;
    //----------------------------------------------------------------

public:

    /**
     * Returns the number of panel child elements.
     */
    U16 GetPanelCount() const;

    /**
     * Returns a pointer to the panel child reference at index item.
     * This method checks the index and returns null if there are no PanelType
     * elements or the 'item' index exceeds the element count.
     */
    const PanelType* GetPanel(const U16 item) const;
};

P_STATIC_ASSERT((sizeof(PanelDatabaseType)) == 8, "PanelDatabaseType size")


inline U16 PanelDatabaseType::GetPanelCount() const
{
    return panelCount;
}

inline const PanelType* PanelDatabaseType::GetPanel(const U16 item) const
{
    const PanelType* pResult = NULL;
    if (item < GetPanelCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U32* childRefROMPtr = reinterpret_cast<const U32*>(pThis + panelOffset);
        pResult = reinterpret_cast<const PanelType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _PANELDATABASETYPE_H_
