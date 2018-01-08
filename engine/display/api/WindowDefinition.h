#ifndef POPULUSSC_WINDOWDEFINITION_H
#define POPULUSSC_WINDOWDEFINITION_H

/******************************************************************************
**
**   File:        WindowDefinition.h
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

namespace psc
{

/**
 * Provides configuration values for the pgl Window
 */
struct WindowDefinition
{
    I32 xPos;     ///< window x position in pixels
    I32 yPos;     ///< window y position in pixels
    I32 width;    ///< window width in pixels
    I32 height;   ///< window heigh in pixels
    U8 id;        ///< window id (pgl implementation specific)
};

}

#endif // POPULUSSC_WINDOWDEFINITION_H
