#ifndef LUXOFTSAFERENDERER_DDHSTATICBITMAPFIELDBUILDER_H
#define LUXOFTSAFERENDERER_DDHSTATICBITMAPFIELDBUILDER_H

/******************************************************************************
**
**   File:        DdhStaticBitmapFieldBuilder.h
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

#include <StaticBitmapFieldTypeFactory.h>

namespace lsr
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

    const lsr::StaticBitmapFieldType* getDdh() const;

    std::size_t getSize() const;

    void create(const lsr::AreaType& area,
                const bool isVisible,
                const U32 bitmapId);

    void create(const lsr::AreaType& area,
                const bool isVisible,
                const lsr::DynamicDataType& bitmapId);

    void createWithoutVisibility(const lsr::AreaType& area,
                                 const U32 bitmapId);

    void createWithoutBitmap(const lsr::AreaType& area,
                             const bool isVisible);

    void createWithoutArea(const bool isVisible,
                           const U32 bitmapId);

private:
    void addArea(const lsr::AreaType& area);
    void addVisibility(const bool isVisible);
    void addBitmap(const U32 bitmapId);
    void addDynamicBitmap(const lsr::DynamicDataType& value);

    StaticBitmapFieldTypeFactory m_factory;
};

inline const lsr::StaticBitmapFieldType* DdhStaticBitmapFieldBuilder::getDdh() const
{
    return reinterpret_cast<const lsr::StaticBitmapFieldType*>(m_factory.getData());
}

inline std::size_t DdhStaticBitmapFieldBuilder::getSize() const
{
    return m_factory.getDataSize();
}

} // namespace framehandlertests

#endif // LUXOFTSAFERENDERER_DDHSTATICBITMAPFIELDBUILDER_H
