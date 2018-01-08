/******************************************************************************
**
**   File:        ReferenceBitmapFieldTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
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

    void setCounterToDH(U32 counter, psc::DynamicDataTypeEnumeration type, psc::DataStatus status)
    {
        const psc::Number counterNum(counter, type);
        m_dataHandler.setNumber(counterNum, m_internalFU, m_counterDataId, status);
    }

    psc::ReferenceBitmapField* createField(const framehandlertests::DdhReferenceBitmapFieldBuilder& builder)
    {
        psc::PSCErrorCollector error(PSC_NO_ERROR);
        psc::ReferenceBitmapField* field =
            psc::ReferenceBitmapField::create(m_widgetPool,
                                              *m_pDb,
                                              builder.getDdh(),
                                              &m_context,
                                              error);
        EXPECT_EQ(PSC_NO_ERROR, error.get());

        return field;
    }

    psc::ReferenceBitmapField* createInconsistentField(
            const framehandlertests::DdhReferenceBitmapFieldBuilder& builder)
    {
        psc::PSCErrorCollector error(PSC_NO_ERROR);
        psc::ReferenceBitmapField* field =
            psc::ReferenceBitmapField::create(m_widgetPool,
                                              *m_pDb,
                                              builder.getDdh(),
                                              &m_context,
                                              error);
        EXPECT_EQ(PSC_DB_INCONSISTENT, error.get());

        return field;
    }


    framehandlertests::DdhReferenceBitmapFieldBuilder m_builder;

    const FUClassId m_internalFU;
    const U16 m_counterDataId;
};

TEST_F(ReferenceBitmapFieldTest, CreateBitmapFieldTest)
{
    psc::AreaType area;
    m_builder.create(43U, area, true, 23U);
    psc::ReferenceBitmapField* field = createField(m_builder);

    EXPECT_TRUE(NULL != field);
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest1)
{
    m_builder.createWithoutArea(43U, true, 23U);
    psc::ReferenceBitmapField* field = createInconsistentField(m_builder);

    EXPECT_TRUE(NULL == field);
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest2)
{
    psc::AreaType area;
    m_builder.createWithoutVisibility(43U, area, 23U);
    psc::ReferenceBitmapField* field = createInconsistentField(m_builder);

    EXPECT_TRUE(NULL == field);
}

TEST_F(ReferenceBitmapFieldTest, CreateWrongBitmapFieldTest3)
{
    psc::AreaType area;
    m_builder.createWithoutBitmap(43U, area, true);
    psc::ReferenceBitmapField* field = createInconsistentField(m_builder);

    EXPECT_TRUE(NULL == field);
}

TEST_F(ReferenceBitmapFieldTest, OnUpdateTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(43U, areaType, true, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(expectedId, psc::DatabaseAccessor::instance().getRequestedBitmapId());
    EXPECT_EQ(PSC_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, OnUpdateWithTheSameValueTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(43U, areaType, true, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(expectedId, psc::DatabaseAccessor::instance().getRequestedBitmapId());

    // update again, the value should be the same
    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(expectedId, psc::DatabaseAccessor::instance().getRequestedBitmapId());

    EXPECT_EQ(PSC_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, OnUpdateWrongValueTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(43U, areaType, true, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDHWithOutdatedData(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    field->verify(m_canvas, area);

    EXPECT_EQ(PSC_DATASTATUS_NOT_AVAIABLE, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(43U, areaType, true, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    EXPECT_TRUE(field->verify(m_canvas, area));

    EXPECT_EQ(PSC_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyWithInvisibleWidgetTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(43U, areaType, false, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    EXPECT_TRUE(field->verify(m_canvas, area));

    EXPECT_EQ(PSC_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    psc::DisplayAccessor::instance().setVerifyFlag(false);

    // Prepare error counter inside DH
    const U32 counter = 46U;
    const psc::DataStatus expectedStatus = psc::DataStatus::VALID;
    setCounterToDH(counter, psc::DATATYPE_INTEGER, expectedStatus);

    const psc::Number expectedNum(counter + 1U, psc::DATATYPE_INTEGER);
    EXPECT_CALL(m_dataHandler, setData(m_internalFU, m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(true));

    field->update(0U);

    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(PSC_NO_ERROR, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithWrongErrorCounterValueTest1)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    psc::DisplayAccessor::instance().setVerifyFlag(false);

    // Check if error counter was incremented inside DataHandler
    const U32 counter = 46U;
    setCounterToDH(counter, psc::DATATYPE_INTEGER, psc::DataStatus::NOT_AVAILABLE);

    EXPECT_CALL(m_dataHandler, setData(_, _, _, _))
        .Times(0);

    field->update(0U);
    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(PSC_DATASTATUS_NOT_AVAIABLE, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithWrongErrorCounterValueTest2)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    psc::DisplayAccessor::instance().setVerifyFlag(false);

    // Check if error counter was incremented inside DataHandler
    const U32 counter = 46U;
    setCounterToDH(counter, psc::DATATYPE_DECIMAL, psc::DataStatus::VALID);

    // method SetData shouldn't be called
    EXPECT_CALL(m_dataHandler, setData(_, _, _, _))
        .Times(0);

    // Here should be a magic
    field->update(0U);
    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(PSC_DATASTATUS_INCONSISTENT, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, VerifyFailsWithSetDataToDHFailedTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    psc::DisplayAccessor::instance().setVerifyFlag(false);

    // Prepare error counter inside DH
    const U32 counter = 46U;
    const psc::DataStatus expectedStatus = psc::DataStatus::VALID;
    setCounterToDH(counter, psc::DATATYPE_INTEGER, expectedStatus);

    const psc::Number expectedNum(counter + 1U, psc::DATATYPE_INTEGER);

    // Set, DH can't set error counter
    EXPECT_CALL(m_dataHandler, setData(m_internalFU, m_counterDataId, expectedNum, expectedStatus))
        .WillOnce(Return(false));

    field->update(0U);
    EXPECT_FALSE(field->verify(m_canvas, area));
    EXPECT_EQ(PSC_DH_INVALID_DATA_ID, field->getError());
}

TEST_F(ReferenceBitmapFieldTest, DrawMethodDrawsNothingTest)
{
    psc::AreaType areaType;
    psc::DynamicDataType dataType;
    m_builder.create(m_counterDataId, areaType, true, dataType);
    psc::ReferenceBitmapField* field = createField(m_builder);

    U16 expectedId = 6U;
    initDataHandler(expectedId);

    psc::Area area(&areaType);

    field->update(0U);
    field->draw(m_canvas, area);

    // Check on empty implementation
    EXPECT_FALSE(psc::DisplayAccessor::instance().wasDrawBitmapExecuted());
}
