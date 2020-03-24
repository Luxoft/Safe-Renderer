/******************************************************************************
**
**   File:        ColorTest.cpp
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

#include "Color.h"

using lsr::Color;

TEST(ColorTest, empty)
{
    Color color;
    EXPECT_EQ(0u, color.getRed());
    EXPECT_EQ(0u, color.getGreen());
    EXPECT_EQ(0u, color.getBlue());
    EXPECT_EQ(0u, color.getAlpha());
    EXPECT_EQ(0u, color.getRawValue());

    Color color1 = Color::fromColorValue(0u);
    EXPECT_EQ(color, color1);
}

TEST(ColorTest, orange)
{
    const U8 r = 0xff;
    const U8 g = 0x10;
    const U8 b = 1;
    const U8 a = 0xcc;
    const U32 rawValue = a << 24 | b << 16 | g << 8 | r;

    Color orange = Color(r, g, b, a);
    EXPECT_EQ(r, orange.getRed());
    EXPECT_EQ(g, orange.getGreen());
    EXPECT_EQ(b, orange.getBlue());
    EXPECT_EQ(a, orange.getAlpha());
    EXPECT_EQ(rawValue, orange.getRawValue());

    EXPECT_EQ(Color::fromColorValue(rawValue), orange);
}

