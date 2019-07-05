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
#include "DdhReferenceBitmapFieldBuilder.h"

#include <ReferenceBitmapField.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;
using ::testing::_;

class ReferenceBitmapFieldTest: public WidgetTestBase
{
protected:
    ReferenceBitmapFieldTest()
        : m_internalFU(255U)
        , m_counterDataId(43U)
    {
    }

    void setCounterToDH(U32 counter, lsr::DynamicDataTypeEnumeration type, lsr::DataStatus status)
    {
        const lsr::Number counterNum(counter, type);
        m_dataHandler.setNumber(counterNum, m_internalFU, m_counterDataId, status);
    }

    void setDefaultCounterToDH()
    {
        const lsr::Number counterNum(0U, lsr::DATATYPE_INTEGER);
        m_dataHandler.setNumber(counterNum, m_internalFU, m_counterDataId, lsr::DataStatus::VALID);
    }

    lsr::ReferenceBitmapField* createField(const framehandlertests::DdhReferenceBitmapFieldBuilder& builder)
    {
        lsr::LSRErrorCollector error(LSR_NO_ERROR);
        lsr::ReferenceBitmapField* field =
            lsr::ReferenceBitmapField::create(m_widgetPool,
                                              *m_pDb,
                                              builder.getDdh(),
                                              &m_context,
                                              error);
        EXPECT_EQ(LSR_NO_ERROR, error.get());

        return field;
    }

    lsr::ReferenceBitmapField* createInconsistentField(
            const framehandlertests::DdhReferenceBitmapFieldBuilder& builder)
    {
        lsr::LSRErrorCollector error(LSR_NO_ERROR);
        lsr::ReferenceBitmapField* field =
            lsr::ReferenceBitmapField::create(m_widgetPool,
                                              *m_pDb,
                                              builder.getDdh(),
                                              &m_context,
                                              error);
        EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());

        return field;
    }


    framehandlertests::DdhReferenceBitmapFieldBuilder m_builder;

    const FUClassId m_internalFU;
    const U16 m_counterDataId;
};

TEST_F(ReferenceBitmapFieldTest, CreateBitmapFieldTest)
{
    lsr::AreaType area;
    m_builder.create(43U, area, true, 23U);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    EXPECT_TRUE(NULL != field);
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest1)
{
    m_builder.createWithoutArea(43U, true, 23U);
    lsr::ReferenceBitmapField* field = createInconsistentField(m_builder);

    EXPECT_TRUE(NULL == field);
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest2)
{
    lsr::AreaType area;
    m_builder.createWithoutVisibility(43U, area, 23U);
    lsr::ReferenceBitmapField* field = createInconsistentField(m_builder);

    EXPECT_TRUE(NULL == field);
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest3)
{
    lsr::AreaType area;
    m_builder.createWithoutBitmap(43U, area, true);
    lsr::ReferenceBitmapField* field = createInconsistentField(m_builder);

    EXPECT_TRUE(NULL == field);
}

TEST_F(ReferenceBitmapFieldTest, OnUpdateTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);
    setDefaultCounterToDH();

    lsr::DisplayAccessor::instance().setVerifyFlag(true);

    lsr::Area area(&areaType);

    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(expectedId, lsr::DatabaseAccessor::instance().getRequestedBitmapId());
    EXPECT_EQ(LSR_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, OnUpdateWithTheSameValueTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

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

    EXPECT_EQ(LSR_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, OnUpdateWrongValueTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(43U, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDHWithOutdatedData(expectedId);
    setDefaultCounterToDH();

    lsr::Area area(&areaType);

    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(LSR_DATASTATUS_NOT_AVAIABLE, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);
    setDefaultCounterToDH();

    lsr::Area area(&areaType);

    field->update(0U);
    EXPECT_TRUE(field->verify(m_canvas, area));

    EXPECT_EQ(LSR_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyWithInvisibleWidgetTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(43U, areaType, false, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);
    setDefaultCounterToDH();

    lsr::Area area(&areaType);

    field->update(0U);
    EXPECT_TRUE(field->verify(m_canvas, area));

    EXPECT_EQ(LSR_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Prepare error counter inside DH
    const U32 counter = 46U;
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    setCounterToDH(counter, lsr::DATATYPE_INTEGER, expectedStatus);

    const lsr::Number expectedNum(counter + 1U, lsr::DATATYPE_INTEGER);
    EXPECT_CALL(m_dataHandler, setData(m_internalFU, m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(true));

    field->update(0U);

    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithVeryLargeCounterValueTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

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
    EXPECT_CALL(m_dataHandler, setData(m_internalFU, m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(true));

    field->update(0U);

    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, ResetErrorCounterValueTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Prepare error counter inside DH
    const U32 counter = 46U;
    const lsr::DataStatus expectedStatus = lsr::DataStatus::VALID;
    setCounterToDH(counter, lsr::DATATYPE_INTEGER, expectedStatus);

    const lsr::Number expectedNum(counter + 1U, lsr::DATATYPE_INTEGER);
    EXPECT_CALL(m_dataHandler, setData(m_internalFU, m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(true));

    field->update(0U);

    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_NO_ERROR, field->getError());

    // Now, verify will return true
    lsr::DisplayAccessor::instance().setVerifyFlag(true);

    const lsr::Number zeroNum(0U, lsr::DATATYPE_INTEGER);
    EXPECT_CALL(m_dataHandler, setData(m_internalFU, m_counterDataId, zeroNum, expectedStatus))
        .WillOnce(Return(true));

    field->update(0U);

    EXPECT_TRUE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithWrongErrorCounterValueTest1)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Check if error counter was incremented inside DataHandler
    const U32 counter = 46U;
    setCounterToDH(counter, lsr::DATATYPE_INTEGER, lsr::DataStatus::NOT_AVAILABLE);

    EXPECT_CALL(m_dataHandler, setData(_, _, _, _))
        .Times(0);

    field->update(0U);
    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_DATASTATUS_NOT_AVAIABLE, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithWrongErrorCounterValueTest2)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    lsr::DisplayAccessor::instance().setVerifyFlag(false);

    // Check if error counter was incremented inside DataHandler
    const U32 counter = 46U;
    setCounterToDH(counter, lsr::DATATYPE_DECIMAL, lsr::DataStatus::VALID);

    // method SetData shouldn't be called
    EXPECT_CALL(m_dataHandler, setData(_, _, _, _))
        .Times(0);

    // Here should be a magic
    field->update(0U);
    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_DATASTATUS_INCONSISTENT, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithSetDataToDHFailedTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

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
    EXPECT_CALL(m_dataHandler, setData(m_internalFU, m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(false));

    field->update(0U);
    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(LSR_DH_INVALID_DATA_ID, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, DrawMethodDrawsNothingTest)
{
    lsr::AreaType areaType;
    lsr::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    lsr::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    lsr::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    // Check on empty implementation
    EXPECT_FALSE(lsr::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
