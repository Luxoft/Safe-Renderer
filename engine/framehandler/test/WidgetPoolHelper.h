#ifndef POPULUSSC_WIDGETPOOLHELPER_H
#define POPULUSSC_WIDGETPOOLHELPER_H

/******************************************************************************
**
**   File:        WidgetPoolHelper.h
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

#include <WidgetPool.h>

#include <BitmapField.h>
#include <Panel.h>
#include <Frame.h>
#include <Window.h>

class WidgetPoolHelper
{
public:
    WidgetPoolHelper(psc::WidgetPool& widgetPool);

    /**
     * Fill up storage with appropriate objects.
     */
    psc::BitmapField* fillUpWithBitmaps(const psc::StaticBitmapFieldType* type,
                                        psc::Database db,
                                        psc::DataContext* context);
    psc::ReferenceBitmapField* fillUpWithReferenceBitmaps(const psc::ReferenceBitmapFieldType* type,
                                                          psc::Database db,
                                                          psc::DataContext* context);
    psc::Panel* fillUpWithPanels(const psc::PanelType* type,
                                 psc::Database db,
                                 psc::DataContext* context);
    psc::Frame* fillUpWithFrames(const psc::Database& db,
                                 psc::FrameId frameId,
                                 psc::Window* parent,
                                 psc::DataContext* context);
    psc::Window* fillUpWithWindows(const psc::Database& db,
                                   psc::DisplayManager& dsp,
                                   const psc::WindowDefinition& winDef,
                                   psc::DataContext* context);

    /**
     * return true if appropriate storage is filled.
     */
    bool isBitMapPoolFilled() const;
    bool isReferenceBitMapPoolFilled() const;
    bool isPanelPoolFilled() const;
    bool isFramePoolFilled() const;
    bool isWindowPoolFilled() const;

private:
    psc::WidgetPool& m_widgetPool;
};

#endif // POPULUSSC_WIDGETPOOLHELPER_H
