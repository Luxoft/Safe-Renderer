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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
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
