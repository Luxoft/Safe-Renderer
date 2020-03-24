#ifndef LUXOFTSAFERENDERER_IMX6_RENDERING_CONFIGURATION_H
#define LUXOFTSAFERENDERER_IMX6_RENDERING_CONFIGURATION_H

/******************************************************************************
**
**   File:        imx6_rendering_configuration.h
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
    int8_t renderDevice;
    char checkDevice[30];
} gil_config_t;

#endif // LUXOFTSAFERENDERER_IMX6_RENDERING_CONFIGURATION_H
