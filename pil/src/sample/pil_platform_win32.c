/******************************************************************************
**
**   File:        pil_platform_win32.c
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

#include "pil.h"
#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t pilGetMonotonicTime(void)
{
    return timeGetTime();
}

#ifdef __cplusplus
}
#endif
