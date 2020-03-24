/******************************************************************************
**
**   File:        DataStatusTest.cpp
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

#include <DataStatus.h>

#include <LsrTypes.h>

#include <gtest/gtest.h>

using namespace lsr;

TEST(DataStatusTest, TestDefaultConstructor)
{
    DataStatus value;

    EXPECT_TRUE(value == DataStatus(DataStatus::NOT_AVAILABLE));
}

TEST(DataStatusTest, TestOpearatorEqualReturnTrue)
{
    DataStatus value1(DataStatus::INVALID);
    DataStatus value2(DataStatus::INVALID);

    EXPECT_TRUE(value1 == value2);
}

TEST(DataStatusTest, TestOpearatorEqualReturnFalse)
{
    DataStatus value1(DataStatus::INVALID);
    DataStatus value2(DataStatus::NOT_AVAILABLE);

    EXPECT_FALSE(value1 == value2);
}

TEST(DataStatusTest, TestOpearatorNotEqualReturnTrue)
{
    DataStatus value1(DataStatus::INVALID);
    DataStatus value2(DataStatus::NOT_AVAILABLE);

    EXPECT_TRUE(value1 != value2);
}

TEST(DataStatusTest, TestOpearatorNotEqualReturnFalse)
{
    DataStatus value1(DataStatus::INVALID);
    DataStatus value2(DataStatus::INVALID);

    EXPECT_FALSE(value1 != value2);
}

TEST(DataStatusTest, TestGetValue)
{
    DataStatus value(DataStatus::INVALID);

    EXPECT_EQ(static_cast<U32>(DataStatus::INVALID), value.getValue());
}

TEST(DataStatusTest, TestConvertToLSRErrorRetrunValid)
{
    DataStatus value(DataStatus::VALID);

    EXPECT_EQ(LSR_NO_ENGINE_ERROR, value.convertToLSRError());
}

TEST(DataStatusTest, TestConvertToLSRErrorRetrunInValid)
{
    DataStatus value(DataStatus::INVALID);

    EXPECT_EQ(LSR_ERR_DATASTATUS_INVALID, value.convertToLSRError());
}

TEST(DataStatusTest, TestConvertToLSRErrorRetrunNotAvaiable)
{
    DataStatus value(DataStatus::NOT_AVAILABLE);

    EXPECT_EQ(LSR_ERR_DATASTATUS_NOT_AVAILABLE, value.convertToLSRError());
}

TEST(DataStatusTest, TestConvertToLSRErrorRetrunInconsistent)
{
    DataStatus value(DataStatus::INCONSISTENT);

    EXPECT_EQ(LSR_ERR_DATASTATUS_INCONSISTENT, value.convertToLSRError());
}

TEST(DataStatusTest, TestConvertToLSRErrorRetrunWrongData)
{
    DataStatus value(static_cast<DataStatus::Enum>(0xAAAA));

    EXPECT_EQ(LSR_ERR_DATASTATUS_INCONSISTENT, value.convertToLSRError());
}
