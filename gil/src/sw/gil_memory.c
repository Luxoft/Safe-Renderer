/******************************************************************************
**
**   File:        gil_memory.c
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

#include "gil.h"
#include "gil_sw_memory_configuration.h"
#include "gil_sw_renderer.h"
#include "gil_assert.h"

#define GIL_MAX_SURFACES 1

#include <stdlib.h>
#include <stdio.h>


typedef struct gil_surface_t
{
    void* pBuffer;
    uint32_t bufferSize;
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
    GILFormat format;
    GILBoolean valid;
} gil_surface_t;

static gil_surface_t gsScreen;
static gil_surface_t gsSurfaces[GIL_MAX_SURFACES] = { 0 };

void* pDoubleBuffer = NULL;

void gilUninit(void)
{
    if (NULL != pDoubleBuffer)
    {
        free(pDoubleBuffer);
    }
}

void gilInit(GILConfig config)
{
    gsScreen.pBuffer = config->outputMemory;
    gsScreen.bufferSize = config->bufferSize;
    gsScreen.x = config->screenX;
    gsScreen.y = config->screenY;
    gsScreen.w = config->screenW;
    gsScreen.h = config->screenH;
    gsScreen.format = config->pixelFormat;
    gsScreen.valid = GIL_TRUE;

    printf("gilInit: gil was inited with config:\r\n");
    printf("\tb: %p, bs: %ld, x: %ld, y: %ld, w: %ld, h: %ld, f: %d, v: %s\r\n",
           gsScreen.pBuffer, gsScreen.bufferSize,
           gsScreen.x, gsScreen.y, gsScreen.w, gsScreen.h,
           gsScreen.format,
           gsScreen.valid ? "True" : "False");
}

GILSurface gilCreateWindow(uint8_t window, int32_t x, int32_t y, int32_t w, int32_t h)
{
    GILSurface retVal = NULL;

    if (GIL_REQUIRE(window < GIL_MAX_SURFACES) &&
        GIL_REQUIRE(x >= 0) && GIL_REQUIRE(y >= 0) &&
        GIL_REQUIRE(w > 0) && GIL_REQUIRE(h > 0) &&
        GIL_REQUIRE(gsSurfaces[window].valid == GIL_FALSE))
    {

        retVal = &gsSurfaces[window];
        retVal->valid = GIL_TRUE;

        // In case of using single buffer (not Double buffer)
        // retVal->pBuffer = gsScreen.pBuffer;
        // retVal->bufferSize = gsScreen.bufferSize;

        retVal->bufferSize = w * h * gil_helper_getbpp(gsScreen.format);
        retVal->format = gsScreen.format;
        retVal->x = x;
        retVal->y = y;
        retVal->w = w;
        retVal->h = h;

        if (NULL == pDoubleBuffer)
        {
            pDoubleBuffer = malloc(retVal->bufferSize);
        }

        retVal->pBuffer = pDoubleBuffer;

        printf("gilCreateWindow(%d, %ld, %ld, %ld, %ld)\r\n", window, x, y, w, h);
        printf("\tCreated window: b: %p, bs: %ld, x: %ld, y: %ld, w: %ld, h: %ld, f: %d, v: %s\r\n",
               retVal->pBuffer, retVal->bufferSize,
               retVal->x, retVal->y, retVal->w, retVal->h,
               retVal->format,
               retVal->valid ? "True" : "False");

        GIL_ASSERT(NULL != pDoubleBuffer);
    }

    return retVal;
}

GILBoolean gilIsValidSurface(GILSurface surface, GILBoolean check4content)
{
    return GIL_REQUIRE(surface) // check if context is valid - additional check to see if surface is special NULL pointer
        && (!check4content || GIL_REQUIRE(surface->valid)) // valid flag set?
        && GIL_REQUIRE(surface >= &gsSurfaces[0]) // check if surface points to valid memory
        && GIL_REQUIRE(surface < &gsSurfaces[GIL_MAX_SURFACES]);
}

GILBoolean gilHandleWindowEvents(GILContext context)
{
    return GIL_TRUE;
}

GILBoolean gilSurfaceToSWSurface(GILSurface s, GIL_SW_Surface * swsurface)
{
    GILBoolean bRet = swsurface && ((s != &gsScreen) ? gilIsValidSurface(s, GIL_TRUE) : GIL_TRUE);

    if (swsurface)
    {
        // To render direct to target buffer we should use screenWidth
        // for calculating alignment.
        swsurface->alignment = bRet ? gil_helper_getbpp(s->format) * s->w : 0;
        swsurface->bytes = bRet ? s->bufferSize : 0;
        swsurface->x = bRet ? s->x : 0;
        swsurface->y = bRet ? s->y : 0;
        swsurface->w = bRet ? s->w : 0;
        swsurface->h = bRet ? s->h : 0;
        swsurface->p = bRet ? s->pBuffer : NULL;
        swsurface->format = bRet ? s->format : GIL_FORMAT_INVALID;

        // printf("gilSurfaceToSWSurface: a: %ld, b: %ld, w: %ld, h: %ld, p: %p)\r\n",
        //        swsurface->alignment,
        //        swsurface->bytes,
        //        swsurface->w,
        //        swsurface->h,
        //        swsurface->p);
    }

    return bRet;
}

GILBoolean gilSwapBuffers(GILSurface surface)
{
    if (gilIsValidSurface(surface, GIL_TRUE))
    {
        GIL_SW_Surface src;
        GIL_SW_Surface dest;

        if (GIL_REQUIRE(gilSurfaceToSWSurface(&gsScreen, &dest)) &&
            GIL_REQUIRE(gilSurfaceToSWSurface(surface, &src)) &&
            GIL_REQUIRE(src.format == dest.format))
        {
            gil_sw_bitblit_copy(&dest, &src);
        }
    }

    return GIL_TRUE;
}

//GILFormat gilSurfaceGetFormat(GILSurface surface)
//{
//  GILFormat retVal = GIL_FORMAT_INVALID;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface, GIL_FALSE))
//  {
//      retVal = s->format;
//  }
//
//  return retVal;
//}

//int32_t gilSurfaceGetWidth(GILSurface surface)
//{
//  int32_t retVal = 0;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface,GIL_FALSE))
//  {
//      retVal = s->mBitmapInfo.bmiHeader.biWidth;
//  }
//
//  return retVal;
//}
//
//int32_t gilSurfaceGetHeight(GILSurface surface)
//{
//  int32_t retVal = 0;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface, GIL_FALSE))
//  {
//      retVal = (- s->mBitmapInfo.bmiHeader.biHeight);
//  }
//
//  return retVal;
//}
//
//uint8_t gilSurfaceGetBPP(GILSurface surface)
//{
//  uint8_t retVal = 0;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface, GIL_FALSE))
//  {
//      retVal = gil_helper_getbpp(s->format);
//  }
//
//  return retVal;
//}
//
//uint32_t gilSurfaceGetMemorySize(GILSurface surface)
//{
//  uint32_t retVal = 0;
//  gil_surface_t * s = (gil_surface_t*)surface;
//
//  if (gilIsValidSurface(surface, GIL_FALSE))
//  {
//      retVal = s->bufferSize;
//  }
//
//  return retVal;
//}
