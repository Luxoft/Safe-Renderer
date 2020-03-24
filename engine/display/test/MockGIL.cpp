/******************************************************************************
**
**   File:        MockGIL.cpp
**   Description: Google Mock object for the gil.h
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
#include "MockGIL.h"

IGIL* gilMock = NULL;

void gilInit(GILConfig config)
{
    gilMock->gilInit(config);
}

void gilUninit(void)
{
    gilMock->gilUninit();
}

GILSurface gilCreateWindow(uint8_t window, int32_t x, int32_t y, int32_t w, int32_t h)
{
    return gilMock->gilCreateWindow(window, x, y, w, h);
}

GILContext gilCreateContext(void)
{
    return gilMock->gilCreateContext();
}

GILBoolean gilSetSurface(GILContext context, GILSurface surface)
{
    return gilMock->gilSetSurface(context, surface);
}

GILBoolean gilSetColor(GILContext context, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    return gilMock->gilSetColor(context, red, green, blue, alpha);
}

GILTexture gilCreateTexture(GILContext context)
{
    return gilMock->gilCreateTexture(context);
}

GILBoolean gilTexPixels(GILTexture t, uint32_t width, uint32_t height, GILFormat format, const void* data)
{
    return gilMock->gilTexPixels(t, width, height, format, data);
}

GILBoolean gilTexPalette4(GILTexture t, const void* palette, uint32_t size)
{
    return gilMock->gilTexPalette4(t, palette, size);
}

GILBoolean gilTexPalette3(GILTexture t, const void* palette, uint32_t size)
{
    return gilMock->gilTexPalette3(t, palette, size);
}

GILBoolean gilTexPalette2(GILTexture t, const void* palette, uint32_t size)
{
    return gilMock->gilTexPalette2(t, palette, size);
}

void gilBindTexture(GILContext context, GILTexture t)
{
    return gilMock->gilBindTexture(context, t);
}

void gilClear(GILContext context)
{
    return gilMock->gilClear(context);
}

void gilDrawQuad(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    return gilMock->gilDrawQuad(ctx, x1, y1, u1, v1, x2, y2, u2, v2);
}

GILBoolean gilSwapBuffers(GILSurface surface)
{
    return gilMock->gilSwapBuffers(surface);
}

GILBoolean gilVerify(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    return gilMock->gilVerify(ctx, x1, y1, u1, v1, x2, y2, u2, v2);
}

GILError gilGetError(GILContext context)
{
    return gilMock->gilGetError(context);
}

GILBoolean gilHandleWindowEvents(GILContext context)
{
    return gilMock->gilHandleWindowEvents(context);
}

void gilSync(GILContext context)
{
    return gilMock->gilSync(context);
}

