#ifndef LUXOFTSAFERENDERER_WIDGETPOOL_H
#define LUXOFTSAFERENDERER_WIDGETPOOL_H

/******************************************************************************
**
**   File:        WidgetPool.h
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

#include "ReferenceBitmapField.h"
#include "BitmapField.h"
#include "Panel.h"
#include "Frame.h"
#include "Window.h"

#include <ddh_defs.h>

#include <Pool.h>
#include <LSRLimits.h>
#include <NonCopyable.h>

class WidgetPoolCorrupter;

namespace lsr
{

/**
 * This class contains several @c Pool objects for storing different widget objects
 * (for each widget type - separate @c Pool object).
 * It provides functionality to access to each pool to be able to allocate or deallocate objects.
 *
 * @reqid SW_ENG_069, SW_ENG_075
 */
class WidgetPool : private NonCopyable
{
public:
    WidgetPool();

    /**
     * Method return state of the pools.
     *
     * @return @c LSR_POOL_IS_CORRUPTED if any of the pool is corrupted (see @c Pool::checkPool),
     *         @c LSR_NO_ENGINE_ERROR otherwise.
     */
    LSREngineError getError() const;

private:
    friend Panel* Panel::create(WidgetPool& factory,
                                const Database& db,
                                const PanelType* pDdhPanel,
                                DataContext* pContext,
                                LSRErrorCollector& error);

    friend BitmapField* BitmapField::create(WidgetPool& factory,
                                            const Database& db,
                                            const StaticBitmapFieldType* pDdh,
                                            DataContext* pContext,
                                            LSRErrorCollector& error);

    friend ReferenceBitmapField* ReferenceBitmapField::create(WidgetPool& factory,
                                            const Database& db,
                                            const ReferenceBitmapFieldType* pDdh,
                                            DataContext* pContext,
                                            LSRErrorCollector& error);

    friend Frame* Frame::create(WidgetPool& factory,
                                const Database& db,
                                FrameId id,
                                Window* pParent,
                                DataContext* pContext,
                                LSRErrorCollector& error);

    friend Window* Window::create(WidgetPool& factory,
                                  const Database& db,
                                  DisplayManager& dsp,
                                  const WindowDefinition& winDef,
                                  DataContext* pContext,
                                  LSRErrorCollector& error);

    friend LSREngineError Widget::dispose(WidgetPool& factory, Widget* pWidget);

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
: NonCopyable()
{
}

inline LSREngineError WidgetPool::getError() const
{
    return (m_framePool.checkPool() &&
            m_panelPool.checkPool() &&
            m_bitmapFieldPool.checkPool() &&
            m_referenceBitmapFieldPool.checkPool() &&
            m_windowPool.checkPool()) ? LSR_NO_ENGINE_ERROR : LSR_POOL_IS_CORRUPTED;
}

inline WidgetPool::FramePool& WidgetPool::framePool()
{
    // coverity[misra_cpp_2008_rule_9_3_2_violation]
    return m_framePool;
}

inline WidgetPool::PanelPool& WidgetPool::panelPool()
{
    // coverity[misra_cpp_2008_rule_9_3_2_violation]
    return m_panelPool;
}

inline WidgetPool::BitmapFieldPool& WidgetPool::bitmapFieldPool()
{
    // coverity[misra_cpp_2008_rule_9_3_2_violation]
    return m_bitmapFieldPool;
}

inline WidgetPool::ReferenceBitmapFieldPool& WidgetPool::referenceBitmapFieldPool()
{
    // coverity[misra_cpp_2008_rule_9_3_2_violation]
    return m_referenceBitmapFieldPool;
}

inline WidgetPool::WindowPool& WidgetPool::windowPool()
{
    // coverity[misra_cpp_2008_rule_9_3_2_violation]
    return m_windowPool;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_WIDGETPOOL_H
