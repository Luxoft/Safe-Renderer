/******************************************************************************
**
**   File:        pgl.h
**   Description: Populus Graphics Library (C interface)
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


/**
 Some requirements
 - the API should support 2 windows / layers in 2 different threads/tasks (i.e. 2 contexts)
 - the API should support 2 windows / layers in 1 thread (i.e. 1 context)
 - the API should support rendering into an offscreen buffer (at least it should be extensible in this direction)
 - the API should support both ROM (directly rendered from ROM w/o RAM usage) and (V)RAM textures for the same instance (i.e. if the image buffer needs to be copied)
 - invalid return values equal to 0 / NULL
 Questions which need clarification
 - int32_t is 4 digits fractional part for u/v coordinates (assumption: to have better user experience when doing scaling animations) - Question: Does it make sense to also have
   positions as fixed point (e.g. translation animations or when using OpenGL). If system doesn't support implementation can easily get rid of fractional part!
 - visibility of window / layer: Idea leave it outside of first prototype. Suggestion: Layer gets visible in first swapBuffer call.
 - Initialization of buffer? --> Upto implementation?
 - Premultiplied alpha?
*/

#ifndef PGL_H
#define PGL_H

#include <stdint.h>

#ifdef WIN32
#define PGL_API extern __declspec(dllexport)
#else
#define PGL_API extern
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef int PGLBoolean;
typedef struct pgl_surface_t* PGLSurface;
typedef struct pgl_context_t* PGLContext;
typedef struct pgl_texture_t* PGLTexture;

#define PGL_FALSE 0
#define PGL_TRUE 1

typedef enum
{
    PGL_FORMAT_A_8,           ///< alpha only
    PGL_FORMAT_P_8_ARGB_8888, ///< 8 bit palette with 32 bit colors
    PGL_FORMAT_P_8_BGRA_8888, ///< 8 bit palette with 32 bit colors
    PGL_FORMAT_P_8_RGBA_8888, ///< 8 bit palette with 32 bit colors
    PGL_FORMAT_P_8_RGB_888,   ///< 8 bit palette with 24 bit colors
    PGL_FORMAT_P_8_RGB_565,   ///< 8 bit palette with 16 bit colors
    PGL_FORMAT_1_BPP, 	  ///< all formats before use 1 byte per pixel
    PGL_FORMAT_RGB_565,
    PGL_FORMAT_BGR_565,
    PGL_FORMAT_2_BPP, 	  ///< all formats before use less than 2 byte per pixel
    PGL_FORMAT_3_BPP, 	  ///< all formats before use less than 3 byte per pixel
    PGL_FORMAT_ARGB_8888,
    PGL_FORMAT_BGRA_8888,
    PGL_FORMAT_RGBA_8888,
    PGL_FORMAT_4_BPP, 	  ///< all formats before use less than 4 byte per pixel
	PGL_FORMAT_INVALID
} PGLFormat;

typedef enum
{
    PGL_NO_ERROR = 0,
    PGL_INVALID_OPERATION
} PGLError;

/**
 * Initializes the library.
 * Used for global configuration. Should only be called once.
 */
PGL_API void pglInit(void);

/**
 * Creates a new window or layer and returns its surface. Does not necessarily be visible (can also be offscreen depending on window configuration). Memory may be uninitialized.
 * A call to pglSetColor, pglDrawArea or a fullscreen background bitmap (pglDrawQuad) is needed to have a defined initial state.
 * @param window window identifier (might refer to some library configuration which specifies the detailed window configuration like double buffering, color format, etc.)
 * @param x x position
 * @param y y position
 * @param w window width
 * @param h window height
 */
PGL_API PGLSurface pglCreateWindow(uint8_t window, int32_t x, int32_t y, int32_t w, int32_t h);

/**
 * Creates a rendering context
 */
PGL_API PGLContext pglCreateContext(void);

/**
 * Attaches the rendering context to a surface (in which the results of drawing commands will be stored)
 * @param context the rendering context to be attached to the surface
 * @param rendertarget the render target
 */
PGL_API PGLBoolean pglSetSurface(PGLContext context, PGLSurface surface);

/**
 * Sets the drawing color for subsequent drawing commands
 * the color is used for pglDrawArea() and also for pglDrawQuad if the texture contains no color information
 */
