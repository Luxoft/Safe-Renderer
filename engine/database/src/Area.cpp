/******************************************************************************
**
**   File:        Area.cpp
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

#include "Area.h"
#include "AreaType.h"
#include <algorithm>


namespace
{

const I32 FIXED_POINT_BITS = 4; ///< Number of fraction bits in the internal sub pixel resolution representation of a coordinate

} // anonymous namespace


namespace lsr
{

Area::Area():
    m_x(0),
    m_y(0),
    m_width(0),
    m_height(0)
{
}

Area::Area(const AreaType* const pArea)
{
    setArea(pArea);
}

Area::Area(const I32 left, const I32 top, const I32 right, const I32 bottom)
{
    m_x = fromIntegerToFP(left);
    m_y = fromIntegerToFP(top);
    setRight(right);
    setBottom(bottom);
}

Area::~Area()
{
}

I32 Area::fromFPToInteger(const I32 coordFP)
{
    return static_cast<I32>(coordFP >> FIXED_POINT_BITS);
}

I32 Area::fromIntegerToFP(const I32 coord)
{
    return static_cast<I32>(coord) << FIXED_POINT_BITS;
}

I32 Area::getLeft() const
{
    return fromFPToInteger(getLeftFP());
}

I32 Area::getLeftFP() const
{
    return m_x;
}

I32 Area::getTop() const
{
    return fromFPToInteger(getTopFP());
}

I32 Area::getTopFP() const
{
    return m_y;
}

I32 Area::getWidth() const
{
    I32 w = getWidthFP();
    if (w != 0)
    {
        w = fromFPToInteger(m_x + w) - fromFPToInteger(m_x);
    }
    return w;
}

I32 Area::getWidthFP() const
{
    return m_width;
}

I32 Area::getHeight() const
{
    I32 h = getHeightFP();
    if (h != 0)
    {
        h = fromFPToInteger(m_y + h) - fromFPToInteger(m_y);
    }
    return h;
}

I32 Area::getHeightFP() const
{
    return m_height;
}

void Area::setArea(const AreaType* const pArea)
{
    m_x = fromIntegerToFP(static_cast<I32>(pArea->GetXCoord()));
    m_y = fromIntegerToFP(static_cast<I32>(pArea->GetYCoord()));
    m_width = fromIntegerToFP(static_cast<I32>(pArea->GetWidth()));
    m_height = fromIntegerToFP(static_cast<I32>(pArea->GetHeight()));
}

void Area::setLeft(const I32 left)
{
    setLeftFP(fromIntegerToFP(left));
}

void Area::setLeftFP(const I32 left)
{
    m_width += (m_x - left);
    m_x = left;
}

void Area::setTop(const I32 top)
{
    setTopFP(fromIntegerToFP(top));
}

void Area::setTopFP(const I32 top)
{
    m_height += (m_y - top);
    m_y = top;
}

void Area::setWidth(const I32 width)
{
    m_width = fromIntegerToFP(width);
}

void Area::setWidthFP(const I32 width)
{
    m_width = width;
}

void Area::setHeight(const I32 height)
{
    m_height = fromIntegerToFP(height);
}

void Area::setHeightFP(const I32 height)
{
    m_height = height;
}

void Area::moveBy(const I32 left, const I32 top)
{
    moveByFP(fromIntegerToFP(left), fromIntegerToFP(top));
}

void Area::moveByFP(const I32 left, const I32 top)
{
    m_x += left;
    m_y += top;
}

void Area::setBottom(const I32 bottom)
{
    setBottomFP(fromIntegerToFP(bottom));
}

void Area::setBottomFP(const I32 bottom)
{
    if (bottom > m_y)
    {
        m_height = (bottom - m_y) + fromIntegerToFP(1);
    }
    else if (bottom < m_y)
    {
        m_height = (bottom - m_y) - fromIntegerToFP(1);
    }
    else
    {
        m_height = fromIntegerToFP(1);
    }
}

I32 Area::getBottom() const
{
    return fromFPToInteger(getBottomFP());
}

I32 Area::getBottomFP() const
{
    I32 bottom;

    if (m_height > 0)
    {
        bottom = (m_y + m_height) - fromIntegerToFP(1);
    }
    else if (m_height < 0)
    {
        bottom = (m_y + m_height) + fromIntegerToFP(1);
    }
    else
    {
        bottom = m_y;
    }

    return bottom;
}

void Area::setRight(const I32 right)
{
    setRightFP(fromIntegerToFP(right));
}

void Area::setRightFP(const I32 right)
{
    if (right > m_x)
    {
        m_width = (right - m_x) + fromIntegerToFP(1);
    }
    else if (right < m_x)
    {
        m_width = (right - m_x) - fromIntegerToFP(1);
    }
    else
    {
        m_width = fromIntegerToFP(1);
    }
}

I32 Area::getRight() const
{
    return fromFPToInteger(getRightFP());
}

I32 Area::getRightFP() const
{
    I32 right;

    if (m_width > 0)
    {
        right = (m_x + m_width) - fromIntegerToFP(1);
    }
    else if (m_width < 0)
    {
        right = (m_x + m_width) + fromIntegerToFP(1);
    }
    else
    {
        right = m_x;
    }

    return right;
}


bool Area::isOverlapping(const Area& other) const
{
    /*http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other

    if (RectA.X1 < RectB.X2 && RectA.X2 > RectB.X1 &&
    RectA.Y1 < RectB.Y2 && RectA.Y2 > RectB.Y1)

    say you have Rect A, and Rect B. Proof is by contradiction. Any one of four conditions guarantees that NO OVERLAP CAN EXIST.

    Cond1.  If A's left edge is to the right of the B's right edge,
               -  then A is Totally to right Of B
    Cond2.  If A's right edge is to the left of the B's left edge,
               -  then A is Totally to left Of B
    Cond3.  If A's top edge is below B's bottom  edge,
               -  then A is Totally below B
    Cond4.  If A's bottom edge is above B's top edge,
               -  then A is Totally above B

    So condition for Non-Overlap is

    Cond1 Or Cond2 Or Cond3 Or Cond4

    Therefore, a sufficient condition for Overlap is the opposite (De Morgan)

    Not Cond1 AND Not Cond2 And Not Cond3 And Not Cond4

    this is equivalent to

    A's Left Edge to left of B's right edge  And
    A's right edge to right of B's left edge And
    A's top above B's bottom And
    A's bottom below B's Top*/

    return ((m_x < (other.m_x + other.m_width)) && ((m_x + m_width) > other.m_x) &&
            (m_y < (other.m_y + other.m_height)) && ((m_y + m_height) > other.m_y));

}

} // namespace lsr
