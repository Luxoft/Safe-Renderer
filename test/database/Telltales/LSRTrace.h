#ifndef LUXOFTSAFERENDERER_LSRTRACE_H
#define LUXOFTSAFERENDERER_LSRTRACE_H

/******************************************************************************
**
**   File:        LSRTrace.h
**   Description: Provides macros to trace log messages
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
#include <stdio.h>

#define LSR_LOG_LEVEL_FATAL  0U
#define LSR_LOG_LEVEL_ERR    1U
#define LSR_LOG_LEVEL_WARN   2U
#define LSR_LOG_LEVEL_VERB   3U

#ifndef LSR_LOG_LEVEL
#define LSR_LOG_LEVEL LSR_LOG_LEVEL_WARN
#endif

#if (LSR_LOG_LEVEL >= LSR_LOG_LEVEL_VERB)
    #define LSR_VERB(msg) printf(msg "\n")
    #define LSR_VERB_1(msg, a1) printf(msg "\n", a1)
    #define LSR_VERB_2(msg, a1, a2) printf(msg "\n", a1, a2)
    #define LSR_VERB_3(msg, a1, a2, a3) printf(msg "\n", a1, a2, a3)
    #define LSR_VERB_4(msg, a1, a2, a3, a4) printf(msg "\n", a1, a2, a3, a4)
#else
    #define LSR_VERB(msg)
    #define LSR_VERB_1(msg, a1)
    #define LSR_VERB_2(msg, a1, a2)
    #define LSR_VERB_3(msg, a1, a2, a3)
    #define LSR_VERB_4(msg, a1, a2, a3, a4)
#endif

#if (LSR_LOG_LEVEL >= LSR_LOG_LEVEL_WARN)
    #define LSR_WARN(msg) printf(msg "\n")
    #define LSR_WARN_1(msg, a1) printf(msg "\n", a1)
    #define LSR_WARN_2(msg, a1, a2) printf(msg "\n", a1, a2)
    #define LSR_WARN_3(msg, a1, a2, a3) printf(msg "\n", a1, a2, a3)
    #define LSR_WARN_4(msg, a1, a2, a3, a4) printf(msg "\n", a1, a2, a3, a4)
#else
    #define LSR_WARN(msg)
    #define LSR_WARN_1(msg, a1)
    #define LSR_WARN_2(msg, a1, a2)
    #define LSR_WARN_3(msg, a1, a2, a3)
    #define LSR_WARN_4(msg, a1, a2, a3, a4)
#endif

#if (LSR_LOG_LEVEL >= LSR_LOG_LEVEL_ERR)
    #define LSR_ERR(msg) printf(msg "\n")
    #define LSR_ERR_1(msg, a1) printf(msg "\n", a1)
    #define LSR_ERR_2(msg, a1, a2) printf(msg "\n", a1, a2)
    #define LSR_ERR_3(msg, a1, a2, a3) printf(msg "\n", a1, a2, a3)
    #define LSR_ERR_4(msg, a1, a2, a3, a4) printf(msg "\n", a1, a2, a3, a4)
#else
    #define LSR_ERR(msg)
    #define LSR_ERR_1(msg, a1)
    #define LSR_ERR_2(msg, a1, a2)
    #define LSR_ERR_3(msg, a1, a2, a3)
    #define LSR_ERR_4(msg, a1, a2, a3, a4)
#endif

// trace scopes - may be deactivated separately
#define LSR_LOG_GIL_4 LSR_VERB_4
#define LSR_LOG_GIL_3 LSR_VERB_3
#define LSR_LOG_GIL_2 LSR_VERB_2
#define LSR_LOG_GIL_1 LSR_VERB_1
#define LSR_LOG_GIL   LSR_VERB

#endif // LUXOFTSAFERENDERER_LSRTRACE_H
