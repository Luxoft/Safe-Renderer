#ifndef LUXOFTSAFERENDERER_LSRLIMITS_H
#define LUXOFTSAFERENDERER_LSRLIMITS_H

/******************************************************************************
**
**   File:        LSRLimits.h
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

#include "LsrTypes.h"
#include "Output/Telltales.hpp"

namespace lsr
{
    /**
     * Value describes maximum nesting level which @c lsr::Expression can have.
     */
    static const U32 MAX_EXPRESSION_NESTING = Telltales::MAX_EXPRESSION_NESTING;

    // FrameHandler constants
    static const U32 MAX_FRAMES_COUNT = Telltales::FRAME_COUNT;
    static const U32 MAX_PANELS_COUNT = Telltales::PANEL_COUNT;
    static const U32 MAX_BITMAPS_COUNT = 20U;
    static const U32 MAX_REFERENCE_BITMAPS_COUNT = 20U;
    static const U32 MAX_WINDOWS_COUNT = 1U;
    static const U32 MAX_WIDGET_CHILDREN_COUNT = 20U;

    // DataHandler constants
    static const U32 MAX_DYNAMIC_DATA = Telltales::MAX_DYNAMIC_DATA;

    // Drawing constants
    static const U32 MAX_TEXTURES = Telltales::MAX_TEXTURES;

    // unit tests require larger pools
    P_STATIC_ASSERT(MAX_REFERENCE_BITMAPS_COUNT >= Telltales::REFERENCE_BITMAP_FIELD_COUNT, "");
    P_STATIC_ASSERT(MAX_BITMAPS_COUNT >= Telltales::BITMAP_FIELD_COUNT, "");
    P_STATIC_ASSERT(MAX_WIDGET_CHILDREN_COUNT >= Telltales::MAX_PANEL_CHILDREN, "");
}

#endif // LUXOFTSAFERENDERER_LSRLIMITS_H
