#ifndef LUXOFTSAFERENDERER_DDHBUILDER_H
#define LUXOFTSAFERENDERER_DDHBUILDER_H

/******************************************************************************
**
**   File:        DdhBuilder.h
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

#include <DDHTypeFactory.h>

namespace lsr
{
    struct DisplaySizeType;
}

namespace framehandlertests
{

class DdhPanelBuilder;
class DdhPageBuilder;

class DdhBuilder
{
public:
    DdhBuilder();

    const lsr::DDHType* getDdh() const;

    std::size_t getSize() const;

    void create(const DdhPanelBuilder& panelBuilder,
                const DdhPageBuilder& pageBuilder);

    void create(const DdhPanelBuilder& panelBuilder,
                const DdhPageBuilder& pageBuilder,
                const lsr::DisplaySizeType& displaySize,
                U32 panelCount = 1U);

private:
    void addPanels(const DdhPanelBuilder& panelBuilder, U32 panelCount);
    void addPages(const DdhPageBuilder& pageBuilder);
    void addDisplaySetting(const lsr::DisplaySizeType& displaySize);

    DDHTypeFactory m_factory;
};

inline const lsr::DDHType* DdhBuilder::getDdh() const
{
    return reinterpret_cast<const lsr::DDHType*>(m_factory.getData());
}

inline std::size_t DdhBuilder::getSize() const
{
    return m_factory.getDataSize();
}

} // namespace framehandlertests

#endif // LUXOFTSAFERENDERER_DDHBUILDER_H
