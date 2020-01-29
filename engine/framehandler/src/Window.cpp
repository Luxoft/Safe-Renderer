/******************************************************************************
**
**   File:        Window.cpp
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

#include "Window.h"
#include "Frame.h"
#include "WidgetPool.h"

#include <Assertion.h>

#include <DDHType.h>
#include <Area.h>
#include <Color.h>

#include <WindowCanvas.h>

#include <new>

namespace lsr
{

Window::Window(DisplayManager& dsp, const WindowDefinition& winDef)
    : Widget()
    , m_canvas(dsp, winDef)
{
    setArea(Area(0, 0, static_cast<I32>(m_canvas.getWidth()) - 1, static_cast<I32>(m_canvas.getHeight()) - 1));
}

bool Window::render()
{
    const bool renderingIsRequired = isInvalidated();
    if (renderingIsRequired)
    {
        m_canvas.makeCurrent();
        m_canvas.clear(Color::fromColorValue(0U));
        draw(m_canvas, getArea());
        m_canvas.swapBuffers();
        const LSREngineError canvasError = m_canvas.getError();
        if (canvasError != LSR_NO_ENGINE_ERROR)
        {
            setError(canvasError);
        }
    }
    return renderingIsRequired;
}

bool Window::verify()
{
    m_canvas.makeCurrent();
    const bool verified = Widget::verify(m_canvas, getArea());
    m_canvas.sync();
    const LSREngineError canvasError = m_canvas.getError();
    if (canvasError != LSR_NO_ENGINE_ERROR)
    {
        setError(canvasError);
    }
    return verified;
}

bool Window::handleWindowEvents()
{
    return m_canvas.handleWindowEvents();
}

bool Window::setup(WidgetPool& factory,
                   const Database& db,
                   DataContext* const pContext,
                   LSRErrorCollector& error)
{
    bool successful = true;

    // Currently there's one frame, but there might be more
    const FrameId id = 1U;

    Frame* const pFrame = Frame::create(factory, db, id, this, pContext, error);
    /**
    * While @c MAX_FRAMES_COUNT < @c MAX_WIDGET_CHILDREN_COUNT,
    * @c addChild method will always return @c true value.
    * That's why we have coverage gap here.
    */
    if ((NULL == pFrame) || (!addChild(pFrame)))
    {
        static_cast<void>(successful);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        successful = false;
    }
    return successful;
}

Window* Window::create(WidgetPool& factory,
                       const Database& db,
                       DisplayManager& dsp,
                       const WindowDefinition& winDef,
                       DataContext* const pContext,
                       LSRErrorCollector& error)
{
    LSREngineError tmpError = LSR_NO_ENGINE_ERROR;
    void* const pRawMemory = factory.windowPool().allocate(tmpError);
    error = tmpError;

    Window* pWnd = new(pRawMemory)Window(dsp, winDef);
    if (NULL != pWnd)
    {
        if (!pWnd->setup(factory, db, pContext, error))
        {
            pWnd->~Window();
            error = factory.windowPool().deallocate(pRawMemory);
            pWnd = NULL;
        }
    }

    return pWnd;
}

void Window::onUpdate(const U32 monotonicTimeMs)
{
    static_cast<void>(monotonicTimeMs);  // ignore unused variable
}

void Window::onDraw(Canvas& /* dst */, const Area& /* rect */) const
{
}

bool Window::onVerify(Canvas&, const Area&)
{
    return true;
}

} // namespace lsr
