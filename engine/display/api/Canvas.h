#ifndef LUXOFTSAFERENDERER_CANVAS_H
#define LUXOFTSAFERENDERER_CANVAS_H

/******************************************************************************
**
**   File:        Canvas.h
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

#include "LsrTypes.h"
#include "LSREngineError.h"


namespace lsr
{
class Color;

class Canvas
{
public:
    void clear(const Color& chroma);
    void drawBitmap(const StaticBitmap& bitmap, const Area& rect);
    bool verify(const StaticBitmap& bitmap, const Area& rect);
    U16 getWidth() const;
    U16 getHeight() const;
    LSREngineError getError() const;

protected:
    Canvas(DisplayManager& dsp, const U16 width, const U16 height);
    DisplayManager& getDisplayManager();

private:
    DisplayManager& m_dsp;
    U16 m_width;
    U16 m_height;
    LSREngineError m_error;
};

// coverity[misra_cpp_2008_rule_9_3_3_violation] Returned object will be modified
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

inline LSREngineError Canvas::getError() const
{
    return m_error;
}

}

#endif // LUXOFTSAFERENDERER_CANVAS_H
