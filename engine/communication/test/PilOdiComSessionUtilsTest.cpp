/******************************************************************************
**
**   File:        PilOdiComSessionUtilsTest.cpp
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

#include "gtest/gtest.h"
#include "PilMsgTransmitter.h"


namespace lsr
{

TEST(PilOdiComSessionUtilsTest, convertErrorPil2LsrTest)
{
    EXPECT_TRUE(convertErrorPil2Lsr(PIL_NO_ERROR) == LSR_NO_ERROR);
    EXPECT_TRUE(convertErrorPil2Lsr(PIL_NOT_INITIALIZED) == LSR_PIL_NOT_INITIALIZED);
    EXPECT_TRUE(convertErrorPil2Lsr(PIL_MBOX_NOT_INITIALIZED) == LSR_PIL_MBOX_NOT_INITIALIZED);
    EXPECT_TRUE(convertErrorPil2Lsr(PIL_MBOX_INVALID) == LSR_PIL_MBOX_INVALID);
    EXPECT_TRUE(convertErrorPil2Lsr(PIL_BUFFER_OVERFLOW) == LSR_PIL_BUFFER_OVERFLOW);
    EXPECT_TRUE(convertErrorPil2Lsr(PIL_INVALID_MSG) == LSR_PIL_INVALID_MSG);
    EXPECT_TRUE(convertErrorPil2Lsr(PIL_UNKNOWN_ERROR) == LSR_UNKNOWN_ERROR);
    EXPECT_TRUE(convertErrorPil2Lsr(static_cast<PILError>(255)) == LSR_UNKNOWN_ERROR);
}

}
