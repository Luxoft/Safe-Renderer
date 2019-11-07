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

#include "pil.h"
#include <stdio.h>
#include <stdlib.h>

extern "C"
{

    void pilError(uint32_t errorCode, const char* msg)
    {
        printf("pilError: %d %s\n", static_cast<int>(errorCode), msg);
    }

    void pilTrace(const char* msg)
    {
        printf("%s\n", msg);
    }

    void pilAssert(const char* msg, const char* file, int32_t lineNo)
    {
        printf("Assertion failed in %s (%d): %s\n", file, lineNo, msg);
        abort();
    }
}
