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

#include "pil.h"
#include <stdio.h>
#include <stdlib.h>

extern "C"
{
    void pilAssert(const char* msg, const char* file, int32_t lineNo)
    {
        printf("Assertion failed in %s (%d): %s\n", file, lineNo, msg);
        abort();
    }
}
