/******************************************************************************
**
**   File:        FrameTest.cpp
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

#include "WidgetTestBase.h"

#include <Frame.h>

#include <LSRErrorCollector.h>
#include <PageDatabaseType.h>
#include <PanelDatabaseType.h>
#include <PageType.h>
#include <HMIGlobalSettingsType.h>
#include <DisplaySizeType.h>
#include <DDHType.h>
#include <Telltales.hpp>

#include <gtest/gtest.h>

using namespace lsr;

class FrameTest: public WidgetTestBase
{
protected:
    FrameTest()
        : m_db(Telltales::getDDH())
    {}

    lsr::Frame* create()
    {
        lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
        lsr::Frame* frame = lsr::Frame::create(m_widgetPool,
                                               m_db,
                                               1U,
                                               NULL,
                                               &m_context,
                                               error);
        EXPECT_EQ(LSR_NO_ENGINE_ERROR, error.get());

        return frame;
    }

    lsr::Database m_db;
};

TEST_F(FrameTest, CreateFrameTest)
{
    lsr::Frame* frame = create();
    EXPECT_TRUE(NULL != frame);
}

TEST_F(FrameTest, CreateFrameWithWrongPanelTest)
{
    PanelId panelIds[] = { 1U };
    PageType page = { panelIds, 1, NULL, NULL };
    PageType* pages[] = { &page };
    PageDatabaseType pageDB = { pages, 1 };

    AreaType area = { 0U, 0U, 0U, 0U };
    PanelType p1 = {&area, NULL, NULL, 0U}; // broken panel (without visibility set)
    PanelType* panels1[] = { &p1 };
    PanelDatabaseType panelDB1 = {panels1, 1};

    DisplaySizeType displaySize = { 0U, 0U };
    HMIGlobalSettingsType globalSettings = { &displaySize, NULL };

    const DDHType ddh = {
        0U,
        DDHType::SCHEMA_CHECKSUM,
        DDHType::SCHEMA_VERSION,
        DDHType::SERIALIZER_VERSION,
        &pageDB,
        &panelDB1,
        &globalSettings,
        NULL,
        NULL,
        NULL,
        0U
    };
    Database db(&ddh);

    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
    lsr::Frame* frame = lsr::Frame::create(m_widgetPool,
                                           db,
                                           1U,
                                           NULL,
                                           &m_context,
                                           error);
    EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());
    EXPECT_TRUE(NULL == frame);
}

TEST_F(FrameTest, VerifyTest)
{
    lsr::Area area;
    lsr::Frame* frame = create();
    EXPECT_TRUE(NULL != frame);
    EXPECT_TRUE(frame->verify(m_canvas, area));
}

TEST_F(FrameTest, DrawTest)
{
    lsr::Area area;
    lsr::Frame* frame = create();

    EXPECT_TRUE(NULL != frame);

    frame->update(0U);
    frame->draw(m_canvas, area);

    // All bitmaps should be drawn
    EXPECT_TRUE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
