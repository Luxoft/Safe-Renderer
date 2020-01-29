#ifndef _LSR_BITMAPIDTABLETYPE_H_
#define _LSR_BITMAPIDTABLETYPE_H_

/******************************************************************************
**
**   File:        BitmapIdTableType.h
**   Description:
**   Generator:   c78c5138ac2e7c6506a52bfc6fbc0ef05f7ad869
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

/**
 * BitmapIdTableType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct BitmapIdTableType
{
    const EnumerationBitmapMapType* const* const m_item;
    const U16 m_itemCount;


    /**
     * Returns the number of item elements.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetItemCount() const
    {
        return m_itemCount;
    }

    /**
     * Returns a pointer to the item child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const EnumerationBitmapMapType* GetItem(const U16 i) const
    {
        // coverity[misra_cpp_2008_rule_5_0_15_violation]
        return (i < m_itemCount) ? m_item[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_BITMAPIDTABLETYPE_H_
