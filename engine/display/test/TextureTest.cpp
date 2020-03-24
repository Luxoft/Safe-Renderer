/******************************************************************************
**
**   File:        TextureTest.cpp
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Texture.h"
#include "LsrImage.h"
#include "MockGIL.h"

using ::testing::Return;
using ::testing::InSequence;

using namespace lsr;

namespace unittest
{

class TextureTest : public ::testing::Test
{
    void SetUp() P_OVERRIDE
    {
        gilMock = &gil;
    }

    void TearDown() P_OVERRIDE
    {
        gilMock = NULL;
    }

protected:
    static U8 getPaletteColorSize(const LsrImage* const img)
    {
        return Texture::getPaletteColorSize(img);
    }

    MockGILStrict gil;
    Texture tx;
    gil_context_t ctx;
    gil_texture_t giltx;
};

TEST_F(TextureTest, empty)
{
    const LsrImage img = {
        {
            1, // width
            1, // height
            0, // clutSize
            0, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_RGB565,
            0, // bit depth
        },
        NULL,
        NULL,
    };
    tx.load(&ctx, &img);
    EXPECT_FALSE(tx.isLoaded());
    EXPECT_EQ(0U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, rgb565)
{
    U8 data[] = { 0xab, 0xcd };
    const LsrImage img = {
        {
            3, // width
            2, // height
            0, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_RGB565,
            0, // bit depth
        },
        NULL,
        data,
    };
    InSequence seq;
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(gil, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_RGB_565, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
    EXPECT_EQ(0U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, rgb888)
{
    U8 data[] = { 0xab, 0xcd };
    const LsrImage img = {
        {
            3, // width
            2, // height
            0, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_RGB888,
            0, // bit depth
        },
        NULL,
        data,
    };
    InSequence seq;
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(gil, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_RGB_888, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
    EXPECT_EQ(0U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, bgr888)
{
    U8 data[] = { 0xab, 0xcd };
    const LsrImage img = {
        {
            3, // width
            2, // height
            0, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_BGR888,
            0, // bit depth
        },
        NULL,
        data,
    };
    InSequence seq;
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(gil, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_BGR_888, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
    EXPECT_EQ(0U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, rgba8888)
{
    U8 data[] = { 0xab, 0xcd };
    const LsrImage img = {
        {
            3, // width
            2, // height
            0, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_RGBA8888,
            0, // bit depth
        },
        NULL,
        data,
    };
    InSequence seq;
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(gil, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_RGBA_8888, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
    EXPECT_EQ(0U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, bgra8888)
{
    U8 data[] = { 0xab, 0xcd };
    const LsrImage img = {
        {
            3, // width
            2, // height
            0, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_BGRA8888,
            0, // bit depth
        },
        NULL,
        data,
    };
    InSequence seq;
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(gil, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_BGRA_8888, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
    EXPECT_EQ(0U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, invalid)
{
    U8 data[] = { 0xab, 0xcd };
    const LsrImage img = {
        {
            3, // width
            2, // height
            0, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_UNKNOWN,
            0, // bit depth
        },
        NULL,
        data,
    };
    tx.load(&ctx, &img);
    EXPECT_FALSE(tx.isLoaded());
    EXPECT_EQ(0U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, rgb565_palette_2bpp)
{
    U8 data[] = { 0xab, 0xcd };
    U8 palette[] = { 0x7e, 0xf9 };
    const LsrImage img = {
        {
            3, // width
            2, // height
            4, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_RGB565,
            2, // bit depth
        },
        palette,
        data,
    };
    InSequence seq;
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(gil, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_P_2_RGB_565, data));
    EXPECT_CALL(gil, gilTexPalette2(&giltx, palette, 4));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
    EXPECT_EQ(2U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, rgb888_palette_2bpp)
{
    U8 data[] = { 0xab, 0xcd };
    U8 palette[] = { 0x7e, 0xf9 };
    const LsrImage img = {
        {
            3, // width
            2, // height
            4, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_RGB888,
            2, // bit depth
        },
        palette,
        data,
    };
    InSequence seq;
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(gil, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_P_2_RGB_888, data));
    EXPECT_CALL(gil, gilTexPalette3(&giltx, palette, 4));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
    EXPECT_EQ(3U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, bgr888_palette_2bpp)
{
    U8 data[] = { 0xab, 0xcd };
    U8 palette[] = { 0x7e, 0xf9 };
    const LsrImage img = {
        {
            3, // width
            2, // height
            4, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_BGR888,
            2, // bit depth
        },
        palette,
        data,
    };
    // not supported by GIL
    tx.load(&ctx, &img);
    EXPECT_FALSE(tx.isLoaded());
    EXPECT_EQ(3U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, rgba8888_palette_2bpp)
{
    U8 data[] = { 0xab, 0xcd };
    U8 palette[] = { 0x7e, 0xf9 };
    const LsrImage img = {
        {
            3, // width
            2, // height
            4, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_RGBA8888,
            2, // bit depth
        },
        palette,
        data,
    };
    InSequence seq;
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(gil, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_P_2_RGBA_8888, data));
    EXPECT_CALL(gil, gilTexPalette4(&giltx, palette, 4));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
    EXPECT_EQ(4U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, bgra8888_palette_2bpp)
{
    U8 data[] = { 0xab, 0xcd };
    U8 palette[] = { 0x7e, 0xf9 };
    const LsrImage img = {
        {
            3, // width
            2, // height
            4, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_BGRA8888,
            2, // bit depth
        },
        palette,
        data,
    };
    InSequence seq;
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(gil, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_P_2_BGRA_8888, data));
    EXPECT_CALL(gil, gilTexPalette4(&giltx, palette, 4));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
    EXPECT_EQ(4U, getPaletteColorSize(&img));
}

TEST_F(TextureTest, invalid_palette)
{
    U8 data[] = { 0xab, 0xcd };
    U8 palette[] = { 0x7e, 0xf9 };
    const LsrImage img = {
        {
            3, // width
            2, // height
            16, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_UNKNOWN,
            4, // bit depth
        },
        palette,
        data,
    };
    tx.load(&ctx, &img);
    EXPECT_FALSE(tx.isLoaded());
    EXPECT_EQ(0U, getPaletteColorSize(&img));
}

// not supported
TEST_F(TextureTest, bgra8888_palette_4bpp)
{
    U8 data[] = { 0xab, 0xcd };
    U8 palette[] = { 0x7e, 0xf9 };
    const LsrImage img = {
        {
            3, // width
            2, // height
            16, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_BGRA8888,
            4, // bit depth
        },
        palette,
        data,
    };
    tx.load(&ctx, &img);
    EXPECT_FALSE(tx.isLoaded());
    EXPECT_EQ(4U, getPaletteColorSize(&img));
}

// not supported
TEST_F(TextureTest, bgra8888_palette_8bpp)
{
    U8 data[] = { 0xab, 0xcd };
    U8 palette[] = { 0x7e, 0xf9 };
    const LsrImage img = {
        {
            3, // width
            2, // height
            256, // clutSize
            3 * 2 * 2, // imageDataSize
            1, // pitch
            LsrImageTypes::PIXEL_FORMAT_BGRA8888,
            8, // bit depth
        },
        palette,
        data,
    };
    tx.load(&ctx, &img);
    EXPECT_FALSE(tx.isLoaded());
    EXPECT_EQ(4U, getPaletteColorSize(&img));
}

} // namespace unittest
