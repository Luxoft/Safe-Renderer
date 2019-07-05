/******************************************************************************
**
**   File:        DataStatusTest.cpp
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

    EXPECT_EQ(LSR_NO_ERROR, value.convertToLSRError());
}

TEST(DataStatusTest, TestConvertToLSRErrorRetrunInValid)
{
    DataStatus value(DataStatus::INVALID);

    EXPECT_EQ(LSR_DATASTATUS_INVALID, value.convertToLSRError());
}

TEST(DataStatusTest, TestConvertToLSRErrorRetrunNotAvaiable)
{
    DataStatus value(DataStatus::NOT_AVAILABLE);

    EXPECT_EQ(LSR_DATASTATUS_NOT_AVAIABLE, value.convertToLSRError());
}

TEST(DataStatusTest, TestConvertToLSRErrorRetrunInconsistent)
{
    DataStatus value(DataStatus::INCONSISTENT);

    EXPECT_EQ(LSR_DATASTATUS_INCONSISTENT, value.convertToLSRError());
}

TEST(DataStatusTest, TestConvertToLSRErrorRetrunWrongData)
{
    DataStatus value(static_cast<DataStatus::Enum>(0xAAAA));

    EXPECT_EQ(LSR_DATASTATUS_INCONSISTENT, value.convertToLSRError());
}
