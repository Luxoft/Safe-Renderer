/******************************************************************************
**
**   File:        FonBinReaderTest.cpp
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
#include "FonBinReader.h"
#include "FonBinWriter.h"
#include <string>

using lsr::FonBinReader;
using lsr::ResourceBuffer;
using test::FonBinWriter;

namespace
{
    const std::string img1 = "aaaaaa/AAAAA.png";
    const std::string img2 = "bbbbbb/BBBBB.png";
    const std::string img3 = "cccccc/CCCCC.png";
}

class FonBinReaderTest : public ::testing::Test
{
public:
    FonBinReader reader;
    U8 fonbin1[1024];

    FonBinReaderTest()
    {
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

    void Verify()
    {
        VerifyImageTable();
    }

    void VerifyImageTable()
    {
        FonBinReader::ImageDataTable imgTable = reader.getImageDataTable();
        EXPECT_EQ(3u, imgTable.GetSize());
        EXPECT_EQ(110, imgTable.GetAttributes(0).height);
        EXPECT_EQ(220, imgTable.GetAttributes(1).height);
        EXPECT_EQ(330, imgTable.GetAttributes(2).height);
        U32 size = 0u;
        const U8* ptr = NULL;
        ptr = imgTable.ReadImage(0, size);
        EXPECT_EQ(img1, std::string((const char*)ptr, size));
        ptr = imgTable.ReadImage(1, size);
        EXPECT_EQ(img2, std::string((const char*)ptr, size));
        ptr = imgTable.ReadImage(2, size);
        EXPECT_EQ(img3, std::string((const char*)ptr, size));
    }
};


TEST_F(FonBinReaderTest, defaultConstruct)
{
    EXPECT_EQ(0u, reader.getSkinBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getStateBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getImageDataTable().GetSize());
}

TEST_F(FonBinReaderTest, emptyBuffer)
{
    EXPECT_EQ(FonBinReader::FILE_OPEN_ERROR, reader.setFonBin(ResourceBuffer(), 42));
    EXPECT_EQ(0u, reader.getSkinBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getStateBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getImageDataTable().GetSize());
}

TEST_F(FonBinReaderTest, smallBuffer)
{
    U8 fonbin[] = {0, 0};
    EXPECT_EQ(FonBinReader::FILE_TOO_SMALL_TO_FIT_HEADER, reader.setFonBin(ResourceBuffer(fonbin, sizeof(fonbin)), 42));
    EXPECT_EQ(0u, reader.getSkinBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getStateBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getImageDataTable().GetSize());
}

TEST_F(FonBinReaderTest, versionError)
{
    U8 fonbin[1024];
    memset(fonbin, 0, sizeof(fonbin));
    EXPECT_EQ(FonBinReader::VERSION_ERROR, reader.setFonBin(ResourceBuffer(fonbin, sizeof(fonbin)), 0u));

    EXPECT_EQ(0u, reader.getSkinBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getStateBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getImageDataTable().GetSize());
}

TEST_F(FonBinReaderTest, checksumError)
{
    U8 fonbin[1024];
    memset(fonbin, 0, sizeof(fonbin));
    fonbin[1] = 2; // fonbin version
    EXPECT_EQ(FonBinReader::CHECKSUM_ERROR, reader.setFonBin(ResourceBuffer(fonbin, sizeof(fonbin)), 42u));

    EXPECT_EQ(0u, reader.getSkinBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getStateBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getImageDataTable().GetSize());
}

TEST_F(FonBinReaderTest, emptyTables)
{
    FonBinWriter writer(fonbin1, sizeof(fonbin1));

    EXPECT_EQ(FonBinReader::OK, reader.setFonBin(ResourceBuffer(fonbin1, sizeof(fonbin1)), 0u));
    EXPECT_EQ(0u, reader.getSkinBitmapTable().GetSize());
    EXPECT_EQ(0xffff, reader.getSkinBitmapTable().GetSkinBitmapIndex(1, 0));
    EXPECT_EQ(0u, reader.getStateBitmapTable().GetSize());
    EXPECT_EQ(0u, reader.getImageDataTable().GetSize());
}

/// 3 images
TEST_F(FonBinReaderTest, images_single)
{
    FonBinWriter writer(fonbin1, sizeof(fonbin1));
    writer.AddImage(img1, 100, 110);
    writer.AddImage(img2, 200, 220);
    writer.AddImage(img3, 300, 330);
    reader.setFonBin(ResourceBuffer(fonbin1, sizeof(fonbin1)), 0u);
    Verify();
}

