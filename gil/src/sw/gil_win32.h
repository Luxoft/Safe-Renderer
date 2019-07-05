#ifndef GIL_WIN32_H
#define GIL_WIN32_H

/******************************************************************************
**
**   File:        gil_win32.h
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

#include "gil.h"
#include "gil_sw_renderer.h"

#define GIL_MAX_SURFACES 4

#ifdef __cplusplus
extern "C"
{
#endif

void gilInit(GILConfig config);
void gilUninit(void);
GILSurface gilCreateWindow(uint8_t window, int32_t x, int32_t y, int32_t w, int32_t h);
GILBoolean gilSwapBuffers(GILSurface surface);

/**
 * Checks if the passed in surface is valid
 * @param surface the surface which to check for validity
 * @param check4content if GIL_TRUE pixel data needs to be included to have a positive result
 * @return returns GIL_TRUE if the rendertarget is valid
 */
GILBoolean gilIsValidSurface(GILSurface surface, GILBoolean check4content);

/**
* stores the data of a surface in a SW surface struct which is returned
* @param surface the surface which to check for validity
* @param swsurface returns the specifics of a surface in a SWSurface struct (width, height, ...)
* @param format returns the format of the surface. Pointer is allowed to be 0
* @return returns GIL_TRUE if the returned SW surface is valid and contains Pixeldata
*/
GILBoolean gilSurfaceToSWSurface(GILSurface surface, GIL_SW_Surface * swsurface);

//GILFormat gilSurfaceGetFormat(GILSurface surface);

//int32_t gilSurfaceGetWidth(GILSurface surface);
//int32_t gilSurfaceGetHeight(GILSurface surface);
//uint8_t gilSurfaceGetBPP(GILSurface surface);
//uint32_t gilSurfaceGetMemorySize(GILSurface surface);

#ifdef __cplusplus
}
#endif


#endif // GIL_WIN32_H
