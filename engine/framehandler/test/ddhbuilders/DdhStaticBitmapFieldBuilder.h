#ifndef POPULUSSC_DDHSTATICBITMAPFIELDBUILDER_H
#define POPULUSSC_DDHSTATICBITMAPFIELDBUILDER_H

/******************************************************************************
**
**   File:        DdhStaticBitmapFieldBuilder.h
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

#include <StaticBitmapFieldTypeFactory.h>

namespace psc
{
    struct AreaType;
    struct StaticBitmapFieldType;
    struct DynamicDataType;
}

namespace framehandlertests
{

class DdhStaticBitmapFieldBuilder
{
public:
    DdhStaticBitmapFieldBuilder();

    const psc::StaticBitmapFieldType* getDdh() const;

    std::size_t getSize() const;

    void create(const psc::AreaType& area,
                const bool isVisible,
                const U32 bitmapId);

    void create(const psc::AreaType& area,
                const bool isVisible,
                const psc::DynamicDataType& bitmapId);

    void createWithoutVisibility(const psc::AreaType& area,
                                 const U32 bitmapId);

    void createWithoutBitmap(const psc::AreaType& area,
                             const bool isVisible);

    void createWithoutArea(const bool isVisible,
                           const U32 bitmapId);

private:
    void addArea(const psc::AreaType& area);
    void addVisibility(const bool isVisible);
    void addBitmap(const U32 bitmapId);
    void addDynamicBitmap(const psc::DynamicDataType& value);

    StaticBitmapFieldTypeFactory m_factory;
};

inline const psc::StaticBitmapFieldType* DdhStaticBitmapFieldBuilder::getDdh() const
{
    return reinterpret_cast<const psc::StaticBitmapFieldType*>(m_factory.getData());
}

inline std::size_t DdhStaticBitmapFieldBuilder::getSize() const
{
    return m_factory.getDataSize();
}

} // namespace framehandlertests

#endif // POPULUSSC_DDHSTATICBITMAPFIELDBUILDER_H
