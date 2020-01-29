/******************************************************************************
**
**   File:        DDHTypeTest.cpp
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

#include "DDHType.h"
#include "PanelDatabaseType.h"
#include "PageDatabaseType.h"

using lsr::DDHType;
using lsr::PageDatabaseType;
using lsr::PanelDatabaseType;


TEST(DDHType, versionCheck)
{
    std::string serializerVersionError = "Data has been serialized with another version of the serializer than what the HMI Engine expects (Expecting Serializer version: 5.5.0)";
    std::string schemaVersionError = "Data has been generated from another schema version than the HMI Engine expects (Expecting Schema Version: 5.5.x)";
    std::string schemaChecksumError = "Data has been generated from a schema version with another checksum than the HMI Engine expects (Expecting Schema checksum: 0x9fa75f84)";
    const U32 arbitraryValue = 42;
    {
        DDHType ddh = { 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0U };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(serializerVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, DDHType::SCHEMA_CHECKSUM, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0U };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(serializerVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, arbitraryValue, DDHType::SCHEMA_VERSION, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0U };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(serializerVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, arbitraryValue, arbitraryValue, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL, NULL, NULL, NULL, 0U };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(schemaVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, DDHType::SCHEMA_CHECKSUM, arbitraryValue, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL, NULL, NULL, NULL, 0U };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(schemaVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, arbitraryValue, DDHType::SCHEMA_VERSION, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL, NULL, NULL, NULL, 0U };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(schemaChecksumError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, DDHType::SCHEMA_CHECKSUM, DDHType::SCHEMA_VERSION, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL, NULL, NULL, NULL, 0U };
        EXPECT_TRUE(ddh.IsVersionOK());
        EXPECT_EQ(std::string(), ddh.GetErrorMessage());
    }
}

TEST(DDHType, emptyReferences)
{
    DDHType ddh = { 0, DDHType::SCHEMA_CHECKSUM, DDHType::SCHEMA_VERSION, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL, NULL, NULL, NULL, 0U };
    EXPECT_TRUE(NULL == ddh.GetColorDatabase());
    EXPECT_TRUE(NULL == ddh.GetPageDatabase());
    EXPECT_TRUE(NULL == ddh.GetPanelDatabase());
    EXPECT_TRUE(NULL == ddh.GetSkinDatabase());
    EXPECT_TRUE(NULL == ddh.GetHMIGlobalSettings());
}

TEST(DDHType, references)
{
    PageDatabaseType pageDB = { NULL, 0U };
    PanelDatabaseType panelDB = { NULL, 0U };
    DDHType ddh = {
            0, 0, 0, 0, // checksums, versions
            &pageDB, &panelDB, NULL, NULL, NULL, NULL, 0u
    };
    EXPECT_EQ(&panelDB, ddh.GetPanelDatabase());
    EXPECT_EQ(&pageDB, ddh.GetPageDatabase());
}

