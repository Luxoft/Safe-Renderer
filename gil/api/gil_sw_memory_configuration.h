#ifndef LUXOFTSAFERENDERER_GIL_SW_MEMORY_CONFIGURATION_H
#define LUXOFTSAFERENDERER_GIL_SW_MEMORY_CONFIGURATION_H

/******************************************************************************
**
**   File:        gil_sw_memory_configuration.h
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

typedef struct gil_config_t
{
    void* outputMemory;
    uint32_t bufferSize;
    int32_t screenX;
    int32_t screenY;
    int32_t screenH;
    int32_t screenW;
    uint8_t pixelFormat;
} gil_config_t;

#endif // LUXOFTSAFERENDERER_GIL_SW_MEMORY_CONFIGURATION_H
