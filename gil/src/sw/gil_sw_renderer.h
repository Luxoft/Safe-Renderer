#ifndef GIL_SW_RENDERER_H
#define GIL_SW_RENDERER_H

/******************************************************************************
**
**   File:        gil_sw_renderer.h
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

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t* GIL_SW_Pointer;
typedef struct
{
    GIL_SW_Pointer p; // pointer to the pixel data
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
    int32_t alignment; // how many bytes one line of pixels occupy (could be more than w*bpp due to CPU memory alignment issues)
    int32_t bytes; // memory ends at p + bytes  - to allow additional checks for being sure to keep inside boundaries
    GILFormat format;
} GIL_SW_Surface;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} GIL_SW_Color;

/**
 * Gets the amount of bytes which one pixel occupies
 * @param format the format for which to determine the bpp value
 * @return returns the bytes per pixel value
 */
uint8_t gil_helper_getbpp(GILFormat format);


/**
 * Does a copy bitblit (no alpha blending). Simply pixel values are copied. Can handle 1,2,3 and 4 bytes per pixel. Destination and Source surface have the same format.
 * Source and dest rectangles are part of the input structures describing the surfaces. Scaling is not supported. Several checks are applied to prevent out of boundary accesses at any circumstance.
 * @param dest the destination surface in which to copy (bitblit) an area out of the source surface. w and h parameter of dest are used for validity checks. Scaling is not applied. x, y is the position
 *        inside the dest to which the source surface is copied.
 * @param source the source surface. It is valid to just copy a portion (x,y / w,h) out of the source surface to the destination.
 * @param format the format in which source and dest are structured. Currently 1, 2, 3 and 4 byte surface formats are supported
 */
void gil_sw_bitblit_copy(GIL_SW_Surface* dest, GIL_SW_Surface* source);

/**
 * Set color to the surface. Simply pixel values are copied.
 * Dest rectangle is part of the input structures describing the surfaces.
 * @param dest the destination surface in which to copy (bitblit) an color data.
 * @param color color to be set
 * @param format the format in which source and dest are structured. Currently 1, 2, 3 and 4 byte surface formats are supported
 */
void gil_sw_set_color(GIL_SW_Surface* dest, const GIL_SW_Color* color);

/**
 * Checks if both surfaces contain the same content
 * @return the number of different pixels
 */
uint32_t gil_sw_compare(const GIL_SW_Surface* dest, const GIL_SW_Surface* source);

void gil_helper_set_8_color(GIL_SW_Pointer dest, const GIL_SW_Color* color, GILFormat format);
void gil_helper_set_16_color(GIL_SW_Pointer dest, const GIL_SW_Color* color, GILFormat format);
void gil_helper_set_24_color(GIL_SW_Pointer dest, const GIL_SW_Color* color, GILFormat format);
void gil_helper_set_32_color(GIL_SW_Pointer dest, const GIL_SW_Color* color, GILFormat format);

#ifdef __cplusplus
}
#endif

#endif // GIL_SW_RENDERER_H
