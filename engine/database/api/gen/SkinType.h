#ifndef _LSR_SKINTYPE_H_
#define _LSR_SKINTYPE_H_

/******************************************************************************
**
**   File:        SkinType.h
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
 * SkinType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct SkinType
{
    const ColorMapType* const* const m_colorMap;
    const U16 m_colorMapCount;
    const BitmapDefinitionType* const* const m_bitmap;
    const U16 m_bitmapCount;


    /**
     * Returns the number of colorMap elements.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetColorMapCount() const
    {
        return m_colorMapCount;
    }

    /**
     * Returns a pointer to the colorMap child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const ColorMapType* GetColorMap(const U16 i) const
    {
        // coverity[misra_cpp_2008_rule_5_0_15_violation]
        return (i < m_colorMapCount) ? m_colorMap[i] : NULL;
    }

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
     *
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const BitmapDefinitionType* GetBitmap(const U16 i) const
    {
        // coverity[misra_cpp_2008_rule_5_0_15_violation]
        return (i < m_bitmapCount) ? m_bitmap[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_SKINTYPE_H_
