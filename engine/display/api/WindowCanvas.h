#ifndef POPULUSSC_WINDOWCANVAS_H
#define POPULUSSC_WINDOWCANVAS_H

/******************************************************************************
**
**   File:        WindowCanvas.h
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

#include "Canvas.h"
#include "pgl.h"

namespace psc
{

class DisplayManager;
struct WindowDefinition;

/**
 * Encapsulates a pgl window surface
 */
class WindowCanvas P_FINAL : public Canvas
{
public:
    WindowCanvas(DisplayManager& dsp, const WindowDefinition& config);

    void makeCurrent();
    void swapBuffers();

    /**
     * @return true to indicate that the window has been closed by the window system
     */
    bool handleWindowEvents();
private:
    PGLSurface m_surface;
};

}

#endif // POPULUSSC_WINDOWCANVAS_H
