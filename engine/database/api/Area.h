#ifndef POPULUSSC_AREA_H
#define POPULUSSC_AREA_H

/******************************************************************************
**
**   File:        Area.h
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

//#include "ddh_defs.h"
//#include "AreaType.h"
#include "PscTypes.h"
#ifdef UNIT_TEST
#include <iostream>
#endif

namespace psc
{
    struct AreaType;

/**
*   Class to represent an area on the display.
*
*   Class that represents an area on the display. It is a runtime equivalent to AreaType.
*   An area having a zero width or height is considered to not enclose any pixel at all, hence considered 'empty'.
*   That also implies that the smallest non-empty area is 1 pixel which has the height 1 and width 1.
*   The class also supports negative width/heights which is the case when the x or y reference point of the rectangle lies to
*   the right or bottom respectively.
*
*   @note Area(3,1,1,3) has the width -3 and height 3 and encloses 9 pixels.
*/
class Area
{
public:
    Area();
    Area(const AreaType* pArea);
    Area(const Area& area);
    Area(const I32 left, const I32 top, const I32 right, const I32 bottom);
    ~Area();

    /**
    *   Converts integer pixel into sub pixel resolution fixed point
    */
    static I32 fromIntegerToFP(const I32 coord);

    /**
    *   Converts sub pixel resolution fixed point into integer pixel
    */
    static I32 fromFPToInteger(const I32 coordFP);

    I32 getTop() const;      ///< Get top coordinate (integer pixels)
    void setTop(const I32 top);           ///< Set top coordinate (integer pixels), alters the size
    I32 getLeft() const;     ///< Get left coordinate (integer pixels)
    void setLeft(const I32 left);         ///< Set left coordinate (integer pixels), alters the size
    I32 getBottom() const;          ///< Get bottom coordinate (integer pixels)
    void setBottom(const I32 bottom);     ///< Set bottom coordinate (integer pixels), alters the size
    I32 getRight() const;           ///< Get right coordinate (integer pixels)
    void setRight(const I32 right);       ///< Set right coordinate (integer pixels), alters the size
    I32 getWidth() const;    ///< Get the width, in integer pixels, of the area
    void setWidth(const I32 width);       ///< Set the width by changing the right coordinate (integer pixels)
    I32 getHeight() const;   ///< Get the height, in integer pixels, of the area
    void setHeight(const I32 height);     ///< Set the height by changing the bottom coordinate (integer pixels)


    I32 getLeftFP() const;   ///< Get sub pixel resolution fixed point left coordinate
    void setLeftFP(const I32 left);       ///< Set sub pixel resolution fixed point left coordinate
    I32 getTopFP() const;    ///< Get sub pixel resolution fixed point top coordinate
    void setTopFP(const I32 top);         ///< Set sub pixel resolution fixed point top coordinate
    I32 getRightFP() const;         ///< Get sub pixel resolution fixed point right coordinate
    void setRightFP(const I32 right);     ///< Set sub pixel resolution fixed point right coordinate
    I32 getBottomFP() const;        ///< Get sub pixel resolution fixed point bottom coordinate
    void setBottomFP(const I32 bottom);   ///< Set sub pixel resolution fixed point bottom coordinate
    I32 getWidthFP() const;  ///< Get sub pixel resolution fixed point width
    void setWidthFP(const I32 width);     ///< Set sub pixel resolution fixed point width
    I32 getHeightFP() const; ///< Get sub pixel resolution fixed point height
    void setHeightFP(const I32 height);   ///< Set sub pixel resolution fixed point height


    inline void clear() {m_x = 0; m_y = 0; m_width = 0; m_height = 0;}      ///< Empties the area and moves it to origin
    inline bool isEmpty() const {return (m_width == 0 || m_height == 0);}   ///< @return Whether area encloses any pixel or not

    /**
    *   @returns True if this area defines the exact same area as the argument
    */
    bool operator==(const Area &area) const {
        return (m_x == area.m_x && m_y == area.m_y && m_width == area.m_width && m_height == area.m_height);
    }

    /**
    *   @returns True if this area doens't define the exact same area as the argument
    */
    bool operator!=(const Area &area) const {
        return !(*this == area);
    }

    /**
    *   Offsets the left-top position of the area and does not alter the size.
    *   @note The right and bottom coordinates are changed as well!
    */
    void moveBy(const I32 left, const I32 top);

     /**
    *   Offsets the left-top position of the area and does not alter the size.
    *   @note The right and bottom coordinates are changed as well!
    */
    void moveByFP(const I32 left, const I32 top);

    /**
    *   Sets the area from a DDH AreaType
    */
    void setArea(const AreaType *pArea);


    /////////////////////////////////////////////////////////////////
    // Utility functions
    /////////////////////////////////////////////////////////////////

    /**
    *   @return whether the given area is overlapping the area of this Area instance (true) or not (false).
    */
    bool isOverlapping(const Area &area) const;

private:
    I32 m_x;        ///< Internal sub pixel resolution fixed point horizontal reference coordinate
    I32 m_y;        ///< Internal sub pixel resolution fixed point vertical reference coordinate
    I32 m_width;    ///< Internal sub pixel resolution fixed point horizontal size
    I32 m_height;   ///< Internal sub pixel resolution fixed point vertical size

    enum {
        FIXED_POINT_BITS = 4,     ///< Number of fraction bits in the internal sub pixel resolution representation of a coordinate
    };
};


#ifdef UNIT_TEST
/**
 * Streaming operator for comparing psc::Area in unit tests.
 *
 * @note Argument-dependent lookup requires this operator to be declared in the namespace
 *       ddh, which is associated to the parameter @p area.
 *       Otherwise the operator has to be declared before it is used in TestAssert.h,
 *       which means this header would have to be included just before including
 *       <cppunit/extensions/HelperMacros.h>.
 */
inline std::ostream& operator<<(std::ostream& out, const psc::Area& area)
{
    out << "x:" << area.getLeft() << ", y:" << area.getTop();
    out << ", w:" << area.getWidth() << ", h:" << area.getHeight();
    return out;
}
#endif // UNIT_TEST

} // namespace psc


#endif // #ifndef POPULUSSC_AREA_H
