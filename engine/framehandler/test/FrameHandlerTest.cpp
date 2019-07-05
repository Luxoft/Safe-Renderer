/******************************************************************************
**
**   File:        FrameHandlerTest.cpp
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

#include "FrameHandlerCorrupter.h"

#include <WidgetTestBase.h>

#include <FrameHandler.h>

#include <DynamicDataType.h>

#include <gtest/gtest.h>

class FrameHandlerTest: public WidgetTestBase
{
protected:
    FrameHandlerTest()
    {}
};

TEST_F(FrameHandlerTest, CreateTest)
{
    initNormalDb();

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ERROR, fh.getError());
}

TEST_F(FrameHandlerTest, CreateTwiceTest)
{
    initNormalDb();

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ERROR, fh.getError());
}

TEST_F(FrameHandlerTest, GetErrorTest)
{
    initNormalDb();

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);
    EXPECT_TRUE(fh.start());

    EXPECT_EQ(LSR_NO_ERROR, fh.getError());
}

TEST_F(FrameHandlerTest, GetErrorWithErrorInWidgetTest)
{
    lsr::AreaType area;
    lsr::DisplaySizeType displaySize;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    lsr::DynamicDataType dataType;
    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.create(area, true, 2U, &dataType);

    initDb(pageBuilder, panelBuilder, displaySize);

    lsr::Number num(5U, lsr::DATATYPE_INTEGER);
    m_dataHandler.setOutDatedNumber(num);

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);
    EXPECT_TRUE(fh.start());

    fh.update(0U);

    EXPECT_EQ(LSR_DATASTATUS_NOT_AVAIABLE, fh.getError());
}

TEST_F(FrameHandlerTest, GetErrorWithErrorInWidgetSetupTest)
{
    lsr::AreaType area;
    lsr::DisplaySizeType displaySize;
    const U32 panelCount = MAX_PANELS_COUNT + 1U;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(panelCount, 1U);

    framehandlertests::DdhPanelBuilder panelBuilder;
    // Create too many fields on the panel
    panelBuilder.create(area, true, panelCount);

    initDbWithManyPanels(pageBuilder, panelBuilder, displaySize, panelCount);

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);
    EXPECT_FALSE(fh.start());

    EXPECT_EQ(LSR_POOL_IS_FULL, fh.getError());
}

TEST_F(FrameHandlerTest, GetErrorWithErrorInWidgetPoolTest)
{
    initNormalDb();

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);
    EXPECT_TRUE(fh.start());

    FrameHandlerCorrupter corrupter(fh);
    corrupter.corruptStorage();

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, fh.getError());
}

TEST_F(FrameHandlerTest, VerifyTest)
{
    lsr::AreaType areaType;

    lsr::DisplaySizeType displaySize;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.createWithRefBitmaps(areaType, true, 2U);

    initDb(pageBuilder, panelBuilder, displaySize);

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ERROR, fh.getError());

    fh.update(0U);
    EXPECT_TRUE(fh.verify());

    lsr::DisplayAccessor::instance().setVerifyFlag(false);
    EXPECT_FALSE(fh.verify());
}

TEST_F(FrameHandlerTest, DrawTest)
{
    initNormalDb();

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ERROR, fh.getError());

    fh.update(0U);
    EXPECT_TRUE(fh.render());

    // All bitmaps should be drawn
    EXPECT_TRUE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

TEST_F(FrameHandlerTest, RenderWithNotInvalidatedStateTest)
{
    initNormalDb();

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ERROR, fh.getError());

    fh.update(0U);
    EXPECT_TRUE(fh.render());

    lsr::DisplayAccessor::instance().toDefault();

    // now we are in validated state
    EXPECT_FALSE(fh.render());

    EXPECT_FALSE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

// test to fulfill coverage
TEST_F(FrameHandlerTest, HandleWindowEventsTest)
{
    initNormalDb();

    lsr::FrameHandler fh(*m_pDb, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ERROR, fh.getError());

    fh.handleWindowEvents();

    EXPECT_FALSE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
