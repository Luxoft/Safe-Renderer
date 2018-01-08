#ifndef PGL_SW_RENDERER_GLUE_H
#define PGL_SW_RENDERER_GLUE_H

/******************************************************************************
**
**   File:        pgl_sw_renderer_glue.h
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

#define PGL_MAX_CONTEXTS 4
#define PGL_MAX_TEXTURES 64


#ifdef __cplusplus
extern "C" {
#endif

/**
* Checks if the passed in context is valid
* @param context the context which to check for validity
* @return returns PGL_TRUE if the context is valid
*/
PGLBoolean pglIsValidContext(PGLContext context);

/**
* Checks if the passed in texture is valid
* @param texture the texture which to check for validity
* @param check4content if PGL_TRUE pixel data needs to be included to have a positive result
* @return returns PGL_TRUE if the texture is valid
*/
PGLBoolean pglIsValidTexture(PGLTexture texture, PGLBoolean check4content);

PGLContext pglCreateContext(void);
PGLBoolean pglSetSurface(PGLContext context, PGLSurface surface);
PGLTexture pglCreateTexture(PGLContext context);
PGLBoolean pglLoadTexture(PGLTexture texture, uint32_t width, uint32_t height, PGLFormat format, PGLBoolean copy, const void* data);
void pglBindTexture(PGLContext context, PGLTexture t);
void pglDrawQuad(PGLContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2);

#ifdef __cplusplus
}
#endif

#endif // PGL_SW_RENDERER_GLUE_H
