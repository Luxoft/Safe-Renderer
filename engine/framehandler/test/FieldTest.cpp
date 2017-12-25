/******************************************************************************
**
**   File:        FieldTest.cpp
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
#include "WidgetPoolHelper.h"
#include "DdhStaticBitmapFieldBuilder.h"
#include "DdhReferenceBitmapFieldBuilder.h"

#include <FieldTypeFactory.h>

#include <PSCErrorCollector.h>

#include <gtest/gtest.h>

class FieldTest: public WidgetTestBase
{
protected:
    FieldTest()
        : m_helper(m_widgetPool)
    {}

    WidgetPoolHelper m_helper;
    FieldTypeFactory m_factory;
};

TEST_F(FieldTest, CreateBitmapFieldTest)
{
    m_factory.create(psc::FieldType::STATICBITMAPFIELD_CHOICE);

    framehandlertests::DdhStaticBitmapFieldBuilder bmpBuilder;
    psc::AreaType area;
    bmpBuilder.create(area, true, 23U);

    m_factory.addBitmap(bmpBuilder.getDdh(), bmpBuilder.getSize());

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    for (U8 i = 0U; i < MAX_BITMAPS_COUNT; ++i)
    {
        psc:: Field* field = psc::Field::create(m_widgetPool,
                                                *m_pDb,
                                                m_factory.getDdh(),
                                                &m_context,
                                                error);
        EXPECT_EQ(PSC_NO_ERROR, error.get());
        EXPECT_TRUE(NULL != field);
    }

    EXPECT_TRUE(m_helper.isBitMapPoolFilled());
}

TEST_F(FieldTest, CreateRefsBitmapFieldTest)
{
    m_factory.create(psc::FieldType::REFERENCEBITMAPFIELD_CHOICE);

    framehandlertests::DdhReferenceBitmapFieldBuilder bmpBuilder;
    psc::AreaType area;
    U16 errorCounter = 0U;
    bmpBuilder.create(errorCounter, area, true, 23U);

    m_factory.addBitmap(bmpBuilder.getDdh(), bmpBuilder.getSize());

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    for (U8 i = 0U; i < MAX_REFERENCE_BITMAPS_COUNT; ++i)
    {
        psc:: Field* field = psc::Field::create(m_widgetPool,
                                                *m_pDb,
                                                m_factory.getDdh(),
                                                &m_context,
                                                error);
        EXPECT_EQ(PSC_NO_ERROR, error.get());
        EXPECT_TRUE(NULL != field);
    }

    EXPECT_TRUE(m_helper.isReferenceBitMapPoolFilled());
}

TEST_F(FieldTest, CreateWrongFieldTest)
{
    m_factory.create(psc::FieldType::STATICBITMAPFIELD_CHOICE + 2U);

    framehandlertests::DdhStaticBitmapFieldBuilder bmpBuilder;
    psc::AreaType area;
    bmpBuilder.create(area, true, 23U);

    m_factory.addBitmap(bmpBuilder.getDdh(), bmpBuilder.getSize());

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc:: Field* field = psc::Field::create(m_widgetPool,
                                            *m_pDb,
                                            m_factory.getDdh(),
                                            &m_context,
                                            error);
    EXPECT_EQ(PSC_DB_INCONSISTENT, error.get());
    EXPECT_TRUE(NULL == field);
}
