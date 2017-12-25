/******************************************************************************
**
**   File:        WindowCanvas.cpp
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

#include "WindowCanvas.h"
#include "WindowDefinition.h"
#include "DisplayManager.h"

namespace psc
{

WindowCanvas::WindowCanvas(DisplayManager& dsp, const WindowDefinition& config)
: Canvas(dsp, config.width, config.height)
{
    m_surface = pglCreateWindow(config.id, config.xPos, config.yPos, config.width, config.height);
}

void WindowCanvas::makeCurrent()
{
    pglSetSurface(getDisplayManager().getContext(), m_surface);
}

void WindowCanvas::swapBuffers()
{
    pglSwapBuffers(m_surface);
}

bool WindowCanvas::handleWindowEvents()
{
    return (pglHandleWindowEvents(getDisplayManager().getContext()) == PGL_TRUE);
}

}
