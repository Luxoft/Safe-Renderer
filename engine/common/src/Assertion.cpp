/******************************************************************************
**
**   File:        Assertion.cpp
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

#include "Assertion.h"
#include <pil.h>

#ifdef NDEBUG

#else

namespace lsr
{

namespace impl
{

bool executeAssert(const char* const msg, const char* const file, const int32_t line)
{
    pilAssert(msg, file, line);
    return false;
}

} // namespace lsr

} // namespace impl

#endif // NDEBUG
