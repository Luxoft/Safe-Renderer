/******************************************************************************
**
**   File:        MockCanvas.cpp
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

#include "MockCanvas.h"

namespace unittest
{
    ICanvas* g_mockCanvas = NULL;
}

namespace lsr
{

Canvas::Canvas(DisplayManager& dsp, const U16 width, const U16 height)
: m_dsp(dsp)
, m_width(width)
, m_height(height)
{
}

void Canvas::clear(const lsr::Color& color)
{
    unittest::g_mockCanvas->clear(color);
}

void Canvas::drawBitmap(const lsr::StaticBitmap& bitmap, const lsr::Area& area)
{
    unittest::g_mockCanvas->drawBitmap(bitmap, area);
}

bool Canvas::verify(const lsr::StaticBitmap& bitmap, const lsr::Area& area)
{
    return unittest::g_mockCanvas->verify(bitmap, area);
}

} // namespace lsr
