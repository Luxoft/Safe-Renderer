#ifndef LUXOFTSAFERENDERER_DDHPANELBUILDER_H
#define LUXOFTSAFERENDERER_DDHPANELBUILDER_H

/******************************************************************************
**
**   File:        DdhPanelBuilder.h
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

#include <PanelTypeFactory.h>

#include <DynamicDataType.h>

namespace framehandlertests
{

class DdhPanelBuilder
{
public:
    DdhPanelBuilder();

    const lsr::PanelType* getDdh() const;

    std::size_t getSize() const;

    void create(const lsr::AreaType& area,
                const bool isVisible,
                U16 fieldsCount,
                const lsr::DynamicDataType* bitmapId = NULL);

    void createWithRefBitmaps(const lsr::AreaType& area,
                              const bool isVisible,
                              U16 fieldsCount);

    void createWithoutArea(const lsr::AreaType& area,
                           const bool isVisible,
                           U16 fieldsCount);

    void createWithoutVisibility(const lsr::AreaType& area,
                                 const bool isVisible,
                                 U16 fieldsCount);

    void createWithoutFields(const lsr::AreaType& area,
                             const bool isVisible);

    void createWithFieldWithWrongType(const lsr::AreaType& area,
                                      const bool isVisible,
                                      U16 fieldsCount);

    void createWithWrongField(const lsr::AreaType& area,
                              const bool isVisible,
                              U16 fieldsCount);

    void createWithTooManyFields(const lsr::AreaType& area,
                                 const bool isVisible);

private:
    void addArea(const lsr::AreaType& area);
    void addVisibility(const bool isVisible);
    void addFields(const U16 fieldsCount,
                   const bool isVisible,
                   const lsr::AreaType& fieldArea,
                   const U16 fieldsType,
                   const lsr::DynamicDataType* bitmapId);
    void addWrongFields(const U16 fieldsCount,
                        const lsr::AreaType& fieldArea,
                        const U16 fieldsType);

    PanelTypeFactory m_factory;
};

inline const lsr::PanelType* DdhPanelBuilder::getDdh() const
{
    return reinterpret_cast<const lsr::PanelType*>(m_factory.getData());
}

inline std::size_t DdhPanelBuilder::getSize() const
{
    return m_factory.getDataSize();
}

} // namespace framehandlertests

#endif // LUXOFTSAFERENDERER_DDHPANELBUILDER_H
