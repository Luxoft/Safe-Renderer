/******************************************************************************
**
**   File:        AreaTest.cpp
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

#include "gtest/gtest.h"
#include "Area.h"
#include "AreaType.h"
#include <iostream>

using lsr::Area;
using lsr::AreaType;

const I32 FIXED_POINT_BITS = 4;

namespace
{
    I32 getFixedPoint(float value)
    {
        return static_cast<I32>(value * (1 << FIXED_POINT_BITS));
    }
}

namespace lsr
{

/**
 * Streaming operator for comparing lsr::Area in unit tests.
 *
 * @note Argument-dependent lookup requires this operator to be declared in the namespace
 *       ddh, which is associated to the parameter @p area.
 *       Otherwise the operator has to be declared before it is used in TestAssert.h,
 *       which means this header would have to be included just before including
 *       <cppunit/extensions/HelperMacros.h>.
 */
std::ostream& operator<<(std::ostream& out, const lsr::Area& area)
{
    out << "x:" << area.getLeft() << ", y:" << area.getTop();
    out << ", w:" << area.getWidth() << ", h:" << area.getHeight();
    return out;
}

} // namespace lsr

TEST(AreaTest, toString)
{
    Area a1(0, 1, 1, 4);
    std::stringstream stream;
    stream << a1;
    EXPECT_EQ("x:0, y:1, w:2, h:4", stream.str());
}

TEST(AreaTest, Area)
{
    Area a1;
    EXPECT_EQ(0, a1.getLeft());
    EXPECT_EQ(0, a1.getTop());
    EXPECT_EQ(0, a1.getWidth());
    EXPECT_EQ(0, a1.getHeight());
    EXPECT_EQ(0, a1.getRight());
    EXPECT_EQ(0, a1.getBottom());
    EXPECT_TRUE(a1.isEmpty());

    Area a2(11, 12, 55, 64);
    EXPECT_EQ(11, a2.getLeft());
    EXPECT_EQ(12, a2.getTop());
    EXPECT_EQ(55 - 11 + 1, a2.getWidth());
    EXPECT_EQ(64 - 12 + 1, a2.getHeight());
    EXPECT_EQ(55, a2.getRight());
    EXPECT_EQ(64, a2.getBottom());
    EXPECT_FALSE(a2.isEmpty());

    AreaType areaType = {10, 11, 40, 30};
    Area a3(&areaType);
    EXPECT_EQ(10, a3.getLeft());
    EXPECT_EQ(11, a3.getTop());
    EXPECT_EQ(40, a3.getWidth());
    EXPECT_EQ(30, a3.getHeight());
    EXPECT_EQ(10 + 40 - 1, a3.getRight());
    EXPECT_EQ(11 + 30 - 1, a3.getBottom());
    EXPECT_FALSE(a3.isEmpty());

    Area a4(a3);
    EXPECT_FALSE(a1 == a2);
    EXPECT_FALSE(a2 == a3);
    EXPECT_FALSE(a1 == a3);
    EXPECT_TRUE(a4 == a3);
    EXPECT_FALSE(a4 == a2);

    EXPECT_TRUE(a1 != a2);
    EXPECT_TRUE(a2 != a3);
    EXPECT_TRUE(a1 != a3);
    EXPECT_FALSE(a4 != a3);
    EXPECT_TRUE(a4 != a2);
}

TEST(AreaTest, negativeSize)
{
    Area a1(100, 10, 0, 1);
    EXPECT_EQ(100, a1.getLeft());
    EXPECT_EQ(10, a1.getTop());
    EXPECT_EQ(-101, a1.getWidth());
    EXPECT_EQ(-10, a1.getHeight());
    EXPECT_EQ(0, a1.getRight());
    EXPECT_EQ(1, a1.getBottom());
}

TEST(AreaTest, empty)
{
    Area a1;
    EXPECT_TRUE(a1.isEmpty());
    a1.setWidth(23);
    EXPECT_TRUE(a1.isEmpty());
    a1.setWidth(-1009);
    EXPECT_TRUE(a1.isEmpty());
    a1.setHeight(1);
    EXPECT_FALSE(a1.isEmpty());
    a1.setWidth(0);
    EXPECT_TRUE(a1.isEmpty());
    a1.setHeight(-1);
    EXPECT_TRUE(a1.isEmpty());
}

TEST(AreaTest, equals)
{
    Area a1, a2;
    EXPECT_TRUE(a1 == a2);
    EXPECT_FALSE(a1 != a2);
    a2.setHeight(100);
    EXPECT_FALSE(a1 == a2);
    EXPECT_TRUE(a1 != a2);
    a2.setHeight(0);
    a2.setWidth(100);
    EXPECT_FALSE(a1 == a2);
    EXPECT_TRUE(a1 != a2);
    a2.setWidth(0);
    a2.moveBy(0, 1);
    EXPECT_FALSE(a1 == a2);
    EXPECT_TRUE(a1 != a2);
    a2.moveBy(1, -1);
    EXPECT_FALSE(a1 == a2);
    EXPECT_TRUE(a1 != a2);
}

