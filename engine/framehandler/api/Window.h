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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "Widget.h"

#include <WindowCanvas.h>
#include <IHMI.h>
#include <ddh_defs.h>

namespace lsr
{

/**
 * Window implements the widget which is parent for @c Frame widgets.
 *
 * @reqid SW_ENG_076
 */
class Window P_FINAL : public Widget
{
public:
    /**
     * Create an object.
     *
     * @param[in] dsp    @c DisplayManager instance.
     * @param[in] winDef window display configuration.
     */
    Window(DisplayManager& dsp, const WindowDefinition& winDef);

    /**
     * Connects the Window and its children with the Database component
     * @param[in] hmi widget instances
     * @param[in] db database provides access to the bitmap resources
     * @return error state will be equal to @c LSR_NO_ENGINE_ERROR if
     *                      operation succeeded, other @c LSREngineError values otherwise.
     */
    LSREngineError setup(IHMI& hmi, const Database& db);

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
     * Method does nothing. It is a stub method
     */
    virtual void onDraw(Canvas& dst, const Area& rect) const P_OVERRIDE;

    /**
     * Method does nothing. It is a stub method
     *
     * @return @c true.
     */
    virtual bool onVerify(Canvas& dst, const Area& rect) P_OVERRIDE;

    virtual LSREngineError getChildError() const P_OVERRIDE;

    virtual bool isChildInvalidated() const P_OVERRIDE;

    WindowCanvas m_canvas;
    Frame* m_pFrame;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_WINDOW_H
