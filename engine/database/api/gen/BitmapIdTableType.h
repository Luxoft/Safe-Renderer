#ifndef _LSR_BITMAPIDTABLETYPE_H_
#define _LSR_BITMAPIDTABLETYPE_H_

/******************************************************************************
**
**   File:        BitmapIdTableType.h
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
struct EnumerationBitmapMapType;

struct BitmapIdTableType
{
    const EnumerationBitmapMapType* const *item;
    const U16 itemCount;


    /**
     * Returns the number of item elements.
     */
    U16 GetItemCount() const
    {
        return itemCount;
    }

    /**
     * Returns a pointer to the item child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    const EnumerationBitmapMapType* GetItem(const U16 i) const
    {
        return (i < itemCount) ? item[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_BITMAPIDTABLETYPE_H_
