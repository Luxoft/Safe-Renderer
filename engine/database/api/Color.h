#ifndef POPULUSSC_COLOR_H
#define POPULUSSC_COLOR_H

/******************************************************************************
**
**   File:        Color.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Render is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Render.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "PscTypes.h"

namespace psc
{

/**
 * Represents an RGBA color (RGB full color and an Alpha value with 8 bit per channel)
 */
class Color
{
public:
    /**
     * Creates a black transparent color
     */
    Color():
        m_value(0)
    {}

    /**
     * Creates a color with the given RGBA components
     * @param red red component
     * @param green green component
     * @param blue blue component
     * @param alpha alpha blend value (opacity)
     */
    Color(U8 red, U8 green, U8 blue, U8 alpha):
        m_value((static_cast <U32> (alpha) << 24) |
                (static_cast <U32> (blue)  << 16) |
                (static_cast <U32> (green) << 8) |
                 static_cast <U32> (red) )
    {}

    /**
     * Creates a color from a raw ODI value
     * @param value ODI representation
     */
    static Color fromColorValue(U32 value)
    {
        Color ret;
        ret.m_value = value;
        return ret;
    }

    /**
     * Get the red component
     */
    inline U8 getRed() const
    {
        return static_cast <U8> (m_value & 0x000000ffU);
    }

    /**
     * Get the green component
     */
    inline U8 getGreen() const
    {
        return static_cast <U8> ((m_value & 0x0000ff00U) >> 8);
    }

    /**
     * Get the blue component
     */
    inline U8 getBlue() const
    {
        return static_cast <U8> ((m_value & 0x00ff0000U) >> 16);
    }

    /**
     * Get the alpha blend value
     */
    inline U8 getAlpha() const
    {
        return static_cast <U8> ((m_value & 0xff000000U) >> 24);
    }

    /**
     * Get the color as raw value (rgba)
     */
    inline U32 getRawValue() const
    {
        return m_value;
    }

    /**
     * Set the Color from a ODI representation value
     * @param colorValue ODI representation of the color
     */
    void setRawValue(U32 colorValue)
    {
        m_value = colorValue;
    }

    bool operator==(const Color& rhs) const
    {
        return m_value == rhs.m_value;
    }

    bool operator!=(const Color& rhs) const
    {
        return m_value != rhs.m_value;
    }

private:
    U32 m_value;
};

} // namespace fusdk

#endif // POPULUSSC_COLOR_H
