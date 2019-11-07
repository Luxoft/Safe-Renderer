/******************************************************************************
**
**   File:        gil_sw_renderer_glue.c
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

// To do: Which functions are independent / and wich are dependent?

// --> We have a SW bitblitting library (platform independent)
// --> We have functions to get memory pointers - render targets (platform dependent)

#include "gil_sw_renderer_glue.h"
#include "gil_sw_renderer.h"
#include "gil_assert.h"
#include <stdlib.h>
#include <string.h>

typedef struct gil_texture_t
{
    uint32_t mWidth;
    uint32_t mHeight;
    GILFormat mFormat;
    const void * mData;
    uint32_t mSize; // Size in memory in bytes
    GILBoolean mAllocated;
    GILBoolean mValid;
} gil_texture_t;

typedef struct gil_context_t
{
    GILSurface mSurface;
    gil_texture_t * mTexture;
    GILBoolean mValid;
    GIL_SW_Color mColor;
} gil_context_t;

static gil_texture_t gsTextures[GIL_MAX_TEXTURES] = { 0 };
static uint8_t gsCurrentTexture = 0u;

static gil_context_t gsContexts[GIL_MAX_CONTEXTS] = { 0 };
static uint8_t gsCurrentContext = 0u;

GILBoolean gilIsValidContext(GILContext context)
{
    return GIL_REQUIRE(context) // check if context is valid - additional check to see if context is special NULL pointer
        && GIL_REQUIRE((context)->mValid) // valid flag set?
        && GIL_REQUIRE(context >= &gsContexts[0]) // check if context points to valid memory
        && GIL_REQUIRE(context < &gsContexts[GIL_MAX_CONTEXTS]);
}

GILBoolean gilIsValidTexture(GILTexture texture, GILBoolean check4content)
{
    return GIL_REQUIRE(texture) // check if texture is valid
        && (!check4content || GIL_REQUIRE((texture)->mValid)) // valid flag set?
        && GIL_REQUIRE(texture >= &gsTextures[0]) // check if texture points to valid memory
        && GIL_REQUIRE(texture < &gsTextures[GIL_MAX_TEXTURES]);
}

GILContext gilCreateContext(void)
{
    GILContext retVal = NULL;

    if (GIL_REQUIRE(gsCurrentContext < GIL_MAX_CONTEXTS)) // do we run out of contexts?
    {
        retVal = &gsContexts[gsCurrentContext++];
        retVal->mValid = GIL_TRUE;
        retVal->mSurface = NULL;
        retVal->mTexture = NULL;
    }

    return retVal;
}

GILBoolean gilIsValidSurface(GILSurface surface, GILBoolean check4content); // Platform dependent (e.g. implemented in win32)

GILBoolean gilSetSurface(GILContext context, GILSurface surface)
{
    GILBoolean ret = GIL_FALSE;
    if (gilIsValidContext(context) // check if context is valid
        && gilIsValidSurface(surface, GIL_TRUE)) // check if surface is valid
    {
        context->mSurface = surface;
        ret = GIL_TRUE;
    }

    return ret;
}

GILTexture gilCreateTexture(GILContext context)
{
    GILTexture retVal = NULL;

    if (GIL_REQUIRE(gsCurrentTexture < GIL_MAX_TEXTURES))
    {
        retVal = &gsTextures[gsCurrentTexture++];
        retVal->mValid = GIL_FALSE;
        retVal->mWidth = 0u;
        retVal->mHeight = 0u;
        retVal->mData = NULL;
        retVal->mFormat = GIL_FORMAT_INVALID;
        retVal->mSize = 0u;
        retVal->mAllocated = GIL_FALSE;
    }

    return retVal;
}

GILBoolean gilSetColor(GILContext context, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    // As we don't have color support in LSR,
    // we need to hardcode the color
    // context->mColor.r = red;
    // context->mColor.g = green;
    // context->mColor.b = blue;
    // context->mColor.a = alpha;

    context->mColor.r = 0xBB;
    context->mColor.g = 0xB7;
    context->mColor.b = 0xB4;
    context->mColor.a = 0x00;
    return GIL_TRUE;
}

GILBoolean gilTexPixels(GILTexture tex, uint32_t width, uint32_t height, GILFormat format, const void* data)
{
    GILBoolean ret = GIL_FALSE;
    if (gilIsValidTexture(tex,GIL_FALSE) // check if texture is valid
        && GIL_REQUIRE(data) // check if data is valid
        )
    {
        const uint8_t bpp = gil_helper_getbpp(format);
        const uint32_t bufSize = width*height*bpp;

        // check if texture already includes allocated memory... If yes free
        //if (tex->mAllocated && GIL_REQUIRE(tex->mData) && GIL_REQUIRE(tex->mValid)) // if it is allocated it should also be a valid pointer
        //{
        //  free((void*)tex->mData);
        //}
        tex->mValid = GIL_TRUE;
        tex->mWidth = width;
        tex->mHeight = height;
        tex->mFormat = format;
        tex->mSize = bufSize;
        tex->mAllocated = GIL_FALSE;
        //if (copy)
        //{

        //  tex->mData = malloc(bufSize);
        //  if (GIL_TRUE == (ret = GIL_REQUIRE(tex->mData))) // test if allocation was succesfull
        //  {
        //      memcpy((void*)tex->mData, data, bufSize);
        //  }
        //}
        //else
        //{
        tex->mData = data;
        ret = GIL_TRUE;
    }

    return ret;
}

GILBoolean gilTexPalette4(GILTexture tex, const void* palette, uint32_t size)
{
    // TODO:
    return GIL_FALSE;
}

GILBoolean gilTexPalette3(GILTexture tex, const void* palette, uint32_t size)
{
    // TODO:
    return GIL_FALSE;
}

GILBoolean gilTexPalette2(GILTexture tex, const void* palette, uint32_t size)
{
    // TODO:
    return GIL_FALSE;
}

void gilBindTexture(GILContext context, GILTexture t)
{
    if (gilIsValidContext(context)
        && gilIsValidTexture(t,GIL_FALSE))
    {
        context->mTexture = t;
    }
}

GILBoolean gilSurfaceToSWSurface(GILSurface surface, GIL_SW_Surface * swsurface); // Implementation Platform dependend (e.g. in gil_win32, ...)

void gilDrawArea(GILContext ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    // TODO
}

void gilClear(GILContext ctx)
{
    if (gilIsValidContext(ctx))
    {
        GIL_SW_Surface dest;
        if (GIL_REQUIRE(gilSurfaceToSWSurface(ctx->mSurface, &dest)))
        {
            gil_sw_set_color(&dest, &ctx->mColor);
        }
    }
}

void gilDrawQuad(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    if (gilIsValidContext(ctx))
    {
        // To do: Add clipping support options
        if (gilIsValidSurface(ctx->mSurface,GIL_TRUE) && gilIsValidTexture(ctx->mTexture, GIL_TRUE)) // we can only draw if we have a surfaqce and a source texture
        {
            //gil_surface_t * rt = (gil_surface_t*)context->mSurface;
            //GILSurface s = context->mSurface;
            GIL_SW_Surface dest;
            GILTexture t = ctx->mTexture;
            if (GIL_REQUIRE(gilSurfaceToSWSurface(ctx->mSurface, &dest) && t && (t->mData))//GIL_REQUIRE(rt && t && (t->mData)) // check for valid pointers
                && GIL_REQUIRE(t->mFormat == dest.format)) // ensure that we have the same format
            {
                const int32_t width = ((u2 - u1) >> 4u) + 1;
                const int32_t height = ((v2 - v1) >> 4u) + 1;
                dest.x = x1 >> 4u;
                dest.y = y1 >> 4u;
                dest.w = width; // we do not support zooming --> use source width
                dest.h = height; // we do not support zooming --> use source width
                //GIL_SW_Surface dest = { s->mData, x1 >> 4u, y1 >> 4u, gilSurfaceGetWidth(s), gilSurfaceGetHeight(s),  gilSurfaceGetBPP(s) * gilSurfaceGetWidth(s), gilSurfaceGetMemorySize(s) };
                GIL_SW_Surface src = { (void*)t->mData, u1 >> 4u, v1 >> 4u,  width, height, gil_helper_getbpp(t->mFormat) * t->mWidth, t->mSize, t->mFormat };

                gil_sw_bitblit_copy(&dest, &src);
            }
        }
    }
}

GILBoolean gilVerify(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    GILBoolean verified = GIL_FALSE;
    if (gilIsValidContext(ctx))
    {
        // To do: Add clipping support options
        if (gilIsValidSurface(ctx->mSurface,GIL_TRUE) && gilIsValidTexture(ctx->mTexture, GIL_TRUE)) // we can only draw if we have a surfaqce and a source texture
        {
            //gil_surface_t * rt = (gil_surface_t*)context->mSurface;
            //GILSurface s = context->mSurface;
            GIL_SW_Surface dest;
            GILTexture t = ctx->mTexture;
            if (gilSurfaceToSWSurface(ctx->mSurface,&dest) && t && (t->mData) && (t->mFormat == dest.format)) // ensure that we have the same format
            {
                const int32_t width = ((u2 - u1) >> 4u) + 1;
                const int32_t height = ((v2 - v1) >> 4u) + 1;
                dest.x = x1 >> 4u;
                dest.y = y1 >> 4u;
                dest.w = width; // we do not support zooming --> use source width
                dest.h = height; // we do not support zooming --> use source width
                GIL_SW_Surface src = { (void*)t->mData, u1 >> 4u, v1 >> 4u,  width, height,
                    gil_helper_getbpp(t->mFormat) * t->mWidth, t->mSize, t->mFormat };

                verified = (gil_sw_compare(&dest, &src) > 0) ? GIL_FALSE : GIL_TRUE;
            }
        }
    }
    return verified;
}

GILError gilGetError(GILContext context)
{
    return GIL_NO_ERROR;
}
