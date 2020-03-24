#ifndef LUXOFTSAFERENDERER_WIDGETTESTBASE_H
#define LUXOFTSAFERENDERER_WIDGETTESTBASE_H

/******************************************************************************
**
**   File:        WidgetTestBase.h
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

#include "TestCanvas.h"
#include <MockCanvas.h>

#include <AreaType.h>
#include <ReferenceBitmapFieldType.h>
#include <StaticBitmapFieldType.h>
#include <ExpressionTermType.h>
#include <BaseFieldChoiceType.h>
#include <PanelType.h>
#include <ResourceBuffer.h>
#include <HMIGlobalSettingsType.h>
#include <PanelDatabaseType.h>
#include <DDHType.h>
#include <Database.h>

#include <DisplayManager.h>
#include <DisplaySizeType.h>
#include <Color.h>

#include <gtest/gtest.h>

class WidgetTestBase: public testing::Test
{
protected:
    WidgetTestBase();

    void SetUp();
    void TearDown();

    lsr::DisplayManager m_dsp;
    TestCanvas m_canvas;
    unittest::MockCanvas m_mockCanvas;
};

inline WidgetTestBase::WidgetTestBase()
    : m_dsp()
    , m_canvas(m_dsp, 640U, 480U)
{
}

inline void WidgetTestBase::SetUp()
{
    unittest::g_mockCanvas = &m_mockCanvas;
}

inline void WidgetTestBase::TearDown()
{
    unittest::g_mockCanvas = NULL;
}

namespace lsr
{
    inline bool operator==(const StaticBitmap& b1, const StaticBitmap& b2)
    {
        return ((b1.getId() == b2.getId()) && (b1.getData() == b2.getData()));
    }
}

#endif // LUXOFTSAFERENDERER_WIDGETTESTBASE_H
