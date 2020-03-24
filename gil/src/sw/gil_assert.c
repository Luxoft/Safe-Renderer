/******************************************************************************
**
**   File:        gil_assert.c
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

#include "gil_assert.h"
#include <pil.h>

GILBoolean gilExecuteAssert(const char* msg, const char* file, int line)
{
    pilAssert(msg, file, line);
    return GIL_FALSE;
}
