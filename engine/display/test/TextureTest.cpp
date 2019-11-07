/******************************************************************************
**
**   File:        TextureTest.cpp
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
#include <gmock/gmock.h>
#include "Texture.h"
#include "LsrImage.h"
#include "MockGIL.h"

using ::testing::Return;
using ::testing::InSequence;

using namespace lsr;

class TextureTest : public ::testing::Test
{
    void SetUp() P_OVERRIDE
    {
        gilMock = new MockGILStrict();
    }

    void TearDown() P_OVERRIDE
    {
        delete gilMock;
    }

protected:
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
    EXPECT_CALL(*gilMock, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(*gilMock, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_RGB_565, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
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
    EXPECT_CALL(*gilMock, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(*gilMock, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_RGB_888, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
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
    EXPECT_CALL(*gilMock, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(*gilMock, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_BGR_888, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
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
    EXPECT_CALL(*gilMock, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(*gilMock, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_RGBA_8888, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
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
    EXPECT_CALL(*gilMock, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(*gilMock, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_BGRA_8888, data));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
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
    EXPECT_CALL(*gilMock, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(*gilMock, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_P_2_RGB_565, data));
    EXPECT_CALL(*gilMock, gilTexPalette2(&giltx, palette, 4));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
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
    EXPECT_CALL(*gilMock, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(*gilMock, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_P_2_RGB_888, data));
    EXPECT_CALL(*gilMock, gilTexPalette3(&giltx, palette, 4));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
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
    EXPECT_CALL(*gilMock, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(*gilMock, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_P_2_RGBA_8888, data));
    EXPECT_CALL(*gilMock, gilTexPalette4(&giltx, palette, 4));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
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
    EXPECT_CALL(*gilMock, gilCreateTexture(&ctx)).WillOnce(Return(&giltx));
    EXPECT_CALL(*gilMock, gilTexPixels(&giltx, 3, 2, GIL_FORMAT_P_2_BGRA_8888, data));
    EXPECT_CALL(*gilMock, gilTexPalette4(&giltx, palette, 4));
    tx.load(&ctx, &img);
    EXPECT_TRUE(tx.isLoaded());
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
}
