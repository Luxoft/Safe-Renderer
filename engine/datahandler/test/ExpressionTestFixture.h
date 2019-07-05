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
#include "TestDataContext.h"

#include <ExpressionTermTypeFactory.h>
#include <ExpressionTypeFactory.h>
#include <BitmapIdTableTypeFactory.h>
#include <EnumerationBitmapMapTypeFactory.h>

#include <IDataHandler.h>

#include <gtest/gtest.h>

class ExpressionTestFixture : public ::testing::Test
{
protected:
    ExpressionTestFixture()
    {
        m_context.setHandler(&m_dataHandler);
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

    void corruptHandler()
    {
        m_context.setHandler(NULL);
    }

    MockDataHandler m_dataHandler;
    TestDataContext m_context;
    ExpressionTermTypeFactory m_termFactory;
};

#endif // LUXOFTSAFERENDERER_EXPRESSIONTESTFIXTURE_H
