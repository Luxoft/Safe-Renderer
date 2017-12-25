/******************************************************************************
**
**   File:        Window.cpp
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

#include "Window.h"
#include "Frame.h"
#include "WidgetPool.h"

#include <Assertion.h>

#include <DDHType.h>
#include <Area.h>
#include <Color.h>

#include <WindowCanvas.h>

#include <new>

namespace psc
{

Window::Window(DisplayManager& dsp, const WindowDefinition& winDef)
    : Widget()
    , m_canvas(dsp, winDef)
{
    setArea(Area(0, 0, m_canvas.getWidth() - 1, m_canvas.getHeight() - 1));
}

bool Window::render()
{
    bool res = false;
    if (isInvalidated())
    {
        m_canvas.makeCurrent();
        Color color;
        m_canvas.clear(color);
        draw(m_canvas, getArea());
        m_canvas.swapBuffers();

        res = true;
    }
    return res;
}

bool Window::verify()
{
    m_canvas.makeCurrent();
    const bool verified = Widget::verify(m_canvas, getArea());
    return verified;
}

bool Window::handleWindowEvents()
{
    return m_canvas.handleWindowEvents();
}

bool Window::setup(WidgetPool& widgetPool,
                   const Database& db,
                   DataContext* pContext,
                   PSCErrorCollector& error)
{
    bool success = true;

    // Currently there's one frame, but there might be more
    const FrameId frameId = 1U;

    Frame* pFrame = Frame::create(widgetPool, db, frameId, this, pContext, error);
    /**
     * While @c MAX_FRAMES_COUNT < @c MAX_WIDGET_CHILDREN_COUNT,
     * @c addChild method will always return @c true value.
     * That's why we have coverage gap here.
     */
    if (NULL == pFrame || !addChild(pFrame))
    {
        success = false;
    }
    return success;
}

Window* Window::create(WidgetPool& widgetPool,
                       const Database& db,
                       DisplayManager& dsp,
                       const WindowDefinition& winDef,
                       DataContext* pContext,
                       PSCErrorCollector& error)
{
    PSCError tmpError = PSC_NO_ERROR;
    void* pRawMemory = widgetPool.windowPool().allocate(tmpError);
    error = tmpError;

    Window* pWnd = new(pRawMemory)Window(dsp, winDef);
    if (pWnd)
    {
        if (!pWnd->setup(widgetPool, db, pContext, error))
        {
            pWnd->~Window();
            error = widgetPool.windowPool().deallocate(pRawMemory);
            pWnd = NULL;
        }
    }

    return pWnd;
}

void Window::onUpdate(const U32 /* monotonicTimeMs */)
{
}

void Window::onDraw(Canvas& /* canvas */, const Area& /* area */)
{
}

bool Window::onVerify(Canvas&, const Area&)
{
    return true;
}

}
