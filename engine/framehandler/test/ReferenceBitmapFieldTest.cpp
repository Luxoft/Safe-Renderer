/******************************************************************************
**
**   File:        ReferenceBitmapFieldTest.cpp
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

#include <ReferenceBitmapField.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Telltales.hpp>

using ::testing::Return;
using ::testing::_;

using namespace lsr;

class ReferenceBitmapFieldTest: public WidgetTestBase
{
protected:
    ReferenceBitmapFieldTest()
        : m_db(Telltales::getDDH())
        , m_counterDataId(255U, 43U)
    {
    }

    void setCounterToDH(U32 counter, lsr::DynamicDataTypeEnumeration type, lsr::DataStatus status)
    {
        const lsr::Number counterNum(counter, type);
        m_dataHandler.setNumber(counterNum, m_counterDataId, status);
    }

    void setDefaultCounterToDH()
    {
        const lsr::Number counterNum(0U, lsr::DATATYPE_INTEGER);
        m_dataHandler.setNumber(counterNum, m_counterDataId, lsr::DataStatus::VALID);
    }

    lsr::ReferenceBitmapField* createField(const ReferenceBitmapFieldType* ddh)
    {
        lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
        lsr::ReferenceBitmapField* field =
            lsr::ReferenceBitmapField::create(m_widgetPool,
                                              m_db,
                                              ddh,
                                              &m_context,
                                              error);
        EXPECT_EQ(LSR_NO_ENGINE_ERROR, error.get());
        return field;
    }

    lsr::ReferenceBitmapField* createInconsistentField(
            const ReferenceBitmapFieldType* ddh)
    {
        lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
        lsr::ReferenceBitmapField* field =
            lsr::ReferenceBitmapField::create(m_widgetPool,
                                              m_db,
                                              ddh,
                                              &m_context,
                                              error);
        EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());

        return field;
    }

    Database m_db;
    const DynamicData m_counterDataId;
};

TEST_F(ReferenceBitmapFieldTest, CreateBitmapFieldTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const ReferenceBitmapFieldType fieldType = { 43U, &area, &visible, &bmp };

    lsr::ReferenceBitmapField* field = createField(&fieldType);
    EXPECT_TRUE(NULL != field);
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest1)
{
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const ReferenceBitmapFieldType fieldType = { 43U, NULL, &visible, &bmp };

    lsr::ReferenceBitmapField* field = createInconsistentField(&fieldType);

    EXPECT_TRUE(NULL == field);
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest2)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const ReferenceBitmapFieldType fieldType = { 43U, &area, NULL, &bmp };
    lsr::ReferenceBitmapField* field = createInconsistentField(&fieldType);

    EXPECT_TRUE(NULL == field);
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest3)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ReferenceBitmapFieldType fieldType = { 43U, &area, &visible, NULL};
    lsr::ReferenceBitmapField* field = createInconsistentField(&fieldType);

    EXPECT_TRUE(NULL == field);
}

TEST_F(ReferenceBitmapFieldTest, OnUpdateTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);
    setDefaultCounterToDH();

    lsr::DisplayAccessor::instance().setVerifyFlag(true);

    lsr::Area area(&areaType);

    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(expectedId, lsr::DatabaseAccessor::instance().getRequestedBitmapId());
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, OnUpdateWithTheSameValueTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);
    setDefaultCounterToDH();

    lsr::DisplayAccessor::instance().setVerifyFlag(true);

    lsr::Area area(&areaType);

    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(expectedId, lsr::DatabaseAccessor::instance().getRequestedBitmapId());

    // update again, the value should be the same
    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(expectedId, lsr::DatabaseAccessor::instance().getRequestedBitmapId());

    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, OnUpdateWrongValueTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDHWithOutdatedData(expectedId);
    setDefaultCounterToDH();

    lsr::Area area(&areaType);

    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(LSR_ERR_DATASTATUS_NOT_AVAILABLE, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);
    setDefaultCounterToDH();

    lsr::Area area(&areaType);

    field->update(0U);
    EXPECT_TRUE(field->verify(m_canvas, area));

    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyWithInvisibleWidgetTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);
    setDefaultCounterToDH();

    lsr::Area area(&areaType);

    field->update(0U);
    EXPECT_TRUE(field->verify(m_canvas, area));

    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Prepare error counter inside DH
    const U32 counter = 46U;
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    setCounterToDH(counter, lsr::DATATYPE_INTEGER, expectedStatus);

    const lsr::Number expectedNum(counter + 1U, lsr::DATATYPE_INTEGER);
    EXPECT_CALL(m_dataHandler, setData(m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(true));

    field->update(0U);

    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithVeryLargeCounterValueTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Prepare error counter inside DH
    const U32 counter = U32_MAX;
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    setCounterToDH(counter, lsr::DATATYPE_INTEGER, expectedStatus);

    // Countervalue shouldn't changed.
    const lsr::Number expectedNum(U32_MAX, lsr::DATATYPE_INTEGER);
    EXPECT_CALL(m_dataHandler, setData(m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(true));

    field->update(0U);

    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, ResetErrorCounterValueTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Prepare error counter inside DH
    const U32 counter = 46U;
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    setCounterToDH(counter, lsr::DATATYPE_INTEGER, expectedStatus);

    const lsr::Number expectedNum(counter + 1U, lsr::DATATYPE_INTEGER);
    EXPECT_CALL(m_dataHandler, setData(m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(true));

    field->update(0U);

    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());

    // Now, verify will return true
    lsr::DisplayAccessor::instance().setVerifyFlag(true);

    const lsr::Number zeroNum(0U, lsr::DATATYPE_INTEGER);
    EXPECT_CALL(m_dataHandler, setData(m_counterDataId, zeroNum, expectedStatus))
        .WillOnce(Return(true));

    field->update(0U);

    EXPECT_TRUE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithWrongErrorCounterValueTest1)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Check if error counter was incremented inside DataHandler
    const U32 counter = 46U;
    setCounterToDH(counter, lsr::DATATYPE_INTEGER, lsr::DataStatus::NOT_AVAILABLE);

    EXPECT_CALL(m_dataHandler, setData(_, _, _))
        .Times(0);

    field->update(0U);
    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_ERR_DATASTATUS_NOT_AVAILABLE, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithWrongErrorCounterValueTest2)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Check if error counter was incremented inside DataHandler
    const U32 counter = 46U;
    setCounterToDH(counter, lsr::DATATYPE_DECIMAL, lsr::DataStatus::VALID);

    // method SetData shouldn't be called
    EXPECT_CALL(m_dataHandler, setData(_, _, _))
        .Times(0);

    // Here should be a magic
    field->update(0U);
    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_ERR_DATASTATUS_INCONSISTENT, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithSetDataToDHFailedTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Prepare error counter inside DH
    const U32 counter = 46U;
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    setCounterToDH(counter, lsr::DATATYPE_INTEGER, expectedStatus);

    const lsr::Number expectedNum(counter + 1U, lsr::DATATYPE_INTEGER);

    // Set, DH can't set error counter
    EXPECT_CALL(m_dataHandler, setData(m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(false));

    field->update(0U);
    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_DH_INVALID_DATA_ID, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, DrawMethodDrawsNothingTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const DynamicDataType dataType = { 0U, DATATYPE_BITMAP_ID };
    const ExpressionTermType bmp = { ExpressionTermType::DYNAMICDATA_CHOICE, 0U, &dataType };
    const ReferenceBitmapFieldType fieldType = { m_counterDataId.getCombined(), &areaType, &visible, &bmp };
    lsr::ReferenceBitmapField* field = createField(&fieldType);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    // Check on empty implementation
    EXPECT_FALSE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
