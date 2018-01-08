/******************************************************************************
**
**   File:        FrameTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "WidgetTestBase.h"

#include <Frame.h>

#include <PSCErrorCollector.h>

#include <gtest/gtest.h>

class FrameTest: public WidgetTestBase
{
protected:
    FrameTest()
    {}

    psc::Frame* create(const psc::AreaType& area,
                       const bool isVisible,
                       const U16 fieldsCount)
    {
        framehandlertests::DdhPageBuilder pageBuilder;
        pageBuilder.create(1U, 1U);

        framehandlertests::DdhPanelBuilder panelBuilder;
        panelBuilder.create(area, isVisible, fieldsCount);

        initDb(pageBuilder, panelBuilder);

        psc::PSCErrorCollector error(PSC_NO_ERROR);
        psc::Frame* frame = psc::Frame::create(m_widgetPool,
                                               *m_pDb,
                                               1U,
                                               NULL,
                                               &m_context,
                                               error);
        EXPECT_EQ(PSC_NO_ERROR, error.get());

        return frame;
    }
};

TEST_F(FrameTest, CreateFrameTest)
{
    psc::AreaType area;
    psc::Frame* frame = create(area, true, 2U);

    EXPECT_TRUE(NULL != frame);
}

TEST_F(FrameTest, CreateFrameWithWrongPanelTest)
{
    psc::AreaType area;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.createWithoutVisibility(area, true, 2U);

    initDb(pageBuilder, panelBuilder);

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::Frame* frame = psc::Frame::create(m_widgetPool,
                                           *m_pDb,
                                           1U,
                                           NULL,
                                           &m_context,
                                           error);
    EXPECT_EQ(PSC_DB_INCONSISTENT, error.get());
    EXPECT_TRUE(NULL == frame);
}

TEST_F(FrameTest, VerifyTest)
{
    psc::AreaType areaType;
    psc::Area area(&areaType);

    psc::Frame* frame = create(areaType, true, 2U);

    EXPECT_TRUE(NULL != frame);
    EXPECT_TRUE(frame->verify(m_canvas, area));
}

TEST_F(FrameTest, DrawTest)
{
    psc::AreaType areaType;
    psc::Area area(&areaType);

    psc::Frame* frame = create(areaType, true, 2U);

    EXPECT_TRUE(NULL != frame);

    frame->update(0U);
    frame->draw(m_canvas, area);

    // All bitmaps should be drawn
    EXPECT_TRUE(psc::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
