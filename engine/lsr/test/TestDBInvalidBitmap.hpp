#ifndef TESTDB_INVALID_BITMAP_HPP
#define TESTDB_INVALID_BITMAP_HPP
/******************************************************************************
**
**   File:        TestDBInvalidBitmap.hpp
**   Description: Serialized Database contains 2 invalid bitmaps
**
**   Copyright (C) 2017 Luxoft GmbH
******************************************************************************/

#include "LsrTypes.h"

namespace lsr
{
    struct DDHType;
} // namespace lsr

namespace TestDBInvalidBitmap
{

static const U32 FUSETTINGS_DISPLAYUNITS = 0x00010001U;  // FU:1 DataId:1
static const U32 FUSETTINGS_DISPLAYLANGUAGE = 0x00010002U;  // FU:1 DataId:2
static const U32 FUSETTINGS_DISPLAYTIMENOTATION = 0x00010003U;  // FU:1 DataId:3
static const U32 FUSETTINGS_SKINVALUE = 0x00010004U;  // FU:1 DataId:4
static const U32 FUSETTINGS_TIMEOFDAY = 0x00010005U;  // FU:1 DataId:5
static const U32 FUSETTINGS_CURRENTDATE = 0x00010006U;  // FU:1 DataId:6
static const U32 FUTELLTALES_BREAKON = 0x002a0001U;  // FU:42 DataId:1
static const U32 FUTELLTALES_BREAKOFF = 0x002a0002U;  // FU:42 DataId:2
static const U32 FUTELLTALES_AIRBAG = 0x002a0003U;  // FU:42 DataId:3
static const U32 INTERNALFU_BREAKERRORCOUNT = 0x00ff0001U;  // FU:255 DataId:1
static const U32 INTERNALFU_AIRBAGERRORCOUNT = 0x00ff0002U;  // FU:255 DataId:2

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
 * The database contains 2 errors:
 * - invalid bitmapID for Break Bitmap
 * - invalid bitmapID for Break Reference Bitmap
 */
const lsr::DDHType* getDDH();

P_STATIC_ASSERT(FRAME_COUNT == 1U, "only one frame is supported - please check ddh configuration")
P_STATIC_ASSERT(PANEL_COUNT >= 1U, "at least one panel should be defined - please check ddh configuration")
P_STATIC_ASSERT(MAX_PANEL_CHILDREN >= 1U, "at least one field should be defined - please check ddh configuration")

} // namespace TestDBInvalidBitmap

#endif // TESTDB_INVALID_BITMAP_HPP
