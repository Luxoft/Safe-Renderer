#ifndef _LSR_BITMAPDATABASETYPE_H_
#define _LSR_BITMAPDATABASETYPE_H_

/******************************************************************************
**
**   File:        BitmapDatabaseType.h
**   Description:
**   Generator:   7db08a476f8107a993e0bf7183b0cf60031dad3e
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "ddh_defs.h"

namespace lsr
{

/**
 * BitmapDatabaseType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct BitmapDatabaseType
{
    const BitmapType* const* const m_bitmap;
    const U16 m_bitmapCount;


    /**
     * Returns the number of bitmap elements.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetBitmapCount() const
    {
        return m_bitmapCount;
    }

    /**
     * Returns a pointer to the bitmap child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     * This list contains the definitions of the bitmaps that are then referenced in the schemas
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const BitmapType* GetBitmap(const U16 i) const
    {
        // coverity[misra_cpp_2008_rule_5_0_15_violation]
        return (i < m_bitmapCount) ? m_bitmap[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_BITMAPDATABASETYPE_H_
