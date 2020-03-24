/******************************************************************************
**
**   File:        EngineAppTest.cpp
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include "Database.h"
#include "ResourceBuffer.h"
#include "gil.h"
#include "FrameHandler.h"
#include "DisplayManager.h"
#include "TelltalesEngineTest.h"
#include <Telltales.hpp>
#include <TelltalesHMI.hpp>
#include "Engine.h"
#include "MockGIL.h"

using namespace lsr;
using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;

namespace unittest
{

class EngineTest : public ::testing::Test
{
public:
    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    void SetUp() P_OVERRIDE
    {
        gilMock = &gil;
    }

    void TearDown() P_OVERRIDE
    {
    }

    void setBitmapId(ReferenceBitmapField& field, BitmapId id)
    {
        field.m_bitmapId = id;
    }

    void setBitmapId(BitmapField& field, BitmapId id)
    {
        field.m_bitmapId = id;
    }

    MockGIL gil;
    ::testing::NiceMock<MockGIL> niceMock;
    gil_context_t ctx;
    gil_texture_t tex;
    gil_surface_t wnd;
};

class EmptyHMI : public lsr::IHMI
{
public:
    virtual Frame* getFrame() P_OVERRIDE
    {
        return NULL;
    }
};



TEST_F(EngineTest, emptyDatabase)
{
    EXPECT_CALL(gil, gilCreateContext()).WillOnce(Return(&ctx));
    Telltales::HMI hmi;
    lsr::Engine engine(NULL, hmi);
    EXPECT_EQ(LSR_DB_DDHBIN_EMPTY, engine.getError().getValue());
}

TEST_F(EngineTest, tooManyTextures)
{
    EXPECT_CALL(gil, gilCreateContext()).WillOnce(Return(&ctx));
    Telltales::HMI hmi;
    const DDHType* pDDH = TelltalesTestTooManyTextures::getDDH();
    lsr::Engine engine(pDDH, hmi);
    EXPECT_EQ(LSR_DB_INCONSISTENT, engine.getError().getValue());
}

TEST_F(EngineTest, missingFrame)
{
    EXPECT_CALL(gil, gilCreateContext()).WillOnce(Return(&ctx));
    EmptyHMI hmi;
    lsr::Engine engine(Telltales::getDDH(), hmi);
    EXPECT_EQ(LSR_DB_ERROR, engine.getError().getValue());
}

// textures are created at startup
TEST_F(EngineTest, setup)
{
    InSequence seq;
    EXPECT_CALL(gil, gilCreateContext()).WillOnce(Return(&ctx));
    EXPECT_CALL(gil, gilCreateWindow(0, 0, 0, 400, 240)).WillOnce(Return(&wnd));

    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&tex));
    EXPECT_CALL(gil, gilTexPixels(&tex, 102, 68, GIL_FORMAT_BGRA_8888, _)).WillOnce(Return(GIL_TRUE));

    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&tex));
    EXPECT_CALL(gil, gilTexPixels(&tex, 102, 68, GIL_FORMAT_P_2_BGRA_8888, _)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilTexPalette4(&tex, _, 4)).WillOnce(Return(GIL_TRUE));

    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&tex));
    EXPECT_CALL(gil, gilTexPixels(&tex, 100, 69, GIL_FORMAT_BGRA_8888, _)).WillOnce(Return(GIL_TRUE));

    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&tex));
    EXPECT_CALL(gil, gilTexPixels(&tex, 100, 69, GIL_FORMAT_P_2_BGRA_8888, _)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilTexPalette4(&tex, _, 8)).WillOnce(Return(GIL_TRUE));

    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillOnce(Return(&tex));
    EXPECT_CALL(gil, gilTexPixels(&tex, 6, 2, GIL_FORMAT_P_2_BGRA_8888, _)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilTexPalette4(&tex, _, 4)).WillOnce(Return(GIL_TRUE));

    Telltales::HMI hmi;
    lsr::Engine engine(Telltales::getDDH(), hmi);

    EXPECT_CALL(gil, gilGetError(&ctx)).WillOnce(Return(0U));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, engine.getError().getValue());
}

TEST_F(EngineTest, normalRun)
{
    EXPECT_CALL(gil, gilCreateContext()).WillOnce(Return(&ctx));
    EXPECT_CALL(gil, gilCreateWindow(0, 0, 0, 400, 240)).WillOnce(Return(&wnd));
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillRepeatedly(Return(&tex));
    EXPECT_CALL(gil, gilTexPixels(&tex, _, _, _, _)).WillRepeatedly(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilTexPalette4(&tex, _, _)).WillRepeatedly(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilGetError(&ctx)).WillOnce(Return(0U));
    Telltales::HMI hmi;
    lsr::Engine engine(Telltales::getDDH(), hmi);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, engine.getError().getValue());

    InSequence seq;

    hmi.getContentPanel_Break().setVisible(true);
    hmi.getReferencePanel_Airbag().setVisible(true);
    hmi.getReferencePanel_Break().setVisible(true);
    EXPECT_CALL(gil, gilSetSurface(&ctx, &wnd)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilSetColor(&ctx, 0, 0, 0, 0)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilClear(&ctx));
    EXPECT_CALL(gil, gilBindTexture(&ctx, &tex));
    EXPECT_CALL(gil, gilDrawQuad(&ctx, _, _, _, _, _, _, _, _));
    EXPECT_CALL(gil, gilSwapBuffers(&wnd));
    EXPECT_TRUE(engine.render());

    EXPECT_CALL(gil, gilGetError(&ctx)).WillOnce(Return(0U));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, engine.getError().getValue());

    EXPECT_CALL(gil, gilSetSurface(&ctx, &wnd)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilBindTexture(&ctx, &tex));
    EXPECT_CALL(gil, gilVerify(&ctx, _, _, _, _, _, _, _, _)).WillOnce(Return(GIL_FALSE));
    EXPECT_CALL(gil, gilBindTexture(&ctx, &tex));
    EXPECT_CALL(gil, gilVerify(&ctx, _, _, _, _, _, _, _, _)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilSync(&ctx));
    EXPECT_FALSE(engine.verify());

    EXPECT_CALL(gil, gilGetError(&ctx)).WillOnce(Return(0U));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, engine.getError().getValue());

    EXPECT_CALL(gil, gilHandleWindowEvents(&ctx));
    EXPECT_FALSE(engine.handleWindowEvents());

    EXPECT_CALL(gil, gilGetError(&ctx)).WillOnce(Return(0U));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, engine.getError().getValue());

    hmi.getContentPanel_Airbag().setVisible(false);
    hmi.getContentPanel_Break().setVisible(false);
    hmi.getReferencePanel_Airbag().setVisible(false);
    hmi.getReferencePanel_Break().setVisible(false);

    EXPECT_CALL(gil, gilSetSurface(&ctx, &wnd)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilSetColor(&ctx, 0, 0, 0, 0)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilClear(&ctx));
    EXPECT_CALL(gil, gilSwapBuffers(&wnd));
    EXPECT_TRUE(engine.render());

    EXPECT_CALL(gil, gilGetError(&ctx)).WillOnce(Return(0U));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, engine.getError().getValue());

    EXPECT_CALL(gil, gilSetSurface(&ctx, &wnd)).WillOnce(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilSync(&ctx));
    EXPECT_TRUE(engine.verify());

    EXPECT_CALL(gil, gilGetError(&ctx)).WillOnce(Return(0U));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, engine.getError().getValue());

    EXPECT_CALL(gil, gilHandleWindowEvents(&ctx));
    EXPECT_FALSE(engine.handleWindowEvents());

    EXPECT_CALL(gil, gilGetError(&ctx)).WillOnce(Return(178U));
    EXPECT_EQ(178U, engine.getError().getValue());
}

TEST_F(EngineTest, verificationErrorCount)
{
    EXPECT_CALL(gil, gilCreateContext()).WillOnce(Return(&ctx));
    EXPECT_CALL(gil, gilCreateWindow(0, 0, 0, 400, 240)).WillOnce(Return(&wnd));
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillRepeatedly(Return(&tex));
    lsr::Database db(Telltales::getDDH());
    Telltales::HMI hmi;
    lsr::DisplayManager dsp;
    lsr::FrameHandler frameHandler(hmi, db, dsp);
    EXPECT_TRUE(frameHandler.start());
    hmi.getReferencePanel_Airbag().setVisible(true);
    hmi.getReferencePanel_Break().setVisible(true);
    EXPECT_EQ(0U, hmi.getReferencePanel_Airbag().getVerificationErrors());
    EXPECT_EQ(0U, hmi.getReferencePanel_Break().getVerificationErrors());
    // both images are expected to fail, because there was no rendering before
    EXPECT_FALSE(frameHandler.verify());
    // error count is incremented for both bitmaps
    EXPECT_EQ(1U, hmi.getReferencePanel_Airbag().getVerificationErrors());
    EXPECT_EQ(1U, hmi.getReferencePanel_Break().getVerificationErrors());
}

TEST_F(EngineTest, dbRenderInvalidBitmapId)
{
    EXPECT_CALL(gil, gilCreateContext()).WillOnce(Return(&ctx));
    EXPECT_CALL(gil, gilCreateWindow(0, 0, 0, 400, 240)).WillOnce(Return(&wnd));
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillRepeatedly(Return(&tex));
    EXPECT_CALL(gil, gilTexPixels(&tex, _, _, _, _)).WillRepeatedly(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilTexPalette4(&tex, _, _)).WillRepeatedly(Return(GIL_TRUE));

    Telltales::HMI hmi;
    lsr::Engine engine(Telltales::getDDH(), hmi);
    hmi.getContentPanel_Break().setVisible(true);
    setBitmapId(hmi.getContentPanel_Break(), 0U);

    // rendering was performed, but an error occurred
    EXPECT_TRUE(engine.render());
    EXPECT_EQ(LSR_ERROR_NO_TEXTURE, engine.getError().getValue());
}

TEST_F(EngineTest, dbVerifyInvalidBitmapId)
{
    EXPECT_CALL(gil, gilCreateContext()).WillOnce(Return(&ctx));
    EXPECT_CALL(gil, gilCreateWindow(0, 0, 0, 400, 240)).WillOnce(Return(&wnd));
    EXPECT_CALL(gil, gilCreateTexture(&ctx)).WillRepeatedly(Return(&tex));
    EXPECT_CALL(gil, gilTexPixels(&tex, _, _, _, _)).WillRepeatedly(Return(GIL_TRUE));
    EXPECT_CALL(gil, gilTexPalette4(&tex, _, _)).WillRepeatedly(Return(GIL_TRUE));

    lsr::Database db(Telltales::getDDH());
    Telltales::HMI hmi;
    lsr::DisplayManager dsp;
    lsr::FrameHandler frameHandler(hmi, db, dsp);
    EXPECT_TRUE(frameHandler.start());

    hmi.getReferencePanel_Airbag().setVisible(true);
    hmi.getReferencePanel_Break().setVisible(true);
    setBitmapId(hmi.getReferencePanel_Airbag(), 42);

    EXPECT_EQ(LSR_NO_ENGINE_ERROR, frameHandler.getError());
    // skip render step to isolate the error, that happend in verification step
    EXPECT_FALSE(frameHandler.verify());
    EXPECT_EQ(LSR_ERROR_NO_TEXTURE, frameHandler.getError());
}

} // unittest
