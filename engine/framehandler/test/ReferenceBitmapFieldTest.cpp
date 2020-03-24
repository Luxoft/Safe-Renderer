/******************************************************************************
**
**   File:        ReferenceBitmapFieldTest.cpp
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

#include "WidgetTestBase.h"

#include <ReferenceBitmapField.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Telltales.hpp>

using ::testing::Return;
using ::testing::_;

using namespace lsr;

namespace unittest
{

class ReferenceBitmapFieldTest: public WidgetTestBase
{
protected:
    ReferenceBitmapFieldTest()
        : m_db(Telltales::getDDH())
    {
    }

    void setVerificationErrors(ReferenceBitmapField& field, U32 value)
    {
        field.m_verificationErrors = value;
    }

    Database m_db;
};

TEST_F(ReferenceBitmapFieldTest, CreateBitmapFieldTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const ReferenceBitmapFieldType fieldType = { &area, &visible, &bmp };

    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest1)
{
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const ReferenceBitmapFieldType fieldType = { NULL, &visible, &bmp };

    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_DB_INCONSISTENT, field.setup(m_db));
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest2)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const ReferenceBitmapFieldType fieldType = { &area, NULL, &bmp };

    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_DB_INCONSISTENT, field.setup(m_db));
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest3)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ReferenceBitmapFieldType fieldType = { &area, &visible, NULL};

    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_DB_INCONSISTENT, field.setup(m_db));
}

TEST_F(ReferenceBitmapFieldTest, VerifyTest)
{
    U16 expectedId = 6U;
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, expectedId, NULL };

    const ReferenceBitmapFieldType fieldType = { &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));
    EXPECT_FALSE(field.getLastVerificationResult());

    EXPECT_CALL(m_mockCanvas, verify(_, _)).WillOnce(Return(true));

    lsr::Area area(&areaType);
    EXPECT_TRUE(field.verify(m_canvas, area));
    EXPECT_EQ(0U, field.getVerificationErrors());
    EXPECT_TRUE(field.getLastVerificationResult());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyWithInvisibleWidgetTest)
{
    U16 expectedId = 6U;
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, expectedId, NULL };

    const ReferenceBitmapFieldType fieldType = { &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));
    EXPECT_FALSE(field.getLastVerificationResult());

    EXPECT_CALL(m_mockCanvas, verify(_, _)).Times(0);

    lsr::Area area(&areaType);
    EXPECT_TRUE(field.verify(m_canvas, area));
    EXPECT_EQ(0U, field.getVerificationErrors());
    EXPECT_TRUE(field.getLastVerificationResult());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsTest)
{
    const U16 expectedId = 6U;
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, expectedId, NULL };
    const ReferenceBitmapFieldType fieldType = { &areaType, &visible, &bmp };

    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));
    EXPECT_FALSE(field.getLastVerificationResult());

    lsr::Area area(&areaType);
    EXPECT_CALL(m_mockCanvas, verify(_, _)).WillOnce(Return(false));

    EXPECT_FALSE(field.verify(m_canvas, area));
    EXPECT_EQ(1U, field.getVerificationErrors());
    EXPECT_FALSE(field.getLastVerificationResult());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithVeryLargeCounterValueTest)
{
    const U16 expectedId = 6U;
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, expectedId, NULL };
    const ReferenceBitmapFieldType fieldType = { &areaType, &visible, &bmp };

    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));

    const lsr::Area area(&areaType);
    EXPECT_CALL(m_mockCanvas, verify(_, _)).Times(2).WillRepeatedly(Return(false));

    setVerificationErrors(field, U32_MAX - 1);
    EXPECT_FALSE(field.verify(m_canvas, area));
    EXPECT_EQ(U32_MAX, field.getVerificationErrors());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.getError());
    EXPECT_FALSE(field.getLastVerificationResult());

    EXPECT_FALSE(field.verify(m_canvas, area));
    EXPECT_EQ(U32_MAX, field.getVerificationErrors());
    EXPECT_FALSE(field.getLastVerificationResult());
}

TEST_F(ReferenceBitmapFieldTest, ResetErrorCounterValueTest)
{
    const U16 expectedId = 6U;
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, expectedId, NULL };
    const ReferenceBitmapFieldType fieldType = { &areaType, &visible, &bmp };

    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));
    EXPECT_CALL(m_mockCanvas, verify(_, _)).WillOnce(Return(false)).WillOnce(Return(false));

    EXPECT_FALSE(field.getLastVerificationResult());
    EXPECT_EQ(0U, field.getVerificationErrors());
    const lsr::Area area(&areaType);

    EXPECT_FALSE(field.verify(m_canvas, area));
    EXPECT_EQ(1U, field.getVerificationErrors());
    EXPECT_FALSE(field.getLastVerificationResult());

    EXPECT_FALSE(field.verify(m_canvas, area));
    EXPECT_EQ(2U, field.getVerificationErrors());
    EXPECT_FALSE(field.getLastVerificationResult());

    EXPECT_CALL(m_mockCanvas, verify(_, _)).WillOnce(Return(true));

    // verification succeeds, error count is kept
    EXPECT_TRUE(field.verify(m_canvas, area));
    EXPECT_EQ(2U, field.getVerificationErrors());
    EXPECT_TRUE(field.getLastVerificationResult());

    field.setVisible(false);
    EXPECT_TRUE(field.verify(m_canvas, area));
    EXPECT_EQ(0U, field.getVerificationErrors());
    EXPECT_TRUE(field.getLastVerificationResult());
}

TEST_F(ReferenceBitmapFieldTest, ClearVerificationErrors)
{
    const U16 expectedId = 6U;
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, expectedId, NULL };
    const ReferenceBitmapFieldType fieldType = { &areaType, &visible, &bmp };

    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));
    EXPECT_CALL(m_mockCanvas, verify(_, _)).WillOnce(Return(false)).WillOnce(Return(false));
    const lsr::Area area(&areaType);

    EXPECT_FALSE(field.verify(m_canvas, area));
    EXPECT_FALSE(field.verify(m_canvas, area));

    EXPECT_FALSE(field.getLastVerificationResult());
    EXPECT_EQ(2U, field.getVerificationErrors());

    field.clearVerificationErrors();

    EXPECT_FALSE(field.getLastVerificationResult()); // last result is untouched
    EXPECT_EQ(0U, field.getVerificationErrors());
}

TEST_F(ReferenceBitmapFieldTest, DrawMethodDrawsNothingTest)
{
    const U16 expectedId = 6U;
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, expectedId, NULL };
    const ReferenceBitmapFieldType fieldType = { &areaType, &visible, &bmp };

    lsr::ReferenceBitmapField field(&fieldType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));

    lsr::Area area(&areaType);

    // Check on empty implementation
    EXPECT_CALL(m_mockCanvas, drawBitmap(_, _)).Times(0);
    field.draw(m_canvas, area);
}

} // unittest
