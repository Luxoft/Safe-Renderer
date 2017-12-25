/******************************************************************************
**
**   File:        pgl_sw_renderer_glue.c
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

// To do: Which functions are independent / and wich are dependent?

// --> We have a SW bitblitting library (platform independent)
// --> We have functions to get memory pointers - render targets (platform dependent)

#include "pgl_sw_renderer_glue.h"
#include "pgl_sw_renderer.h"
#include "pgl_assert.h"
#include <stdlib.h>
#include <string.h>

typedef struct pgl_texture_t
{
    uint32_t mWidth;
    uint32_t mHeight;
    PGLFormat mFormat;
    const void * mData;
    uint32_t mSize; // Size in memory in bytes
    PGLBoolean mAllocated;
    PGLBoolean mValid;
} pgl_texture_t;

typedef struct pgl_context_t
{
    PGLSurface mSurface;
    pgl_texture_t * mTexture;
    PGLBoolean mValid;
} pgl_context_t;

static pgl_texture_t gsTextures[PGL_MAX_TEXTURES] = { 0 };
static uint8_t gsCurrentTexture = 0u;

static pgl_context_t gsContexts[PGL_MAX_CONTEXTS] = { 0 };
static uint8_t gsCurrentContext = 0u;

PGLBoolean pglIsValidContext(PGLContext context)
{
    return PGL_REQUIRE(context) // check if context is valid - additional check to see if context is special NULL pointer
        && PGL_REQUIRE((context)->mValid) // valid flag set?
        && PGL_REQUIRE(context >= &gsContexts[0]) // check if context points to valid memory
        && PGL_REQUIRE(context < &gsContexts[PGL_MAX_CONTEXTS]);
}

PGLBoolean pglIsValidTexture(PGLTexture texture, PGLBoolean check4content)
{
    return PGL_REQUIRE(texture) // check if texture is valid
        && (!check4content || PGL_REQUIRE((texture)->mValid)) // valid flag set?
        && PGL_REQUIRE(texture >= &gsTextures[0]) // check if texture points to valid memory
        && PGL_REQUIRE(texture < &gsTextures[PGL_MAX_TEXTURES]);
}

PGLContext pglCreateContext(void)
{
    PGLContext retVal = NULL;

    if (PGL_REQUIRE(gsCurrentContext < PGL_MAX_CONTEXTS)) // do we run out of contexts?
    {
        retVal = &gsContexts[gsCurrentContext++];
        retVal->mValid = PGL_TRUE;
        retVal->mSurface = NULL;
        retVal->mTexture = NULL;
    }

    return retVal;
}

PGLBoolean pglIsValidSurface(PGLSurface surface, PGLBoolean check4content); // Platform dependent (e.g. implemented in win32)

PGLBoolean pglSetSurface(PGLContext context, PGLSurface surface)
{
    PGLBoolean ret = PGL_FALSE;
    if (pglIsValidContext(context) // check if context is valid
        && pglIsValidSurface(surface, PGL_TRUE)) // check if surface is valid
    {
        context->mSurface = surface;
        ret = PGL_TRUE;
    }

    return ret;
}

PGLTexture pglCreateTexture(PGLContext context)
{
    PGLTexture retVal = NULL;

    if (PGL_REQUIRE(gsCurrentTexture < PGL_MAX_TEXTURES))
    {
        retVal = &gsTextures[gsCurrentTexture++];
        retVal->mValid = PGL_FALSE;
        retVal->mWidth = 0u;
        retVal->mHeight = 0u;
        retVal->mData = NULL;
        retVal->mFormat = PGL_FORMAT_RGBA_8888;
        retVal->mSize = 0u;
        retVal->mAllocated = PGL_FALSE;
    }

    return retVal;
}

PGLBoolean pglSetColor(PGLContext context, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    // TODO
    return PGL_TRUE;
}

PGLBoolean pglLoadTexture(PGLTexture tex, uint32_t width, uint32_t height, PGLFormat format, PGLBoolean copy, const void* data)
{
    PGLBoolean ret = PGL_FALSE;
    if (pglIsValidTexture(tex,PGL_FALSE) // check if texture is valid
        && PGL_REQUIRE(data) // check if data is valid
        && PGL_REQUIRE(!copy) // As copy comes along with heap-management this is not a valid use case for Functional Safety solution
        )
    {
        const uint8_t bpp = pgl_helper_getbpp(format);
        const uint32_t bufSize = width*height*bpp;

        // check if texture already includes allocated memory... If yes free
        //if (tex->mAllocated && PGL_REQUIRE(tex->mData) && PGL_REQUIRE(tex->mValid)) // if it is allocated it should also be a valid pointer
        //{
        //  free((void*)tex->mData);
        //}
        tex->mValid = PGL_TRUE;
        tex->mWidth = width;
        tex->mHeight = height;
        tex->mFormat = format;
        tex->mSize = bufSize;
        tex->mAllocated = copy;
        //if (copy)
        //{

        //  tex->mData = malloc(bufSize);
        //  if (PGL_TRUE == (ret = PGL_REQUIRE(tex->mData))) // test if allocation was succesfull
        //  {
        //      memcpy((void*)tex->mData, data, bufSize);
        //  }
        //}
        //else
        //{
        tex->mData = data;
        ret = PGL_TRUE;
    }

    return ret;
}

void pglBindTexture(PGLContext context, PGLTexture t)
{
    if (pglIsValidContext(context)
        && pglIsValidTexture(t,PGL_FALSE))
    {
        context->mTexture = t;
    }
}

PGLBoolean pglSurfaceToSWSurface(PGLSurface surface, PGL_SW_Surface * swsurface, PGLFormat * format); // Implementation Platform dependend (e.g. in pgl_win32, ...)

void pglDrawArea(PGLContext ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    // TODO
}

void pglClear(PGLContext ctx)
{
    if (pglIsValidContext(ctx))
    {
        PGL_SW_Surface dest;
        PGLFormat destFormat;
        if (PGL_REQUIRE(pglSurfaceToSWSurface(ctx->mSurface, &dest, &destFormat)))
        {
            // TODO: use color from context
            memset(dest.p, 0, dest.bytes);
        }
    }
}

void pglDrawQuad(PGLContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    if (pglIsValidContext(ctx))
    {
        // To do: Add clipping support options
        if (pglIsValidSurface(ctx->mSurface,PGL_TRUE) && pglIsValidTexture(ctx->mTexture, PGL_TRUE)) // we can only draw if we have a surfaqce and a source texture
        {
            //pgl_surface_t * rt = (pgl_surface_t*)context->mSurface;
            //PGLSurface s = context->mSurface;
            PGL_SW_Surface dest;
            PGLFormat destFormat;
            PGLTexture t = ctx->mTexture;
            if (PGL_REQUIRE(pglSurfaceToSWSurface(ctx->mSurface,&dest,&destFormat) && t && (t->mData))//PGL_REQUIRE(rt && t && (t->mData)) // check for valid pointers
                && PGL_REQUIRE(t->mFormat == destFormat)) // ensure that we have the same format
            {
                const int32_t width = ((u2 - u1) >> 4u) + 1;
                const int32_t height = ((v2 - v1) >> 4u) + 1;
                dest.x = x1 >> 4u;
                dest.y = y1 >> 4u;
                dest.w = width; // we do not support zooming --> use source width
                dest.h = height; // we do not support zooming --> use source width
                //PGL_SW_Surface dest = { s->mData, x1 >> 4u, y1 >> 4u, pglSurfaceGetWidth(s), pglSurfaceGetHeight(s),  pglSurfaceGetBPP(s) * pglSurfaceGetWidth(s), pglSurfaceGetMemorySize(s) };
                PGL_SW_Surface src = { (void*)t->mData, u1 >> 4u, v1 >> 4u,  width, height, pgl_helper_getbpp(t->mFormat) * t->mWidth, t->mSize };

                pgl_sw_bitblit_copy(&dest, &src, t->mFormat);
            }
        }
    }
}

PGLBoolean pglVerify(PGLContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2)
{
    PGLBoolean verified = PGL_FALSE;
    if (pglIsValidContext(ctx))
    {
        // To do: Add clipping support options
        if (pglIsValidSurface(ctx->mSurface,PGL_TRUE) && pglIsValidTexture(ctx->mTexture, PGL_TRUE)) // we can only draw if we have a surfaqce and a source texture
        {
            //pgl_surface_t * rt = (pgl_surface_t*)context->mSurface;
            //PGLSurface s = context->mSurface;
            PGL_SW_Surface dest;
            PGLFormat destFormat;
            PGLTexture t = ctx->mTexture;
            if (pglSurfaceToSWSurface(ctx->mSurface,&dest,&destFormat) && t && (t->mData) && (t->mFormat == destFormat)) // ensure that we have the same format
            {
                const int32_t width = ((u2 - u1) >> 4u) + 1;
                const int32_t height = ((v2 - v1) >> 4u) + 1;
                dest.x = x1 >> 4u;
                dest.y = y1 >> 4u;
                dest.w = width; // we do not support zooming --> use source width
                dest.h = height; // we do not support zooming --> use source width
                PGL_SW_Surface src = { (void*)t->mData, u1 >> 4u, v1 >> 4u,  width, height, pgl_helper_getbpp(t->mFormat) * t->mWidth, t->mSize };

                verified = (pgl_sw_compare(&dest, &src, t->mFormat) > 0) ? PGL_FALSE : PGL_TRUE;
            }
        }
    }
    return verified;
}

PGLError pglGetError(PGLContext context)
{
    return PGL_NO_ERROR;
}
