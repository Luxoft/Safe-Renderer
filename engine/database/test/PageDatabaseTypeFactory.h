#ifndef POPULUSSC_PAGEDATABASETYPEFACTORY_H
#define POPULUSSC_PAGEDATABASETYPEFACTORY_H

/******************************************************************************
**
**   File:        PageDatabaseTypeFactory.h
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

#include <PageDatabaseType.h>

namespace ddh
{
    struct PageType;
}

class PageDatabaseTypeFactory: public DdhArrayObject<psc::PageDatabaseType, U32>
{
public:
    PageDatabaseTypeFactory();

    const psc::PageDatabaseType* getDdh() const;

    std::size_t getSize() const;

    void create(U32 pageCount);

    void addPage(const psc::PageType* page, std::size_t pageSize);

protected:
    void setPageCount(U32 value);

    void setPageOffset(U32 value);
};

inline PageDatabaseTypeFactory::PageDatabaseTypeFactory()
{
    setPageCount(0U);
    setPageOffset(0U);
}

inline const psc::PageDatabaseType* PageDatabaseTypeFactory::getDdh() const
{
    return reinterpret_cast<const psc::PageDatabaseType*>(getData());
}

inline std::size_t PageDatabaseTypeFactory::getSize() const
{
    return getDataSize();
}

inline void PageDatabaseTypeFactory::create(U32 pageCount)
{
    setPageCount(pageCount);

    U32 pageOffset = addArray(pageCount);
    setPageOffset(pageOffset);
}

inline void PageDatabaseTypeFactory::addPage(const psc::PageType* page, std::size_t pageSize)
{
    addDataToArray(reinterpret_cast<const U8*>(page), pageSize);
}

inline void PageDatabaseTypeFactory::setPageCount(U32 value)
{
    psc::PageDatabaseType& obj = getObj();
    obj.pageCount = value;
}

inline void PageDatabaseTypeFactory::setPageOffset(U32 value)
{
    psc::PageDatabaseType& obj = getObj();
    obj.pageOffset = value;
}

#endif // POPULUSSC_PAGEDATABASETYPEFACTORY_H
