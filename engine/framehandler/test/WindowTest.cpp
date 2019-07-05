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

#include <gtest/gtest.h>

class WindowTest: public WidgetTestBase
{
protected:
    WindowTest()
    {}

    lsr::Window* createWindow()
    {
        lsr::WindowDefinition winDef;

        lsr::LSRErrorCollector error(LSR_NO_ERROR);
        lsr::Window* window = lsr::Window::create(m_widgetPool,
                                                  *m_pDb,
                                                  m_dsp,
                                                  winDef,
                                                  &m_context,
                                                  error);
        EXPECT_EQ(LSR_NO_ERROR, error.get());

        return window;
    }
};

TEST_F(WindowTest, CreateWindowTest)
{
    initNormalDb();

    lsr::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);
}

TEST_F(WindowTest, CreateWindowWithWrongPanelsTest)
{
    lsr::AreaType area;
    lsr::DisplaySizeType displaySize;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.createWithoutVisibility(area, true, 2U);

    initDb(pageBuilder, panelBuilder, displaySize);

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::WindowDefinition winDef;
    lsr::Window* window = lsr::Window::create(m_widgetPool,
                                              *m_pDb,
                                              m_dsp,
                                              winDef,
                                              &m_context,
                                              error);

    EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());


    EXPECT_TRUE(NULL == window);
}

TEST_F(WindowTest, VerifyTest)
{
    lsr::AreaType areaType;

    lsr::DisplaySizeType displaySize;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.createWithRefBitmaps(areaType, true, 2U);

    initDb(pageBuilder, panelBuilder, displaySize);

    lsr::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    window->update(0U);
    EXPECT_TRUE(window->verify());

    lsr::DisplayAccessor::instance().setVerifyFlag(false);
    EXPECT_FALSE(window->verify());
}

TEST_F(WindowTest, DrawTest)
{
    initNormalDb();

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
    initNormalDb();

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
    initNormalDb();

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
    initNormalDb();

    lsr::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    window->handleWindowEvents();

    EXPECT_FALSE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
