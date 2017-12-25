#ifndef POPULUSSC_DDHBUILDER_H
#define POPULUSSC_DDHBUILDER_H

/******************************************************************************
**
**   File:        DdhBuilder.h
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

#include <DDHTypeFactory.h>

namespace psc
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

    const psc::DDHType* getDdh() const;

    std::size_t getSize() const;

    void create(const DdhPanelBuilder& panelBuilder,
                const DdhPageBuilder& pageBuilder);

    void create(const DdhPanelBuilder& panelBuilder,
                const DdhPageBuilder& pageBuilder,
                const psc::DisplaySizeType& displaySize,
                U32 panelCount = 1U);

private:
    void addPanels(const DdhPanelBuilder& panelBuilder, U32 panelCount);
    void addPages(const DdhPageBuilder& pageBuilder);
    void addDisplaySetting(const psc::DisplaySizeType& displaySize);

    DDHTypeFactory m_factory;
};

inline const psc::DDHType* DdhBuilder::getDdh() const
{
    return reinterpret_cast<const psc::DDHType*>(m_factory.getData());
}

inline std::size_t DdhBuilder::getSize() const
{
    return m_factory.getDataSize();
}

} // namespace framehandlertests

#endif // POPULUSSC_DDHBUILDER_H
