/******************************************************************************
**
**   File:        DDHTypeTest.cpp
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

#include <gtest/gtest.h>

#include "DDHType.h"

using psc::DDHType;


TEST(DDHType, versionCheck)
{
    const U32 arbitraryValue = 42;
    U8 buf[sizeof(DDHType)] = { 0 };
    DDHType* ddh = reinterpret_cast<DDHType*>(buf);
    EXPECT_FALSE(ddh->IsVersionOK());
    EXPECT_EQ(DDHType::serializerVersionError, ddh->GetErrorMessage());

    ddh->schemaChecksum = DDHType::SCHEMA_CHECKSUM;
    EXPECT_FALSE(ddh->IsVersionOK());
    EXPECT_EQ(DDHType::serializerVersionError, ddh->GetErrorMessage());

    ddh->schemaChecksum = arbitraryValue;
    ddh->schemaVersion = DDHType::SCHEMA_VERSION;
    EXPECT_FALSE(ddh->IsVersionOK());
    EXPECT_EQ(DDHType::serializerVersionError, ddh->GetErrorMessage());

    ddh->schemaChecksum = arbitraryValue;
    ddh->schemaVersion = arbitraryValue;
    ddh->serializerVersion = DDHType::SERIALIZER_VERSION;
    EXPECT_FALSE(ddh->IsVersionOK());
    EXPECT_EQ(DDHType::schemaVersionError, ddh->GetErrorMessage());

    ddh->schemaChecksum = DDHType::SCHEMA_CHECKSUM;
    ddh->schemaVersion = arbitraryValue;
    ddh->serializerVersion = DDHType::SERIALIZER_VERSION;
    EXPECT_FALSE(ddh->IsVersionOK());
    EXPECT_EQ(DDHType::schemaVersionError, ddh->GetErrorMessage());

    ddh->schemaChecksum = arbitraryValue;
    ddh->schemaVersion = DDHType::SCHEMA_VERSION;
    ddh->serializerVersion = DDHType::SERIALIZER_VERSION;
    EXPECT_FALSE(ddh->IsVersionOK());
    EXPECT_EQ(DDHType::schemaChecksumError, ddh->GetErrorMessage());

    ddh->schemaChecksum = DDHType::SCHEMA_CHECKSUM;
    EXPECT_TRUE(ddh->IsVersionOK());
    EXPECT_EQ(std::string(), ddh->GetErrorMessage());
}

TEST(DDHType, emptyReferences)
{
    DDHType ddh = { 0 };
    EXPECT_TRUE(NULL == ddh.GetColorDatabase());
    EXPECT_TRUE(NULL == ddh.GetFUDatabase());
    EXPECT_TRUE(NULL == ddh.GetPageDatabase());
    EXPECT_TRUE(NULL == ddh.GetPanelDatabase());
    EXPECT_TRUE(NULL == ddh.GetSkinDatabase());
    EXPECT_TRUE(NULL == ddh.GetHMIGlobalSettings());
}

TEST(DDHType, references)
{
    DDHType ddh = {
            0, 0, 0, 0, // checksums, versions
            1024, 2048, 3096, 4192, 5120, 6144 // offsets
    };
    uintptr_t base = reinterpret_cast<uintptr_t>(&ddh);
    EXPECT_EQ(base + ddh.colorDatabaseOffset * 4u, reinterpret_cast<uintptr_t>(ddh.GetColorDatabase()));
    EXPECT_EQ(base + ddh.fUDatabaseOffset * 4u, reinterpret_cast<uintptr_t>(ddh.GetFUDatabase()));
    EXPECT_EQ(base + ddh.pageDatabaseOffset * 4u, reinterpret_cast<uintptr_t>(ddh.GetPageDatabase()));
    EXPECT_EQ(base + ddh.panelDatabaseOffset * 4u, reinterpret_cast<uintptr_t>(ddh.GetPanelDatabase()));
    EXPECT_EQ(base + ddh.skinDatabaseOffset * 4u, reinterpret_cast<uintptr_t>(ddh.GetSkinDatabase()));
    EXPECT_EQ(base + ddh.hMIGlobalSettingsOffset * 4u, reinterpret_cast<uintptr_t>(ddh.GetHMIGlobalSettings()));
}

