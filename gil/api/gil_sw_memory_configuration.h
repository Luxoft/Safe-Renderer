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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
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
