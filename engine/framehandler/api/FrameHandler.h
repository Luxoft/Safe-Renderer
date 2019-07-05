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

#include <LsrTypes.h>
#include <LSRErrorCollector.h>
#include <NonCopyable.h>

#include <DefaultDataContext.h>

class FrameHandlerCorrupter;

namespace lsr
{

class Database;
class DisplayManager;
class IDataHandler;
class Window;

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
class FrameHandler: private NonCopyable<FrameHandler>
{
public:
    /**
     * Constructs an object.
     *
     * @param[in] db          reference to @c Database object with widget configuration.
     * @param[in] dataHandler pointer to @c IDataHandler object.
     * @param[in] dsp         reference to @c DisplayManager object.
     */
    FrameHandler(Database& db, IDataHandler& dataHandler, DisplayManager& dsp);

    ~FrameHandler();

    /**
     * Creates the widgets.
     *
     * @return @c true if all widgets were successfully created, @c false otherwise.
     */
    bool start();

    /**
     * Informs object about the monotonic system time
     * It's called once for every main loop iteration.
     *
     * @param[in] monotonicTimeMs current monotonic system time in milliseconds.
     */
    void update(U32 monotonicTimeMs);

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
     * Method return the worst error, which can occur inside @c FrameHandler object.
     *
     * @return the worst error. See @c LSRError.
     */
    LSRError getError();

private:
    friend class ::FrameHandlerCorrupter;

    Database& m_db;
    WidgetPool m_widgetPool;
    IDataHandler& m_dataHandler;
    DefaultDataContext m_dataContext;
    DisplayManager& m_display;
    LSRErrorCollector m_error;
    Window* m_pWindow;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_FRAMEHANDLER_H
