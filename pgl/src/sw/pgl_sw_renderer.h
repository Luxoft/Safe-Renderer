#ifndef PGL_SW_RENDERER_H
#define PGL_SW_RENDERER_H

/******************************************************************************
**
**   File:        pgl_sw_renderer.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "pgl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t* PGL_SW_Pointer;
typedef struct
{
    PGL_SW_Pointer p; // pointer to the pixel data
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
    int32_t alignment; // how many bytes one line of pixels occupy (could be more than w*bpp due to CPU memory alignment issues)
    int32_t bytes; // memory ends at p + bytes  - to allow additional checks for being sure to keep inside boundaries
} PGL_SW_Surface;

/**
 * Gets the amount of bytes which one pixel occupies
 * @param format the format for which to determine the bpp value
 * @return returns the bytes per pixel value
 */
uint8_t pgl_helper_getbpp(PGLFormat format);


/**
 * Does a copy bitblit (no alpha blending). Simply pixel values are copied. Can handle 1,2 and 4 bytes per pixel. Destination and Source surface have the same format.
 * Source and dest rectangles are part of the input structures describing the surfaces. Scaling is not supported. Several checks are applied to prevent out of boundary accesses at any circumstance.
 * @param dest the destination surface in which to copy (bitblit) an area out of the source surface. w and h parameter of dest are used for validity checks. Scaling is not applied. x, y is the position
 *        inside the dest to which the source surface is copied.
 * @param source the source surface. It is valid to just copy a portion (x,y / w,h) out of the source surface to the destination.
 * @param format the format in which source and dest are structured. Currently 1, 2 and 4 byte surface formats are supported
 * @return returns the bytes per pixel value
 */
void pgl_sw_bitblit_copy(PGL_SW_Surface *dest, PGL_SW_Surface *source, PGLFormat format);

/**
 * Checks if both surfaces contain the same content
 * @return the number of different pixels
 */
uint32_t pgl_sw_compare(const PGL_SW_Surface *dest, const PGL_SW_Surface *source, PGLFormat format);

#ifdef __cplusplus
}
#endif

#endif // PGL_SW_RENDERER_H
