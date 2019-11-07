#ifndef _TELLTALES_H_
#define _TELLTALES_H_
/******************************************************************************
**
**   File:        Telltales.h
**   Description: Serialized Database
**
**   Copyright (C) 2017 Luxoft GmbH
******************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

#include <lsr.h>

#define TELLTALES_FUSETTINGS_DISPLAYUNITS ((1U << 16U) + 1U)
#define TELLTALES_FUSETTINGS_DISPLAYLANGUAGE ((1U << 16U) + 2U)
#define TELLTALES_FUSETTINGS_DISPLAYTIMENOTATION ((1U << 16U) + 3U)
#define TELLTALES_FUSETTINGS_SKINVALUE ((1U << 16U) + 4U)
#define TELLTALES_FUSETTINGS_TIMEOFDAY ((1U << 16U) + 5U)
#define TELLTALES_FUSETTINGS_CURRENTDATE ((1U << 16U) + 6U)
#define TELLTALES_FUTELLTALES_BREAKON ((42U << 16U) + 1U)
#define TELLTALES_FUTELLTALES_BREAKOFF ((42U << 16U) + 2U)
#define TELLTALES_FUTELLTALES_AIRBAG ((42U << 16U) + 3U)
#define TELLTALES_INTERNALFU_BREAKERRORCOUNT ((255U << 16U) + 1U)
#define TELLTALES_INTERNALFU_AIRBAGERRORCOUNT ((255U << 16U) + 2U)

#define TELLTALES_FRAME_COUNT 1U;
#define TELLTALES_PANEL_COUNT 2U;
#define TELLTALES_BITMAP_FIELD_COUNT 2U;
#define TELLTALES_REFERENCE_BITMAP_FIELD_COUNT 2U;
#define TELLTALES_MAX_PANEL_CHILDREN 2U;
#define TELLTALES_MAX_DYNAMIC_DATA 23U;
#define TELLTALES_MAX_TEXTURES 5U;
#define TELLTALES_MAX_EXPRESSION_NESTING 3U;

/**
 * Returns the root of the generated database
 */
LSRDatabase getTelltalesDDH();

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _TELLTALES_H_ */
