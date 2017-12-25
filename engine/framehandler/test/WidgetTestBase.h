#ifndef POPULUSSC_WIDGETTESTBASE_H
#define POPULUSSC_WIDGETTESTBASE_H

/******************************************************************************
**
**   File:        WidgetTestBase.h
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

#include "DdhBuilder.h"
#include "DdhPanelBuilder.h"
#include "DdhPageBuilder.h"
#include "TestCanvas.h"

#include <WidgetPool.h>

#include <TestDataContext.h>
#include <MockDataHandler.h>

#include <AreaType.h>
#include <ResourceBuffer.h>
#include <Database.h>
#include <DatabaseAccessor.h>

#include <DisplayManager.h>
#include <DisplayAccessor.h>
#include <DisplaySizeType.h>

#include <gtest/gtest.h>

class WidgetTestBase: public testing::Test
{
protected:
    WidgetTestBase();

    void SetUp();
    void TearDown();

    void initDataHandler(U32 value);
    void initDHWithOutdatedData(U32 value);

    void initNullDb();
    void initNormalDb();
    void initDb(framehandlertests::DdhPageBuilder& pageBuilder,
                framehandlertests::DdhPanelBuilder& panelBuilder);
    void initDb(framehandlertests::DdhPageBuilder& pageBuilder,
                framehandlertests::DdhPanelBuilder& panelBuilder,
                const psc::DisplaySizeType& displaySize);
    void initDbWithManyPanels(framehandlertests::DdhPageBuilder& pageBuilder,
                              framehandlertests::DdhPanelBuilder& panelBuilder,
                              const psc::DisplaySizeType& displaySize,
                              U32 panelCount);

    framehandlertests::DdhBuilder m_ddhBuilder;

    psc::WidgetPool m_widgetPool;
    MockDataHandler m_dataHandler;
    TestDataContext m_context;
    psc::DisplayManager m_dsp;
    TestCanvas m_canvas;

    psc::ResourceBuffer* m_pBinBuffer;
    psc::ResourceBuffer* m_pImgBuffer;
    psc::Database* m_pDb;

private:
    void deinitDB();
};

inline WidgetTestBase::WidgetTestBase()
    : m_ddhBuilder()
    , m_widgetPool()
    , m_dataHandler()
    , m_context()
    , m_dsp()
    , m_canvas(m_dsp, 640U, 480U)
    , m_pBinBuffer(NULL)
    , m_pImgBuffer(NULL)
    , m_pDb(NULL)
{
    m_context.setHandler(&m_dataHandler);
}

inline void WidgetTestBase::SetUp()
{
    initNullDb();

    psc::DatabaseAccessor::instance().toDefault();
    psc::DisplayAccessor::instance().toDefault();
}

inline void WidgetTestBase::TearDown()
{
    deinitDB();
}

inline void WidgetTestBase::deinitDB()
{
    if (m_pDb)
    {
        delete m_pDb;
        m_pDb = NULL;
    }

    if (m_pBinBuffer)
    {
        delete m_pBinBuffer;
        m_pBinBuffer = NULL;
    }

    if (m_pImgBuffer)
    {
        delete m_pImgBuffer;
        m_pImgBuffer = NULL;
    }
}

inline void WidgetTestBase::initDataHandler(U32 value)
{
    psc::Number num(value, psc::DATATYPE_INTEGER);
    m_dataHandler.setNumber(num);
}

inline void WidgetTestBase::initDHWithOutdatedData(U32 value)
{
    psc::Number num(value, psc::DATATYPE_INTEGER);
    m_dataHandler.setOutDatedNumber(num);
}

inline void WidgetTestBase::initDb(framehandlertests::DdhPageBuilder& pageBuilder,
                            framehandlertests::DdhPanelBuilder& panelBuilder)
{
    deinitDB();

    psc::DisplaySizeType displaySize;
    m_ddhBuilder.create(panelBuilder, pageBuilder, displaySize);

    m_pBinBuffer = new psc::ResourceBuffer(m_ddhBuilder.getDdh(), m_ddhBuilder.getSize());
    m_pImgBuffer = new psc::ResourceBuffer();
    m_pDb = new psc::Database(*m_pBinBuffer, *m_pImgBuffer);
}

inline void WidgetTestBase::initDb(framehandlertests::DdhPageBuilder& pageBuilder,
                            framehandlertests::DdhPanelBuilder& panelBuilder,
                            const psc::DisplaySizeType& displaySize)
{
    deinitDB();

    m_ddhBuilder.create(panelBuilder, pageBuilder, displaySize);

    m_pBinBuffer = new psc::ResourceBuffer(m_ddhBuilder.getDdh(), m_ddhBuilder.getSize());
    m_pImgBuffer = new psc::ResourceBuffer();
    m_pDb = new psc::Database(*m_pBinBuffer, *m_pImgBuffer);
}

inline void WidgetTestBase::initDbWithManyPanels(framehandlertests::DdhPageBuilder& pageBuilder,
                                                 framehandlertests::DdhPanelBuilder& panelBuilder,
                                                 const psc::DisplaySizeType& displaySize,
                                                 U32 panelCount)
{
    deinitDB();

    m_ddhBuilder.create(panelBuilder, pageBuilder, displaySize, panelCount);

    m_pBinBuffer = new psc::ResourceBuffer(m_ddhBuilder.getDdh(), m_ddhBuilder.getSize());
    m_pImgBuffer = new psc::ResourceBuffer();
    m_pDb = new psc::Database(*m_pBinBuffer, *m_pImgBuffer);
}

inline void WidgetTestBase::initNullDb()
{
    deinitDB();

    m_pBinBuffer = new psc::ResourceBuffer();
    m_pImgBuffer = new psc::ResourceBuffer();
    m_pDb = new psc::Database(*m_pBinBuffer, *m_pImgBuffer);
}

inline void WidgetTestBase::initNormalDb()
{
    deinitDB();

    psc::AreaType area;
    psc::DisplaySizeType displaySize;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.create(area, true, 2U);

    initDb(pageBuilder, panelBuilder, displaySize);
}

#endif // POPULUSSC_WIDGETTESTBASE_H
