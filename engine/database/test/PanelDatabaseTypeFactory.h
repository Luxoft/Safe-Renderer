#ifndef POPULUSSC_PANELDATABASETYPEFACTORY_H
#define POPULUSSC_PANELDATABASETYPEFACTORY_H

/******************************************************************************
**
**   File:        PanelDatabaseTypeFactory.h
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

#include "DdhArrayObject.h"

#include <PanelDatabaseType.h>

namespace ddh
{
    struct PanelType;
}

class PanelDatabaseTypeFactory: public DdhArrayObject<psc::PanelDatabaseType, U32>
{
public:
    PanelDatabaseTypeFactory();

    const psc::PanelDatabaseType* getDdh() const;

    std::size_t getSize() const;

    void create(U32 panelCount);

    void addPanel(const psc::PanelType* panel, std::size_t panelSize);

protected:
    void setPanelCount(U32 value);

    void setPanelOffset(U32 value);
};

inline PanelDatabaseTypeFactory::PanelDatabaseTypeFactory()
{
    setPanelCount(0U);
    setPanelOffset(0U);
}

inline const psc::PanelDatabaseType* PanelDatabaseTypeFactory::getDdh() const
{
    return reinterpret_cast<const psc::PanelDatabaseType*>(getData());
}

inline std::size_t PanelDatabaseTypeFactory::getSize() const
{
    return getDataSize();
}

inline void PanelDatabaseTypeFactory::create(U32 panelCount)
{
    setPanelCount(panelCount);

    U32 offset = addArray(panelCount);
    setPanelOffset(offset);
}

inline void PanelDatabaseTypeFactory::addPanel(const psc::PanelType* panel, std::size_t panelSize)
{
    addDataToArray(reinterpret_cast<const U8*>(panel), panelSize);
}

inline void PanelDatabaseTypeFactory::setPanelCount(U32 value)
{
    psc::PanelDatabaseType& obj = getObj();
    obj.panelCount = value;
}

inline void PanelDatabaseTypeFactory::setPanelOffset(U32 value)
{
    psc::PanelDatabaseType& obj = getObj();
    obj.panelOffset = value;
}

#endif // POPULUSSC_PANELDATABASETYPEFACTORY_H
