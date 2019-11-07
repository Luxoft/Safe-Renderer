#ifndef _LSR_SKINTYPE_H_
#define _LSR_SKINTYPE_H_

/******************************************************************************
**
**   File:        SkinType.h
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
struct ColorMapType;
struct BitmapDefinitionType;

struct SkinType
{
    const ColorMapType* const *colorMap;
    const U16 colorMapCount;
    const BitmapDefinitionType* const *bitmap;
    const U16 bitmapCount;


    /**
     * Returns the number of colorMap elements.
     */
    U16 GetColorMapCount() const
    {
        return colorMapCount;
    }

    /**
     * Returns a pointer to the colorMap child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    const ColorMapType* GetColorMap(const U16 i) const
    {
        return (i < colorMapCount) ? colorMap[i] : NULL;
    }

    /**
     * Returns the number of bitmap elements.
     */
    U16 GetBitmapCount() const
    {
        return bitmapCount;
    }

    /**
     * Returns a pointer to the bitmap child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    const BitmapDefinitionType* GetBitmap(const U16 i) const
    {
        return (i < bitmapCount) ? bitmap[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_SKINTYPE_H_
