#ifndef LUXOFTSAFERENDERER_FIELDTYPEFACTORY_H
#define LUXOFTSAFERENDERER_FIELDTYPEFACTORY_H

/******************************************************************************
**
**   File:        FieldTypeFactory.h
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

#include <FieldType.h>

namespace ddh
{
    struct StaticBitmapFieldType;
}

class FieldTypeFactory: public DdhObject<lsr::FieldType>
{
public:
    FieldTypeFactory();

    const lsr::FieldType* getDdh() const;

    std::size_t getSize() const;

    void create(U16 type);

    void addBitmap(const lsr::StaticBitmapFieldType* obj, std::size_t objSize);

    void addBitmap(const lsr::ReferenceBitmapFieldType* obj, std::size_t objSize);

protected:
    void setType(U16 value);
};

inline FieldTypeFactory::FieldTypeFactory()
{
    setType(0U);
}

inline const lsr::FieldType* FieldTypeFactory::getDdh() const
{
    return reinterpret_cast<const lsr::FieldType*>(getData());
}

inline std::size_t FieldTypeFactory::getSize() const
{
    return getDataSize();
}

inline void FieldTypeFactory::addBitmap(const lsr::StaticBitmapFieldType* obj, std::size_t objSize)
{
    addData(reinterpret_cast<const U8*>(obj), objSize);
}

inline void FieldTypeFactory::addBitmap(const lsr::ReferenceBitmapFieldType* obj, std::size_t objSize)
{
    addData(reinterpret_cast<const U8*>(obj), objSize);
}

inline void FieldTypeFactory::create(U16 type)
{
    setType(type);
}

inline void FieldTypeFactory::setType(U16 value)
{
    lsr::FieldType& obj = getObj();
    obj.fieldTypeChoice = value;
}

#endif // LUXOFTSAFERENDERER_FIELDTYPEFACTORY_H
