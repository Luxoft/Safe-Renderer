#ifndef POPULUSSC_FIELDTYPEFACTORY_H
#define POPULUSSC_FIELDTYPEFACTORY_H

/******************************************************************************
**
**   File:        FieldTypeFactory.h
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

#include <FieldType.h>

namespace ddh
{
    struct StaticBitmapFieldType;
}

class FieldTypeFactory: public DdhObject<psc::FieldType>
{
public:
    FieldTypeFactory();

    const psc::FieldType* getDdh() const;

    std::size_t getSize() const;

    void create(U16 type);

    void addBitmap(const psc::StaticBitmapFieldType* obj, std::size_t objSize);

    void addBitmap(const psc::ReferenceBitmapFieldType* obj, std::size_t objSize);

protected:
    void setType(U16 value);
};

inline FieldTypeFactory::FieldTypeFactory()
{
    setType(0U);
}

inline const psc::FieldType* FieldTypeFactory::getDdh() const
{
    return reinterpret_cast<const psc::FieldType*>(getData());
}

inline std::size_t FieldTypeFactory::getSize() const
{
    return getDataSize();
}

inline void FieldTypeFactory::addBitmap(const psc::StaticBitmapFieldType* obj, std::size_t objSize)
{
    addData(reinterpret_cast<const U8*>(obj), objSize);
}

inline void FieldTypeFactory::addBitmap(const psc::ReferenceBitmapFieldType* obj, std::size_t objSize)
{
    addData(reinterpret_cast<const U8*>(obj), objSize);
}

inline void FieldTypeFactory::create(U16 type)
{
    setType(type);
}

inline void FieldTypeFactory::setType(U16 value)
{
    psc::FieldType& obj = getObj();
    obj.fieldTypeChoice = value;
}

#endif // POPULUSSC_FIELDTYPEFACTORY_H
