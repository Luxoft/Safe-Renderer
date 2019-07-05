#ifndef LUXOFTSAFERENDERER_FRAMEHANDLERCORRUPTER_H
#define LUXOFTSAFERENDERER_FRAMEHANDLERCORRUPTER_H

/******************************************************************************
**
**   File:        FrameHandlerCorrupter.h
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

#include "WidgetPoolCorrupter.h"

#include <FrameHandler.h>

class FrameHandlerCorrupter
{
public:
    FrameHandlerCorrupter(lsr::FrameHandler& fh)
        : m_poolCorrupter(&fh.m_widgetPool)
    {
    }

    void corruptStorage()
    {
        m_poolCorrupter.corruptBitmapStorage();
    }

private:
    WidgetPoolCorrupter m_poolCorrupter;
};

#endif // LUXOFTSAFERENDERER_FRAMEHANDLERCORRUPTER_H
