/******************************************************************************
**
**   File:        Window.cpp
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

#include "Window.h"
#include "Frame.h"

#include <Assertion.h>

#include <DDHType.h>
#include <Area.h>
#include <Color.h>

#include <WindowCanvas.h>
#include <IHMI.h>

#include <new>

namespace lsr
{

Window::Window(DisplayManager& dsp, const WindowDefinition& winDef)
    : Widget()
    , m_canvas(dsp, winDef)
    , m_pFrame(NULL)
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

LSREngineError Window::setup(IHMI& hmi,
                   const Database& db)
{
    // Currently there's one frame, but there might be more
    m_pFrame = hmi.getFrame();
    LSRErrorCollector err(LSR_NO_ENGINE_ERROR);
    if (m_pFrame != NULL)
    {
        err = m_pFrame->setup(db);
    }
    else
    {
        err = LSR_DB_ERROR;
    }
    return err.get();
}

void Window::onDraw(Canvas& dst, const Area& rect) const
{
    m_pFrame->draw(dst, rect);
}

bool Window::onVerify(Canvas& dst, const Area& rect)
{
    return m_pFrame->verify(dst, rect);
}

LSREngineError Window::getChildError() const
{
    return (m_pFrame != NULL) ? m_pFrame->getError() : LSR_DB_ERROR;
}

bool Window::isChildInvalidated() const
{
    return m_pFrame->isInvalidated();
}

} // namespace lsr
