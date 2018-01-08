#ifndef _PAGEDATABASETYPE_H_
#define _PAGEDATABASETYPE_H_

/******************************************************************************
**
**   File:        PageDatabaseType.h
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
struct PageType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct PageDatabaseType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the PageDatabaseType.
     * Each element of this type has this exact image in ROM memory.
     */
    U32 pageCount :32;
    U32 pageOffset :32;
    //----------------------------------------------------------------

public:

    /**
     * Returns the number of page child elements.
     * Documentation from xsd file:
     *
     * Each page in the database collects a number of panels and may also
     * specify an overriding Control Map to change control behavior
     */
    U16 GetPageCount() const;

    /**
     * Returns a pointer to the page child reference at index item.
     * This method checks the index and returns null if there are no PageType
     * elements or the 'item' index exceeds the element count.
     * Each page in the database collects a number of panels and may also
     * specify an overriding Control Map to change control behavior
     */
    const PageType* GetPage(const U16 item) const;
};

P_STATIC_ASSERT((sizeof(PageDatabaseType)) == 8, "PageDatabaseType size")


inline U16 PageDatabaseType::GetPageCount() const
{
    return pageCount;
}

inline const PageType* PageDatabaseType::GetPage(const U16 item) const
{
    const PageType* pResult = NULL;
    if (item < GetPageCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U32* childRefROMPtr = reinterpret_cast<const U32*>(pThis + pageOffset);
        pResult = reinterpret_cast<const PageType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _PAGEDATABASETYPE_H_
