/******************************************************************************
**
**   File:        pil.cpp
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

//#include "pil.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

std::string g_lastErrorMsg;
uint32_t g_lastErrorCode;

extern "C" void pilAssert(const char* msg,  const char* file, int line)
{
    fprintf(stderr, "Assertion Failed: %s (%s:%d)\n", msg, file, line);
    abort();
}

extern "C" void pilError(uint32_t errorCode, const char* msg)
{
    g_lastErrorCode = errorCode;
    g_lastErrorMsg = msg;
}
