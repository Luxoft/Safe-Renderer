/******************************************************************************
**
**   File:        PanelTest.cpp
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

#include <Panel.h>

#include <LSRErrorCollector.h>

#include <gtest/gtest.h>

class PanelTest: public WidgetTestBase
{
protected:
    PanelTest()
    {}

    lsr::Panel* createPanel(framehandlertests::DdhPanelBuilder& builder)
    {
        lsr::LSRErrorCollector error(LSR_NO_ERROR);
        lsr::Panel* panel = lsr::Panel::create(m_widgetPool,
                                               *m_pDb,
                                               builder.getDdh(),
                                               &m_context,
                                               error);

        EXPECT_EQ(LSR_NO_ERROR, error.get());

        return panel;
    }

    lsr::Panel* createWrongPanel(framehandlertests::DdhPanelBuilder& builder)
    {
        lsr::LSRErrorCollector error(LSR_NO_ERROR);
        lsr::Panel* panel = lsr::Panel::create(m_widgetPool,
                                               *m_pDb,
                                               builder.getDdh(),
                                               &m_context,
                                               error);

        EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());

        return panel;
    }

    framehandlertests::DdhPanelBuilder m_builder;
};

TEST_F(PanelTest, CreatePanelTest)
{
    lsr::AreaType area;
    m_builder.create(area, true, 2U);

    lsr::Panel* panel = createPanel(m_builder);

    EXPECT_TRUE(NULL != panel);
}

TEST_F(PanelTest, CreatePanelWithoutAreaTest)
{
    lsr::AreaType area;
    m_builder.createWithoutArea(area, true, 2U);

    lsr::Panel* panel = createWrongPanel(m_builder);

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithoutVisibilityTest)
{
    lsr::AreaType area;
    m_builder.createWithoutVisibility(area, true, 2U);

    lsr::Panel* panel = createWrongPanel(m_builder);

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithoutFieldsTest)
{
    lsr::AreaType area;
    m_builder.createWithoutFields(area, true);

    lsr::Panel* panel = createPanel(m_builder);

    EXPECT_TRUE(NULL != panel);
}

TEST_F(PanelTest, CreatePanelWithFieldWithWrongTypeTest)
{
    lsr::AreaType area;
    m_builder.createWithFieldWithWrongType(area, true, 2U);

    lsr::Panel* panel = createWrongPanel(m_builder);

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithWrongFieldTest)
{
    lsr::AreaType area;
    m_builder.createWithWrongField(area, true, 2U);

    lsr::Panel* panel = createWrongPanel(m_builder);

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithTooManyFieldsTest)
{
    /**
     * To make this test successful, statement should be true
     * MAX_BITMAPS_COUNT > MAX_WIDGET_CHILDREN_COUNT
     */
    lsr::AreaType area;
    m_builder.createWithTooManyFields(area, true);

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::Panel* panel = lsr::Panel::create(m_widgetPool,
                                           *m_pDb,
                                           m_builder.getDdh(),
                                           &m_context,
                                           error);

    EXPECT_EQ(LSR_POOL_IS_FULL, error.get());

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, VerifyTest)
{
    lsr::AreaType areaType;
    lsr::Area area(&areaType);
    m_builder.create(areaType, true, 2U);

    lsr::Panel* panel = createPanel(m_builder);

    EXPECT_TRUE(NULL != panel);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    EXPECT_TRUE(panel->verify(canvas, area));
}
