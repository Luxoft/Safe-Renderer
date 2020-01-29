/******************************************************************************
**
**   File:        BitmapFieldTest.cpp
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

#include <LSRErrorCollector.h>

#include <BitmapField.h>
#include <StaticBitmapFieldType.h>
#include "Telltales.hpp"

#include <gtest/gtest.h>

using namespace lsr;

class BitmapFieldTest: public WidgetTestBase
{
protected:
    BitmapFieldTest()
        : m_db(Telltales::getDDH())
    {}

    lsr::BitmapField* createField(const StaticBitmapFieldType* ddh)
    {
        lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
        lsr::BitmapField* field =
            lsr::BitmapField::create(m_widgetPool,
                                     m_db,
                                     ddh,
                                     &m_context,
                                     error);
        EXPECT_EQ(LSR_NO_ENGINE_ERROR, error.get());

        return field;
    }

    lsr::BitmapField* createWrongField(const StaticBitmapFieldType* ddh)
    {
        lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
        lsr::BitmapField* field =
            lsr::BitmapField::create(m_widgetPool,
                                     m_db,
                                     ddh,
                                     &m_context,
                                     error);
        EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());

        return field;
    }

    lsr::Database m_db;
};

TEST_F(BitmapFieldTest, CreateBitmapFieldTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &area, &visible, &bmp };
    lsr::BitmapField* field = createField(&bmpField);
    EXPECT_TRUE(NULL != field);
}

TEST_F(BitmapFieldTest, CreateWrongBitmapFieldTest1)
{
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { NULL, &visible, &bmp };
    lsr::BitmapField* field = createWrongField(&bmpField);
    EXPECT_TRUE(NULL == field);
}

TEST_F(BitmapFieldTest, CreateWrongBitmapFieldTest2)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &area, NULL, &bmp };
    lsr::BitmapField* field = createWrongField(&bmpField);
    EXPECT_TRUE(NULL == field);
}

TEST_F(BitmapFieldTest, CreateWrongBitmapFieldTest3)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const StaticBitmapFieldType bmpField = { &area, &visible, NULL };
    lsr::BitmapField* field = createWrongField(&bmpField);
    EXPECT_TRUE(NULL == field);
}

TEST_F(BitmapFieldTest, VerifyTest)
{
    const AreaType tarea = { 0U, 0U, 1U, 3U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &tarea, &visible, &bmp };
    lsr::BitmapField* field = createField(&bmpField);

    lsr::Area area(&tarea);
    EXPECT_TRUE(field->verify(m_canvas, area));
}

TEST_F(BitmapFieldTest, OnUpdateTest)
{
    const AreaType areaType = { 0U, 0U, 1U, 3U };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const StaticBitmapFieldType bmpField = { &areaType, &visible, &bmp };

    lsr::BitmapField* field = createField(&bmpField);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_EQ(expectedId, lsr::DatabaseAccessor::instance().getRequestedBitmapId());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());
}

TEST_F(BitmapFieldTest, OnUpdateWithTheSameValueTest)
{
    const AreaType areaType = { 0U, 0U, 1U, 3U };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const StaticBitmapFieldType bmpField = { &areaType, &visible, &bmp };

    lsr::BitmapField* field = createField(&bmpField);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_EQ(expectedId, lsr::DatabaseAccessor::instance().getRequestedBitmapId());

    // update again, the value should be the same
    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_EQ(expectedId, lsr::DatabaseAccessor::instance().getRequestedBitmapId());

    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());
}

TEST_F(BitmapFieldTest, OnUpdateWrongValueTest)
{
    const AreaType areaType = { 0U, 0U, 1U, 3U };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const StaticBitmapFieldType bmpField = { &areaType, &visible, &bmp };

    lsr::BitmapField* field = createField(&bmpField);

    U16 expectedId = 6U;
    initDHWithOutdatedData(expectedId);

    lsr::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_EQ(LSR_ERR_DATASTATUS_NOT_AVAILABLE, field->getError());
}

TEST_F(BitmapFieldTest, DrawBitmapFieldTest)
{
    const AreaType areaType = { 0U, 0U, 1U, 3U };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const StaticBitmapFieldType bmpField = { &areaType, &visible, &bmp };

    lsr::BitmapField* field = createField(&bmpField);

    U16 expectedId = 6U;
    initDHWithOutdatedData(expectedId);

    lsr::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_TRUE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
