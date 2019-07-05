/******************************************************************************
**
**   File:        pil.cpp
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