PGL_API PGLBoolean pglSetColor(PGLContext context, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

/**
 * Creates a new (empty) texture
 */
PGL_API PGLTexture pglCreateTexture(PGLContext context);

/**
 * Loads pixel data into the texture
 * @param t texture
 * @param width width in pixels
 * @param height height in pixels
 * @param format color format
 * @param copy indicates if the data needs to be copied. If set to false the client guarantees that data pointer is valid until shutdown (e.g. textures in ROM)
 * @param data pixel data
 */
PGL_API PGLBoolean pglLoadTexture(PGLTexture, uint32_t width, uint32_t height, PGLFormat format, PGLBoolean copy, const void* data);

/**
 * Assigns a texture to the context
 *
 * @note If the texture only contains alpha information, the color will be used from the color attribute
 */
PGL_API void pglBindTexture(PGLContext context, PGLTexture t);

/**
 * Sets the clipping area for subsequent drawing commands
 */
PGL_API PGLBoolean pglSetClip(PGLContext context, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

/**
 * Clears the current surface with the current fill color
 */
PGL_API void pglClear(PGLContext context);

/**
 * Draws a rectangle with the current fill color
 */
PGL_API void pglDrawArea(PGLContext ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

/**
 * Draws a rectangle with the current texture reference (interface allows scaling, what happens if coordinates oustide bounds?)
 * @param x1 Specify the start point X1 of the drawing coordinate system.
 * @param y1 Specify the start point Y1 of the drawing coordinate system.
 * @param u1 Specify the U1 of source coordinate system corresponding to the value, (X1, Y1) of drawing coordinate system.
 * @param v1 Specify the V1 of source coordinate system corresponding to the value, (X1, Y1) of drawing coordinate system.
 * @param x2 Specify the end point X2 of the drawing coordinate system.
 * @param y2 Specify the end point Y2 of the drawing coordinate system.
 * @param u2 Specify the U2 of source coordinate system corresponding to the value, (X2, Y2) of drawing coordinate system.
 * @param v2 Specify the V2 of source coordinate system corresponding to the value, (X2, Y2) of drawing coordinate system.
 *
 * Each coordinate is given by the fixed-point number in the fractional part 4 bits.
 */
PGL_API void pglDrawQuad(PGLContext ctx, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2);

/**
 * Post the window buffer to the display
 * Only works for window surfaces
 */
PGL_API PGLBoolean pglSwapBuffers(PGLSurface surface);

/**
 * Checks the current surface with the currently bound texture
 * @param context the context will contain the reference texture and has bound the surface which is about to be verified
 * @param x1...y2 coordinates on the surface to verify
 * @param u1...v2 coordinates on the texture
 */
PGL_API PGLBoolean pglVerify(PGLContext context, int32_t x1, int32_t y1, int32_t u1, int32_t v1, int32_t x2, int32_t y2, int32_t u2, int32_t v2);

/**
 * Returns the value of the error flag.
 *
 * Each detectable error is assigned a numeric code and symbolic name. When an error occurs, the error flag is set
 * to the appropriate error code value. No other errors are recorded until pglGetError is called, the error code is returned,
 * and the flag is reset to PGL_NO_ERROR. If a call to pglGetError returns PGL_NO_ERROR, there has been no detectable error
 * since the last call to pglGetError, or since the GL was initialized.
 *
 * To allow for distributed implementations, there may be several error flags. If any single error flag has recorded an error,
 * the value of that flag is returned and that flag is reset to PGL_NO_ERROR when pglGetError is called.
 * If more than one flag has recorded an error, pglGetError returns and clears an arbitrary error flag value.
 * Thus, pglGetError should always be called in a loop, until it returns PGL_NO_ERROR, if all error flags are to be reset.
 *
 * Initially, all error flags are set to PGL_NO_ERROR.
 */
PGL_API PGLError pglGetError(PGLContext context);

/**
 * Handles the window events and indicates if the window has been closed
 *
 * This function may be mainly useful for simulation environments or systems, which use a window manager.
 * The engine will call it in its main loop independently from drawing or verification.
 * @return true indicates that the window has been closed by the window manager
 */
PGL_API PGLBoolean pglHandleWindowEvents(PGLContext context);

#ifdef __cplusplus
}
#endif

#endif // PGL_H
