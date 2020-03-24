#ifndef GIL_SW_RENDERER_GLUE_H
#define GIL_SW_RENDERER_GLUE_H

/******************************************************************************
**
**   File:        gil_sw_renderer_glue.h
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

#define GIL_MAX_CONTEXTS 4
#define GIL_MAX_TEXTURES 64


#ifdef __cplusplus
extern "C" {
#endif

/**
* Checks if the passed in context is valid
* @param context the context which to check for validity
* @return returns GIL_TRUE if the context is valid
*/
GILBoolean gilIsValidContext(GILContext context);

/**
* Checks if the passed in texture is valid
* @param texture the texture which to check for validity
* @param check4content if GIL_TRUE pixel data needs to be included to have a positive result
* @return returns GIL_TRUE if the texture is valid
*/
GILBoolean gilIsValidTexture(GILTexture texture, GILBoolean check4content);

GILContext gilCreateContext(void);
GILBoolean gilSetSurface(GILContext context, GILSurface surface);
GILTexture gilCreateTexture(GILContext context);
void gilBindTexture(GILContext context, GILTexture t);
void gilDrawQuad(GILContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2);

#ifdef __cplusplus
}
#endif

#endif // GIL_SW_RENDERER_GLUE_H
