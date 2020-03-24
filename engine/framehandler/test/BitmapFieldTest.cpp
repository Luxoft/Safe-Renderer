/******************************************************************************
**
**   File:        BitmapFieldTest.cpp
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
#include <StaticBitmap.h>

#include "WidgetTestBase.h"

#include <LSRErrorCollector.h>

#include <BitmapField.h>
#include <StaticBitmapFieldType.h>
#include "Telltales.hpp"
#include "Database.h"

#include <gtest/gtest.h>

using namespace lsr;
using testing::_;
using testing::Return;

class BitmapFieldTest: public WidgetTestBase
{
protected:
    BitmapFieldTest()
        : m_db(Telltales::getDDH())
    {}

    lsr::Database m_db;
};

TEST_F(BitmapFieldTest, CreateBitmapFieldTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &area, &visible, &bmp };
    lsr::BitmapField field(&bmpField);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));
}

TEST_F(BitmapFieldTest, CreateWrongBitmapFieldTest1)
{
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { NULL, &visible, &bmp };
    lsr::BitmapField field(&bmpField);
    EXPECT_EQ(LSR_DB_INCONSISTENT, field.setup(m_db));
}

TEST_F(BitmapFieldTest, CreateWrongBitmapFieldTest2)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &area, NULL, &bmp };
    lsr::BitmapField field(&bmpField);
    EXPECT_EQ(LSR_DB_INCONSISTENT, field.setup(m_db));
}

TEST_F(BitmapFieldTest, CreateWrongBitmapFieldTest3)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const StaticBitmapFieldType bmpField = { &area, &visible, NULL };
    lsr::BitmapField field(&bmpField);
    EXPECT_EQ(LSR_DB_INCONSISTENT, field.setup(m_db));
}

TEST_F(BitmapFieldTest, VerifyTest)
{
    const AreaType tarea = { 0U, 0U, 1U, 3U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &tarea, &visible, &bmp };
    lsr::BitmapField field(&bmpField);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));
    lsr::Area area(&tarea);
    EXPECT_TRUE(field.verify(m_canvas, area));
}

TEST_F(BitmapFieldTest, DrawBitmapFieldTest)
{
    const AreaType areaType = { 0U, 0U, 1U, 3U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 6U, NULL };
    const StaticBitmapFieldType bmpField = { &areaType, &visible, &bmp };

    lsr::BitmapField field(&bmpField);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field.setup(m_db));
    lsr::Area area(&areaType);

    lsr::StaticBitmap b = m_db.getBitmap(6U);
    EXPECT_CALL(m_mockCanvas, drawBitmap(b, area));
    field.draw(m_canvas, area);
}
