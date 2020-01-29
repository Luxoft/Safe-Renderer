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

#include <LSRLimits.h>

#include <AreaType.h>
#include <ResourceBuffer.h>
#include <DisplaySizeType.h>
#include <Database.h>

#include <MockDataHandler.h>

#include <DisplayManager.h>
#include <WindowDefinition.h>

#include <AreaType.h>
#include <ExpressionTermType.h>
#include <StaticBitmapFieldType.h>
#include <ReferenceBitmapFieldType.h>
#include <PanelType.h>

#include <Telltales.hpp>

using namespace lsr;

WidgetPoolHelper::WidgetPoolHelper(lsr::WidgetPool& widgetPool)
    : m_widgetPool(widgetPool)
{}

lsr::BitmapField* WidgetPoolHelper::fillUpWithBitmaps(const lsr::StaticBitmapFieldType* type,
                                                               lsr::Database db,
                                                               lsr::DataContext* context)
{
    lsr::BitmapField* field = NULL;
    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
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
    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
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
    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
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
    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
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
    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
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
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    StaticBitmapFieldType bmpField = { &area, &visible, &bmp };

    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(Telltales::getDDH());

    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
    lsr::BitmapField* field =
        lsr::BitmapField::create(m_widgetPool,
                                 db,
                                 &bmpField,
                                 &context,
                                 error);

    return NULL == field;
}

bool WidgetPoolHelper::isReferenceBitMapPoolFilled() const
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    ReferenceBitmapFieldType bmpField = { 32U, &area, &visible, &bmp };

    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(Telltales::getDDH());

    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
    lsr::ReferenceBitmapField* field =
        lsr::ReferenceBitmapField::create(m_widgetPool,
                                          db,
                                          &bmpField,
                                          &context,
                                          error);

    return NULL == field;
}

bool WidgetPoolHelper::isPanelPoolFilled() const
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType tpanel = { &area, &visible, NULL, 0 };

    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(Telltales::getDDH());

    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
    lsr::Panel* panel =
        lsr::Panel::create(m_widgetPool,
                           db,
                           &tpanel,
                           &context,
                           error);

    return NULL == panel;
}

bool WidgetPoolHelper::isFramePoolFilled() const
{
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(Telltales::getDDH());

    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
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
    lsr::DisplayManager dm;
    lsr::WindowDefinition winDef;
    lsr::ResourceBuffer imgBuffer;
    lsr::Database db(Telltales::getDDH());

    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
    lsr::Window* window =
        lsr::Window::create(m_widgetPool,
                            db,
                            dm,
                            winDef,
                            &context,
                            error);

    return NULL == window;
}
