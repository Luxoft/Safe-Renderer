#ifndef POPULUSSC_REFERENCEBITMAPFIELDTYPEFACTORY_H
#define POPULUSSC_REFERENCEBITMAPFIELDTYPEFACTORY_H

/******************************************************************************
**
**   File:        ReferenceBitmapFieldTypeFactory.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

#include <ReferenceBitmapFieldType.h>
#include <AreaType.h>

namespace psc
{
    struct ExpressionTermType;
}

class ReferenceBitmapFieldTypeFactory: public DdhObject<psc::ReferenceBitmapFieldType>
{
public:
    ReferenceBitmapFieldTypeFactory();

    const psc::ReferenceBitmapFieldType* getDdh() const;

    std::size_t getSize() const;

    void setErrorCounter(U16 value);

    void addArea(const psc::AreaType& area);

    void addVisibleExpr(const psc::ExpressionTermType* expr, std::size_t exprSize);

    void addBitmapExpr(const psc::ExpressionTermType* expr, std::size_t exprSize);

protected:
    void setAreaOffset(U16 value);
    void setVisibilityExprOffset(U16 value);
    void setBitmapExprOffset(U16 value);
};

inline ReferenceBitmapFieldTypeFactory::ReferenceBitmapFieldTypeFactory()
{
    setErrorCounter(0U);
    setAreaOffset(0U);
    setVisibilityExprOffset(0U);
    setBitmapExprOffset(0U);
}

inline const psc::ReferenceBitmapFieldType* ReferenceBitmapFieldTypeFactory::getDdh() const
{
    return reinterpret_cast<const psc::ReferenceBitmapFieldType*>(getData());
}

inline std::size_t ReferenceBitmapFieldTypeFactory::getSize() const
{
    return getDataSize();
}

inline void ReferenceBitmapFieldTypeFactory::setErrorCounter(U16 value)
{
    psc::ReferenceBitmapFieldType& obj = getObj();
    obj.errorCounter = value;
}

inline void ReferenceBitmapFieldTypeFactory::addArea(const psc::AreaType& area)
{
    U16 offset = addData(reinterpret_cast<const U8*>(&area), sizeof(psc::AreaType));
    setAreaOffset(offset / 4U);
}

inline void ReferenceBitmapFieldTypeFactory::addVisibleExpr(const psc::ExpressionTermType* expr, std::size_t exprSize)
{
    U16 offset = addData(reinterpret_cast<const U8*>(expr), exprSize);
    setVisibilityExprOffset(offset / 4U);
}

inline void ReferenceBitmapFieldTypeFactory::addBitmapExpr(const psc::ExpressionTermType* expr, std::size_t exprSize)
{
    U16 offset = addData(reinterpret_cast<const U8*>(expr), exprSize);
    setBitmapExprOffset(offset / 4U);
}

inline void ReferenceBitmapFieldTypeFactory::setAreaOffset(U16 value)
{
    psc::ReferenceBitmapFieldType& obj = getObj();
    obj.areaOffset = value;
}

inline void ReferenceBitmapFieldTypeFactory::setVisibilityExprOffset(U16 value)
{
    psc::ReferenceBitmapFieldType& obj = getObj();
    obj.visibleOffset = value;
}

inline void ReferenceBitmapFieldTypeFactory::setBitmapExprOffset(U16 value)
{
    psc::ReferenceBitmapFieldType& obj = getObj();
    obj.bitmapOffset = value;
}


#endif // POPULUSSC_REFERENCEBITMAPFIELDTYPEFACTORY_H
