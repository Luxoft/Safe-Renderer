/******************************************************************************
**
**   File:        DatabaseTest.cpp
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <string>

#include "Database.h"
#include "ResourceBuffer.h"
#include "LsrImage.h"
#include "DDHType.h"
#include "FUDatabaseType.h"
#include "FUClassType.h"
#include "DynamicDataEntryType.h"
#include "PageDatabaseType.h"
#include "PageType.h"
#include "PanelDatabaseType.h"
#include "PanelType.h"
#include "FieldType.h"
#include "FieldsType.h"
#include "Area.h"
#include "ExpressionTermType.h"
#include "StaticBitmapFieldType.h"
#include "ReferenceBitmapFieldType.h"
#include "ExpressionType.h"
#include "ExpressionTermType.h"
#include "DynamicDataType.h"

using namespace lsr;

const char* ddhbin = ROOT_PATH "/test/database/Telltales/Output/Telltales.ddhbin";
const char* imgbin = ROOT_PATH "/test/database/Telltales/Output/Telltales.imgbin";

class DatabaseTest : public ::testing::Test
{
    void SetUp() P_OVERRIDE
    {
        std::ifstream ifs1(ddhbin, std::ios::binary);
        m_ddhbinData.assign ((std::istreambuf_iterator<char>(ifs1)), (std::istreambuf_iterator<char>()));
        m_ddhbin = ResourceBuffer(m_ddhbinData.c_str(), m_ddhbinData.size());
        std::ifstream ifs2(imgbin, std::ios::binary);
        m_imgbinData.assign ((std::istreambuf_iterator<char>(ifs2)), (std::istreambuf_iterator<char>()));
        m_imgbin = ResourceBuffer(m_imgbinData.c_str(), m_imgbinData.size());
    }

    std::string m_ddhbinData;
    std::string m_imgbinData;

protected:
    ResourceBuffer m_ddhbin;
    ResourceBuffer m_imgbin;
};

class BitmapAccessTest : public DatabaseTest
{
};

TEST_F(BitmapAccessTest, BitmapAccess)
{
    ResourceBuffer imgbin;
    const DDHType* ddh = static_cast<const DDHType*>(m_ddhbin.getData());
    {
        BitmapAccess access(NULL, imgbin);
        EXPECT_EQ(LSR_DB_IMGBIN_VERSION_MISMATCH, access.getError());
    }
    {
        BitmapAccess access(ddh, imgbin);
        EXPECT_EQ(LSR_DB_IMGBIN_VERSION_MISMATCH, access.getError());
    }
    {
        BitmapAccess access(ddh, m_imgbin);
        EXPECT_EQ(LSR_NO_ERROR, access.getError());
    }
}

TEST_F(BitmapAccessTest, getBitmap)
{
    const DDHType* ddh = static_cast<const DDHType*>(m_ddhbin.getData());
    BitmapAccess access(ddh, m_imgbin);
    {
        StaticBitmap bmp = access.getBitmap(0, 0);
        EXPECT_EQ(0, bmp.getId());
        EXPECT_EQ(0u, bmp.getData().getSize());
        EXPECT_EQ(NULL, bmp.getData().getData());
        EXPECT_EQ(LSR_NO_ERROR, access.getError());
    }
    {
        // bitmapId out of bounds
        StaticBitmap bmp = access.getBitmap(0x1fff, 0);
        EXPECT_EQ(0, bmp.getId());
        EXPECT_EQ(0u, bmp.getData().getSize());
        EXPECT_EQ(NULL, bmp.getData().getData());
        EXPECT_EQ(LSR_NO_ERROR, access.getError());
    }
    {
        // bitmapId out of bounds - skin fallback
        StaticBitmap bmp = access.getBitmap(0x1fff, 1);
        EXPECT_EQ(0, bmp.getId());
        EXPECT_EQ(0u, bmp.getData().getSize());
        EXPECT_EQ(NULL, bmp.getData().getData());
        EXPECT_EQ(LSR_NO_ERROR, access.getError());
    }
}


TEST_F(DatabaseTest, Database)
{
    // empty ddhbin
    {
        ResourceBuffer ddhbin;
        ResourceBuffer imgbin;
        Database db(ddhbin, imgbin);
        EXPECT_EQ(LSRError(LSR_DB_DDHBIN_EMPTY), db.getError());
    }
    // invalid ddhbin
    {
        U8 buf[] = { 1, 4, 55 };
        ResourceBuffer ddhbin(buf, sizeof(buf));
        ResourceBuffer imgbin;
        Database db(ddhbin, imgbin);
        EXPECT_EQ(LSRError(LSR_DB_DDHBIN_VERSION_MISMATCH), db.getError());
    }
    // empty imgbin
    {
        ResourceBuffer imgbin;
        Database db(m_ddhbin, imgbin);
        EXPECT_EQ(LSRError(LSR_DB_IMGBIN_VERSION_MISMATCH), db.getError());
    }
    // invalid imgbin
    {
        U8 buf[] = { 1, 4, 55 };
        ResourceBuffer imgbin(buf, sizeof(buf));
        Database db(m_ddhbin, imgbin);
        EXPECT_EQ(LSRError(LSR_DB_IMGBIN_VERSION_MISMATCH), db.getError());
    }
}

TEST_F(DatabaseTest, getBitmap)
{
    Database db(m_ddhbin, m_imgbin);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), db.getError());
    ResourceBuffer buf = db.getBitmap(1).getData();
    EXPECT_EQ(27800u, buf.getSize());
    LsrImage image(buf);
    EXPECT_EQ(102u, image.getWidth());
    EXPECT_EQ(68u, image.getHeight());
    EXPECT_EQ(LsrImage::PIXEL_FORMAT_BGRA8888, image.getPixelFormat());
    const U8* pixelData = static_cast<const U8*>(image.getPixelData());
    const U8 expect[] = { 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff };
    ASSERT_THAT(std::vector<uint8_t>(pixelData, pixelData + sizeof(expect)),
        ::testing::ElementsAreArray(expect));
    EXPECT_TRUE(pixelData != NULL);
}

TEST_F(DatabaseTest, pageDatabase)
{
    Database db(m_ddhbin, m_imgbin);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), db.getError());

    const PageDatabaseType* pageDB = db.getDdh()->GetPageDatabase();
    EXPECT_EQ(1u, pageDB->GetPageCount());
    const PageType* page = pageDB->GetPage(0);
    EXPECT_TRUE(page != NULL);
    EXPECT_EQ(2, page->GetSizeOfPanelIdList());
    EXPECT_EQ(1, page->GetPanelIdItem(0)); // panelId
    EXPECT_EQ(2, page->GetPanelIdItem(1)); // panelId
}

TEST_F(DatabaseTest, panelDatabase)
{
    const Area panelArea(10, 153, 380, 224);
    const Area breakArea(20, 2, 119, 70);
    Database db(m_ddhbin, m_imgbin);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), db.getError());

    const PanelDatabaseType* panelDB = db.getDdh()->GetPanelDatabase();
    EXPECT_EQ(2u, panelDB->GetPanelCount());
    // Content Panel
    const PanelType* contentPanel = panelDB->GetPanel(0);
    EXPECT_TRUE(contentPanel != NULL);
    EXPECT_EQ(panelArea, Area(contentPanel->GetArea()));
    EXPECT_TRUE(contentPanel->GetVisible()->GetBoolean());
    EXPECT_EQ(2u, contentPanel->GetFields()->GetFieldCount());

    // Icon1
    const StaticBitmapFieldType* field1 = contentPanel->GetFields()->GetField(0)->GetStaticBitmapField();
    EXPECT_TRUE(field1 != NULL);
    EXPECT_TRUE(NULL != field1->GetVisible()->GetExpression());
    EXPECT_EQ(breakArea, Area(field1->GetArea()));
    EXPECT_EQ(2u, field1->GetBitmap()->GetBitmapId());

    // Reference Panel
    const PanelType* referencePanel = panelDB->GetPanel(1);
    EXPECT_TRUE(referencePanel != NULL);
    EXPECT_EQ(panelArea, Area(referencePanel->GetArea()));
    EXPECT_TRUE(referencePanel->GetVisible()->GetBoolean());
    EXPECT_EQ(2u, referencePanel->GetFields()->GetFieldCount());

    // Break
    const ReferenceBitmapFieldType* refBreak = referencePanel->GetFields()->GetField(0)->GetReferenceBitmapField();
    EXPECT_TRUE(refBreak != NULL);
    const ExpressionType* visible = refBreak->GetVisible()->GetExpression();
    EXPECT_TRUE(visible != NULL);
    EXPECT_EQ(EXPRESSION_OPERATOR_FALLBACK, visible->GetOperator());
    EXPECT_EQ(2, visible->GetTermCount());
    const ExpressionType* orExpression = visible->GetTerm(0)->GetExpression();
    EXPECT_EQ(EXPRESSION_OPERATOR_OR, orExpression->GetOperator());
    EXPECT_EQ(42u, orExpression->GetTerm(0)->GetDynamicData()->GetFUClassId());
    EXPECT_EQ(1u, orExpression->GetTerm(0)->GetDynamicData()->GetDataId());
    const ExpressionType* notExpression = orExpression->GetTerm(1)->GetExpression();
    EXPECT_EQ(EXPRESSION_OPERATOR_NOT, notExpression->GetOperator());
    EXPECT_EQ(42u, notExpression->GetTerm(0)->GetDynamicData()->GetFUClassId());
    EXPECT_EQ(2u, notExpression->GetTerm(0)->GetDynamicData()->GetDataId());
    EXPECT_TRUE(visible->GetTerm(1)->GetBoolean());
    EXPECT_EQ(breakArea, Area(refBreak->GetArea()));
    EXPECT_EQ(2u, refBreak->GetBitmap()->GetBitmapId());
    EXPECT_EQ(1u, refBreak->GetErrorCounter());

    // Airbag
    const ReferenceBitmapFieldType* refAirbag = referencePanel->GetFields()->GetField(1)->GetReferenceBitmapField();
    EXPECT_EQ(2u, refAirbag->GetErrorCounter());
}

TEST_F(DatabaseTest, fuDatabase)
{
    Database db(m_ddhbin, m_imgbin);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), db.getError());

    const FUDatabaseType* fudb =  db.getDdh()->GetFUDatabase();
    EXPECT_EQ(4u, fudb->GetFUCount());
    // Internal FU 0
    const FUClassType* fu0 = fudb->GetFU(0);
    EXPECT_EQ(0u, fu0->GetFUClassId());
    EXPECT_TRUE(NULL == fu0->GetDynamicDataEntry(fu0->GetDynamicDataEntryCount()));
    // External FUSettings 1
    const FUClassType* fu1 = fudb->GetFU(1);
    EXPECT_EQ(1u, fu1->GetFUClassId());
    EXPECT_EQ(6u, fu1->GetDynamicDataEntryCount());
    const DynamicDataEntryType* data = fu1->GetDynamicDataEntry(5);
    EXPECT_EQ(6u, data->GetDataId());
    EXPECT_EQ(DATATYPE_DATE, data->GetDataType());
    EXPECT_FALSE(data->IsMaximumSet());
    EXPECT_FALSE(data->IsMinimumSet());
    // External FU 42
    const FUClassType* fu42 = fudb->GetFU(2);
    EXPECT_EQ(42u, fu42->GetFUClassId());
    EXPECT_EQ(3u, fu42->GetDynamicDataEntryCount());
    EXPECT_EQ(DATATYPE_BOOLEAN, fu42->GetDynamicDataEntry(0)->GetDataType());
    EXPECT_EQ(100, fu42->GetDynamicDataEntry(0)->GetRepeatTimeout());
    EXPECT_EQ(DATATYPE_BOOLEAN, fu42->GetDynamicDataEntry(1)->GetDataType());
    EXPECT_EQ(0, fu42->GetDynamicDataEntry(1)->GetRepeatTimeout());
    EXPECT_EQ(DATATYPE_BOOLEAN, fu42->GetDynamicDataEntry(2)->GetDataType());
    EXPECT_EQ(200, fu42->GetDynamicDataEntry(2)->GetRepeatTimeout());
    // Internal FU 255
    const FUClassType* fu255 = fudb->GetFU(3);
    EXPECT_EQ(255u, fu255->GetFUClassId());
    EXPECT_TRUE(NULL == fudb->GetFU(fudb->GetFUCount()));
}
