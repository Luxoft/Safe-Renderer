/******************************************************************************
**
**   File:        pil_platform_linux.c
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
