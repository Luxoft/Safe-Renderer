/******************************************************************************
**
**   File:        pil_platform_linux.c
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
#include <time.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t pilGetMonotonicTime(void)
{
    struct timespec now;
    int res = clock_gettime(CLOCK_MONOTONIC, &now);
    uint32_t t = 0;
    if (res == 0)
    {
        t = (uint32_t)(now.tv_sec*1000 + now.tv_nsec/1000000);
    }
    return t;
}

#ifdef __cplusplus
}
#endif
