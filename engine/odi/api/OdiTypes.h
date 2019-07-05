#ifndef LUXOFTSAFERENDERER_ODITYPES_H
#define LUXOFTSAFERENDERER_ODITYPES_H

/******************************************************************************
**
**   File:        OdiTypes.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   Luxoft Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Render is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Render.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
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

#endif // LUXOFTSAFERENDERER_ODITYPES_H
