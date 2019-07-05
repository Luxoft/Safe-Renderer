/******************************************************************************
**
**   File:        LsrImageTest.cpp
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

#include <gtest/gtest.h>
#include "LsrImage.h"
#include "LsrImageTypes.h"

using lsr::LsrImage;
using lsr::ResourceBuffer;
using namespace lsr::LsrImageTypes;

namespace
{
    struct Image
    {
        ImgHeader img;
        FrameHeader frame;
        U8 data[256];
    };
}

extern std::string g_lastErrorMsg;



TEST(LsrImageTest, empty)
{
    ResourceBuffer buf;
    LsrImage img(buf);

    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, tooSmall)
{
    char data[] = { 1, 42, 5, 7, 2, 73, 2 }; // garbage
    ResourceBuffer buf(data, sizeof(data));
    LsrImage img(buf);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(0u, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, invalidHeader)
{
    char data[sizeof(ImgHeader) + sizeof(FrameHeader)] = { 0 };
    ResourceBuffer buf(data, sizeof(data));
    LsrImage img(buf);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, placeholder)
{
    Image data = {0};
    data.img.guid = placeholderGuid;
    ResourceBuffer buf(&data, sizeof(data));
    g_lastErrorMsg = "";
    LsrImage img(buf);
    EXPECT_EQ("LsrImage: placeholder images are not supported on this platform", g_lastErrorMsg);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, atlas)
{
    Image data = {0};
    data.img.guid = atlasPlaceholderGuid;
    ResourceBuffer buf(&data, sizeof(data));
    g_lastErrorMsg = "";
    LsrImage img(buf);
    EXPECT_EQ("LsrImage: atlas images are not supported on this platform", g_lastErrorMsg);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, multiframe)
{
    Image data = {0};
    data.img.guid = simpleGuid;
    data.img.frames = 2;
    ResourceBuffer buf(&data, sizeof(data));
    g_lastErrorMsg = "";
    LsrImage img(buf);
    EXPECT_EQ("LsrImage: multiframe images are not supported on this platform", g_lastErrorMsg);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, altasFrames)
{
    Image data = {0};
    data.img.guid = simpleGuid;
    data.img.frames = 1;
    data.frame.atlasFrames = 2;
    data.frame.pixelformat = 22; // invalid enum value
    ResourceBuffer buf(&data, sizeof(data));
    g_lastErrorMsg = "";
    LsrImage img(buf);
    EXPECT_EQ("LsrImage: atlas frames are not supported", g_lastErrorMsg);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, unsupportedEncoding)
{
    Image data = {0};
    data.img.guid = simpleGuid;
    data.img.frames = 1;
    data.frame.atlasFrames = 0;
    data.frame.encoding = ENCODING_PALETTE;
    data.frame.pixelformat = 1; // invalid enum value
    ResourceBuffer buf(&data, sizeof(data));
    g_lastErrorMsg = "";
    LsrImage img(buf);
    EXPECT_EQ("LsrImage: raw encoding is required", g_lastErrorMsg);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, bad_size)
{
    Image data = {0};
    data.img.guid = simpleGuid;
    data.img.frames = 1;
    data.frame.atlasFrames = 0;
    data.frame.encoding = ENCODING_RAW;
    data.frame.pixelformat = 5; // invalid enum value
    data.frame.imageDataSize = sizeof(data)+1;
    ResourceBuffer buf(&data, sizeof(data));
    g_lastErrorMsg = "";
    LsrImage img(buf);
    EXPECT_EQ("LsrImage: size out of bounds", g_lastErrorMsg);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, bad_palette_size)
{
    Image data = {0};
    data.img.guid = simpleGuid;
    data.img.frames = 1;
    data.frame.atlasFrames = 0;
    data.frame.encoding = ENCODING_RAW;
    data.frame.pixelformat = 255;
    data.frame.imageDataSize = 1;
    data.frame.paletteSize = 1;
    ResourceBuffer buf(&data, sizeof(data));
    g_lastErrorMsg = "";
    LsrImage img(buf);
    EXPECT_EQ("LsrImage: palette images are not supported", g_lastErrorMsg);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, badFormat)
{
    Image data = {0};
    data.img.guid = simpleGuid;
    data.img.frames = 1;
    data.frame.atlasFrames = 0;
    data.frame.encoding = ENCODING_RAW;
    data.frame.imageDataSize = 1;
    data.frame.paletteSize = 0;
    data.frame.pixelformat = LsrImage::PIXEL_FORMAT_UNKNOWN;
    ResourceBuffer buf(&data, sizeof(data));
    g_lastErrorMsg = "";
    LsrImage img(buf);
    EXPECT_EQ("LsrImage: unsupported pixel format", g_lastErrorMsg);
    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, bgra8888_1_1)
{
    Image data;
    data.img.guid = simpleGuid;
    data.img.frames = 1;
    data.img.width = 1;
    data.img.height = 1;
    data.frame.atlasFrames = 0;
    data.frame.encoding = ENCODING_RAW;
    data.frame.imageDataSize = 1;
    data.frame.nOfPadBytes = 0;
    data.frame.nOfPalettePadBytes = 0;
    data.frame.paletteSize = 0;
    data.frame.pitch = 1;
    data.frame.pixelformat = LsrImage::PIXEL_FORMAT_BGRA8888;
    data.frame.transparentColor = 0;
    data.frame.useTransparantColor = 0;
    ResourceBuffer buf(&data, sizeof(data));
    LsrImage img(buf);
    EXPECT_EQ(1u, img.getHeight());
    EXPECT_EQ(1u, img.getWidth());
    EXPECT_EQ(&data.data, img.getPixelData());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_BGRA8888, img.getPixelFormat());
}
