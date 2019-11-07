/******************************************************************************
**
**   File:        WindowTest.cpp
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

#include <Window.h>
#include <WindowDefinition.h>

#include <LSRErrorCollector.h>
#include <Telltales.hpp>

#include <gtest/gtest.h>

using namespace lsr;

class WindowTest: public WidgetTestBase
{
protected:
    WindowTest()
        : m_db(Telltales::getDDH())
    {}

    lsr::Window* createWindow()
    {
        lsr::WindowDefinition winDef;

        lsr::LSRErrorCollector error(LSR_NO_ERROR);
        lsr::Window* window = lsr::Window::create(m_widgetPool,
                                                  m_db,
                                                  m_dsp,
                                                  winDef,
                                                  &m_context,
                                                  error);
        EXPECT_EQ(LSR_NO_ERROR, error.get());

        return window;
    }

    lsr::Database m_db;
};

TEST_F(WindowTest, CreateWindowTest)
{
    lsr::Window* window = createWindow();
    EXPECT_TRUE(NULL != window);
}

TEST_F(WindowTest, CreateWindowWithWrongPanelsTest)
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

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::WindowDefinition winDef;
    lsr::Window* window = lsr::Window::create(m_widgetPool,
                                              db,
                                              m_dsp,
                                              winDef,
                                              &m_context,
                                              error);

    EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());


    EXPECT_TRUE(NULL == window);
}

TEST_F(WindowTest, VerifyTest)
{
    lsr::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    window->update(0U);
    EXPECT_TRUE(window->verify());

    lsr::DisplayAccessor::instance().setVerifyFlag(false);
    EXPECT_FALSE(window->verify());
}

TEST_F(WindowTest, DrawTest)
{
    lsr::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    lsr::Area area;

    window->update(0U);
    window->draw(m_canvas, area);

    // All bitmaps should be drawn
    EXPECT_TRUE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

TEST_F(WindowTest, RenderTest)
{
    lsr::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    lsr::Area area;

    window->update(0U);
    EXPECT_TRUE(window->render());

    // All bitmaps should be drawn
    EXPECT_TRUE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

TEST_F(WindowTest, RenderWithNotInvalidatedStateTest)
{
    lsr::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    lsr::Area area;

    window->update(0U);
    EXPECT_TRUE(window->render());

    lsr::DisplayAccessor::instance().toDefault();

    // now we are in validated state
    EXPECT_FALSE(window->render());

    EXPECT_FALSE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

// test to fulfill coverage
TEST_F(WindowTest, HandleWindowEventsTest)
{
    lsr::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    window->handleWindowEvents();

    EXPECT_FALSE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
