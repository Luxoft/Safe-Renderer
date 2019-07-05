/******************************************************************************
**
**   File:        DisplayTest.cpp
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

#include <gtest/gtest.h>
#include "DisplayManager.h"
#include "WindowCanvas.h"
#include "Area.h"
#include "Color.h"
#include "StaticBitmap.h"
#include "Database.h"
#include "WindowDefinition.h"
#include <fstream>
#include <string>

using namespace lsr;

const char* ddhbin = ROOT_PATH "/test/database/Telltales/Output/Telltales.ddhbin";
const char* imgbin = ROOT_PATH "/test/database/Telltales/Output/Telltales.imgbin";

class DisplayManagerTest : public ::testing::Test
{
    void SetUp() P_OVERRIDE
    {
        std::ifstream ifs1(ddhbin, std::ios::binary);
        m_ddhbinData.assign ((std::istreambuf_iterator<char>(ifs1)), (std::istreambuf_iterator<char>()));
        ResourceBuffer ddhbin = ResourceBuffer(m_ddhbinData.c_str(), m_ddhbinData.size());
        std::ifstream ifs2(imgbin, std::ios::binary);
        m_imgbinData.assign ((std::istreambuf_iterator<char>(ifs2)), (std::istreambuf_iterator<char>()));
        ResourceBuffer imgbin = ResourceBuffer(m_imgbinData.c_str(), m_imgbinData.size());
        m_db = new Database(ddhbin, imgbin);
    }

    void TearDown() P_OVERRIDE
    {
        delete m_db;
        m_db = NULL;
    }

    std::string m_ddhbinData;
    std::string m_imgbinData;

protected:
    Database* m_db;
};

TEST_F(DisplayManagerTest, empty)
{
    testing::internal::CaptureStdout();
    // gilInit() is not called by the DisplayManager,
    // because it shall only be called once and there may be several DisplayManager instances
    gilInit(NULL);

    // create the DisplayManager
    DisplayManager dsp;

    // create a window
    WindowDefinition config = WindowDefinition();
    config.width = 400;
    config.height = 320;
    WindowCanvas canvas(dsp, config);

    // draw on the window
    canvas.makeCurrent();
    canvas.clear(Color(0xff, 0, 0, 0xff));
    canvas.drawBitmap(m_db->getBitmap(1), Area(10, 15, 42, 52));
    canvas.swapBuffers();

    EXPECT_TRUE(canvas.verify(m_db->getBitmap(1), Area(10, 15, 42, 52)));
    EXPECT_FALSE(canvas.handleWindowEvents());

    std::string output = testing::internal::GetCapturedStdout();
    std::cout << "###### Render dump begin ######" << std::endl;
    std::cout << output;
    std::cout << "####### Render dump end #######" << std::endl;
    // TODO : verify captured stdout
}

