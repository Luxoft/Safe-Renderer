#ifndef POPULUSSC_WIDGETPOOLCORRUPTER_H
#define POPULUSSC_WIDGETPOOLCORRUPTER_H

/******************************************************************************
**
**   File:        WidgetPoolCorrupter.h
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

#include <WidgetPool.h>
#include <ReferenceBitmapField.h>
#include <BitmapField.h>
#include <Panel.h>
#include <Frame.h>
#include <Window.h>

#include <PoolCorrupter.h>

class WidgetPoolCorrupter
{
public:
    WidgetPoolCorrupter(psc::WidgetPool* pool)
        : m_frameCorrupter(reinterpret_cast<FramePoolCorrupter&>(pool->framePool()))
        , m_panelCorrupter(reinterpret_cast<PanelPoolCorrupter&>(pool->panelPool()))
        , m_bitmapCorrupter(reinterpret_cast<BitmapFieldPoolCorrupter&>(pool->bitmapFieldPool()))
        , m_refBitmapCorrupter(reinterpret_cast<ReferenceBitmapFieldPoolCorrupter&>(pool->referenceBitmapFieldPool()))
        , m_windowCorrupter(reinterpret_cast<WindowPoolCorrupter&>(pool->windowPool()))
    {
    }

    void corruptBitmapStorage()
    {
        m_bitmapCorrupter.corruptStorage();
    }

    void corruptRefBitmapStorage()
    {
        m_refBitmapCorrupter.corruptStorage();
    }

    void corruptFrameStorage()
    {
        m_frameCorrupter.corruptFreeMarker();
    }

    void corruptPanelStorage()
    {
        m_panelCorrupter.corruptStorage();
    }

    void corruptWindowStorage()
    {
        m_windowCorrupter.corruptFreeMarker();
    }

private:
    typedef PoolCorrupter<psc::Frame, MAX_FRAMES_COUNT, sizeof(P_MAX_ALIGN)> FramePoolCorrupter;
    typedef PoolCorrupter<psc::Panel, MAX_PANELS_COUNT, sizeof(P_MAX_ALIGN)> PanelPoolCorrupter;
    typedef PoolCorrupter<psc::BitmapField, MAX_BITMAPS_COUNT, sizeof(P_MAX_ALIGN)> BitmapFieldPoolCorrupter;
    typedef PoolCorrupter<psc::ReferenceBitmapField, MAX_REFERENCE_BITMAPS_COUNT, sizeof(P_MAX_ALIGN)> ReferenceBitmapFieldPoolCorrupter;
    typedef PoolCorrupter<psc::Window, MAX_WINDOWS_COUNT, sizeof(P_MAX_ALIGN)> WindowPoolCorrupter;

    FramePoolCorrupter& m_frameCorrupter;
    PanelPoolCorrupter& m_panelCorrupter;
    BitmapFieldPoolCorrupter& m_bitmapCorrupter;
    ReferenceBitmapFieldPoolCorrupter& m_refBitmapCorrupter;
    WindowPoolCorrupter& m_windowCorrupter;
};

#endif // POPULUSSC_WIDGETPOOLCORRUPTER_H
