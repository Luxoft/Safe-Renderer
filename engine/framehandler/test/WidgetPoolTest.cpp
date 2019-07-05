/******************************************************************************
**
**   File:        WidgetPoolTest.cpp
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

#include "WidgetPoolHelper.h"
#include "WidgetPoolCorrupter.h"
#include "DdhStaticBitmapFieldBuilder.h"
#include "DdhReferenceBitmapFieldBuilder.h"
#include "DdhPanelBuilder.h"
#include "DdhPageBuilder.h"
#include "DdhBuilder.h"

#include <ResourceBuffer.h>
#include <Database.h>
#include <DisplaySizeType.h>

#include <DisplayManager.h>
#include <WindowDefinition.h>

#include <TestDataContext.h>
#include <MockDataHandler.h>

#include <LsrLimits.h>

#include <gtest/gtest.h>

TEST(WidgetPoolTest, CreateMaxBitmaps)
{
    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    framehandlertests::DdhStaticBitmapFieldBuilder builder;
    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    lsr::ResourceBuffer binBuffer;
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    lsr::AreaType area;
    builder.create(area, true, 23U);

    helper.fillUpWithBitmaps(builder.getDdh(), db, &context);

    EXPECT_TRUE(helper.isBitMapPoolFilled());
}

TEST(WidgetPoolTest, CreateMaxReferenceBitmaps)
{
    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    framehandlertests::DdhReferenceBitmapFieldBuilder builder;
    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    lsr::ResourceBuffer binBuffer;
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    lsr::AreaType area;
    builder.create(23U, area, true, 23U);

    helper.fillUpWithReferenceBitmaps(builder.getDdh(), db, &context);

    EXPECT_TRUE(helper.isReferenceBitMapPoolFilled());
}

TEST(WidgetPoolTest, CreateMaxPanels)
{
    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    framehandlertests::DdhPanelBuilder builder;
    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    lsr::ResourceBuffer binBuffer;
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    lsr::AreaType area;
    builder.create(area, true, 0U);

    helper.fillUpWithPanels(builder.getDdh(), db, &context);

    EXPECT_TRUE(helper.isPanelPoolFilled());
}

TEST(WidgetPoolTest, CreateMaxFrames)
{
    lsr::AreaType area;
    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.create(area, true, 2U);

    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    lsr::DisplaySizeType displaySize;

    framehandlertests::DdhBuilder ddhBuilder;
    ddhBuilder.create(panelBuilder, pageBuilder, displaySize);

    lsr::ResourceBuffer binBuffer(ddhBuilder.getDdh(), ddhBuilder.getSize());
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    helper.fillUpWithFrames(db, 1U, NULL, &context);

    EXPECT_TRUE(helper.isFramePoolFilled());
}

TEST(WidgetPoolTest, CreateMaxWindows)
{
    lsr::AreaType area;
    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.create(area, true, 2U);

    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhBuilder ddhBuilder;
    lsr::DisplaySizeType displaySize;
    ddhBuilder.create(panelBuilder, pageBuilder, displaySize);

    lsr::ResourceBuffer binBuffer(ddhBuilder.getDdh(), ddhBuilder.getSize());
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    lsr::WindowDefinition winDef;
    winDef.width = displaySize.GetWidth();
    winDef.height = displaySize.GetHeight();
    winDef.xPos = 0;
    winDef.yPos = 0;
    winDef.id = 0;

    lsr::DisplayManager dm;
    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    helper.fillUpWithWindows(db, dm, winDef, &context);

    EXPECT_TRUE(helper.isWindowPoolFilled());
}

TEST(WidgetPoolTest, GetErrorTest)
{
    lsr::WidgetPool widgetPool;

    EXPECT_EQ(LSR_NO_ERROR, widgetPool.getError());
}

TEST(WidgetPoolTest, GetErrorWithCorruptedBitmapPoolTest)
{
    lsr::WidgetPool widgetPool;
    WidgetPoolCorrupter corrupter(&widgetPool);

    corrupter.corruptBitmapStorage();

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, widgetPool.getError());
}

TEST(WidgetPoolTest, GetErrorWithCorruptedRefBitmapPoolTest)
{
    lsr::WidgetPool widgetPool;
    WidgetPoolCorrupter corrupter(&widgetPool);

    corrupter.corruptRefBitmapStorage();

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, widgetPool.getError());
}

TEST(WidgetPoolTest, GetErrorWithCorruptedFramePoolTest)
{
    lsr::WidgetPool widgetPool;
    WidgetPoolCorrupter corrupter(&widgetPool);

    corrupter.corruptFrameStorage();

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, widgetPool.getError());
}

TEST(WidgetPoolTest, GetErrorWithCorruptedPanelPoolTest)
{
    lsr::WidgetPool widgetPool;
    WidgetPoolCorrupter corrupter(&widgetPool);

    corrupter.corruptPanelStorage();

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, widgetPool.getError());
}

TEST(WidgetPoolTest, GetErrorWithCorruptedWindowPoolTest)
{
    lsr::WidgetPool widgetPool;
    WidgetPoolCorrupter corrupter(&widgetPool);

    corrupter.corruptWindowStorage();

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, widgetPool.getError());
}
