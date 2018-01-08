#ifndef POPULUSSC_ODIRECORDER_H
#define POPULUSSC_ODIRECORDER_H

/******************************************************************************
**
**   File:        OdiRecorder.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "PscTypes.h"

// Comment to implement in the future
//#include "ConfigData.h"

namespace psc
{

class OdiRecorder
{
public:

    struct MessageDirection
    {
        enum Val
        {
            INCOMING,
            OUTGOING,
        };
    };

    struct MessageTokens
    {
        enum Val
        {
            TOKEN_IN = UINT32_MAX,
            TOKEN_WARN = UINT32_MAX - 1,
            TOKEN_OUT = UINT32_MAX - 2,
            TOKEN_IN_END = UINT32_MAX - 3,
            TOKEN_OUT_END = UINT32_MAX - 4,
            TOKEN_VERSION = UINT32_MAX - 5,
            TOKEN_CONFIG = UINT32_MAX - 6,
            TOKEN_CONFIG_END = UINT32_MAX - 7,
            TOKEN_CONFIG_OPTION = UINT32_MAX - 8,
            TOKEN_CONFIG_OPTION_END = UINT32_MAX - 9,
        };
    };

    struct VersionMask
    {
        enum Val
        {
            MAJOR_MASK = 0xFF00,
            MINOR_MASK = 0x00FF,
        };
    };

    static const U32 FILE_ID;
    static const U32 VERSION;

    /**
     * @brief Creates an OdiRecorder which writes to a memory buffer.
     * @param buffer Pre-allocated memory buffer.
     * @param bufferSize Size of pre-allocated memory buffer.
     */
    OdiRecorder(void* buffer, size_t bufferSize);

    ~OdiRecorder();

    void beginChunk(MessageDirection::Val direction);
    void endChunk(MessageDirection::Val direction);
    void write(const U8* msgBuffer, U32 msgLen, U8 msgType);

    /* Comment to implement in the future
    void WriteConfigData(const ConfigData& configData);
    */
};

} // namespace psc

#endif // POPULUSSC_ODIRECORDER_H
