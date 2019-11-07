#ifndef LUXOFTSAFERENDERER_WINDOW_H
#define LUXOFTSAFERENDERER_WINDOW_H

/******************************************************************************
**
**   File:        Window.h
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

#include "Widget.h"

#include <WindowCanvas.h>

#include <ddh_defs.h>

namespace lsr
{

struct DDHType;
class Database;
class DataContext;

/**
 * Window implements the widget which is parent for @c Frame widgets.
 *
 * @reqid SW_ENG_076
 */
class Window P_FINAL : public Widget
{
public:

    /**
     * Method creates a @c Window object and all its children
     * with given @c widgetPool according to configuration from @c db object.
     *
     * @param[in]  widgetPool pool which provides allocation an @c Window object.
     * @param[in]  db         object provides work with database.
     * @param[in]  dsp        @c DisplayManager instance.
     * @param[in]  winDef     window display configuration.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c LSR_NO_ERROR if
     *                        operation succeeded, other @c LSRError values otherwise.
     *
     * @return pointer to @c Window object if initialization of object was successful,
     *         @c NULL otherwise.
     */
    static Window* create(WidgetPool& widgetPool,
                          const Database& db,
                          DisplayManager& dsp,
                          const WindowDefinition& winDef,
                          DataContext* const pContext,
                          LSRErrorCollector& error);

    /**
     * Method renders window widget and all its children on internal canvas.
     * Render operation will be evaluated only if window or its children are in invalidated state.
     *
     * @return @c true if rendering was emitted, @c false otherwise.
     */
    bool render();

    /**
     * Performs a pixel verification on the canvas
     *
     * @returns @c false if any error was detected, @c true if there's no error
     *          detected or no error check performed.
     */
    bool verify();

    /**
     * Handles the window events and indicates if the window has been closed
     *
     * This function may be mainly useful for simulation environments or systems,
     * which use a window manager.
     *
     * @return @c true if window has been closed by the window manager, @c false otherwise.
     */
    bool handleWindowEvents();

private:
    /**
     * Create an object.
     *
     * @param[in] dsp    @c DisplayManager instance.
     * @param[in] winDef window display configuration.
     */
    Window(DisplayManager& dsp, const WindowDefinition& winDef);

    /**
     * Method initialize object.
     *
     * @param[in]  widgetPool pool which provides allocation an @c Frame object.
     * @param[in]  db         object provides work with database.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c LSR_NO_ERROR if
     *                        operation succeeded, other @c LSRError values otherwise.
     *
     * @return @c true if object initialization succeeded, @c false otherwise.
     */
    bool setup(WidgetPool& widgetPool,
               const Database& db,
               DataContext* const pContext,
               LSRErrorCollector& error);

    /**
     * Method does nothing. It is a stub method
     */
    virtual void onUpdate(const U32 monotonicTimeMs) P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     */
    virtual void onDraw(Canvas& canvas, const Area& area) P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     *
     * @return @c true.
     */
    virtual bool onVerify(Canvas& canvas, const Area& area) P_OVERRIDE;

    /**
     * Method returns type of the widget.
     *
     * @return @c WIDGET_TYPE_WINDOW value.
     */
    virtual WidgetType getType() const P_OVERRIDE;

    WindowCanvas m_canvas;
};

inline Widget::WidgetType Window::getType() const
{
  return WIDGET_TYPE_WINDOW;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_WINDOW_H
