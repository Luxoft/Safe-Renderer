#ifndef LUXOFTSAFERENDERER_ODITYPES_H
#define LUXOFTSAFERENDERER_ODITYPES_H

#include "LsrTypes.h"

/******************************************************************************
**
**   File:        OdiTypes.h
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

/**
 * Major version gets increased when Engine introduces incompatible changes
 * e.g. a change in an existing message type
 * Minor version gets increased when Engine introduces changes that are backward compatible
 * e.g. a new message type
 * FUs may connect if major number equals Engine's major number and
 * minor number is smaller or equal to Engine's minor number
 * (old FUs may connect to new Engines if major number is the same)
 */
struct OdiVersion
{
    enum Val
    {
        VERSION_MAJOR = 3,
        VERSION_MINOR = 8
    };
};

/**
 * @reqid SW_ENG_138
 */
struct RegistrationMode
{
    enum Val
    {
        REPLACE = 0, ///< Replace existing FU-list with provided list.
        REMOVE = 1, ///< Remove listed FU:s from registered list.
        APPEND = 2,  ///< Append listed FU:s to existing.
        LAST,
        UNKNOWN = 0xFF
    };
};

/**
 * @reqid SW_ENG_138
 */
struct MessageTypes
{
    enum Val
    {
        REGISTRATION = 0,
        ODI = 1,
        ALIVE = 7,
        LAST,
        UNKNOWN = 0xFF
    };
};

/**
 * @reqid SW_ENG_138
 */
struct DataMessageTypes
{
    enum Val
    {
        DYN_DATA_RESP = 0,
        EVENT = 2,
        INDICATION = 3,
        LAST,
        UNKNOWN = 0xFF
    };
};

namespace lsr
{

typedef U16 FUClassId;
typedef U16 DataId;
typedef U16 EventId;
typedef U8 IndicationId;

/** DynamicDataTypeEnumeration */
enum DynamicDataTypeEnumeration
{
    DATATYPE_SPEED = 0,
    DATATYPE_STRING = 1,
    DATATYPE_INTEGER = 2,
    DATATYPE_ENUMERATION_VALUE = 3,
    DATATYPE_DECIMAL = 4,
    DATATYPE_TIME = 5,
    DATATYPE_DATE = 6,
    DATATYPE_LIST = 7,
    DATATYPE_PICTOGRAM = 8,
    DATATYPE_TEXT_ID = 9,
    DATATYPE_BITMAP_ID = 10,
    DATATYPE_DISTANCE_LONG = 11,
    DATATYPE_DISTANCE_SHORT = 12,
    DATATYPE_VOLUME = 13,
    DATATYPE_TEMPERATURE = 14,
    DATATYPE_PRESSURE = 15,
    DATATYPE_FUEL_CONSUMPTION = 16,
    DATATYPE_FUEL_CONSUMPTION_INVERTED = 17,
    DATATYPE_CHARACTER = 18,
    DATATYPE_HOURS_OF_DAY = 19,
    DATATYPE_DECIMAL_SHORT = 20,
    DATATYPE_BITMAP = 21,
    DATATYPE_FUEL_CONSUMPTION_STANDING_STILL = 22,
    DATATYPE_FUEL_CONSUMPTION_C_N_G = 23,
    DATATYPE_FUEL_CONSUMPTION_C_N_G_INVERTED = 24,
    DATATYPE_FUEL_CONSUMPTION_C_N_G_STANDING_STILL = 25,
    DATATYPE_FUEL_USED_C_N_G = 26,
    DATATYPE_COORDINATE2_D = 27,
    DATATYPE_BITMAP_PATH = 28,
    DATATYPE_MATRIX4X4 = 29,
    DATATYPE_COLOR = 30,
    DATATYPE_BOOLEAN = 31,
    DATATYPE_ENUM_SIZE = 32
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_ODITYPES_H
