/******************************************************************************
**
**   File:        DDHTypeTest.cpp
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

#include "DDHType.h"
#include "PanelDatabaseType.h"

using lsr::DDHType;
using lsr::PanelDatabaseType;


TEST(DDHType, versionCheck)
{
    std::string serializerVersionError = "Data has been serialized with another version of the serializer than what the HMI Engine expects (Expecting Serializer version: 5.5.0)";
    std::string schemaVersionError = "Data has been generated from another schema version than the HMI Engine expects (Expecting Schema Version: 5.5.x)";
    std::string schemaChecksumError = "Data has been generated from a schema version with another checksum than the HMI Engine expects (Expecting Schema checksum: 0xa70903e4)";
    const U32 arbitraryValue = 42;
    {
        DDHType ddh = { 0, 0, 0, 0, NULL, NULL, NULL };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(serializerVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, DDHType::SCHEMA_CHECKSUM, 0, 0, NULL, NULL, NULL };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(serializerVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, arbitraryValue, DDHType::SCHEMA_VERSION, 0, NULL, NULL, NULL };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(serializerVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, arbitraryValue, arbitraryValue, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(schemaVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, DDHType::SCHEMA_CHECKSUM, arbitraryValue, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(schemaVersionError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, arbitraryValue, DDHType::SCHEMA_VERSION, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL };
        EXPECT_FALSE(ddh.IsVersionOK());
        EXPECT_EQ(schemaChecksumError, ddh.GetErrorMessage());
    }
    {
        DDHType ddh = { 0, DDHType::SCHEMA_CHECKSUM, DDHType::SCHEMA_VERSION, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL };
        EXPECT_TRUE(ddh.IsVersionOK());
        EXPECT_EQ(std::string(), ddh.GetErrorMessage());
    }
}

TEST(DDHType, emptyReferences)
{
    DDHType ddh = { 0, DDHType::SCHEMA_CHECKSUM, DDHType::SCHEMA_VERSION, DDHType::SERIALIZER_VERSION, NULL, NULL, NULL };
    EXPECT_TRUE(NULL == ddh.GetPanelDatabase());
    EXPECT_TRUE(NULL == ddh.GetBitmapDatabase());
    EXPECT_TRUE(NULL == ddh.GetHMIGlobalSettings());
}

TEST(DDHType, references)
{
    PanelDatabaseType panelDB = { NULL, 0U };
    DDHType ddh = {
            0, 0, 0, 0, // checksums, versions
            &panelDB, NULL, NULL
    };
    EXPECT_EQ(&panelDB, ddh.GetPanelDatabase());
}

