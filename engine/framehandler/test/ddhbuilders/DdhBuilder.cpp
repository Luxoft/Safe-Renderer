/******************************************************************************
**
**   File:        DdhBuilder.cpp
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

#include "DdhBuilder.h"
#include "DdhPanelBuilder.h"
#include "DdhPageBuilder.h"

#include <PanelDatabaseTypeFactory.h>
#include <PageDatabaseTypeFactory.h>
#include <HMIGlobalSettingsTypeFactory.h>
#include <DisplaySizeType.h>

namespace framehandlertests
{

DdhBuilder::DdhBuilder()
{}

void DdhBuilder::create(const DdhPanelBuilder& panelBuilder,
                        const DdhPageBuilder& pageBuilder)
{
    addPanels(panelBuilder, 1U);
    addPages(pageBuilder);
}

void DdhBuilder::create(const DdhPanelBuilder& panelBuilder,
                        const DdhPageBuilder& pageBuilder,
                        const lsr::DisplaySizeType& displaySize,
                        U32 panelCount)
{
    addPanels(panelBuilder, panelCount);
    addPages(pageBuilder);
    addDisplaySetting(displaySize);
}

void DdhBuilder::addPanels(const DdhPanelBuilder& panelBuilder, U32 panelCount)
{
    PanelDatabaseTypeFactory panelDBFactory;
    panelDBFactory.create(panelCount);
    for (U32 i = 0U; i < panelCount; ++i)
    {
        panelDBFactory.addPanel(panelBuilder.getDdh(), panelBuilder.getSize());
    }
    m_factory.addPanelDatabase(panelDBFactory.getDdh(), panelDBFactory.getSize());
}

void DdhBuilder::addPages(const DdhPageBuilder& pageBuilder)
{
    PageDatabaseTypeFactory pageDbFactory;
    const U32 pageCount = 1U;
    pageDbFactory.create(pageCount);
    pageDbFactory.addPage(pageBuilder.getDdh(), pageBuilder.getSize());
    m_factory.addPageDatabase(pageDbFactory.getDdh(), pageDbFactory.getSize());
}

void DdhBuilder::addDisplaySetting(const lsr::DisplaySizeType& displaySize)
{
    HMIGlobalSettingsTypeFactory factory;
    factory.addDisplaySize(displaySize);
    m_factory.addHMIGlobalSettings(factory.getDdh(), factory.getSize());
}

} // namespace framehandlertests
