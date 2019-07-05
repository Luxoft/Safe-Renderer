/******************************************************************************
**
**   File:        WidgetPoolHelper.cpp
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

#include "WidgetPoolHelper.h"
#include "DdhStaticBitmapFieldBuilder.h"
#include "DdhReferenceBitmapFieldBuilder.h"
#include "DdhPanelBuilder.h"
#include "DdhPageBuilder.h"
#include "DdhBuilder.h"

#include <LsrLimits.h>

#include <AreaType.h>
#include <ResourceBuffer.h>
#include <DisplaySizeType.h>
#include <Database.h>

#include <TestDataContext.h>
#include <MockDataHandler.h>

#include <DisplayManager.h>
#include <WindowDefinition.h>

WidgetPoolHelper::WidgetPoolHelper(lsr::WidgetPool& widgetPool)
    : m_widgetPool(widgetPool)
{}

lsr::BitmapField* WidgetPoolHelper::fillUpWithBitmaps(const lsr::StaticBitmapFieldType* type,
                                                               lsr::Database db,
                                                               lsr::DataContext* context)
{
    lsr::BitmapField* field = NULL;
    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    for (U8 i = 0U; i < MAX_BITMAPS_COUNT; ++i)
    {
        field = lsr::BitmapField::create(m_widgetPool,
                                         db,
                                         type,
                                         context,
                                         error);
    }

    return field;
}

lsr::ReferenceBitmapField* WidgetPoolHelper::fillUpWithReferenceBitmaps(
                                                               const lsr::ReferenceBitmapFieldType* type,
                                                               lsr::Database db,
                                                               lsr::DataContext* context)
{
    lsr::ReferenceBitmapField* field = NULL;
    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    for (U8 i = 0U; i < MAX_REFERENCE_BITMAPS_COUNT; ++i)
    {
        field = lsr::ReferenceBitmapField::create(m_widgetPool,
                                                  db,
                                                  type,
                                                  context,
                                                  error);
    }

    return field;
}

lsr::Panel* WidgetPoolHelper::fillUpWithPanels(const lsr::PanelType* type,
                                                        lsr::Database db,
                                                        lsr::DataContext* context)
{
    lsr::Panel* panel = NULL;
    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    for (U8 i = 0U; i < MAX_PANELS_COUNT; ++i)
    {
        panel = lsr::Panel::create(m_widgetPool,
                                   db,
                                   type,
                                   context,
                                   error);
    }

    return panel;
}

lsr::Frame* WidgetPoolHelper::fillUpWithFrames(const lsr::Database& db,
                                                        lsr::FrameId frameId,
                                                        lsr::Window* parent,
                                                        lsr::DataContext* context)
{
    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::Frame* frame = NULL;
    for (U8 i = 0U; i < MAX_FRAMES_COUNT; ++i)
    {
        frame = lsr::Frame::create(m_widgetPool,
                                   db,
                                   frameId,
                                   parent,
                                   context,
                                   error);
    }

    return frame;
}

lsr::Window* WidgetPoolHelper::fillUpWithWindows(const lsr::Database& db,
                                                          lsr::DisplayManager& dsp,
                                                          const lsr::WindowDefinition& winDef,
                                                          lsr::DataContext* context)
{
    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::Window* window = NULL;
    for (U8 i = 0U; i < MAX_WINDOWS_COUNT; ++i)
    {
        window = lsr::Window::create(m_widgetPool,
                                    db,
                                    dsp,
                                    winDef,
                                    context,
                                    error);
    }

    return window;
}

bool WidgetPoolHelper::isBitMapPoolFilled() const
{
    lsr::AreaType area;
    framehandlertests::DdhStaticBitmapFieldBuilder builder;
    builder.create(area, true, 23U);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    lsr::ResourceBuffer binBuffer;
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::BitmapField* field =
        lsr::BitmapField::create(m_widgetPool,
                                 db,
                                 builder.getDdh(),
                                 &context,
                                 error);

    return NULL == field;
}

bool WidgetPoolHelper::isReferenceBitMapPoolFilled() const
{
    lsr::AreaType area;
    framehandlertests::DdhReferenceBitmapFieldBuilder builder;
    builder.create(32U, area, true, 23U);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    lsr::ResourceBuffer binBuffer;
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::ReferenceBitmapField* field =
        lsr::ReferenceBitmapField::create(m_widgetPool,
                                          db,
                                          builder.getDdh(),
                                          &context,
                                          error);

    return NULL == field;
}

bool WidgetPoolHelper::isPanelPoolFilled() const
{
    lsr::AreaType area;
    framehandlertests::DdhPanelBuilder builder;
    builder.create(area, true, 0U);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    lsr::ResourceBuffer binBuffer;
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::Panel* panel =
        lsr::Panel::create(m_widgetPool,
                           db,
                           builder.getDdh(),
                           &context,
                           error);

    return NULL == panel;
}

bool WidgetPoolHelper::isFramePoolFilled() const
{
    lsr::AreaType area;
    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.create(area, true, 2U);

    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    lsr::DisplaySizeType displaySize;

    framehandlertests::DdhBuilder ddhBuilder;
    ddhBuilder.create(panelBuilder, pageBuilder, displaySize);

    lsr::ResourceBuffer binBuffer(ddhBuilder.getDdh(), ddhBuilder.getSize());
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::Frame* frame =
        lsr::Frame::create(m_widgetPool,
                           db,
                           1U,
                           NULL,
                           &context,
                           error);

    return NULL == frame;
}

bool WidgetPoolHelper::isWindowPoolFilled() const
{
    lsr::AreaType area;
    lsr::DisplaySizeType displaySize;
    lsr::DisplayManager dm;
    lsr::WindowDefinition winDef;
    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.create(area, true, 2U);

    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhBuilder ddhBuilder;
    ddhBuilder.create(panelBuilder, pageBuilder, displaySize);

    lsr::ResourceBuffer binBuffer(ddhBuilder.getDdh(), ddhBuilder.getSize());
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(binBuffer, imgBuffer);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::Window* window =
        lsr::Window::create(m_widgetPool,
                            db,
                            dm,
                            winDef,
                            &context,
                            error);

    return NULL == window;
}
