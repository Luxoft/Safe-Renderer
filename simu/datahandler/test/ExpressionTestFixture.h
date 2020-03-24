#ifndef LUXOFTSAFERENDERER_EXPRESSIONTESTFIXTURE_H
#define LUXOFTSAFERENDERER_EXPRESSIONTESTFIXTURE_H

/******************************************************************************
**
**   File:        ExpressionTestFixture.h
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

#include "MockDataHandler.h"

#include <IDataHandler.h>

#include <gtest/gtest.h>

class ExpressionTestFixture : public ::testing::Test
{
protected:
    ExpressionTestFixture()
        : m_dataHandler()
    {
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

    MockDataHandler m_dataHandler;
};

#endif // LUXOFTSAFERENDERER_EXPRESSIONTESTFIXTURE_H
