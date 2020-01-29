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

#define TELLTALES_FUSETTINGS_DISPLAYUNITS 0x00010001U /* FU:1 DataId:1 */
#define TELLTALES_FUSETTINGS_DISPLAYLANGUAGE 0x00010002U /* FU:1 DataId:2 */
#define TELLTALES_FUSETTINGS_DISPLAYTIMENOTATION 0x00010003U /* FU:1 DataId:3 */
#define TELLTALES_FUSETTINGS_SKINVALUE 0x00010004U /* FU:1 DataId:4 */
#define TELLTALES_FUSETTINGS_TIMEOFDAY 0x00010005U /* FU:1 DataId:5 */
#define TELLTALES_FUSETTINGS_CURRENTDATE 0x00010006U /* FU:1 DataId:6 */
#define TELLTALES_FUTELLTALES_BREAKON 0x002a0001U /* FU:42 DataId:1 */
#define TELLTALES_FUTELLTALES_BREAKOFF 0x002a0002U /* FU:42 DataId:2 */
#define TELLTALES_FUTELLTALES_AIRBAG 0x002a0003U /* FU:42 DataId:3 */
#define TELLTALES_INTERNALFU_BREAKERRORCOUNT 0x00ff0001U /* FU:255 DataId:1 */
#define TELLTALES_INTERNALFU_AIRBAGERRORCOUNT 0x00ff0002U /* FU:255 DataId:2 */

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
