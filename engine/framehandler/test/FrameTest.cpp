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

#include <gtest/gtest.h>

class FrameTest: public WidgetTestBase
{
protected:
    FrameTest()
    {}

    lsr::Frame* create(const lsr::AreaType& area,
                       const bool isVisible,
                       const U16 fieldsCount)
    {
        framehandlertests::DdhPageBuilder pageBuilder;
        pageBuilder.create(1U, 1U);

        framehandlertests::DdhPanelBuilder panelBuilder;
        panelBuilder.create(area, isVisible, fieldsCount);

        initDb(pageBuilder, panelBuilder);

        lsr::LSRErrorCollector error(LSR_NO_ERROR);
        lsr::Frame* frame = lsr::Frame::create(m_widgetPool,
                                               *m_pDb,
                                               1U,
                                               NULL,
                                               &m_context,
                                               error);
        EXPECT_EQ(LSR_NO_ERROR, error.get());

        return frame;
    }
};

TEST_F(FrameTest, CreateFrameTest)
{
    lsr::AreaType area;
    lsr::Frame* frame = create(area, true, 2U);

    EXPECT_TRUE(NULL != frame);
}

TEST_F(FrameTest, CreateFrameWithWrongPanelTest)
{
    lsr::AreaType area;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.createWithoutVisibility(area, true, 2U);

    initDb(pageBuilder, panelBuilder);

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::Frame* frame = lsr::Frame::create(m_widgetPool,
                                           *m_pDb,
                                           1U,
                                           NULL,
                                           &m_context,
                                           error);
    EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());
    EXPECT_TRUE(NULL == frame);
}

TEST_F(FrameTest, VerifyTest)
{
    lsr::AreaType areaType;
    lsr::Area area(&areaType);

    lsr::Frame* frame = create(areaType, true, 2U);

    EXPECT_TRUE(NULL != frame);
    EXPECT_TRUE(frame->verify(m_canvas, area));
}

TEST_F(FrameTest, DrawTest)
{
    lsr::AreaType areaType;
    lsr::Area area(&areaType);

    lsr::Frame* frame = create(areaType, true, 2U);

    EXPECT_TRUE(NULL != frame);

    frame->update(0U);
    frame->draw(m_canvas, area);

    // All bitmaps should be drawn
    EXPECT_TRUE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
