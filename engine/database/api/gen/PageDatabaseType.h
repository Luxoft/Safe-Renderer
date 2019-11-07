#ifndef _LSR_PAGEDATABASETYPE_H_
#define _LSR_PAGEDATABASETYPE_H_

/******************************************************************************
**
**   File:        PageDatabaseType.h
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
struct PageType;

struct PageDatabaseType
{
    const PageType* const *page;
    const U16 pageCount;


    /**
     * Returns the number of page elements.
     */
    U16 GetPageCount() const
    {
        return pageCount;
    }

    /**
     * Returns a pointer to the page child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     * Each page in the database collects a number of panels and may also specify an overriding Control Map to change control behavior
     */
    const PageType* GetPage(const U16 i) const
    {
        return (i < pageCount) ? page[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_PAGEDATABASETYPE_H_
