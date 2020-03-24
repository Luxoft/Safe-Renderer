/******************************************************************************
**
**   File:        DatabaseTest.cpp
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <string>

#include "Database.h"
#include "ResourceBuffer.h"
#include "LsrImage.h"
#include "DDHType.h"
#include "PanelDatabaseType.h"
#include "PanelType.h"
#include "BaseFieldChoiceType.h"
#include "Area.h"
#include "ExpressionTermType.h"
#include "StaticBitmapFieldType.h"
#include "ReferenceBitmapFieldType.h"
#include "ExpressionTermType.h"
#include "Telltales.hpp"
#include "BitmapDatabaseType.h"
#include "BitmapType.h"
#include "SkinnedBitmapType.h"

using namespace lsr;

class DatabaseTest : public ::testing::Test
{
    void SetUp() P_OVERRIDE
    {
        m_ddh = Telltales::getDDH();
    }
protected:
    const DDHType* m_ddh;
};

class BitmapAccessTest : public DatabaseTest
{
};

TEST_F(BitmapAccessTest, BitmapAccess)
{
    const DDHType* ddh = m_ddh;
    {
        Database access(NULL);
        EXPECT_EQ(LSR_DB_DDHBIN_EMPTY, access.getError());
    }
    {
        Database access(ddh);
        EXPECT_EQ(LSR_NO_ENGINE_ERROR, access.getError());
    }
}

TEST_F(BitmapAccessTest, getBitmap)
{
    const DDHType* ddh = m_ddh;
    Database access(ddh);
    {
        StaticBitmap bmp = access.getBitmap(0);
        EXPECT_EQ(0, bmp.getId());
        EXPECT_EQ(NULL, bmp.getData());
        EXPECT_EQ(LSR_NO_ENGINE_ERROR, access.getError());
    }
    {
        // bitmapId out of bounds
        StaticBitmap bmp = access.getBitmap(0x1fff);
        EXPECT_EQ(0, bmp.getId());
        EXPECT_EQ(NULL, bmp.getData());
        EXPECT_EQ(LSR_NO_ENGINE_ERROR, access.getError());
    }
}


TEST_F(DatabaseTest, Database)
{
    // empty ddhbin
    {
        Database db(NULL);
        EXPECT_EQ(LSREngineError(LSR_DB_DDHBIN_EMPTY), db.getError());
    }
    // invalid ddhbin
    {
        U8 buf[] = { 1, 4, 55 };
        Database db(reinterpret_cast<DDHType*>(&buf));
        EXPECT_EQ(LSREngineError(LSR_DB_DDHBIN_VERSION_MISMATCH), db.getError());
    }
}

TEST_F(DatabaseTest, getBitmap)
{
    Database db(m_ddh);
    EXPECT_EQ(LSREngineError(LSR_NO_ENGINE_ERROR), db.getError());
    const LsrImage* image = db.getBitmap(1).getData();
    ASSERT_TRUE(image != NULL);
    EXPECT_EQ(102u, image->getWidth());
    EXPECT_EQ(68u, image->getHeight());
    EXPECT_EQ(LsrImageTypes::PIXEL_FORMAT_BGRA8888, image->getPixelFormat());
    const U8* pixelData = static_cast<const U8*>(image->getPixelData());
    const U8 expect[] = { 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff };
    ASSERT_THAT(std::vector<U8>(pixelData, pixelData + sizeof(expect)),
        ::testing::ElementsAreArray(expect));
    EXPECT_TRUE(pixelData != NULL);
}

TEST_F(DatabaseTest, panelDatabase)
{
    const Area panelArea(10, 153, 380, 224);
    const Area breakArea(20, 2, 119, 70);
    Database db(m_ddh);
    EXPECT_EQ(LSREngineError(LSR_NO_ENGINE_ERROR), db.getError());

    const PanelDatabaseType* panelDB = db.getDdh()->GetPanelDatabase();
    EXPECT_EQ(2u, panelDB->GetPanelCount());
    // Content Panel
    const PanelType* contentPanel = panelDB->GetPanel(0);
    EXPECT_TRUE(contentPanel != NULL);
    EXPECT_EQ(panelArea, Area(contentPanel->GetArea()));
    EXPECT_TRUE(contentPanel->GetVisible()->GetBoolean());
    EXPECT_EQ(2u, contentPanel->GetFieldCount());

    // Icon1
    const StaticBitmapFieldType* field1 = contentPanel->GetField(0)->GetStaticBitmapField();
    EXPECT_TRUE(NULL == contentPanel->GetField(0)->GetReferenceBitmapField());
    EXPECT_TRUE(field1 != NULL);
    EXPECT_FALSE(field1->GetVisible()->GetBoolean());
    EXPECT_EQ(breakArea, Area(field1->GetArea()));
    EXPECT_EQ(3u, field1->GetBitmap()->GetBitmapId());

    // Reference Panel
    const PanelType* referencePanel = panelDB->GetPanel(1);
    EXPECT_TRUE(referencePanel != NULL);
    EXPECT_EQ(panelArea, Area(referencePanel->GetArea()));
    EXPECT_TRUE(referencePanel->GetVisible()->GetBoolean());
    EXPECT_EQ(2u, referencePanel->GetFieldCount());

    // Break
    const ReferenceBitmapFieldType* refBreak = referencePanel->GetField(0)->GetReferenceBitmapField();
    EXPECT_TRUE(NULL == referencePanel->GetField(0)->GetStaticBitmapField()); // bad type
    EXPECT_TRUE(refBreak != NULL);
    EXPECT_FALSE(refBreak->GetVisible()->GetBoolean());
    EXPECT_EQ(breakArea, Area(refBreak->GetArea()));
    EXPECT_EQ(4U, refBreak->GetBitmap()->GetBitmapId());

    // Airbag
    const ReferenceBitmapFieldType* refAirbag = referencePanel->GetField(1)->GetReferenceBitmapField();
    EXPECT_TRUE(refAirbag != NULL);

    EXPECT_TRUE(NULL == panelDB->GetPanel(2U));
    EXPECT_TRUE(NULL == referencePanel->GetField(2U));
}

TEST_F(DatabaseTest, bitmapDatabase)
{
    Database db(m_ddh);
    EXPECT_EQ(LSREngineError(LSR_NO_ENGINE_ERROR), db.getError());
    const BitmapDatabaseType* bitmapDB = db.getDdh()->GetBitmapDatabase();
    EXPECT_EQ(5U, bitmapDB->GetBitmapCount());
    EXPECT_TRUE(NULL == bitmapDB->GetBitmap(5U));
    const BitmapType* bitmap = bitmapDB->GetBitmap(0U);
    EXPECT_EQ(1U, bitmap->GetSkinnedBitmapCount());
    EXPECT_TRUE(NULL == bitmap->GetSkinnedBitmap(1U));
    const SkinnedBitmapType* skinned = bitmap->GetSkinnedBitmap(0U);
    const BitmapStateDefinitionType* state = skinned->GetDefault();
    EXPECT_EQ(1U, state->GetStateBitmapId());
    EXPECT_EQ(68U, state->GetFile()->getHeight());
    EXPECT_EQ(102U, state->GetFile()->getWidth());
}

TEST_F(DatabaseTest, ExpressionTermType_none)
{
    const ExpressionTermType term = {
        ExpressionTermType::NONE,
        0,
        NULL
    };

    EXPECT_EQ(0U, term.GetBitmapId());
    EXPECT_FALSE(term.GetBoolean());
}

