/******************************************************************************
**
**   File:        ColorTest.cpp
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

#include <gtest/gtest.h>

#include "Color.h"

using psc::Color;

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

