#ifndef LUXOFTSAFERENDERER_BITMAPIDTABLETYPEFACTORY_H
#define LUXOFTSAFERENDERER_BITMAPIDTABLETYPEFACTORY_H

/******************************************************************************
**
**   File:        BitmapIdTableTypeFactory.h
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

#include "DdhArrayObject.h"

#include <BitmapIdTableType.h>

namespace ddh
{
    struct EnumerationBitmapMapType;
}

class BitmapIdTableTypeFactory: public DdhArrayObject<lsr::BitmapIdTableType>
{
public:
    BitmapIdTableTypeFactory();

    const lsr::BitmapIdTableType* getDdh() const;

    std::size_t getSize() const;

    void createExpr(U16 itemCount);

    void addRow(const lsr::EnumerationBitmapMapType* row, std::size_t rowSize);

protected:
    void setItemCount(U16 value);

    void setItemOffset(U16 value);
};

inline BitmapIdTableTypeFactory::BitmapIdTableTypeFactory()
{
    setItemCount(0U);
    setItemOffset(0U);
}

inline const lsr::BitmapIdTableType* BitmapIdTableTypeFactory::getDdh() const
{
    return reinterpret_cast<const lsr::BitmapIdTableType*>(getData());
}

inline std::size_t BitmapIdTableTypeFactory::getSize() const
{
    return getDataSize();
}

inline void BitmapIdTableTypeFactory::createExpr(U16 itemCount)
{
    setItemCount(itemCount);

    U16 itemOffset = addArray(itemCount);
    setItemOffset(itemOffset);
}

inline void BitmapIdTableTypeFactory::addRow(const lsr::EnumerationBitmapMapType* row, std::size_t rowSize)
{
    addDataToArray(reinterpret_cast<const U8*>(row), rowSize);
}

inline void BitmapIdTableTypeFactory::setItemCount(U16 value)
{
    lsr::BitmapIdTableType& obj = getObj();
    obj.itemCount = value;
}

inline void BitmapIdTableTypeFactory::setItemOffset(U16 value)
{
    lsr::BitmapIdTableType& obj = getObj();
    obj.itemOffset = value;
}

#endif // LUXOFTSAFERENDERER_BITMAPIDTABLETYPEFACTORY_H
