/******************************************************************************
**
**   File:        WidgetPoolHelper.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
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

#include <PscLimits.h>

#include <AreaType.h>
#include <ResourceBuffer.h>
#include <DisplaySizeType.h>
#include <Database.h>

#include <TestDataContext.h>
#include <MockDataHandler.h>

#include <DisplayManager.h>
#include <WindowDefinition.h>

WidgetPoolHelper::WidgetPoolHelper(psc::WidgetPool& widgetPool)
    : m_widgetPool(widgetPool)
{}

psc::BitmapField* WidgetPoolHelper::fillUpWithBitmaps(const psc::StaticBitmapFieldType* type,
                                                               psc::Database db,
                                                               psc::DataContext* context)
{
    psc::BitmapField* field = NULL;
    psc::PSCErrorCollector error(PSC_NO_ERROR);
    for (U8 i = 0U; i < MAX_BITMAPS_COUNT; ++i)
    {
        field = psc::BitmapField::create(m_widgetPool,
                                         db,
                                         type,
                                         context,
                                         error);
    }

    return field;
}

psc::ReferenceBitmapField* WidgetPoolHelper::fillUpWithReferenceBitmaps(
                                                               const psc::ReferenceBitmapFieldType* type,
                                                               psc::Database db,
                                                               psc::DataContext* context)
{
    psc::ReferenceBitmapField* field = NULL;
    psc::PSCErrorCollector error(PSC_NO_ERROR);
    for (U8 i = 0U; i < MAX_REFERENCE_BITMAPS_COUNT; ++i)
    {
        field = psc::ReferenceBitmapField::create(m_widgetPool,
                                                  db,
                                                  type,
                                                  context,
                                                  error);
    }

    return field;
}

psc::Panel* WidgetPoolHelper::fillUpWithPanels(const psc::PanelType* type,
                                                        psc::Database db,
                                                        psc::DataContext* context)
{
    psc::Panel* panel = NULL;
    psc::PSCErrorCollector error(PSC_NO_ERROR);
    for (U8 i = 0U; i < MAX_PANELS_COUNT; ++i)
    {
        panel = psc::Panel::create(m_widgetPool,
                                   db,
                                   type,
                                   context,
                                   error);
    }

    return panel;
}

psc::Frame* WidgetPoolHelper::fillUpWithFrames(const psc::Database& db,
                                                        psc::FrameId frameId,
                                                        psc::Window* parent,
                                                        psc::DataContext* context)
{
    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::Frame* frame = NULL;
    for (U8 i = 0U; i < MAX_FRAMES_COUNT; ++i)
    {
        frame = psc::Frame::create(m_widgetPool,
                                   db,
                                   frameId,
                                   parent,
                                   context,
                                   error);
    }

    return frame;
}

psc::Window* WidgetPoolHelper::fillUpWithWindows(const psc::Database& db,
                                                          psc::DisplayManager& dsp,
                                                          const psc::WindowDefinition& winDef,
                                                          psc::DataContext* context)
{
    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::Window* window = NULL;
    for (U8 i = 0U; i < MAX_WINDOWS_COUNT; ++i)
    {
        window = psc::Window::create(m_widgetPool,
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
    psc::AreaType area;
    framehandlertests::DdhStaticBitmapFieldBuilder builder;
    builder.create(area, true, 23U);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    psc::ResourceBuffer binBuffer;
    psc::ResourceBuffer imgBuffer;
    psc::Database db(binBuffer, imgBuffer);

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::BitmapField* field =
        psc::BitmapField::create(m_widgetPool,
                                 db,
                                 builder.getDdh(),
                                 &context,
                                 error);

    return NULL == field;
}

bool WidgetPoolHelper::isReferenceBitMapPoolFilled() const
{
    psc::AreaType area;
    framehandlertests::DdhReferenceBitmapFieldBuilder builder;
    builder.create(32U, area, true, 23U);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    psc::ResourceBuffer binBuffer;
    psc::ResourceBuffer imgBuffer;
    psc::Database db(binBuffer, imgBuffer);

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::ReferenceBitmapField* field =
        psc::ReferenceBitmapField::create(m_widgetPool,
                                          db,
                                          builder.getDdh(),
                                          &context,
                                          error);

    return NULL == field;
}

bool WidgetPoolHelper::isPanelPoolFilled() const
{
    psc::AreaType area;
    framehandlertests::DdhPanelBuilder builder;
    builder.create(area, true, 0U);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    psc::ResourceBuffer binBuffer;
    psc::ResourceBuffer imgBuffer;
    psc::Database db(binBuffer, imgBuffer);

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::Panel* panel =
        psc::Panel::create(m_widgetPool,
                           db,
                           builder.getDdh(),
                           &context,
                           error);

    return NULL == panel;
}

bool WidgetPoolHelper::isFramePoolFilled() const
{
    psc::AreaType area;
    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.create(area, true, 2U);

    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    psc::DisplaySizeType displaySize;

    framehandlertests::DdhBuilder ddhBuilder;
    ddhBuilder.create(panelBuilder, pageBuilder, displaySize);

    psc::ResourceBuffer binBuffer(ddhBuilder.getDdh(), ddhBuilder.getSize());
    psc::ResourceBuffer imgBuffer;
    psc::Database db(binBuffer, imgBuffer);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::Frame* frame =
        psc::Frame::create(m_widgetPool,
                           db,
                           1U,
                           NULL,
                           &context,
                           error);

    return NULL == frame;
}

bool WidgetPoolHelper::isWindowPoolFilled() const
{
    psc::AreaType area;
    psc::DisplaySizeType displaySize;
    psc::DisplayManager dm;
    psc::WindowDefinition winDef;
    framehandlertests::DdhPanelBuilder panelBuilder;
    panelBuilder.create(area, true, 2U);

    framehandlertests::DdhPageBuilder pageBuilder;
    pageBuilder.create(1U, 1U);

    framehandlertests::DdhBuilder ddhBuilder;
    ddhBuilder.create(panelBuilder, pageBuilder, displaySize);

    psc::ResourceBuffer binBuffer(ddhBuilder.getDdh(), ddhBuilder.getSize());
    psc::ResourceBuffer imgBuffer;
    psc::Database db(binBuffer, imgBuffer);

    MockDataHandler dataHandler;
    TestDataContext context;
    context.setHandler(&dataHandler);

    psc::PSCErrorCollector error(PSC_NO_ERROR);
    psc::Window* window =
        psc::Window::create(m_widgetPool,
                            db,
                            dm,
                            winDef,
                            &context,
                            error);

    return NULL == window;
}
