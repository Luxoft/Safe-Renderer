#ifndef LUXOFTSAFERENDERER_WIDGETPOOLHELPER_H
#define LUXOFTSAFERENDERER_WIDGETPOOLHELPER_H

/******************************************************************************
**
**   File:        WidgetPoolHelper.h
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

#include <WidgetPool.h>

#include <BitmapField.h>
#include <Panel.h>
#include <Frame.h>
#include <Window.h>

class WidgetPoolHelper
{
public:
    WidgetPoolHelper(lsr::WidgetPool& widgetPool);

    /**
     * Fill up storage with appropriate objects.
     */
    lsr::BitmapField* fillUpWithBitmaps(const lsr::StaticBitmapFieldType* type,
                                        lsr::Database db,
                                        lsr::DataContext* context);
    lsr::ReferenceBitmapField* fillUpWithReferenceBitmaps(const lsr::ReferenceBitmapFieldType* type,
                                                          lsr::Database db,
                                                          lsr::DataContext* context);
    lsr::Panel* fillUpWithPanels(const lsr::PanelType* type,
                                 lsr::Database db,
                                 lsr::DataContext* context);
    lsr::Frame* fillUpWithFrames(const lsr::Database& db,
                                 lsr::FrameId frameId,
                                 lsr::Window* parent,
                                 lsr::DataContext* context);
    lsr::Window* fillUpWithWindows(const lsr::Database& db,
                                   lsr::DisplayManager& dsp,
                                   const lsr::WindowDefinition& winDef,
                                   lsr::DataContext* context);

    /**
     * return true if appropriate storage is filled.
     */
    bool isBitMapPoolFilled() const;
    bool isReferenceBitMapPoolFilled() const;
    bool isPanelPoolFilled() const;
    bool isFramePoolFilled() const;
    bool isWindowPoolFilled() const;

private:
    lsr::WidgetPool& m_widgetPool;
};

#endif // LUXOFTSAFERENDERER_WIDGETPOOLHELPER_H
