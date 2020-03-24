#ifndef LOG_MSG_H
#define LOG_MSG_H

/******************************************************************************
**
**   File:        logmsg.h
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

#include <stdarg.h>
#include <stdio.h>

static void dbg_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

#define DEBUG 2
#define LOG_VERB(x) do { if (DEBUG>=3) dbg_printf x; } while (0)
#define LOG_WARN(x) do { if (DEBUG>=2) dbg_printf x; } while (0)
#define LOG_ERR(x) do { if (DEBUG>=1) dbg_printf x; } while (0)

#endif
