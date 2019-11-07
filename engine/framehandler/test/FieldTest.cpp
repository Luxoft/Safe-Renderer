/******************************************************************************
**
**   File:        FieldTest.cpp
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
#include "WidgetPoolHelper.h"

#include <LSRErrorCollector.h>
#include <Telltales.hpp>

#include <gtest/gtest.h>
using namespace lsr;

class FieldTest: public WidgetTestBase
{
protected:
    FieldTest()
        : m_helper(m_widgetPool)
        , m_db(Telltales::getDDH())
    {}

    WidgetPoolHelper m_helper;
    lsr::Database m_db;
};

TEST_F(FieldTest, CreateBitmapFieldTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &area, &visible, &bmp };
    const BaseFieldChoiceType fieldChoice = { BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE, &bmpField };

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    for (U8 i = 0U; i < MAX_BITMAPS_COUNT; ++i)
    {
        lsr:: Field* field = lsr::Field::create(m_widgetPool,
                                                m_db,
                                                &fieldChoice,
                                                &m_context,
                                                error);
        EXPECT_EQ(LSR_NO_ERROR, error.get());
        EXPECT_TRUE(NULL != field);
    }

    EXPECT_TRUE(m_helper.isBitMapPoolFilled());
}

TEST_F(FieldTest, CreateRefsBitmapFieldTest)
{
    U16 errorCounter = 0U;
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const ReferenceBitmapFieldType bmpField = { errorCounter, &area, &visible, &bmp };
    const BaseFieldChoiceType fieldChoice = { BaseFieldChoiceType::REFERENCEBITMAPFIELD_CHOICE, &bmpField };

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    for (U8 i = 0U; i < MAX_REFERENCE_BITMAPS_COUNT; ++i)
    {
        lsr:: Field* field = lsr::Field::create(m_widgetPool,
                                                m_db,
                                                &fieldChoice,
                                                &m_context,
                                                error);
        EXPECT_EQ(LSR_NO_ERROR, error.get());
        EXPECT_TRUE(NULL != field);
    }

    EXPECT_TRUE(m_helper.isReferenceBitMapPoolFilled());
}

TEST_F(FieldTest, CreateWrongFieldTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &area, &visible, &bmp };
    const BaseFieldChoiceType fieldChoice = { BaseFieldChoiceType::NONE, &bmpField };

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr:: Field* field = lsr::Field::create(m_widgetPool,
                                            m_db,
                                            &fieldChoice,
                                            &m_context,
                                            error);
    EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());
    EXPECT_TRUE(NULL == field);
}
