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

#include <ResourceBuffer.h>
#include <Database.h>
#include <DisplaySizeType.h>
#include <StaticBitmapFieldType.h>
#include <ReferenceBitmapFieldType.h>
#include <AreaType.h>
#include <PanelType.h>

#include <DisplayManager.h>
#include <WindowDefinition.h>

#include <DataContext.h>
#include <MockDataHandler.h>

#include <Telltales.hpp>
#include <LsrLimits.h>

#include <gtest/gtest.h>

using namespace lsr;

TEST(WidgetPoolTest, CreateMaxBitmaps)
{
    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::Database db(Telltales::getDDH());

    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &area, &visible, &bmp };

    helper.fillUpWithBitmaps(&bmpField, db, &context);

    EXPECT_TRUE(helper.isBitMapPoolFilled());
}

TEST(WidgetPoolTest, CreateMaxReferenceBitmaps)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const ReferenceBitmapFieldType bmpField = { 32U, &area, &visible, &bmp };

    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(Telltales::getDDH());

    helper.fillUpWithReferenceBitmaps(&bmpField, db, &context);

    EXPECT_TRUE(helper.isReferenceBitMapPoolFilled());
}

TEST(WidgetPoolTest, CreateMaxPanels)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const PanelType tpanel = { &area, &visible, NULL, 0 };

    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(Telltales::getDDH());

    helper.fillUpWithPanels(&tpanel, db, &context);

    EXPECT_TRUE(helper.isPanelPoolFilled());
}

TEST(WidgetPoolTest, CreateMaxFrames)
{
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(Telltales::getDDH());

    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    helper.fillUpWithFrames(db, 1U, NULL, &context);

    EXPECT_TRUE(helper.isFramePoolFilled());
}

TEST(WidgetPoolTest, CreateMaxWindows)
{
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(Telltales::getDDH());

    lsr::WindowDefinition winDef;
    winDef.width = 400;
    winDef.height = 240;
    winDef.xPos = 0;
    winDef.yPos = 0;
    winDef.id = 0;

    lsr::DisplayManager dm;
    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);

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
