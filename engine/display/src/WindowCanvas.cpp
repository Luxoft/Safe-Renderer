/******************************************************************************
**
**   File:        WindowCanvas.cpp
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

#include "WindowCanvas.h"
#include "WindowDefinition.h"
#include "DisplayManager.h"

namespace lsr
{

WindowCanvas::WindowCanvas(DisplayManager& dsp, const WindowDefinition& config)
: Canvas(dsp, static_cast<U16>(config.width), static_cast<U16>(config.height))
{
    m_surface = gilCreateWindow(config.id, config.xPos, config.yPos, config.width, config.height);
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
