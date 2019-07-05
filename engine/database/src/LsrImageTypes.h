#ifndef LSRIMAGETYPES_H
#define LSRIMAGETYPES_H

/******************************************************************************
**
**   File:        LsrImageTypes.h
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

#include "LsrTypes.h"

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
    enum Encoding
    {
        ENCODING_RAW=0,  ///< Raw.
        ENCODING_RLE=1,  ///< RLE.
        ENCODING_PALETTE=2, ///< Palette.
        ENCODING_FLZ=4, ///< Fast LZ.
        ENCODING_DIFF=8, ///< Differences from previous frame.
        ENCODING_RLE2=16,  ///< RLE with switched endian.
        ENCODING_EXTERNAL=32  ///< External utility compression.
    };

#pragma pack(push)
#pragma pack(1)
    /**
    * GUID type
    */
    struct GUID
    {
        U32 Data1;
        U16 Data2;
        U16 Data3;
        U8 Data4[8];
    };

    /**
    * GUID for a LSR Image
    */
    const LsrImageTypes::GUID simpleGuid = {0xa09f2aa6, 0xf5c0, 0x45df, {0xb3, 0xed, 0x59, 0xc7, 0x47, 0x9d, 0x57, 0xbc}};

    /**
    * GUID for a placeholder image
    */
    const LsrImageTypes::GUID placeholderGuid = {0xa173ca0d, 0x14cb, 0x4dbd, {0x84, 0x88, 0x6a, 0xf4, 0xc4, 0x3e, 0x6b, 0x54}};

    /**
    * GUID for an atlas placeholder image
    */
    const LsrImageTypes::GUID atlasPlaceholderGuid = {0x2e08c646, 0x1e8e, 0x46dc, {0x8e, 0xf1, 0x99, 0xa9, 0xb5, 0x28, 0xa6, 0xc1}};

    /**
    * A placeholder image is generated when an image exists as a part in another image.
    */
    struct PlaceholderImg
    {
        LsrImageTypes::GUID guid; ///< GUID
        U32 baseImageID; ///< The ID of the image where this image is stored.
        U32 frame; ///< Which frame in the base image contains this image.

        /**
         *  Additional meta information about frame. Meaning depends on GUID.
         *
         *  For atlas placeholders this field corresponds to the ID of atlas frame within base image frame.
         *  For animation placeholders this field corresponds to the closest lower frame that is not diff coded
         *  and is not dependent on the previous frame.
         */
        U32 metaFrameId;
    };

    /**
    * Header for the image.
    */
    struct ImgHeader
    {
        LsrImageTypes::GUID guid; ///< GUID
        U32 width; ///< The width of the image
        U32 height; ///< The height of the image
        U32 frames; ///< The number of frames in the image.
    };

    /**
    * Header for a frame within the image.
    */
    struct FrameHeader
    {
        U32 imageDataSize; ///< The size of the frame image data in bytes
        U32 pitch; ///< The number of pixels (not bytes) in a row. Could be more than width
        U32 transparentColor; ///< This color will be replaced by transparent pixels if useTransparantColor is true.
        U16 nOfPadBytes; ///< Number of pad bytes following the frame image data.
        U16 nOfPalettePadBytes; ///< Number of pad bytes following the palette data
        U8 pixelformat; ///< The format of the pixels
        U8 useTransparantColor; ///< true if transparentColor should be used
        U8 encoding; ///< The encoding of the frame.
        U8 reserved1; ///< Reserved.
        U16 paletteSize; ///< in number of colors not bytes
        U8 reserved2; ///< Reserved.
        U8 reserved3; ///< Reserved.

        U32 atlasFrames; ///< Number of atlas frames in this frame.
    };

    /**
    * Atlas frame information.
    */
    struct AtlasFrameDescription
    {
        U16 posX;
        U16 posY;
        U16 width;
        U16 height;
    };

#pragma pack(pop)

    P_STATIC_ASSERT(sizeof(GUID) == 16 ,"POI marker size (GUID)");
    P_STATIC_ASSERT(sizeof(ImgHeader) == 28 ,"Image header size");
    P_STATIC_ASSERT(sizeof(PlaceholderImg) == 28 ,"Image placeholder header size");
    P_STATIC_ASSERT(sizeof(FrameHeader) == 28 ,"Frame header size");
    P_STATIC_ASSERT(sizeof(AtlasFrameDescription) == 8 ,"AtlasFrameDescription header size");
}

} // namespace lsr


#endif // LSRIMAGETYPES_H
