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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
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
