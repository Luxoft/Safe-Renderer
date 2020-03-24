#ifndef LUXOFTSAFERENDERER_FRAMEHANDLER_H
#define LUXOFTSAFERENDERER_FRAMEHANDLER_H

/******************************************************************************
**
**   File:        FrameHandler.h
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

#include <LsrTypes.h>
#include <LSRErrorCollector.h>
#include <NonCopyable.h>
#include <Window.h>

namespace lsr
{

/**
 * FrameHandler creates and stores all widgets and provide a functionality to work
 * with them.
 * Widgets creating evaluates in the method @c start.
 * If this method wasn't emitted, @c FrameHandler component suggested not to be initialized
 * and normal work of other methods (except @c getError) is not guaranteed.
 * @c getError method can be called in anytime. It returns the worst error, which can occur
 * in the object.
 *
 * @reqid SW_ENG_068, SW_ENG_069, SW_ENG_070, SW_ENG_071, SW_ENG_073, SW_ENG_074, SW_ENG_075, SW_ENG_076
 */
class FrameHandler: private NonCopyable
{
public:
    /**
     * Constructs an object.
     *
     * @param[in] hmi         reference to the HMI runtime objects (widgets)
     * @param[in] db          reference to @c Database object with widget configuration.
     * @param[in] dsp         reference to @c DisplayManager object.
     */
    FrameHandler(IHMI& hmi, Database& db, DisplayManager& dsp);

    /**
     * Creates the widgets.
     *
     * @return @c true if all widgets were successfully created, @c false otherwise.
     */
    bool start();

    /**
     * Method renders the hole widgets tree on some canvas.
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

    /**
     * Method returns the most severe error, which occurred inside @c FrameHandler object.
     *
     * @return the most severe error. See @c LSREngineError.
     */
    LSREngineError getError();

private:
    Database& m_db;
    DisplayManager& m_display;
    LSRErrorCollector m_error;
    Window m_window;
    IHMI& m_hmi;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_FRAMEHANDLER_H
