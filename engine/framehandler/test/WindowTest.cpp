/******************************************************************************
**
**   File:        WindowTest.cpp
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

#include <Window.h>
#include <WindowDefinition.h>

#include <PSCErrorCollector.h>

#include <gtest/gtest.h>

class WindowTest: public WidgetTestBase
{
protected:
    WindowTest()
    {}

    psc::Window* createWindow()
    {
        psc::WindowDefinition winDef;

        psc::PSCErrorCollector error(PSC_NO_ERROR);
        psc::Window* window = psc::Window::create(m_widgetPool,
                                                  *m_pDb,
                                                  m_dsp,
                                                  winDef,
                                                  &m_context,
                                                  error);
        EXPECT_EQ(PSC_NO_ERROR, error.get());

        return window;
    }
};

TEST_F(WindowTest, CreateWindowTest)
{
    initNormalDb();

    psc::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);
}

TEST_F(WindowTest, CreateWindowWithWrongPanelsTest)
{
    psc::AreaType area;
    psc::DisplaySizeType displaySize;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.createWithoutVisibility(area, true, 2U);

    initDb(pageBuilder, panelBuilder, displaySize);

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::WindowDefinition winDef;
    psc::Window* window = psc::Window::create(m_widgetPool,
                                              *m_pDb,
                                              m_dsp,
                                              winDef,
                                              &m_context,
                                              error);

    EXPECT_EQ(PSC_DB_INCONSISTENT, error.get());


    EXPECT_TRUE(NULL == window);
}

TEST_F(WindowTest, VerifyTest)
{
    psc::AreaType areaType;

    psc::DisplaySizeType displaySize;
    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.createWithRefBitmaps(areaType, true, 2U);

    initDb(pageBuilder, panelBuilder, displaySize);

    psc::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    window->update(0U);
    EXPECT_TRUE(window->verify());

    psc::DisplayAccessor::instance().setVerifyFlag(false);
    EXPECT_FALSE(window->verify());
}

TEST_F(WindowTest, DrawTest)
{
    initNormalDb();

    psc::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    psc::Area area;

    window->update(0U);
    window->draw(m_canvas, area);

    // All bitmaps should be drawn
    EXPECT_TRUE(psc::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

TEST_F(WindowTest, RenderTest)
{
    initNormalDb();

    psc::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    psc::Area area;

    window->update(0U);
    EXPECT_TRUE(window->render());

    // All bitmaps should be drawn
    EXPECT_TRUE(psc::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

TEST_F(WindowTest, RenderWithNotInvalidatedStateTest)
{
    initNormalDb();

    psc::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    psc::Area area;

    window->update(0U);
    EXPECT_TRUE(window->render());

    psc::DisplayAccessor::instance().toDefault();

    // now we are in validated state
    EXPECT_FALSE(window->render());

    EXPECT_FALSE(psc::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

// test to fulfill coverage
TEST_F(WindowTest, HandleWindowEventsTest)
{
    initNormalDb();

    psc::Window* window = createWindow();

    EXPECT_TRUE(NULL != window);

    window->handleWindowEvents();

    EXPECT_FALSE(psc::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
