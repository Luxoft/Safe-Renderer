/******************************************************************************
**
**   File:        CanvasMock.cpp
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

#include "Canvas.h"
#include "DisplayManager.h"
#include "DisplayAccessor.h"


namespace psc
{

Canvas::Canvas(DisplayManager& dsp, const U16 width, const U16 height)
: m_dsp(dsp)
, m_width(width)
, m_height(height)
{
}

void Canvas::clear(const psc::Color& color)
{
}

void Canvas::drawBitmap(const psc::StaticBitmap& bitmap, const psc::Area& area)
{
    DisplayAccessor::instance().drawBitmapWasExecuted(true);
}

bool Canvas::verify(const psc::StaticBitmap& bitmap, const psc::Area& area)
{
    return DisplayAccessor::instance().getVerifyFlag();
}

} // namespace psc
