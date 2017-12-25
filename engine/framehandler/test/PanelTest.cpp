/******************************************************************************
**
**   File:        PanelTest.cpp
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

#include "WidgetTestBase.h"

#include <Panel.h>

#include <PSCErrorCollector.h>

#include <gtest/gtest.h>

class PanelTest: public WidgetTestBase
{
protected:
    PanelTest()
    {}

    psc::Panel* createPanel(framehandlertests::DdhPanelBuilder& builder)
    {
        psc::PSCErrorCollector error(PSC_NO_ERROR);
        psc::Panel* panel = psc::Panel::create(m_widgetPool,
                                               *m_pDb,
                                               builder.getDdh(),
                                               &m_context,
                                               error);

        EXPECT_EQ(PSC_NO_ERROR, error.get());

        return panel;
    }

    psc::Panel* createWrongPanel(framehandlertests::DdhPanelBuilder& builder)
    {
        psc::PSCErrorCollector error(PSC_NO_ERROR);
        psc::Panel* panel = psc::Panel::create(m_widgetPool,
                                               *m_pDb,
                                               builder.getDdh(),
                                               &m_context,
                                               error);

        EXPECT_EQ(PSC_DB_INCONSISTENT, error.get());

        return panel;
    }

    framehandlertests::DdhPanelBuilder m_builder;
};

TEST_F(PanelTest, CreatePanelTest)
{
    psc::AreaType area;
    m_builder.create(area, true, 2U);

    psc::Panel* panel = createPanel(m_builder);

    EXPECT_TRUE(NULL != panel);
}

TEST_F(PanelTest, CreatePanelWithoutAreaTest)
{
    psc::AreaType area;
    m_builder.createWithoutArea(area, true, 2U);

    psc::Panel* panel = createWrongPanel(m_builder);

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithoutVisibilityTest)
{
    psc::AreaType area;
    m_builder.createWithoutVisibility(area, true, 2U);

    psc::Panel* panel = createWrongPanel(m_builder);

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithoutFieldsTest)
{
    psc::AreaType area;
    m_builder.createWithoutFields(area, true);

    psc::Panel* panel = createPanel(m_builder);

    EXPECT_TRUE(NULL != panel);
}

TEST_F(PanelTest, CreatePanelWithFieldWithWrongTypeTest)
{
    psc::AreaType area;
    m_builder.createWithFieldWithWrongType(area, true, 2U);

    psc::Panel* panel = createWrongPanel(m_builder);

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithWrongFieldTest)
{
    psc::AreaType area;
    m_builder.createWithWrongField(area, true, 2U);

    psc::Panel* panel = createWrongPanel(m_builder);

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithTooManyFieldsTest)
{
    /**
     * To make this test successful, statement should be true
     * MAX_BITMAPS_COUNT > MAX_WIDGET_CHILDREN_COUNT
     */
    psc::AreaType area;
    m_builder.createWithTooManyFields(area, true);

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::Panel* panel = psc::Panel::create(m_widgetPool,
                                           *m_pDb,
                                           m_builder.getDdh(),
                                           &m_context,
                                           error);

    EXPECT_EQ(PSC_POOL_IS_FULL, error.get());

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, VerifyTest)
{
    psc::AreaType areaType;
    psc::Area area(&areaType);
    m_builder.create(areaType, true, 2U);

    psc::Panel* panel = createPanel(m_builder);

    EXPECT_TRUE(NULL != panel);

    psc::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    EXPECT_TRUE(panel->verify(canvas, area));
}
