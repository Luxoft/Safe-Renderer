#ifndef POPULUSSC_CANVAS_H
#define POPULUSSC_CANVAS_H

/******************************************************************************
**
**   File:        Canvas.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
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

#include "PscTypes.h"


namespace psc
{
class DisplayManager;
class StaticBitmap;
class Area;
class Color;

class Canvas
{
public:
    void clear(const Color& color);
    void drawBitmap(const StaticBitmap& bitmap, const Area& area);
    bool verify(const StaticBitmap& bitmap, const Area& area);
    U16 getWidth() const;
    U16 getHeight() const;

protected:
    Canvas(DisplayManager& dsp, const U16 width, const U16 height);
    DisplayManager& getDisplayManager();

private:
    DisplayManager& m_dsp;
    U16 m_width;
    U16 m_height;
};

inline DisplayManager& Canvas::getDisplayManager()
{
    return m_dsp;
}

inline U16 Canvas::getWidth() const
{
    return m_width;
}

inline U16 Canvas::getHeight() const
{
    return m_height;
}

}

#endif // POPULUSSC_CANVAS_H
