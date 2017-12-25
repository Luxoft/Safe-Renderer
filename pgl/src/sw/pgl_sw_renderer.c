/******************************************************************************
**
**   File:        pgl_sw_renderer.c
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

#include "pgl_sw_renderer.h"
#include "pgl_assert.h"


static void checkPreconditions(const PGL_SW_Surface *dest, const PGL_SW_Surface *source, const uint8_t bpp)
{
    PGL_ASSERT((bpp == 1u) || (bpp == 2u) || (bpp == 4u)); // we support only 1, 2 and 4 bytes per pixel

    PGL_ASSERT(dest);
    //PGL_ASSERT(dest->x >= 0); // beginning could be negative?
    //PGL_ASSERT(dest->y >= 0);
    PGL_ASSERT(dest->w >= 0);
    PGL_ASSERT(dest->h >= 0);
    PGL_ASSERT((dest->y+dest->h-1)*dest->alignment+(dest->x+dest->w)*bpp <= dest->bytes); // is rect maximum inside memory boundaries

    PGL_ASSERT(source);
    //PGL_ASSERT(source->x >= 0);
    //PGL_ASSERT(source->y >= 0);
    PGL_ASSERT(source->w >= 0);
    PGL_ASSERT(source->h >= 0);
    PGL_ASSERT((source->y+source->h-1)*source->alignment+(source->x+source->w)*bpp <= source->bytes); // is rect maximum inside memory boundaries

    // check for correct start memory alignment
    PGL_ASSERT( ((bpp == 2u) && (((uint32_t)dest->p & 1) == 0)) || ((bpp == 4u) && (((uint32_t)dest->p & 3) == 0)) );
    PGL_ASSERT( ((bpp == 2u) && (((uint32_t)source->p & 1) == 0)) || ((bpp == 4u) && (((uint32_t)source->p & 3) == 0)));

    // check for correct alignment of columns
    PGL_ASSERT( ((bpp == 2u) && (((uint32_t)dest->alignment & 1) == 0)) || ((bpp == 4u) && (((uint32_t)dest->alignment & 3) == 0)) );
    PGL_ASSERT( ((bpp == 2u) && (((uint32_t)source->alignment & 1) == 0)) || ((bpp == 4u) && (((uint32_t)source->alignment & 3) == 0)) );
}

// To do: Which functions are independent / and wich are dependent?

// --> We have a SW bitblitting library (platform independent)
// --> We have functions to get memory pointers - render targets (platform dependent)

// --> A Glue piece which combines windowing system with renderer
// --> Windows implementation which get Windows and memory pointer in RAM

uint8_t pgl_helper_getbpp(PGLFormat format)
{
    // check that format is supported
    uint8_t bpp = 0u;
    if (format < PGL_FORMAT_1_BPP)
        bpp = 1u;
    else if (format < PGL_FORMAT_2_BPP)
        bpp = 2u;
    else if (format < PGL_FORMAT_3_BPP)
        PGL_ASSERT(PGL_FALSE); // we do not support 3 bpp format
    else if (format < PGL_FORMAT_4_BPP)
        bpp = 4u;

    return bpp;
}

// What interface needs the SW renderer
// SW renderer needs dest - memory pointer, x & y and alignment / offset to come to next column
// SW renderer needs src - memory pointer , x & y, width & height and alignment
// SW renderer can handle all format by simply copying content (no alpha blending in one render target support / bitblit over bitblit)

void pgl_sw_bitblit_copy(PGL_SW_Surface *dest, PGL_SW_Surface *source, PGLFormat format)
{
    // check that format is supported
    const uint8_t bpp =pgl_helper_getbpp(format);
    checkPreconditions(dest, source, bpp);

    PGL_SW_Pointer ps = source->p + source->y*source->alignment + source->x*bpp; // calculate start position of source memory pointer
    PGL_SW_Pointer pd = dest->p + dest->y*dest->alignment + dest->x*bpp; // calculate start position of dest memory pointer
    int32_t offsets = source->alignment - source->w*bpp; // calculate how many bytes need to be added to source when switching to the next column
    int32_t offsetd = dest->alignment - source->w*bpp; // attention: width of destination is only for informational purpose. No scaling applied. Currently ignored
    const PGL_SW_Pointer psBegin = source->p;
    const PGL_SW_Pointer psEnd = psBegin + source->bytes;
    const PGL_SW_Pointer pdBegin = dest->p;
    const PGL_SW_Pointer pdEnd = pdBegin + dest->bytes;
    for (int32_t y = 0; y < source->h; ++y)
    {
        for (int32_t x = 0; x < source->w; ++x)
        {
            // to make it safe check if pointers are inside valid boundaries
            // as negative values are acceptable --> we do have the following assertions active
            //PGL_ASSERT((ps >= psBegin) && (ps < psEnd));
            //PGL_ASSERT((pd >= pdBegin) && (pd < pdEnd));
            if ((ps >= psBegin) && (ps < psEnd) && (pd >= pdBegin) && (pd < pdEnd))
            {
                switch (bpp)
                {
                    case 1u:
                        *pd = *ps;
                        break;
                    case 2u:
                        *((uint16_t*)(pd)) = *((uint16_t*)(ps));
                        break;
                    case 4u:
                        *((uint32_t*)(pd)) = *((uint32_t*)(ps));
                        break;
                }
            }
            ps += bpp;
            pd += bpp;
        }
        ps += offsets;
        pd += offsetd;
    }
}

uint32_t pgl_sw_compare(const PGL_SW_Surface *dest, const PGL_SW_Surface *source, PGLFormat format)
{
    // check that format is supported
    const uint8_t bpp =pgl_helper_getbpp(format);
    checkPreconditions(dest, source, bpp);

    PGL_SW_Pointer ps = source->p + source->y*source->alignment + source->x*bpp; // calculate start position of source memory pointer
    PGL_SW_Pointer pd = dest->p + dest->y*dest->alignment + dest->x*bpp; // calculate start position of dest memory pointer
    int32_t offsets = source->alignment - source->w*bpp; // calculate how many bytes need to be added to source when switching to the next column
    int32_t offsetd = dest->alignment - source->w*bpp; // attention: width of destination is only for informational purpose. No scaling applied. Currently ignored
    const PGL_SW_Pointer psBegin = source->p;
    const PGL_SW_Pointer psEnd = psBegin + source->bytes;
    const PGL_SW_Pointer pdBegin = dest->p;
    const PGL_SW_Pointer pdEnd = pdBegin + dest->bytes;
    uint32_t failures = 0;
    for (int32_t y = 0; y < source->h; ++y)
    {
        for (int32_t x = 0; x < source->w; ++x)
        {
            if ((ps >= psBegin) && (ps < psEnd) && (pd >= pdBegin) && (pd < pdEnd))
            {
                switch (bpp)
                {
                    case 1u:
                        if (*pd != *ps)
                        {
                            ++failures;
                        }
                        break;
                    case 2u:
                        if (*((uint16_t*)(pd)) != *((uint16_t*)(ps)))
                        {
                            ++failures;
                        }
                        break;
                    case 4u:
                        if (*((uint32_t*)(pd)) != *((uint32_t*)(ps)))
                        {
                            ++failures;
                        }
                        break;
                }
            }
            else
            {
                ++failures;
            }
            ps += bpp;
            pd += bpp;
        }
        ps += offsets;
        pd += offsetd;
    }
    return failures;
}
