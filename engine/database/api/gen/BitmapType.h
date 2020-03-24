#ifndef _LSR_BITMAPTYPE_H_
#define _LSR_BITMAPTYPE_H_

/******************************************************************************
**
**   File:        BitmapType.h
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
 * BitmapType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct BitmapType
{
    const SkinnedBitmapType* const* const m_skinnedBitmap;
    const U16 m_skinnedBitmapCount;


    /**
     * Returns the number of skinnedBitmap elements.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetSkinnedBitmapCount() const
    {
        return m_skinnedBitmapCount;
    }

    /**
     * Returns a pointer to the skinnedBitmap child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const SkinnedBitmapType* GetSkinnedBitmap(const U16 i) const
    {
        // coverity[misra_cpp_2008_rule_5_0_15_violation]
        return (i < m_skinnedBitmapCount) ? m_skinnedBitmap[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_BITMAPTYPE_H_
