#ifndef POPULUSSC_PAGETYPEFACTORY_H
#define POPULUSSC_PAGETYPEFACTORY_H

/******************************************************************************
**
**   File:        PageTypeFactory.h
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

#include <PageType.h>

namespace ddh
{
    struct PanelType;
}

class PageTypeFactory: public DdhArrayObject<psc::PageType>
{
public:
    PageTypeFactory();

    const psc::PageType* getDdh() const;

    std::size_t getSize() const;

    void create(U16 panelIdCount);

    void addPanelId(U16 panelId);

protected:
    void setPanelIdCount(U16 value);

    void setPanelIdOffset(U16 value);
};

inline PageTypeFactory::PageTypeFactory()
{
    setPanelIdCount(0U);
    setPanelIdOffset(0U);
}

inline const psc::PageType* PageTypeFactory::getDdh() const
{
    return reinterpret_cast<const psc::PageType*>(getData());
}

inline std::size_t PageTypeFactory::getSize() const
{
    return getDataSize();
}

inline void PageTypeFactory::create(U16 panelIdCount)
{
    setPanelIdCount(panelIdCount);

    U16 panelsIdOffset = addArray(panelIdCount);
    setPanelIdOffset(panelsIdOffset);
}

inline void PageTypeFactory::addPanelId(U16 panelId)
{
    addValueToArray(panelId);
}

inline void PageTypeFactory::setPanelIdCount(U16 value)
{
    psc::PageType& obj = getObj();
    obj.panelIdSize = value;
}

inline void PageTypeFactory::setPanelIdOffset(U16 value)
{
    psc::PageType& obj = getObj();
    obj.panelIdOffset = value;
}

#endif // POPULUSSC_PAGETYPEFACTORY_H
