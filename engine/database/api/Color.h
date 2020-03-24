#ifndef LUXOFTSAFERENDERER_COLOR_H
#define LUXOFTSAFERENDERER_COLOR_H

/******************************************************************************
**
**   File:        Color.h
**   Description:
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

#include "LsrTypes.h"

namespace lsr
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
        m_value(0U)
    {}

    /**
     * Creates a color with the given RGBA components
     * @param red red component
     * @param green green component
     * @param blue blue component
     * @param alpha alpha blend value (opacity)
     */
    Color(const U8 red, const U8 green, const U8 blue, const U8 alpha):
        m_value((static_cast <U32> (alpha) << 24U) |
                (static_cast <U32> (blue)  << 16U) |
                (static_cast <U32> (green) << 8U) |
                 static_cast <U32> (red) )
    {}

    /**
     * Creates a color from a raw ODI value
     * @param value ODI representation
     */
    static Color fromColorValue(const U32 value)
    {
        Color res;
        res.m_value = value;
        return res;
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
        return static_cast <U8> ((m_value & 0x0000ff00U) >> 8U);
    }

    /**
     * Get the blue component
     */
    inline U8 getBlue() const
    {
        return static_cast <U8> ((m_value & 0x00ff0000U) >> 16U);
    }

    /**
     * Get the alpha blend value
     */
    inline U8 getAlpha() const
    {
        return static_cast <U8> ((m_value & 0xff000000U) >> 24U);
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
    void setRawValue(const U32 colorValue)
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

#endif // LUXOFTSAFERENDERER_COLOR_H
