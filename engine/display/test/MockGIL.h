/******************************************************************************
**
**   File:        MockGIL.h
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

#include <gil.h>
#include <gmock/gmock.h>

struct IGIL
{
    virtual void gilInit(GILConfig config) = 0;
    virtual void gilUninit() = 0;
    virtual GILSurface gilCreateWindow(uint8_t window, int32_t x, int32_t y, int32_t w, int32_t h) = 0;
    virtual GILContext gilCreateContext(void) = 0;
    virtual GILBoolean gilSetSurface(GILContext context, GILSurface surface) = 0;
    virtual GILBoolean gilSetColor(GILContext context, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) = 0;
    virtual GILTexture gilCreateTexture(GILContext context) = 0;
    virtual GILBoolean gilTexPixels(GILTexture t, uint32_t width, uint32_t height, GILFormat format, const void* data) = 0;
    virtual GILBoolean gilTexPalette4(GILTexture t, const void* palette, uint32_t size) = 0;
    virtual GILBoolean gilTexPalette3(GILTexture t, const void* palette, uint32_t size) = 0;
    virtual GILBoolean gilTexPalette2(GILTexture t, const void* palette, uint32_t size) = 0;
    virtual void gilBindTexture(GILContext context, GILTexture t) = 0;
    virtual void gilClear(GILContext context) = 0;
    virtual void gilDrawQuad(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2) = 0;
    virtual GILBoolean gilSwapBuffers(GILSurface surface) = 0;
    virtual GILBoolean gilVerify(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2) = 0;
    virtual GILError gilGetError(GILContext context) = 0;
    virtual GILBoolean gilHandleWindowEvents(GILContext context) = 0;
    virtual void gilSync(GILContext context) = 0;
};

struct MockGIL : public IGIL
{
    MOCK_METHOD1(gilInit, void(GILConfig));
    MOCK_METHOD0(gilUninit, void());
    MOCK_METHOD5(gilCreateWindow, GILSurface(uint8_t, int32_t, int32_t, int32_t, int32_t));
    MOCK_METHOD0(gilCreateContext, GILContext());
    MOCK_METHOD2(gilSetSurface, GILBoolean(GILContext context, GILSurface surface));
    MOCK_METHOD5(gilSetColor, GILBoolean(GILContext context, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha));
    MOCK_METHOD1(gilCreateTexture, GILTexture(GILContext context));
    MOCK_METHOD5(gilTexPixels, GILBoolean(GILTexture t, uint32_t width, uint32_t height, GILFormat format, const void* data));
    MOCK_METHOD3(gilTexPalette4, GILBoolean(GILTexture t, const void* palette, uint32_t size));
    MOCK_METHOD3(gilTexPalette3, GILBoolean(GILTexture t, const void* palette, uint32_t size));
    MOCK_METHOD3(gilTexPalette2, GILBoolean(GILTexture t, const void* palette, uint32_t size));
    MOCK_METHOD2(gilBindTexture, void(GILContext context, GILTexture t));
    MOCK_METHOD1(gilClear, void(GILContext context));
    MOCK_METHOD9(gilDrawQuad, void(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2));
    MOCK_METHOD1(gilSwapBuffers, GILBoolean(GILSurface surface));
    MOCK_METHOD9(gilVerify, GILBoolean(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2));
    MOCK_METHOD1(gilGetError, GILError(GILContext context));
    MOCK_METHOD1(gilHandleWindowEvents, GILBoolean(GILContext context));
    MOCK_METHOD1(gilSync, void(GILContext context));
};

struct gil_context_t
{};

struct gil_texture_t
{};

struct gil_surface_t
{};

typedef ::testing::StrictMock<MockGIL> MockGILStrict;
extern IGIL* gilMock;