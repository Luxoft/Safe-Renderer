#ifndef LUXOFTSAFERENDERER_LSR_IMAGE_H
#define LUXOFTSAFERENDERER_LSR_IMAGE_H

/******************************************************************************
**
**   File:        LsrImage.h
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

#include "LsrTypes.h"
#include "ResourceBuffer.h"

namespace lsr
{
    /**
    * LSR image uses a layout optimized to be read and displayed by the LSR Engine.
    * Image layout:
    *
    *  ImgHeader
    *  FrameHeader, frame 1
    *  Palette data (if any), frame 1
    *  Pad bytes, frame 1
    *  Image data, frame 1
    *  Pad bytes, frame 1
    *  ...
    *  FrameHeader, frame n
    *  Palette data (if any), frame n
    *  Pad bytes, frame n
    *  Image data, frame n
    *  Pad bytes, frame n
    */
namespace LsrImageTypes
{
    enum PixelSize
    {
        PIXEL_SIZE_1BYTE=1,
        PIXEL_SIZE_2BYTE=4,
        PIXEL_SIZE_3BYTE=16,
        PIXEL_SIZE_4BYTE=64
    };

    enum PixelFormat
    {
        PIXEL_FORMAT_UNKNOWN = 0,
        PIXEL_FORMAT_RGB565 = PIXEL_SIZE_2BYTE,
        PIXEL_FORMAT_RGB888 = PIXEL_SIZE_3BYTE,
        PIXEL_FORMAT_BGR888 = PIXEL_SIZE_3BYTE + 1,
        PIXEL_FORMAT_RGBA8888 = PIXEL_SIZE_4BYTE,
        PIXEL_FORMAT_BGRA8888 = PIXEL_SIZE_4BYTE + 1
    };

    /**
    * Header for the image.
    */
    struct ImgHeader
    {
        const U32 width; ///< The width of the image in pixels
        const U32 height; ///< The height of the image in pixels
        const U32 clutSize; ///< The number of colors in the clut
        const U32 imageDataSize; ///< The size of the frame image data in bytes
        const U32 pitch; ///< The number of pixels (not bytes) in a row. Could be more than width
        const PixelFormat format; ///< The format of the pixels
        const U8 bitDepth; ///< Bits per pixel (if palette is used)
    };
}


struct LsrImage
{
    const LsrImageTypes::ImgHeader header;
    const U8* const palette; // color lookup table
    const U8* const data; // pixel data

    U32 getWidth() const
    {
        return header.width;
    }

    U32 getHeight() const
    {
        return header.height;
    }

    LsrImageTypes::PixelFormat getPixelFormat() const
    {
        return header.format;
    }

    const void* getPixelData() const
    {
        return data;
    }
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_LSR_IMAGE_H
