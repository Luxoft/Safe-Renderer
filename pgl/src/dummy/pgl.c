/******************************************************************************
**
**   File:        pgl.c
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

#include <pgl.h>
#include <stdlib.h>
#include <stdio.h>
#include "crc32.h"

typedef struct
{
    int32_t x;
    int32_t y;
    uint32_t crc;
} Blit;

typedef struct pgl_context_t
{
    int id;
    PGLTexture texture;
    Blit blits[255];
    uint8_t nBlits;
} pgl_context_t;

typedef struct pgl_surface_t
{
    int id;
} pgl_surface_t;

typedef struct pgl_texture_t
{
    int id;
    uint32_t width;
    uint32_t height;
    uint32_t crc;
} pgl_texture_t;

#define MAX_CONTEXTS 1
#define MAX_WINDOWS 1
#define MAX_TEXTURES 10
static pgl_context_t g_contexts[MAX_CONTEXTS];
static pgl_surface_t g_windows[MAX_WINDOWS];
static pgl_texture_t g_textures[MAX_TEXTURES];
static size_t g_usedContexts;
static size_t g_usedWindows;
static size_t g_usedTextures;

void pglInit()
{
    fprintf(stdout, "pglInit()\n");
    g_usedWindows = 0;
    g_usedContexts = 0;
    g_usedTextures = 0;
}

PGLSurface pglCreateWindow(uint8_t window, int32_t x, int32_t y, int32_t w, int32_t h)
{
    PGLSurface win = NULL;
    if (g_usedWindows < MAX_WINDOWS)
    {
        win = &g_windows[g_usedWindows++];
        win->id = g_usedWindows;
    }
    fprintf(stdout, "pglCreateWindow(%d, %d, %d, %d, %d) ret:%d\n", window, x, y, w, h, win ? win->id : 0);
    return win;
}

PGLContext pglCreateContext(void)
{
    PGLContext ctx = NULL;
    if (g_usedContexts < MAX_CONTEXTS)
    {
        ctx = &g_contexts[g_usedContexts++];
        ctx->id = g_usedContexts;
    }
    fprintf(stdout, "pglCreateContext() ret :%d\n", ctx ? ctx->id : 0);
    return ctx;
}

PGLBoolean pglSetSurface(PGLContext context, PGLSurface surface)
{
    PGLBoolean ret = PGL_TRUE;
    fprintf(stdout, "pglSetSurface(%d, %d) ret :%d\n", context ? context->id : 0, surface ? surface->id : 0, ret);
    return ret;
}

PGLBoolean pglSetColor(PGLContext context, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    PGLBoolean ret = PGL_TRUE;
    fprintf(stdout, "pglSetColor(%d, %d, %d, %d, %d) ret :%d\n", context ? context->id : 0, red, green, blue, alpha, ret);
    return ret;
}

PGLTexture pglCreateTexture(PGLContext context)
{
    PGLTexture tx = NULL;
    if (g_usedTextures < MAX_TEXTURES)
    {
        tx = &g_textures[g_usedTextures++];
        tx->id = g_usedTextures;
    }
    fprintf(stdout, "pglCreateTexture(%d) ret :%d\n", context ? context->id : 0, tx ? tx->id : 0);
    return tx;
}

PGLBoolean pglLoadTexture(PGLTexture t, uint32_t width, uint32_t height, PGLFormat format, PGLBoolean copy, const void* data)
{
    PGLBoolean ret = PGL_TRUE;
    uint32_t pixelSize = 4;
    if (format < PGL_FORMAT_1_BPP)
    {
        pixelSize = 1;
    }
    else if (format < PGL_FORMAT_2_BPP)
    {
        pixelSize = 2;
    }
    else if (format < PGL_FORMAT_3_BPP)
    {
        pixelSize = 3;
    }
    else
    {
        pixelSize = 4;
    }
    const uint32_t crc = calcCrc32Complete(data, width*height * pixelSize);
    fprintf(stdout, "pglLoadTexture(%d, %d, %d, %d, %d, 0x%X) ret :%d\n", t ? t->id : 0, width, height, format, copy, crc, ret);
    t->crc = crc;
    t->width = width;
    t->height = height;
    return ret;
}

void pglBindTexture(PGLContext context, PGLTexture t)
{
    fprintf(stdout, "pglBindTexture(%d, %d)\n", context ? context->id : 0, t ? t->id : 0);
    context->texture = t;
}

PGLBoolean pglSetClip(PGLContext context, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    PGLBoolean ret = PGL_TRUE;
    fprintf(stdout, "pglSetClip(%d, %d, %d, %d, %d) ret :%d\n", context ? context->id : 0, x1, x2, y1, y2, ret);
    return ret;
}

void pglClear(PGLContext context)
{
    fprintf(stdout, "pglClear(%d)\n", context ? context->id : 0);
    context->nBlits = 0;
}

void pglDrawArea(PGLContext ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    fprintf(stdout, "pglDrawArea(%d, %0.1f, %0.1f, %0.1f, %0.1f)\n", ctx ? ctx->id : 0, x1 / 16., y1 / 16., x2 / 16., y2 / 16.);
}

void pglDrawQuad(PGLContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    fprintf(stdout, "pglDrawQuad(%d, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f)\n",
        ctx ? ctx->id : 0,
        x1 / 16., y1 / 16., u1 / 16., v1 / 16.,
        x2 / 16., y2 / 16., u2 / 16., v2 / 16.);
    Blit blit = { x1, y1, ctx->texture->crc };
    ctx->blits[ctx->nBlits++] = blit;
}

PGLBoolean pglSwapBuffers(PGLSurface surface)
{
    fprintf(stdout, "pglSwapBuffers(%d)\n", surface ? surface->id : 0);
    return PGL_TRUE;
}

PGLBoolean pglVerify(PGLContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    PGLBoolean ret = PGL_FALSE;
    for (uint8_t i = 0; i < ctx->nBlits; ++i)
    {
        if ((ctx->blits[i].crc == ctx->texture->crc) && (ctx->blits[i].x == x1) && (ctx->blits[i].y == y1))
        {
            ret = PGL_TRUE;
            break;
        }
    }
    fprintf(stdout, "pglVerify(%d, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f) ret:%d\n",
        ctx ? ctx->id : 0,
        x1 / 16., y1 / 16., u1 / 16., v1 / 16.,
        x2 / 16., y2 / 16., u2 / 16., v2 / 16.,
        ret);
    return ret;
}

PGLError pglGetError(PGLContext context)
{
    PGLError ret = PGL_NO_ERROR;
    fprintf(stdout, "pglGetError(%d) ret:%d\n", context ? context->id : 0, ret);
    return ret;
}

PGLBoolean pglHandleWindowEvents(PGLContext context)
{
    PGLBoolean ret = PGL_FALSE;
    fprintf(stdout, "pglHandleWindowEvents(%d) ret:%d\n", context ? context->id : 0, ret);
    return ret;
}