TEST(AreaTest, setBottom)
{
    Area area(10, 11, 20, 21);
    area.setBottom(0);
    EXPECT_EQ(10, area.getLeft());
    EXPECT_EQ(11, area.getTop());
    EXPECT_EQ(11, area.getWidth());
    EXPECT_EQ(-12, area.getHeight());
    EXPECT_EQ(20, area.getRight());
    EXPECT_EQ(0, area.getBottom());

    area.setBottom(11); // same as top
    EXPECT_EQ(10, area.getLeft());
    EXPECT_EQ(11, area.getTop());
    EXPECT_EQ(11, area.getWidth());
    EXPECT_EQ(1, area.getHeight());
    EXPECT_EQ(20, area.getRight());
    EXPECT_EQ(11, area.getBottom());

    area.setBottom(12);
    EXPECT_EQ(10, area.getLeft());
    EXPECT_EQ(11, area.getTop());
    EXPECT_EQ(11, area.getWidth());
    EXPECT_EQ(2, area.getHeight());
    EXPECT_EQ(20, area.getRight());
    EXPECT_EQ(12, area.getBottom());
}

TEST(AreaTest, moveEmpty)
{
    Area a1;
    a1.moveBy(20,30);
    EXPECT_EQ(20, a1.getLeft());
    EXPECT_EQ(30, a1.getTop());
    EXPECT_EQ(0, a1.getWidth());
    EXPECT_EQ(0, a1.getHeight());
    EXPECT_EQ(20, a1.getRight());
    EXPECT_EQ(30, a1.getBottom());
    EXPECT_TRUE(a1.isEmpty());

    a1.moveBy(55,1);
    EXPECT_EQ(75, a1.getLeft());
    EXPECT_EQ(31, a1.getTop());
    EXPECT_EQ(0, a1.getWidth());
    EXPECT_EQ(0, a1.getHeight());
    EXPECT_EQ(75, a1.getRight());
    EXPECT_EQ(31, a1.getBottom());
    EXPECT_TRUE(a1.isEmpty());

    a1.moveBy(-100, -60);
    EXPECT_EQ(-25, a1.getLeft());
    EXPECT_EQ(-29, a1.getTop());
    EXPECT_EQ(0, a1.getWidth());
    EXPECT_EQ(0, a1.getHeight());
    EXPECT_EQ(-25, a1.getRight());
    EXPECT_EQ(-29, a1.getBottom());
    EXPECT_TRUE(a1.isEmpty());
}

TEST(AreaTest, setRight)
{
    Area area(10, 11, 20, 21);
    area.setRight(9);
    EXPECT_EQ(10, area.getLeft());
    EXPECT_EQ(11, area.getTop());
    EXPECT_EQ(-2, area.getWidth());
    EXPECT_EQ(11, area.getHeight());
    EXPECT_EQ(9, area.getRight());
    EXPECT_EQ(21, area.getBottom());

    area.setRight(10); // same as left
    EXPECT_EQ(10, area.getLeft());
    EXPECT_EQ(11, area.getTop());
    EXPECT_EQ(1, area.getWidth());
    EXPECT_EQ(11, area.getHeight());
    EXPECT_EQ(10, area.getRight());
    EXPECT_EQ(21, area.getBottom());

    area.setRight(11);
    EXPECT_EQ(10, area.getLeft());
    EXPECT_EQ(11, area.getTop());
    EXPECT_EQ(2, area.getWidth());
    EXPECT_EQ(11, area.getHeight());
    EXPECT_EQ(11, area.getRight());
    EXPECT_EQ(21, area.getBottom());
}


TEST(AreaTest, isOverlapping)
{
    Area area1 = Area(-10, -10, 10, 10);
    Area area2;

    // Top
    // no overlap
    area2 = Area(0, -15, 5, -14);
    EXPECT_FALSE(area1.isOverlapping(area2));

    // no overlap
    area2.setHeight(5);
    EXPECT_FALSE(area1.isOverlapping(area2));

    // overlap
    area2.setHeightFP(getFixedPoint(5.1f));
    EXPECT_TRUE(area1.isOverlapping(area2));

    // Bottom
    // no overlap
    area2 = Area(0, 14, 5, 15);
    EXPECT_FALSE(area1.isOverlapping(area2));

    // no overlap
    area2.setTop(11);
    EXPECT_FALSE(area1.isOverlapping(area2));

    // overlap
    area2.setTopFP(getFixedPoint(10.9f));
    EXPECT_TRUE(area1.isOverlapping(area2));

    // Left
    // no overlap
    area2 = Area(-15, 0, -14, 5);
    EXPECT_FALSE(area1.isOverlapping(area2));

    // no overlap
    area2.setWidth(5);
    EXPECT_FALSE(area1.isOverlapping(area2));

    // overlap
    area2.setWidthFP(getFixedPoint(5.1f));
    EXPECT_TRUE(area1.isOverlapping(area2));

    // Right
    // no overlap
    area2 = Area(15, 0, 16, 5);
    EXPECT_FALSE(area1.isOverlapping(area2));

    // no overlap
    area2.setLeft(11);
    EXPECT_FALSE(area1.isOverlapping(area2));

    // overlap
    area2.setLeftFP(getFixedPoint(10.9f));
    EXPECT_TRUE(area1.isOverlapping(area2));
}

