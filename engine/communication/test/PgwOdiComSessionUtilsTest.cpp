/******************************************************************************
**
**   File:        PgwOdiComSessionUtilsTest.cpp
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

#include "gtest/gtest.h"
#include "PgwMsgTransmitter.h"


namespace psc
{

TEST(PgwOdiComSessionUtilsTest, convertErrorPgw2PscTest)
{
    EXPECT_TRUE(convertErrorPgw2Psc(PGW_NO_ERROR) == PSC_NO_ERROR);
    EXPECT_TRUE(convertErrorPgw2Psc(PGW_NOT_INITIALIZED) == PSC_PGW_NOT_INITIALIZED);
    EXPECT_TRUE(convertErrorPgw2Psc(PGW_MBOX_NOT_INITIALIZED) == PSC_PGW_MBOX_NOT_INITIALIZED);
    EXPECT_TRUE(convertErrorPgw2Psc(PGW_MBOX_INVALID) == PSC_PGW_MBOX_INVALID);
    EXPECT_TRUE(convertErrorPgw2Psc(PGW_BUFFER_OVERFLOW) == PSC_PGW_BUFFER_OVERFLOW);
    EXPECT_TRUE(convertErrorPgw2Psc(PGW_INVALID_MSG) == PSC_PGW_INVALID_MSG);
    EXPECT_TRUE(convertErrorPgw2Psc(PGW_UNKNOWN_ERROR) == PSC_UNKNOWN_ERROR);
    EXPECT_TRUE(convertErrorPgw2Psc(static_cast<PGWError>(255)) == PSC_UNKNOWN_ERROR);
}

}
