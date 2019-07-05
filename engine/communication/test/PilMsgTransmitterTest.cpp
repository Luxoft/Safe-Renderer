/******************************************************************************
**
**   File:        PilMsgTransmitterTest.cpp
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
#include "gmock/gmock.h"
#include "OdiTypes.h"
#include "PilMsgTransmitter.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::AtLeast;

namespace lsr
{

class PilMsgTransmitterTest : public ::testing::Test
{
public:
    PilMsgTransmitterTest(){};
};

static PilMsgTransmitter transmitter;

TEST_F(PilMsgTransmitterTest, DynamicAllocation)
{
    int transmittersNumber = 10;
    PilMsgTransmitter* pTransmitter = new PilMsgTransmitter[transmittersNumber];

    for (int i = 0; i < transmittersNumber; ++i)
    {
        for (int j = 0; j < transmittersNumber; ++j)
        {
            pTransmitter[i].setConnection(i,j);
            EXPECT_EQ(i, pTransmitter[i].getFrom());
            EXPECT_EQ(j, pTransmitter[i].getTo());
        }
    }

    delete [] pTransmitter;

    PilMsgTransmitter* pTransmitter1 = new PilMsgTransmitter();

    const U8 expectedFrom = 0;
    const U8 expectedTo = 1;
    pTransmitter1->setConnection(expectedFrom, expectedTo);
    EXPECT_EQ(expectedFrom, pTransmitter1->getFrom());
    EXPECT_EQ(expectedTo, pTransmitter1->getTo());

    delete pTransmitter1;
}

TEST_F(PilMsgTransmitterTest, StaticAllocation)
{
    const U8 expectedFrom = 0;
    const U8 expectedTo = 1;

    transmitter.setConnection(expectedFrom, expectedTo);
    EXPECT_EQ(expectedFrom, transmitter.getFrom());
    EXPECT_EQ(expectedTo, transmitter.getTo());
}

}
