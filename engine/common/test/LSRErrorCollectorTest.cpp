/******************************************************************************
**
**   File:        LSRErrorCollectorTest.cpp
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

