#ifndef POPULUSSC_PSCLIMITS_H
#define POPULUSSC_PSCLIMITS_H

/******************************************************************************
**
**   File:        PscLimits.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "PscTypes.h"

static const U32 MAX_NUM_MESSAGE_TO_PROCESS = 10U;

/**
 * Value describes maximum nesting level which @c psc::Expression can have.
 */
static const U32 MAX_EXPRESSION_NESTING = 10U;

// FrameHandler constants
static const U8 MAX_FRAMES_COUNT = 1U;
static const U8 MAX_PANELS_COUNT = 2U;
static const U8 MAX_BITMAPS_COUNT = 10U;
static const U8 MAX_REFERENCE_BITMAPS_COUNT = 10U;
static const U8 MAX_WINDOWS_COUNT = 1U;
static const U8 MAX_WIDGET_CHILDREN_COUNT = 10U;

// DataHandler constants
static const U32 MAX_DYNAMIC_DATA = 40U;

#endif // POPULUSSC_PSCLIMITS_H
