#ifndef LUXOFTSAFERENDERER_WIDGETTESTBASE_H
#define LUXOFTSAFERENDERER_WIDGETTESTBASE_H

/******************************************************************************
**
**   File:        WidgetTestBase.h
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

#include "TestCanvas.h"

#include <WidgetPool.h>

#include <MockDataHandler.h>

#include <AreaType.h>
#include <ReferenceBitmapFieldType.h>
#include <StaticBitmapFieldType.h>
#include <ExpressionTermType.h>
#include <BaseFieldChoiceType.h>
#include <PanelType.h>
#include <ResourceBuffer.h>
#include <PageDatabaseType.h>
#include <PageType.h>
#include <HMIGlobalSettingsType.h>
#include <PanelDatabaseType.h>
#include <DDHType.h>
#include <Database.h>
#include <DatabaseAccessor.h>

#include <DisplayManager.h>
#include <DisplayAccessor.h>
#include <DisplaySizeType.h>
#include <DataContext.h>

#include <gtest/gtest.h>

class WidgetTestBase: public testing::Test
{
protected:
    WidgetTestBase();

    void SetUp();
    void TearDown();

    void initDataHandler(U32 value);
    void initDHWithOutdatedData(U32 value);

    lsr::WidgetPool m_widgetPool;
    MockDataHandler m_dataHandler;
    lsr::DataContext m_context;
    lsr::DisplayManager m_dsp;
    TestCanvas m_canvas;
};

inline WidgetTestBase::WidgetTestBase()
    : m_widgetPool()
    , m_dataHandler()
    , m_context(m_dataHandler)
    , m_dsp()
    , m_canvas(m_dsp, 640U, 480U)
{
}

inline void WidgetTestBase::SetUp()
{
    lsr::DatabaseAccessor::instance().toDefault();
    lsr::DisplayAccessor::instance().toDefault();
}

inline void WidgetTestBase::TearDown()
{
}

inline void WidgetTestBase::initDataHandler(U32 value)
{
    lsr::Number num(value, lsr::DATATYPE_INTEGER);
    m_dataHandler.setNumber(num);
}

inline void WidgetTestBase::initDHWithOutdatedData(U32 value)
{
    lsr::Number num(value, lsr::DATATYPE_INTEGER);
    m_dataHandler.setOutDatedNumber(num);
}




#endif // LUXOFTSAFERENDERER_WIDGETTESTBASE_H
