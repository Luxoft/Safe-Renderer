/******************************************************************************
**
**   File:        FrameHandlerTest.cpp
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

#include "FrameHandlerCorrupter.h"

#include <WidgetTestBase.h>

#include <FrameHandler.h>

#include <DynamicDataType.h>

#include <gtest/gtest.h>
#include <PageType.h>
#include <PanelType.h>
#include <BaseFieldChoiceType.h>
#include <StaticBitmapFieldType.h>
#include <ReferenceBitmapFieldType.h>
#include <PageDatabaseType.h>
#include <PanelDatabaseType.h>
#include <HMIGlobalSettingsType.h>
#include <DDHType.h>
#include <Telltales.hpp>

using namespace lsr;

class FrameHandlerTest: public WidgetTestBase
{
protected:
    FrameHandlerTest()
    {}
};

TEST_F(FrameHandlerTest, CreateTest)
{
    lsr::Database db(Telltales::getDDH());
    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);
    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());
}

TEST_F(FrameHandlerTest, CreateTwiceTest)
{
    lsr::Database db(Telltales::getDDH());
    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);
    EXPECT_TRUE(fh.start());
    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());
}

TEST_F(FrameHandlerTest, GetErrorTest)
{
    lsr::Database db(Telltales::getDDH());
    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);
    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());
}

namespace testdb
{
    PanelId panelIds[] = { 1U };
    PageType page = { panelIds, 1, NULL, NULL };
    PageType* pages[] = { &page };
    PageDatabaseType pageDB = { pages, 1 };

    AreaType area = { 0U, 0U, 0U, 0U };
    DynamicDataType dataType = { 0U, DATATYPE_INTEGER };
    ExpressionTermType visible = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    ExpressionTermType bitmap1 = {ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType};
    StaticBitmapFieldType p1_bitmapField1 = { &area, &visible, &bitmap1 };
    StaticBitmapFieldType p1_bitmapField2 = { &area, &visible, &bitmap1 };
    BaseFieldChoiceType p1_field1 = { BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE, &p1_bitmapField1 };
    BaseFieldChoiceType p1_field2 = { BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE, &p1_bitmapField2 };
    const BaseFieldChoiceType* p1_fields[] = {&p1_field1, &p1_field2};
    PanelType p1 = {&area, &visible, p1_fields, 2};
    PanelType* panels1[] = { &p1 };
    PanelDatabaseType panelDB1 = {panels1, 1};

    ExpressionTermType bitmap2 = { ExpressionTermType::BITMAPID_CHOICE, 1U, NULL };
    ReferenceBitmapFieldType p2_refBitmapField1 = { 1, &area, &visible, &bitmap2 };
    ReferenceBitmapFieldType p2_refBitmapField2 = { 1, &area, &visible, &bitmap2 };
    BaseFieldChoiceType p2_field1 = { BaseFieldChoiceType::REFERENCEBITMAPFIELD_CHOICE, &p2_refBitmapField1 };
    BaseFieldChoiceType p2_field2 = { BaseFieldChoiceType::REFERENCEBITMAPFIELD_CHOICE, &p2_refBitmapField2 };
    const BaseFieldChoiceType* p2_fields[] = {&p2_field1, &p2_field2};
    PanelType p2 = {&area, &visible, p2_fields, 2};
    PanelType* panels2[] = { &p2 };
    PanelDatabaseType panelDB2 = {panels2, 1};

    DisplaySizeType displaySize = { 0U, 0U };
    HMIGlobalSettingsType globalSettings = { &displaySize, NULL };
}

TEST_F(FrameHandlerTest, GetErrorWithErrorInWidgetTest)
{
    const DDHType ddh = {
        0U,
        DDHType::SCHEMA_CHECKSUM,
        DDHType::SCHEMA_VERSION,
        DDHType::SERIALIZER_VERSION,
        &testdb::pageDB,
        &testdb::panelDB1,
        &testdb::globalSettings,
        NULL,
        NULL,
        NULL,
        0U
    };

    lsr::Number num(5U, lsr::DATATYPE_INTEGER);
    m_dataHandler.setOutDatedNumber(num);

    lsr::Database db(&ddh);

    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);
    EXPECT_TRUE(fh.start());

    fh.update(0U);

    EXPECT_EQ(LSR_ERR_DATASTATUS_NOT_AVAILABLE, fh.getError());
}


TEST_F(FrameHandlerTest, GetErrorWithErrorInWidgetSetupTest)
{
    EXPECT_EQ(2U, MAX_PANELS_COUNT); // assumption for the test
    const U32 panelCount = MAX_PANELS_COUNT + 1U;
    // Create too many panels for the page

    PanelId panelIds[] = { 1U, 2U, 3U };
    PageType page = { panelIds, panelCount, NULL, NULL };
    PageType* pages[] = { &page };
    PageDatabaseType pageDB = { pages, 1 };

    PanelType* panels[] = { &testdb::p1, &testdb::p1, &testdb::p1 };
    PanelDatabaseType panelDB = {panels, panelCount};

    const DDHType ddh = {
        0U,
        DDHType::SCHEMA_CHECKSUM,
        DDHType::SCHEMA_VERSION,
        DDHType::SERIALIZER_VERSION,
        &pageDB,
        &panelDB,
        &testdb::globalSettings,
        NULL,
        NULL,
        NULL,
        0U
    };

    lsr::Database db(&ddh);
    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);
    EXPECT_FALSE(fh.start());

    EXPECT_EQ(LSR_POOL_IS_FULL, fh.getError());
}

TEST_F(FrameHandlerTest, GetErrorWithErrorInWidgetPoolTest)
{
    lsr::Database db(Telltales::getDDH());
    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);
    EXPECT_TRUE(fh.start());

    FrameHandlerCorrupter corrupter(fh);
    corrupter.corruptStorage();

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, fh.getError());
}

TEST_F(FrameHandlerTest, VerifyTest)
{
    const DDHType ddh = {
        0U,
        DDHType::SCHEMA_CHECKSUM,
        DDHType::SCHEMA_VERSION,
        DDHType::SERIALIZER_VERSION,
        &testdb::pageDB,
        &testdb::panelDB2,
        &testdb::globalSettings,
        NULL,
        NULL,
        NULL,
        0U
    };

    lsr::Database db(&ddh);
    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());

    fh.update(0U);
    EXPECT_TRUE(fh.verify());

    lsr::DisplayAccessor::instance().setVerifyFlag(false);
    EXPECT_FALSE(fh.verify());
}

TEST_F(FrameHandlerTest, DrawTest)
{
    lsr::Database db(Telltales::getDDH());

    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());

    fh.update(0U);
    EXPECT_TRUE(fh.render());

    // All bitmaps should be drawn
    EXPECT_TRUE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

TEST_F(FrameHandlerTest, RenderWithNotInvalidatedStateTest)
{
    lsr::Database db(Telltales::getDDH());

    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());

    fh.update(0U);
    EXPECT_TRUE(fh.render());

    lsr::DisplayAccessor::instance().toDefault();

    // now we are in validated state
    EXPECT_FALSE(fh.render());

    EXPECT_FALSE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

// test to fulfill coverage
TEST_F(FrameHandlerTest, HandleWindowEventsTest)
{
    lsr::Database db(Telltales::getDDH());

    lsr::FrameHandler fh(db, m_dataHandler, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());

    fh.handleWindowEvents();

    EXPECT_FALSE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}

