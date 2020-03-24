#ifndef _TELLTALES_HPP_
#define _TELLTALES_HPP_
/******************************************************************************
**
**   File:        Telltales.hpp
**   Description: Serialized Database
**
**   Copyright (C) 2017 Luxoft GmbH
******************************************************************************/

#include "LsrTypes.h"
#include <DatabaseTypes.h>

namespace Telltales
{

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U16 DISPLAY_WIDTH = 400U;

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional
static const U16 DISPLAY_HEIGHT = 240U;

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FUSETTINGS_DISPLAYUNITS = 0x00010001U;  // FU:1 DataId:1
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FUSETTINGS_DISPLAYLANGUAGE = 0x00010002U;  // FU:1 DataId:2
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FUSETTINGS_DISPLAYTIMENOTATION = 0x00010003U;  // FU:1 DataId:3
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FUSETTINGS_SKINVALUE = 0x00010004U;  // FU:1 DataId:4
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FUSETTINGS_TIMEOFDAY = 0x00010005U;  // FU:1 DataId:5
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FUSETTINGS_CURRENTDATE = 0x00010006U;  // FU:1 DataId:6
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FUTELLTALES_BREAKON = 0x002a0001U;  // FU:42 DataId:1
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FUTELLTALES_BREAKOFF = 0x002a0002U;  // FU:42 DataId:2
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FUTELLTALES_AIRBAG = 0x002a0003U;  // FU:42 DataId:3
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 INTERNALFU_BREAKERRORCOUNT = 0x00ff0001U;  // FU:255 DataId:1
// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 INTERNALFU_AIRBAGERRORCOUNT = 0x00ff0002U;  // FU:255 DataId:2

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 FRAME_COUNT = 1U;

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 PANEL_COUNT = 2U;

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 BITMAP_FIELD_COUNT = 2U;

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 REFERENCE_BITMAP_FIELD_COUNT = 2U;

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 PANEL_CHILDREN_COUNT = 2U;

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 DYNAMIC_DATA_COUNT = 23U;

// coverity[misra_cpp_2008_rule_0_1_4_violation] generic code (usage optional)
// coverity[misra_cpp_2008_rule_0_1_6_violation] generic code (usage optional)
static const U32 TEXTURES_COUNT = 5U;

/**
 * Returns the root of the generated database
 */
const lsr::DDHType* getDDH();

P_STATIC_ASSERT(FRAME_COUNT == 1U, "only one frame is supported - please check ddh configuration")
P_STATIC_ASSERT(PANEL_COUNT >= 1U, "at least one panel should be defined - please check ddh configuration")
P_STATIC_ASSERT(PANEL_CHILDREN_COUNT >= 1U, "at least one field should be defined - please check ddh configuration")

} // namespace Telltales

#endif // _TELLTALES_HPP_
