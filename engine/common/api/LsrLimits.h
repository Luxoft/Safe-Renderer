#ifndef LUXOFTSAFERENDERER_LSRLIMITS_H
#define LUXOFTSAFERENDERER_LSRLIMITS_H

/******************************************************************************
**
**   File:        LsrLimits.h
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

static const U32 MAX_NUM_MESSAGE_TO_PROCESS = 10U;

/**
 * Value describes maximum nesting level which @c lsr::Expression can have.
 */
static const U32 MAX_EXPRESSION_NESTING = 10U;

// FrameHandler constants
static const U8 MAX_FRAMES_COUNT = 1U;
static const U8 MAX_PANELS_COUNT = 2U;
static const U8 MAX_BITMAPS_COUNT = 20U;
static const U8 MAX_REFERENCE_BITMAPS_COUNT = 20U;
static const U8 MAX_WINDOWS_COUNT = 1U;
static const U8 MAX_WIDGET_CHILDREN_COUNT = 20U;

// DataHandler constants
static const U32 MAX_DYNAMIC_DATA = 40U;

#endif // LUXOFTSAFERENDERER_LSRLIMITS_H
