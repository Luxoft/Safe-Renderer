#ifndef LUXOFTSAFERENDERER_WINDOWCANVAS_H
#define LUXOFTSAFERENDERER_WINDOWCANVAS_H

/******************************************************************************
**
**   File:        WindowCanvas.h
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

#include "Canvas.h"
#include "gil.h"

namespace lsr
{

struct WindowDefinition;

/**
 * Encapsulates a gil window surface
 */
class WindowCanvas P_FINAL : public Canvas
{
public:
    WindowCanvas(DisplayManager& dsp, const WindowDefinition& config);

    void makeCurrent();
    void swapBuffers();

    /**
     * notifies the canvas about the finished main loop
     * (all verification calls done for one Engine iteration)
     */
    void sync();

    /**
     * @return true to indicate that the window has been closed by the window system
     */
    bool handleWindowEvents();
private:
    GILSurface m_surface;
};

}

#endif // LUXOFTSAFERENDERER_WINDOWCANVAS_H
