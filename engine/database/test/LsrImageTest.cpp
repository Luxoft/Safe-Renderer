/******************************************************************************
**
**   File:        LsrImageTest.cpp
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
#include "LsrImage.h"

using lsr::LsrImage;
using lsr::ResourceBuffer;
using namespace lsr::LsrImageTypes;


extern std::string g_lastErrorMsg;



TEST(LsrImageTest, empty)
{
    ResourceBuffer buf;
    LsrImage img = {
        { 0U, 0U, 0U, 0U, 0U, PIXEL_FORMAT_UNKNOWN, 0U },
        NULL,
        NULL
    };

    EXPECT_EQ(0u, img.getHeight());
    EXPECT_EQ(0u, img.getWidth());
    EXPECT_EQ(NULL, img.getPixelData());
    EXPECT_EQ(PIXEL_FORMAT_UNKNOWN, img.getPixelFormat());
}

TEST(LsrImageTest, bgra8888_1_1)
{
    const U8 pixels[] = { 42U, 43U, 44U, 45U };
    LsrImage img = {
        {1U, 11U, 0U, 2U, 3U, PIXEL_FORMAT_BGRA8888, 8U},
        NULL,
        pixels
    };
    EXPECT_EQ(1U, img.getWidth());
    EXPECT_EQ(11U, img.getHeight());
    EXPECT_EQ(pixels, img.getPixelData());
    EXPECT_EQ(PIXEL_FORMAT_BGRA8888, img.getPixelFormat());
}
