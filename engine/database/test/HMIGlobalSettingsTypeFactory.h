#ifndef LUXOFTSAFERENDERER_HMIGLOBALSETTINGSTYPEFACTORY_H
#define LUXOFTSAFERENDERER_HMIGLOBALSETTINGSTYPEFACTORY_H

/******************************************************************************
**
**   File:        HMIGlobalSettingsTypeFactory.h
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

#include <HMIGlobalSettingsType.h>
#include <DisplaySizeType.h>
#include <ColorSetType.h>

class HMIGlobalSettingsTypeFactory: public DdhObject<lsr::HMIGlobalSettingsType>
{
public:
    HMIGlobalSettingsTypeFactory();

    const lsr::HMIGlobalSettingsType* getDdh() const;

    std::size_t getSize() const;

    void addDisplaySize(const lsr::DisplaySizeType& size);
    void addColorSet(const lsr::ColorSetType& color);

protected:
    void setDisplaySizeOffset(U16 value);
    void setColorSetOffset(U16 value);
};

inline HMIGlobalSettingsTypeFactory::HMIGlobalSettingsTypeFactory()
{
    setDisplaySizeOffset(0U);
    setColorSetOffset(0U);
}

inline const lsr::HMIGlobalSettingsType* HMIGlobalSettingsTypeFactory::getDdh() const
{
    return reinterpret_cast<const lsr::HMIGlobalSettingsType*>(getData());
}

inline std::size_t HMIGlobalSettingsTypeFactory::getSize() const
{
    return getDataSize();
}

inline void HMIGlobalSettingsTypeFactory::setDisplaySizeOffset(U16 value)
{
    lsr::HMIGlobalSettingsType& obj = getObj();
    obj.displaySizeOffset = value;
}

inline void HMIGlobalSettingsTypeFactory::setColorSetOffset(U16 value)
{
    lsr::HMIGlobalSettingsType& obj = getObj();
    obj.colorSetOffset = value;
}

inline void HMIGlobalSettingsTypeFactory::addDisplaySize(const lsr::DisplaySizeType& size)
{
    U32 offset = addData(reinterpret_cast<const U8*>(&size), sizeof(lsr::DisplaySizeType));
    setDisplaySizeOffset(offset / 4U);
}

inline void HMIGlobalSettingsTypeFactory::addColorSet(const lsr::ColorSetType& color)
{
    U32 offset = addData(reinterpret_cast<const U8*>(&color), sizeof(lsr::ColorSetType));
    setColorSetOffset(offset / 4U);
}

#endif // LUXOFTSAFERENDERER_HMIGLOBALSETTINGSTYPEFACTORY_H
