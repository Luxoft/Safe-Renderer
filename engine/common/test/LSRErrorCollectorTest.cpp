/******************************************************************************
**
**   File:        LSRErrorCollectorTest.cpp
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

#include "LSRErrorCollector.h"
#include "gtest/gtest.h"

using lsr::LSRErrorCollector;

TEST(LSRErrorCollectorTest, base)
{
    LSRErrorCollector err = LSR_NO_ENGINE_ERROR;
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, err.get());
    err = LSR_ERR_DATASTATUS_INCONSISTENT;
    EXPECT_EQ(LSR_ERR_DATASTATUS_INCONSISTENT, err.get());
    err = LSR_NO_ENGINE_ERROR;
    EXPECT_EQ(LSR_ERR_DATASTATUS_INCONSISTENT, err.get());
}

