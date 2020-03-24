/******************************************************************************
**
**   File:        imx6_demonstartor_constants.h
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

#ifndef LUXOFTSAFERENDERER_IMX6_DEMONSTARTOR_CONSTANTS_H
#define LUXOFTSAFERENDERER_IMX6_DEMONSTARTOR_CONSTANTS_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * This file is used for comparison the pixel data.
 * Currently it is hard coded.
 */
typedef enum
{
    AIRBAG_COORD = 507,
    ABS_COORD = 540,
    FOG_COORD = 579,
    ESP_COORD = 615,
    PARKING_COORD = 657,
    PARKING_BRAKE_COORD = 689,
    LOW_BEAM_COORD = 729,
    HIGH_BEAM_COORD = 767
} TEXTURE_X_COORDS;

typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t value;
} gil_check_point;

typedef struct
{
    gil_check_point point[3];
} gil_check_texture;

static const gil_check_texture m_airbag = {{{511, 67, 51488}, {517, 67, 14400}, {515, 73, 37056}}};
static const gil_check_texture m_abs = {{{544, 66, 35713}, {550, 71, 25184}, {558, 61, 33600}}};
static const gil_check_texture m_fog = {{{584, 69, 62976}, {588, 74, 33601}, {599, 65, 35712}}};
static const gil_check_texture m_esp = {{{616, 72, 39873}, {624, 69, 44064}, {635, 74, 60897}}};
static const gil_check_texture m_parking = {{{658, 73, 1079}, {664, 70, 850}, {669, 66, 980}}};
static const gil_check_texture m_parkingBreak = {{{694, 77, 33600}, {700, 71, 65088}, {708, 63, 35680}}};
static const gil_check_texture m_lowBeam = {{{732, 70, 512}, {738, 68, 800}, {748, 73, 768}}};
static const gil_check_texture m_highBeam = {{{768, 75, 948}, {776, 68, 2996}, {786, 67, 948}}};

#ifdef __cplusplus
}
#endif

#endif // LUXOFTSAFERENDERER_IMX6_DEMONSTARTOR_CONSTANTS_H
