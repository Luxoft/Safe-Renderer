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

namespace lsr
{
    struct DDHType;
} // namespace lsr

namespace Telltales
{

static const U32 FUSETTINGS_DISPLAYUNITS = ((1U << 16U) + 1U);
static const U32 FUSETTINGS_DISPLAYLANGUAGE = ((1U << 16U) + 2U);
static const U32 FUSETTINGS_DISPLAYTIMENOTATION = ((1U << 16U) + 3U);
static const U32 FUSETTINGS_SKINVALUE = ((1U << 16U) + 4U);
static const U32 FUSETTINGS_TIMEOFDAY = ((1U << 16U) + 5U);
static const U32 FUSETTINGS_CURRENTDATE = ((1U << 16U) + 6U);
static const U32 FUTELLTALES_BREAKON = ((42U << 16U) + 1U);
static const U32 FUTELLTALES_BREAKOFF = ((42U << 16U) + 2U);
static const U32 FUTELLTALES_AIRBAG = ((42U << 16U) + 3U);
static const U32 INTERNALFU_BREAKERRORCOUNT = ((255U << 16U) + 1U);
static const U32 INTERNALFU_AIRBAGERRORCOUNT = ((255U << 16U) + 2U);

static const U32 FRAME_COUNT = 1U;
static const U32 PANEL_COUNT = 2U;
static const U32 BITMAP_FIELD_COUNT = 2U;
static const U32 REFERENCE_BITMAP_FIELD_COUNT = 2U;
static const U32 MAX_PANEL_CHILDREN = 2U;
static const U32 MAX_DYNAMIC_DATA = 23U;
static const U32 MAX_TEXTURES = 5U;
static const U32 MAX_EXPRESSION_NESTING = 3U;

/**
 * Returns the root of the generated database
 */
const lsr::DDHType* getDDH();

P_STATIC_ASSERT(FRAME_COUNT == 1U, "only one frame is supported - please check ddh configuration")
P_STATIC_ASSERT(PANEL_COUNT >= 1U, "at least one panel should be defined - please check ddh configuration")
P_STATIC_ASSERT(MAX_PANEL_CHILDREN >= 1U, "at least one field should be defined - please check ddh configuration")

} // namespace Telltales

#endif // _TELLTALES_HPP_
