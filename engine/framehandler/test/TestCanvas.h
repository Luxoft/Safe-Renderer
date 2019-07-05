#ifndef LUXOFTSAFERENDERER_TESTCANVAS_H
#define LUXOFTSAFERENDERER_TESTCANVAS_H

/******************************************************************************
**
**   File:        TestCanvas.h
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

#include <Canvas.h>

namespace display
{
    class DisplayManager;
}

class TestCanvas P_FINAL : public lsr::Canvas
{
public:
    TestCanvas(lsr::DisplayManager& dsp, const U16 width, const U16 height)
        : lsr::Canvas(dsp, width, height)
    {
    }
};

#endif // LUXOFTSAFERENDERER_TESTCANVAS_H
