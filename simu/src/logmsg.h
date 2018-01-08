#ifndef LOG_MSG_H
#define LOG_MSG_H

/******************************************************************************
**
**   File:        logmsg.h
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

#define DEBUG 3
#define LOG_VERB(x) do { if (DEBUG>=3) dbg_printf x; } while (0)
#define LOG_WARN(x) do { if (DEBUG>=2) dbg_printf x; } while (0)
#define LOG_ERR(x) do { if (DEBUG>=1) dbg_printf x; } while (0)

#endif
