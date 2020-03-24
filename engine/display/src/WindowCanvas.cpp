/******************************************************************************
**
**   File:        WindowCanvas.cpp
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

#include "WindowCanvas.h"
#include "WindowDefinition.h"
#include "DisplayManager.h"

namespace lsr
{

WindowCanvas::WindowCanvas(DisplayManager& dsp, const WindowDefinition& config)
: Canvas(dsp, static_cast<U16>(config.getWidth()), static_cast<U16>(config.getHeight()))
{
    m_surface = gilCreateWindow(config.getWindowId(), config.getX(), config.getY(), config.getWidth(), config.getHeight());
}

void WindowCanvas::makeCurrent()
{
    static_cast<void>(gilSetSurface(getDisplayManager().getContext(), m_surface));  // ignore return value
}

void WindowCanvas::swapBuffers()
{
    static_cast<void>(gilSwapBuffers(m_surface));  // ignore return value
}

void WindowCanvas::sync()
{
    gilSync(getDisplayManager().getContext());
}

bool WindowCanvas::handleWindowEvents()
{
    return (gilHandleWindowEvents(getDisplayManager().getContext()) == GIL_TRUE);
}

} // namespace lsr
