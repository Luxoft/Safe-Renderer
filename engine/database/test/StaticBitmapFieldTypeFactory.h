#ifndef LUXOFTSAFERENDERER_STATICBITMAPFIELDTYPEFACTORY_H
#define LUXOFTSAFERENDERER_STATICBITMAPFIELDTYPEFACTORY_H

/******************************************************************************
**
**   File:        StaticBitmapFieldTypeFactory.h
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

#include "DdhObject.h"

#include <StaticBitmapFieldType.h>
#include <AreaType.h>

namespace lsr
{
    struct ExpressionTermType;
}

class StaticBitmapFieldTypeFactory: public DdhObject<lsr::StaticBitmapFieldType>
{
public:
    StaticBitmapFieldTypeFactory();

    const lsr::StaticBitmapFieldType* getDdh() const;

    std::size_t getSize() const;

    void addArea(const lsr::AreaType& area);

    void addVisibleExpr(const lsr::ExpressionTermType* expr, std::size_t exprSize);

    void addBitmapExpr(const lsr::ExpressionTermType* expr, std::size_t exprSize);

protected:
    void setAreaOffset(U16 value);
    void setVisibilityExprOffset(U16 value);
    void setBitmapExprOffset(U16 value);
};

inline StaticBitmapFieldTypeFactory::StaticBitmapFieldTypeFactory()
{
    setAreaOffset(0U);
    setVisibilityExprOffset(0U);
    setBitmapExprOffset(0U);
}

inline const lsr::StaticBitmapFieldType* StaticBitmapFieldTypeFactory::getDdh() const
{
    return reinterpret_cast<const lsr::StaticBitmapFieldType*>(getData());
}

inline std::size_t StaticBitmapFieldTypeFactory::getSize() const
{
    return getDataSize();
}

inline void StaticBitmapFieldTypeFactory::addArea(const lsr::AreaType& area)
{
    U16 offset = addData(reinterpret_cast<const U8*>(&area), sizeof(lsr::AreaType));
    setAreaOffset(offset);
}

inline void StaticBitmapFieldTypeFactory::addVisibleExpr(const lsr::ExpressionTermType* expr, std::size_t exprSize)
{
    U16 offset = addData(reinterpret_cast<const U8*>(expr), exprSize);
    setVisibilityExprOffset(offset / 4U);
}

inline void StaticBitmapFieldTypeFactory::addBitmapExpr(const lsr::ExpressionTermType* expr, std::size_t exprSize)
{
    U16 offset = addData(reinterpret_cast<const U8*>(expr), exprSize);
    setBitmapExprOffset(offset / 4U);
}

inline void StaticBitmapFieldTypeFactory::setAreaOffset(U16 value)
{
    lsr::StaticBitmapFieldType& obj = getObj();
    obj.areaOffset = value;
}

inline void StaticBitmapFieldTypeFactory::setVisibilityExprOffset(U16 value)
{
    lsr::StaticBitmapFieldType& obj = getObj();
    obj.visibleOffset = value;
}

inline void StaticBitmapFieldTypeFactory::setBitmapExprOffset(U16 value)
{
    lsr::StaticBitmapFieldType& obj = getObj();
    obj.bitmapOffset = value;
}


#endif // LUXOFTSAFERENDERER_STATICBITMAPFIELDTYPEFACTORY_H
