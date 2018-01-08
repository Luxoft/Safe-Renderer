#ifndef POPULUSSC_WIDGETPOOL_H
#define POPULUSSC_WIDGETPOOL_H

/******************************************************************************
**
**   File:        WidgetPool.h
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

#include "ReferenceBitmapField.h"
#include "BitmapField.h"
#include "Panel.h"
#include "Frame.h"
#include "Window.h"

#include <ddh_defs.h>

#include <Pool.h>
#include <PscLimits.h>
#include <NonCopyable.h>

class WidgetPoolCorrupter;

namespace psc
{

struct PanelType;
struct FieldType;
struct DDHType;
class DataContext;

/**
 * This class contains several @c Pool objects for storing different widget objects
 * (for each widget type - separate @c Pool object).
 * It provides functionality to access to each pool to be able to allocate or deallocate objects.
 *
 * @reqid SW_ENG_069, SW_ENG_075
 */
class WidgetPool : private NonCopyable<WidgetPool>
{
public:
    WidgetPool();

    /**
     * Method return state of the pools.
     *
     * @return @c PSC_POOL_IS_CORRUPTED if any of the pool is corrupted (see @c Pool::checkPool),
     *         @c PSC_NO_ERROR otherwise.
     */
    PSCError getError() const;

private:
    friend Panel* Panel::create(WidgetPool& widgetPool,
                                const Database& db,
                                const PanelType* pDdhPanel,
                                DataContext* pContext,
                                PSCErrorCollector& error);

    friend BitmapField* BitmapField::create(WidgetPool& widgetPool,
                                            const Database& db,
                                            const StaticBitmapFieldType* pDdh,
                                            DataContext* pContext,
                                            PSCErrorCollector& error);

    friend ReferenceBitmapField* ReferenceBitmapField::create(WidgetPool& widgetPool,
                                            const Database& db,
                                            const ReferenceBitmapFieldType* pDdh,
                                            DataContext* pContext,
                                            PSCErrorCollector& error);

    friend Frame* Frame::create(WidgetPool& widgetPool,
                                const Database& db,
                                FrameId frameId,
                                Window* pParent,
                                DataContext* pContext,
                                PSCErrorCollector& error);

    friend Window* Window::create(WidgetPool& widgetPool,
                                  const Database& db,
                                  DisplayManager& dsp,
                                  const WindowDefinition& winDef,
                                  DataContext* pContext,
                                  PSCErrorCollector& error);

    friend PSCError Widget::dispose(WidgetPool& factory, Widget* pWidget);

    typedef Pool<Frame, MAX_FRAMES_COUNT> FramePool;
    typedef Pool<Panel, MAX_PANELS_COUNT> PanelPool;
    typedef Pool<BitmapField, MAX_BITMAPS_COUNT> BitmapFieldPool;
    typedef Pool<ReferenceBitmapField, MAX_REFERENCE_BITMAPS_COUNT> ReferenceBitmapFieldPool;
    typedef Pool<Window, MAX_WINDOWS_COUNT> WindowPool;

    friend class ::WidgetPoolCorrupter;

    /**
     * @return pool for storing @c Frame objects.
     */
    FramePool& framePool();

    /**
     * @return pool for storing @c Panel objects.
     */
    PanelPool& panelPool();

    /**
     * @return pool for storing @c BitmapField objects.
     */
    BitmapFieldPool& bitmapFieldPool();

    /**
     * @return pool for storing @c ReferenceBitmapField objects.
     */
    ReferenceBitmapFieldPool& referenceBitmapFieldPool();

    /**
     * @return pool for storing @c Window objects.
     */
    WindowPool& windowPool();

    FramePool m_framePool;
    PanelPool m_panelPool;
    BitmapFieldPool m_bitmapFieldPool;
    ReferenceBitmapFieldPool m_referenceBitmapFieldPool;
    WindowPool m_windowPool;
};

inline WidgetPool::WidgetPool()
{
}

inline PSCError WidgetPool::getError() const
{
    return (m_framePool.checkPool() &&
            m_panelPool.checkPool() &&
            m_bitmapFieldPool.checkPool() &&
            m_referenceBitmapFieldPool.checkPool() &&
            m_windowPool.checkPool()) ? PSC_NO_ERROR : PSC_POOL_IS_CORRUPTED;
}

inline WidgetPool::FramePool& WidgetPool::framePool()
{
    return m_framePool;
}

inline WidgetPool::PanelPool& WidgetPool::panelPool()
{
    return m_panelPool;
}

inline WidgetPool::BitmapFieldPool& WidgetPool::bitmapFieldPool()
{
    return m_bitmapFieldPool;
}

inline WidgetPool::ReferenceBitmapFieldPool& WidgetPool::referenceBitmapFieldPool()
{
    return m_referenceBitmapFieldPool;
}

inline WidgetPool::WindowPool& WidgetPool::windowPool()
{
    return m_windowPool;
}

} // namespace psc

#endif // POPULUSSC_WIDGETPOOL_H
