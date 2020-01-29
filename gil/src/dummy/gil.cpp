/******************************************************************************
**
**   File:        gil.c
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

#include <gil.h>
#include <stdlib.h>
#include <stdio.h>
#include "crc32.h"
#include <LSRLimits.h>

typedef struct
{
    int32_t x;
    int32_t y;
    uint32_t crc;
} Blit;

struct gil_config_t
{
	int dummy;
};

typedef struct gil_context_t
{
    int id;
    GILTexture texture;
    Blit blits[255];
    uint8_t nBlits;
} gil_context_t;

typedef struct gil_surface_t
{
    int id;
} gil_surface_t;

typedef struct gil_texture_t
{
    int id;
    uint32_t width;
    uint32_t height;
    uint32_t crc;
} gil_texture_t;

#define MAX_CONTEXTS 1
#define MAX_WINDOWS 1
static gil_context_t g_contexts[MAX_CONTEXTS];
static gil_surface_t g_windows[MAX_WINDOWS];
static gil_texture_t g_textures[lsr::MAX_TEXTURES];
static size_t g_usedContexts;
static size_t g_usedWindows;
static size_t g_usedTextures;

static uint32_t getBpp(GILFormat format)
{
    switch (format)
    {
    case GIL_FORMAT_P_2_ARGB_8888:
    case GIL_FORMAT_P_2_BGRA_8888:
    case GIL_FORMAT_P_2_RGBA_8888:
    case GIL_FORMAT_P_2_RGB_888:
    case GIL_FORMAT_P_2_RGB_565:
        return 2;
    case GIL_FORMAT_P_4_ARGB_8888:
    case GIL_FORMAT_P_4_BGRA_8888:
    case GIL_FORMAT_P_4_RGBA_8888:
    case GIL_FORMAT_P_4_RGB_888:
    case GIL_FORMAT_P_4_RGB_565:
        return 4;
    case GIL_FORMAT_P_8_ARGB_8888:
    case GIL_FORMAT_P_8_BGRA_8888:
    case GIL_FORMAT_P_8_RGBA_8888:
    case GIL_FORMAT_P_8_RGB_888:
    case GIL_FORMAT_P_8_RGB_565:
    case GIL_FORMAT_A_8:
        return 8;
    case GIL_FORMAT_RGB_565:
    case GIL_FORMAT_BGR_565:
        return 16;
    case GIL_FORMAT_RGB_888:
    case GIL_FORMAT_BGR_888:
        return 24;
    case GIL_FORMAT_ARGB_8888:
    case GIL_FORMAT_BGRA_8888:
    case GIL_FORMAT_RGBA_8888:
    case GIL_FORMAT_INVALID:
        break;
    //no default clause to cause compiler warning if new format is added
    }
    return 32;
}

static uint32_t getBufferSize(uint32_t width, uint32_t height, GILFormat format)
{
    uint32_t bpp = getBpp(format);
    return (width * height * bpp) / 8U;
}

void gilInit(GILConfig config)
{
    fprintf(stdout, "gilInit()\n");
    g_usedWindows = 0;
    g_usedContexts = 0;
    g_usedTextures = 0;
}

void gilUninit(void)
{
}

GILSurface gilCreateWindow(uint8_t window, int32_t x, int32_t y, int32_t w, int32_t h)
{
    GILSurface win = NULL;
    if (g_usedWindows < MAX_WINDOWS)
    {
        win = &g_windows[g_usedWindows++];
        win->id = g_usedWindows;
    }
    fprintf(stdout, "gilCreateWindow(%d, %d, %d, %d, %d) ret:%d\n", window, x, y, w, h, win ? win->id : 0);
    return win;
}

GILContext gilCreateContext(void)
{
    GILContext ctx = NULL;
    if (g_usedContexts < MAX_CONTEXTS)
    {
        ctx = &g_contexts[g_usedContexts++];
        ctx->id = g_usedContexts;
        ctx->nBlits = 0;
        ctx->texture = 0;
    }
    fprintf(stdout, "gilCreateContext() ret :%d\n", ctx ? ctx->id : 0);
    return ctx;
}

GILBoolean gilSetSurface(GILContext context, GILSurface surface)
{
    GILBoolean ret = GIL_TRUE;
    fprintf(stdout, "gilSetSurface(%d, %d) ret :%d\n", context ? context->id : 0, surface ? surface->id : 0, ret);
    return ret;
}

GILBoolean gilSetColor(GILContext context, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    GILBoolean ret = GIL_TRUE;
    fprintf(stdout, "gilSetColor(%d, %d, %d, %d, %d) ret :%d\n", context ? context->id : 0, red, green, blue, alpha, ret);
    return ret;
}

GILTexture gilCreateTexture(GILContext context)
{
    GILTexture tx = NULL;
    if (g_usedTextures < lsr::MAX_TEXTURES)
    {
        tx = &g_textures[g_usedTextures++];
        tx->id = g_usedTextures;
        tx->crc = 0;
        tx->height = 0;
        tx->width = 0;
    }
    fprintf(stdout, "gilCreateTexture(%d) ret :%d\n", context ? context->id : 0, tx ? tx->id : 0);
    return tx;
}

GILBoolean gilTexPixels(GILTexture t, uint32_t width, uint32_t height, GILFormat format, const void* data)
{
    GILBoolean ret = GIL_TRUE;
    uint32_t bufSize = getBufferSize(width, height, format);
    const uint32_t crc = calcCrc32Complete(static_cast<const U8*>(data), bufSize);
    fprintf(stdout, "gilTexPixels(%d, %u, %u, %d, %u) ret :%d\n",
            t ? t->id : 0, width, height, format, crc, ret);
    t->crc = crc;
    t->width = width;
    t->height = height;
    return ret;
}

GILBoolean gilTexPalette4(GILTexture t, const void* palette, uint32_t size)
{
    GILBoolean ret = GIL_TRUE;
    fprintf(stdout, "gilTexPalette4(");
    const uint32_t* palette32 = (const uint32_t*)(palette);
    uint32_t i = 0U;
    for (; i < size; ++i)
    {
        fprintf(stdout, "0x%X, ", palette32[i]);
    }
    fprintf(stdout, ") ret :%d\n", ret);
    return ret;
}

GILBoolean gilTexPalette3(GILTexture t, const void* palette, uint32_t size)
{
    GILBoolean ret = GIL_TRUE;
    fprintf(stdout, "gilTexPalette3(");
    fprintf(stdout, ") ret :%d\n", ret);
    return ret;
}

GILBoolean gilTexPalette2(GILTexture t, const void* palette, uint32_t size)
{
    GILBoolean ret = GIL_TRUE;
    fprintf(stdout, "gilTexPalette2(");
    fprintf(stdout, ") ret :%d\n", ret);
    return ret;
}

void gilBindTexture(GILContext context, GILTexture t)
{
    fprintf(stdout, "gilBindTexture(%d, %d)\n", context ? context->id : 0, t ? t->id : 0);
    context->texture = t;
}

GILBoolean gilSetClip(GILContext context, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    GILBoolean ret = GIL_TRUE;
    fprintf(stdout, "gilSetClip(%d, %d, %d, %d, %d) ret :%d\n", context ? context->id : 0, x1, x2, y1, y2, ret);
    return ret;
}

void gilClear(GILContext context)
{
    fprintf(stdout, "gilClear(%d)\n", context ? context->id : 0);
    context->nBlits = 0;
}

void gilDrawArea(GILContext ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    fprintf(stdout, "gilDrawArea(%d, %0.1f, %0.1f, %0.1f, %0.1f)\n", ctx ? ctx->id : 0, x1 / 16., y1 / 16., x2 / 16., y2 / 16.);
}

void gilDrawQuad(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    fprintf(stdout, "gilDrawQuad(%d, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f)\n",
        ctx ? ctx->id : 0,
        x1 / 16., y1 / 16., u1 / 16., v1 / 16.,
        x2 / 16., y2 / 16., u2 / 16., v2 / 16.);
    Blit blit = { x1, y1, ctx->texture->crc };
    ctx->blits[ctx->nBlits++] = blit;
}

GILBoolean gilSwapBuffers(GILSurface surface)
{
    fprintf(stdout, "gilSwapBuffers(%d)\n", surface ? surface->id : 0);
    return GIL_TRUE;
}

GILBoolean gilVerify(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    GILBoolean ret = GIL_FALSE;
    uint8_t i = 0;
    for (; i < ctx->nBlits; ++i)
    {
        if ((ctx->blits[i].crc == ctx->texture->crc) && (ctx->blits[i].x == x1) && (ctx->blits[i].y == y1))
        {
            ret = GIL_TRUE;
            break;
        }
    }
    fprintf(stdout, "gilVerify(%d, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f) ret:%d\n",
        ctx ? ctx->id : 0,
        x1 / 16., y1 / 16., u1 / 16., v1 / 16.,
        x2 / 16., y2 / 16., u2 / 16., v2 / 16.,
        ret);
    return ret;
}

GILError gilGetError(GILContext context)
{
    GILError ret = GIL_NO_ERROR;
    fprintf(stdout, "gilGetError(%d) ret:%d\n", context ? context->id : 0, ret);
    return ret;
}

GILBoolean gilHandleWindowEvents(GILContext context)
{
    GILBoolean ret = GIL_FALSE;
    fprintf(stdout, "gilHandleWindowEvents(%d) ret:%d\n", context ? context->id : 0, ret);
    return ret;
}

void gilSync(GILContext context)
{
    fprintf(stdout, "gilSync(%d)\n", context ? context->id : 0);
}
