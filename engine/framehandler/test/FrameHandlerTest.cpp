/******************************************************************************
**
**   File:        FrameHandlerTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include <WidgetTestBase.h>

#include <FrameHandler.h>

#include <gtest/gtest.h>
#include <PanelType.h>
#include <BaseFieldChoiceType.h>
#include <StaticBitmapFieldType.h>
#include <ReferenceBitmapFieldType.h>
#include <PanelDatabaseType.h>
#include <HMIGlobalSettingsType.h>
#include <DDHType.h>
#include <Telltales.hpp>
#include <TelltalesHMI.hpp>

using namespace lsr;
using testing::_;
using testing::Return;

class FrameHandlerTest: public WidgetTestBase
{
protected:
    FrameHandlerTest()
    {}
};

TEST_F(FrameHandlerTest, CreateTest)
{
    lsr::Database db(Telltales::getDDH());
    Telltales::HMI hmi;
    lsr::FrameHandler fh(hmi, db, m_dsp);
    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());
}

TEST_F(FrameHandlerTest, CreateTwiceTest)
{
    lsr::Database db(Telltales::getDDH());
    Telltales::HMI hmi;
    lsr::FrameHandler fh(hmi, db, m_dsp);
    EXPECT_TRUE(fh.start());
    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());
}

TEST_F(FrameHandlerTest, GetErrorTest)
{
    lsr::Database db(Telltales::getDDH());
    Telltales::HMI hmi;
    lsr::FrameHandler fh(hmi, db, m_dsp);
    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());
}

namespace testdb
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    ExpressionTermType bitmap1 = {ExpressionTermType::BITMAPID_CHOICE, 2U, NULL};
    StaticBitmapFieldType p1_bitmapField1 = { &area, &visible, &bitmap1 };
    StaticBitmapFieldType p1_bitmapField2 = { &area, &visible, &bitmap1 };
    BaseFieldChoiceType p1_field1 = { BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE, &p1_bitmapField1 };
    BaseFieldChoiceType p1_field2 = { BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE, &p1_bitmapField2 };
    const BaseFieldChoiceType* p1_fields[] = {&p1_field1, &p1_field2};
    PanelType p1 = {&area, &visible, p1_fields, 2};

    ExpressionTermType bitmap2 = { ExpressionTermType::BITMAPID_CHOICE, 1U, NULL };
    ReferenceBitmapFieldType p2_refBitmapField1 = { &area, &visible, &bitmap2 };
    ReferenceBitmapFieldType p2_refBitmapField2 = { &area, &visible, &bitmap2 };
    BaseFieldChoiceType p2_field1 = { BaseFieldChoiceType::REFERENCEBITMAPFIELD_CHOICE, &p2_refBitmapField1 };
    BaseFieldChoiceType p2_field2 = { BaseFieldChoiceType::REFERENCEBITMAPFIELD_CHOICE, &p2_refBitmapField2 };
    const BaseFieldChoiceType* p2_fields[] = {&p2_field1, &p2_field2};
    PanelType p2 = {&area, &visible, p2_fields, 2};
    PanelType* panels2[] = { &p2 };
    PanelDatabaseType panelDB2 = {panels2, 1};

    DisplaySizeType displaySize = { 0U, 0U };
    HMIGlobalSettingsType globalSettings = { &displaySize };

    class HMI : public IHMI
    {
    public:
        HMI()
            :m_frame()
            , m_panel(&p2)
            , m_field1(&p2_refBitmapField1)
            , m_field2(&p2_refBitmapField2)
        {
            m_frame.addChild(m_panel);
            m_panel.addChild(m_field1);
            m_panel.addChild(m_field2);
        };

        virtual Frame* getFrame() P_OVERRIDE
        {
            return &m_frame;
        }

        Frame m_frame;
        Panel m_panel;
        ReferenceBitmapField m_field1;
        ReferenceBitmapField m_field2;
    };
}

TEST_F(FrameHandlerTest, VerifyTest)
{
    const DDHType ddh = {
        0U,
        DDHType::SCHEMA_CHECKSUM,
        DDHType::SCHEMA_VERSION,
        DDHType::SERIALIZER_VERSION,
        &testdb::panelDB2,
        NULL,
        &testdb::globalSettings,
    };

    lsr::Database db(&ddh);
    testdb::HMI hmi;
    lsr::FrameHandler fh(hmi, db, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());

    EXPECT_CALL(m_mockCanvas, verify(_, _)).Times(2).WillRepeatedly(Return(true));
    EXPECT_TRUE(fh.verify());

    EXPECT_CALL(m_mockCanvas, verify(_, _)).Times(2).WillRepeatedly(Return(false));
    EXPECT_FALSE(fh.verify());
}

TEST_F(FrameHandlerTest, DrawTest)
{
    lsr::Database db(Telltales::getDDH());
    Telltales::HMI hmi;
    lsr::FrameHandler fh(hmi, db, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());

    hmi.getContentPanel_Break().setVisible(true);

    // All bitmaps should be drawn
    EXPECT_CALL(m_mockCanvas, drawBitmap(_, _));
    EXPECT_TRUE(fh.render());
}

TEST_F(FrameHandlerTest, RenderWithNotInvalidatedStateTest)
{
    lsr::Database db(Telltales::getDDH());
    Telltales::HMI hmi;
    lsr::FrameHandler fh(hmi, db, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());

    hmi.getContentPanel_Break().setVisible(true);
    EXPECT_CALL(m_mockCanvas, drawBitmap(_, _)).Times(1);
    EXPECT_TRUE(fh.render());

    // now we are in validated state
    EXPECT_FALSE(fh.render());
}

// test to fulfill coverage
TEST_F(FrameHandlerTest, HandleWindowEventsTest)
{
    lsr::Database db(Telltales::getDDH());
    Telltales::HMI hmi;
    lsr::FrameHandler fh(hmi, db, m_dsp);

    EXPECT_TRUE(fh.start());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, fh.getError());

    fh.handleWindowEvents();
}

