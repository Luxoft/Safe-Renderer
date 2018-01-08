#ifndef POPULUSSC_DDHPANELBUILDER_H
#define POPULUSSC_DDHPANELBUILDER_H

/******************************************************************************
**
**   File:        DdhPanelBuilder.h
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

#include <PanelTypeFactory.h>

#include <DynamicDataType.h>

namespace framehandlertests
{

class DdhPanelBuilder
{
public:
    DdhPanelBuilder();

    const psc::PanelType* getDdh() const;

    std::size_t getSize() const;

    void create(const psc::AreaType& area,
                const bool isVisible,
                U16 fieldsCount,
                const psc::DynamicDataType* bitmapId = NULL);

    void createWithRefBitmaps(const psc::AreaType& area,
                              const bool isVisible,
                              U16 fieldsCount);

    void createWithoutArea(const psc::AreaType& area,
                           const bool isVisible,
                           U16 fieldsCount);

    void createWithoutVisibility(const psc::AreaType& area,
                                 const bool isVisible,
                                 U16 fieldsCount);

    void createWithoutFields(const psc::AreaType& area,
                             const bool isVisible);

    void createWithFieldWithWrongType(const psc::AreaType& area,
                                      const bool isVisible,
                                      U16 fieldsCount);

    void createWithWrongField(const psc::AreaType& area,
                              const bool isVisible,
                              U16 fieldsCount);

    void createWithTooManyFields(const psc::AreaType& area,
                                 const bool isVisible);

private:
    void addArea(const psc::AreaType& area);
    void addVisibility(const bool isVisible);
    void addFields(const U16 fieldsCount,
                   const bool isVisible,
                   const psc::AreaType& fieldArea,
                   const U16 fieldsType,
                   const psc::DynamicDataType* bitmapId);
    void addWrongFields(const U16 fieldsCount,
                        const psc::AreaType& fieldArea,
                        const U16 fieldsType);

    PanelTypeFactory m_factory;
};

inline const psc::PanelType* DdhPanelBuilder::getDdh() const
{
    return reinterpret_cast<const psc::PanelType*>(m_factory.getData());
}

inline std::size_t DdhPanelBuilder::getSize() const
{
    return m_factory.getDataSize();
}

} // namespace framehandlertests

#endif // POPULUSSC_DDHPANELBUILDER_H
