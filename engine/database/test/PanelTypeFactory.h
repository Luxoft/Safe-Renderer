#ifndef LUXOFTSAFERENDERER_PANELTYPEFACTORY_H
#define LUXOFTSAFERENDERER_PANELTYPEFACTORY_H

/******************************************************************************
**
**   File:        PanelTypeFactory.h
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

#include <PanelType.h>
#include <AreaType.h>

namespace ddh
{
    struct ExpressionTermType;
    struct FieldsType;
}

class PanelTypeFactory: public DdhObject<lsr::PanelType>
{
public:
    PanelTypeFactory();

    const lsr::PanelType* getDdh() const;

    std::size_t getSize() const;

    void addArea(const lsr::AreaType& area);

    void addVisibleExpr(const lsr::ExpressionTermType* expr, std::size_t exprSize);

    void addFields(const lsr::FieldsType* fields, std::size_t fieldsSize);

protected:
    void setAreaOffset(U16 value);
    void setVisibilityExprOffset(U16 value);
    void setFieldsOffset(U16 value);
};

inline PanelTypeFactory::PanelTypeFactory()
{
    setAreaOffset(0U);
    setVisibilityExprOffset(0U);
    setFieldsOffset(0U);
}

inline const lsr::PanelType* PanelTypeFactory::getDdh() const
{
    return reinterpret_cast<const lsr::PanelType*>(getData());
}

inline std::size_t PanelTypeFactory::getSize() const
{
    return getDataSize();
}

inline void PanelTypeFactory::addArea(const lsr::AreaType& area)
{
    U16 offset = addData(reinterpret_cast<const U8*>(&area), sizeof(lsr::AreaType));
    setAreaOffset(offset / 4U);
}

inline void PanelTypeFactory::addVisibleExpr(const lsr::ExpressionTermType* expr, std::size_t exprSize)
{
    U16 offset = addData(reinterpret_cast<const U8*>(expr), exprSize);
    setVisibilityExprOffset(offset / 4U);
}

inline void PanelTypeFactory::addFields(const lsr::FieldsType* fields, std::size_t fieldsSize)
{
    U16 offset = addData(reinterpret_cast<const U8*>(fields), fieldsSize);
    setFieldsOffset(offset / 4U);
}

inline void PanelTypeFactory::setAreaOffset(U16 value)
{
    lsr::PanelType& obj = getObj();
    obj.areaOffset = value;
}

inline void PanelTypeFactory::setVisibilityExprOffset(U16 value)
{
    lsr::PanelType& obj = getObj();
    obj.visibleOffset = value;
}

inline void PanelTypeFactory::setFieldsOffset(U16 value)
{
    lsr::PanelType& obj = getObj();
    obj.fieldsOffset = value;
}

#endif // LUXOFTSAFERENDERER_PANELTYPEFACTORY_H
