#ifndef LUXOFTSAFERENDERER_LSRLIMITS_H
#define LUXOFTSAFERENDERER_LSRLIMITS_H

/******************************************************************************
**
**   File:        LSRLimits.h
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

#include "LsrTypes.h"
#include "Output/Telltales.hpp"

namespace lsr
{
    // FrameHandler constants
    // coverity[misra_cpp_2008_rule_0_1_4_violation] used by tests
    // coverity[misra_cpp_2008_rule_0_1_6_violation] used by tests
    static const U32 MAX_FRAMES_COUNT = Telltales::FRAME_COUNT;

    // coverity[misra_cpp_2008_rule_0_1_4_violation] used by tests
    // coverity[misra_cpp_2008_rule_0_1_6_violation] used by tests
    static const U32 MAX_PANELS_COUNT = Telltales::PANEL_COUNT;

    // coverity[misra_cpp_2008_rule_0_1_4_violation] used by tests
    // coverity[misra_cpp_2008_rule_0_1_6_violation] used by tests
    static const U32 MAX_BITMAPS_COUNT = 20U;

    // coverity[misra_cpp_2008_rule_0_1_4_violation] used by tests
    // coverity[misra_cpp_2008_rule_0_1_6_violation] used by tests
    static const U32 MAX_REFERENCE_BITMAPS_COUNT = 20U;

    // coverity[misra_cpp_2008_rule_0_1_4_violation] used by tests
    // coverity[misra_cpp_2008_rule_0_1_6_violation] used by tests
    static const U32 MAX_WINDOWS_COUNT = 1U;

    // coverity[misra_cpp_2008_rule_0_1_4_violation] used by tests
    // coverity[misra_cpp_2008_rule_0_1_6_violation] used by tests
    static const U32 MAX_WIDGET_CHILDREN_COUNT = 20U;

    // DataHandler constants
    // coverity[misra_cpp_2008_rule_0_1_4_violation] used by tests
    // coverity[misra_cpp_2008_rule_0_1_6_violation] used by tests
    static const U32 MAX_DYNAMIC_DATA = Telltales::DYNAMIC_DATA_COUNT;

    // Drawing constants
    // coverity[misra_cpp_2008_rule_0_1_4_violation] used by tests
    // coverity[misra_cpp_2008_rule_0_1_6_violation] used by tests
    static const U32 MAX_TEXTURES = Telltales::TEXTURES_COUNT;

    // unit tests require larger pools
    P_STATIC_ASSERT(MAX_REFERENCE_BITMAPS_COUNT >= Telltales::REFERENCE_BITMAP_FIELD_COUNT, "");
    P_STATIC_ASSERT(MAX_BITMAPS_COUNT >= Telltales::BITMAP_FIELD_COUNT, "");
    P_STATIC_ASSERT(MAX_WIDGET_CHILDREN_COUNT >= Telltales::PANEL_CHILDREN_COUNT, "");
}

#endif // LUXOFTSAFERENDERER_LSRLIMITS_H
