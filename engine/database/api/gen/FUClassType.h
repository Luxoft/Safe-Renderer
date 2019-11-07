#ifndef _LSR_FUCLASSTYPE_H_
#define _LSR_FUCLASSTYPE_H_

/******************************************************************************
**
**   File:        FUClassType.h
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
struct DynamicDataEntryType;

struct FUClassType
{
    const U16 fUClassId;
    const bool internal;
    const DynamicDataEntryType* const *dynamicDataEntry;
    const U16 dynamicDataEntryCount;


    /**
     * Returns the value of the fUClassId attribute
     */
    U16 GetFUClassId() const
    {
        return fUClassId;
    }

    /**
     * Returns the value of the internal attribute
     */
    bool GetInternal() const
    {
        return internal;
    }

    /**
     * Returns the number of dynamicDataEntry elements.
     */
    U16 GetDynamicDataEntryCount() const
    {
        return dynamicDataEntryCount;
    }

    /**
     * Returns a pointer to the dynamicDataEntry child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    const DynamicDataEntryType* GetDynamicDataEntry(const U16 i) const
    {
        return (i < dynamicDataEntryCount) ? dynamicDataEntry[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_FUCLASSTYPE_H_
