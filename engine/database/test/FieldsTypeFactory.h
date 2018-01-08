#ifndef POPULUSSC_FIELDSTYPEFACTORY_H
#define POPULUSSC_FIELDSTYPEFACTORY_H

/******************************************************************************
**
**   File:        FieldsTypeFactory.h
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

#include "DdhArrayObject.h"

#include <FieldsType.h>

namespace ddh
{
    struct FieldType;
}

class FieldsTypeFactory: public DdhArrayObject<psc::FieldsType>
{
public:
    FieldsTypeFactory();

    const psc::FieldsType* getDdh() const;

    std::size_t getSize() const;

    void create(U16 itemCount);

    void addField(const psc::FieldType* field, std::size_t fieldSize);

protected:
    void setItemCount(U16 value);

    void setItemOffset(U16 value);
};

inline FieldsTypeFactory::FieldsTypeFactory()
{
    setItemCount(0U);
    setItemOffset(0U);
}

inline const psc::FieldsType* FieldsTypeFactory::getDdh() const
{
    return reinterpret_cast<const psc::FieldsType*>(getData());
}

inline std::size_t FieldsTypeFactory::getSize() const
{
    return getDataSize();
}

inline void FieldsTypeFactory::create(U16 itemCount)
{
    setItemCount(itemCount);

    U16 itemOffset = addArray(itemCount);
    setItemOffset(itemOffset);
}

inline void FieldsTypeFactory::addField(const psc::FieldType* field, std::size_t fieldSize)
{
    addDataToArray(reinterpret_cast<const U8*>(field), fieldSize);
}

inline void FieldsTypeFactory::setItemCount(U16 value)
{
    psc::FieldsType& obj = getObj();
    obj.fieldCount = value;
}

inline void FieldsTypeFactory::setItemOffset(U16 value)
{
    psc::FieldsType& obj = getObj();
    obj.fieldOffset = value;
}

#endif // POPULUSSC_FIELDSTYPEFACTORY_H
