/******************************************************************************
**
**   File:        BitmapFieldTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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
#include "DdhStaticBitmapFieldBuilder.h"

#include <PSCErrorCollector.h>

#include <BitmapField.h>

#include <gtest/gtest.h>

class BitmapFieldTest: public WidgetTestBase
{
protected:
    BitmapFieldTest()
    {}

    psc::BitmapField* createField(const framehandlertests::DdhStaticBitmapFieldBuilder& builder)
    {
        psc::PSCErrorCollector error(PSC_NO_ERROR);
        psc::BitmapField* field =
            psc::BitmapField::create(m_widgetPool,
                                     *m_pDb,
                                     builder.getDdh(),
                                     &m_context,
                                     error);
        EXPECT_EQ(PSC_NO_ERROR, error.get());

        return field;
    }

    psc::BitmapField* createWrongField(const framehandlertests::DdhStaticBitmapFieldBuilder& builder)
    {
        psc::PSCErrorCollector error(PSC_NO_ERROR);
        psc::BitmapField* field =
            psc::BitmapField::create(m_widgetPool,
                                     *m_pDb,
                                     builder.getDdh(),
                                     &m_context,
                                     error);
        EXPECT_EQ(PSC_DB_INCONSISTENT, error.get());

        return field;
    }

    framehandlertests::DdhStaticBitmapFieldBuilder m_builder;
};

TEST_F(BitmapFieldTest, CreateBitmapFieldTest)
{
    psc::AreaType area;
    m_builder.create(area, true, 23U);
    psc::BitmapField* field = createField(m_builder);

    EXPECT_TRUE(NULL != field);
}

TEST_F(BitmapFieldTest, CreateWrongBitmapFieldTest1)
{
    m_builder.createWithoutArea(true, 23U);
    psc::BitmapField* field = createWrongField(m_builder);

    EXPECT_TRUE(NULL == field);
}

TEST_F(BitmapFieldTest, CreateWrongBitmapFieldTest2)
{
    psc::AreaType area;
    m_builder.createWithoutVisibility(area, 23U);
    psc::BitmapField* field = createWrongField(m_builder);

    EXPECT_TRUE(NULL == field);
}

TEST_F(BitmapFieldTest, CreateWrongBitmapFieldTest3)
{
    psc::AreaType area;
    m_builder.createWithoutBitmap(area, true);
    psc::BitmapField* field = createWrongField(m_builder);

    EXPECT_TRUE(NULL == field);
}

TEST_F(BitmapFieldTest, VerifyTest)
{
    psc::AreaType areaType;
    m_builder.create(areaType, true, 23U);
    psc::BitmapField* field = createField(m_builder);

    psc::Area area(&areaType);
    EXPECT_TRUE(field->verify(m_canvas, area));
}

TEST_F(BitmapFieldTest, OnUpdateTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(areaType, true, dataType);
    psc::BitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_EQ(expectedId, psc::DatabaseAccessor::instance().getRequestedBitmapId());
    EXPECT_EQ(PSC_NO_ERROR, field->getError());
}

TEST_F(BitmapFieldTest, OnUpdateWithTheSameValueTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(areaType, true, dataType);
    psc::BitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_EQ(expectedId, psc::DatabaseAccessor::instance().getRequestedBitmapId());

    // update again, the value should be the same
    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_EQ(expectedId, psc::DatabaseAccessor::instance().getRequestedBitmapId());

    EXPECT_EQ(PSC_NO_ERROR, field->getError());
}

TEST_F(BitmapFieldTest, OnUpdateWrongValueTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(areaType, true, dataType);
    psc::BitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDHWithOutdatedData(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_EQ(PSC_DATASTATUS_NOT_AVAIABLE, field->getError());
}

TEST_F(BitmapFieldTest, DrawBitmapFieldTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(areaType, true, dataType);
    psc::BitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDHWithOutdatedData(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    EXPECT_TRUE(psc::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
