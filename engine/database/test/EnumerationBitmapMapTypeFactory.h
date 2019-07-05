#ifndef LUXOFTSAFERENDERER_ENUMERATIONBITMAPMAPTYPEFACTORY_H
#define LUXOFTSAFERENDERER_ENUMERATIONBITMAPMAPTYPEFACTORY_H

/******************************************************************************
**
**   File:        EnumerationBitmapMapTypeFactory.h
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

#include <EnumerationBitmapMapType.h>
#include <EnumerationValueType.h>

class EnumerationBitmapMapTypeFactory: public DdhObject<lsr::EnumerationBitmapMapType>
{
public:
    EnumerationBitmapMapTypeFactory();

    const lsr::EnumerationBitmapMapType* getDdh() const;

    std::size_t getSize() const;

    void create(U16 bitmapId, bool isValueSet, U16 value);

protected:
    void setBitmapId(U16 id);
    void setValueOffset(U16 value);
};

inline EnumerationBitmapMapTypeFactory::EnumerationBitmapMapTypeFactory()
{
    setBitmapId(0U);
    setValueOffset(0U);
}

inline const lsr::EnumerationBitmapMapType* EnumerationBitmapMapTypeFactory::getDdh() const
{
    return reinterpret_cast<const lsr::EnumerationBitmapMapType*>(getData());
}

inline std::size_t EnumerationBitmapMapTypeFactory::getSize() const
{
    return getDataSize();
}

inline void EnumerationBitmapMapTypeFactory::setBitmapId(U16 id)
{
    lsr::EnumerationBitmapMapType& obj = getObj();
    obj.bitmapId = id;
}

inline void EnumerationBitmapMapTypeFactory::setValueOffset(U16 value)
{
    lsr::EnumerationBitmapMapType& obj = getObj();
    obj.enumerationValueOffset = value;
}

inline void EnumerationBitmapMapTypeFactory::create(U16 bitmapId, bool isValueSet, U16 value)
{
    setBitmapId(bitmapId);

    lsr::EnumerationValueType valueType;
    valueType.valueSet = static_cast<U8>(isValueSet);
    valueType.value = value;

    U16 offset = addData(reinterpret_cast<const U8*>(&valueType), sizeof(lsr::EnumerationValueType));
    setValueOffset(offset / 4U);
}

#endif // LUXOFTSAFERENDERER_ENUMERATIONBITMAPMAPTYPEFACTORY_H
