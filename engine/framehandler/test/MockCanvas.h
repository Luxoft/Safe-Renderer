/******************************************************************************
**
**   File:        MockCanvas.h
**   Description: Google Mock object for the lsr::Canvas
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

#include <gmock/gmock.h>
#include <Canvas.h>
#include <Color.h>
#include <StaticBitmap.h>
#include <Area.h>

namespace unittest
{

struct ICanvas
{
    virtual void clear(const lsr::Color& color) = 0;
    virtual void drawBitmap(const lsr::StaticBitmap& bitmap, const lsr::Area& area) = 0;
    virtual bool verify(const lsr::StaticBitmap& bitmap, const lsr::Area& area) = 0;
};

struct MockCanvas : public ICanvas
{
    MOCK_METHOD1(clear, void(const lsr::Color&));
    MOCK_METHOD2(drawBitmap, void(const lsr::StaticBitmap&, const lsr::Area&));
    MOCK_METHOD2(verify, bool(const lsr::StaticBitmap&, const lsr::Area&));
};

extern ICanvas* g_mockCanvas;

} // namespace unittest

