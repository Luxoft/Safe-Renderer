/******************************************************************************
**
**   File:        TelltalesDisplayTest.h
**   Description: Test database
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
#ifndef TELLTALES_DISPLAY_TEST_H
#define TELLTALES_DISPLAY_TEST_H

#include "Telltales.hpp"

namespace TelltalesDisplayNoBmp
{
    const lsr::DDHType* getDDH();
}

namespace TelltalesDisplayNoSkin
{
    const lsr::DDHType* getDDH();
}

namespace TelltalesDisplayNoState
{
    const lsr::DDHType* getDDH();
}

#endif // TELLTALES_DISPLAY_TEST_H
