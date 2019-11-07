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

#include "MockDataHandler.h"

#include <IDataHandler.h>
#include <DataContext.h>

#include <gtest/gtest.h>

class ExpressionTestFixture : public ::testing::Test
{
protected:
    ExpressionTestFixture()
        : m_dataHandler()
        , m_context(m_dataHandler)
    {
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

    MockDataHandler m_dataHandler;
    lsr::DataContext m_context;
};

#endif // LUXOFTSAFERENDERER_EXPRESSIONTESTFIXTURE_H
