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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
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
