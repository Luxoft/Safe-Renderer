/******************************************************************************
**
**   File:        OutputStream.cpp
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

#include "OutputStream.h"

#include <cstring>
#include <algorithm>

namespace lsr
{

OutputStream::OutputStream(void* const pBuffer, const uint32_t bufferSize)
    : m_pBuffer(static_cast<uint8_t*>(pBuffer))
    , m_bufferSize(bufferSize)
    , m_pos(0U)
    , m_error(COM_NO_ERROR)
{
    if ((NULL == m_pBuffer) || (0U == m_bufferSize))
    {
        m_error = COM_NOT_ENOUGH_BUFFER_SIZE;
        m_pBuffer = NULL;
        m_bufferSize = 0U;
    }
}

uint32_t OutputStream::bytesWritten() const
{
    return (m_bufferSize > m_pos) ? m_pos : m_bufferSize;
}

uint32_t OutputStream::bytesAvailable() const
{
    return (m_bufferSize > m_pos) ? (m_bufferSize - m_pos) : 0U;
}

uint32_t OutputStream::write(const void* const pData, const uint32_t dataSize)
{
    uint32_t sizeOfWrittenData = 0U;
    if (m_error == COM_NO_ERROR)
    {
        if ((NULL == pData) || (0U == dataSize))
        {
            m_error = COM_NOT_ENOUGH_INPUT_DATA;
        }
        else
        {
            if (dataSize > bytesAvailable())
            {
                m_error = COM_NOT_ENOUGH_BUFFER_SIZE;
            }
            else
            {
                memcpy(m_pBuffer + m_pos, pData, dataSize);
                m_pos += dataSize;
                sizeOfWrittenData = dataSize;
            }
        }
    }
    return sizeOfWrittenData;
}

OutputStream& OutputStream::operator<<(const bool& value)
{
    static const uint32_t sizeOfBool = 1U;
    write(&value, sizeOfBool);
    return *this;
}

OutputStream& OutputStream::operator<<(const int8_t& value)
{
    const uint8_t tmp = static_cast<uint8_t>(value);
    write(&tmp, sizeof(tmp));
    return *this;
}

OutputStream& OutputStream::operator<<(const uint8_t& value)
{
    write(&value, sizeof(value));
    return *this;
}

OutputStream& OutputStream::operator<<(const int16_t& value)
{
    const uint16_t tmp = static_cast<uint16_t>(value);
    *this << tmp;
    return *this;
}

OutputStream& OutputStream::operator<<(const uint16_t& value)
{
    uint8_t tmp[2] = {0U};
    tmp[0] = static_cast<uint8_t>(value >> 8U);
    tmp[1] = static_cast<uint8_t>(value);
    write(&tmp, sizeof(tmp));
    return *this;
}

OutputStream& OutputStream::operator<<(const int32_t& value)
{
    const uint32_t tmp = static_cast<uint32_t>(value);
    *this << tmp;
    return *this;
}

OutputStream& OutputStream::operator<<(const uint32_t& value)
{
    uint8_t tmp[4] = {0U};
    tmp[0] = static_cast<uint8_t>(value >> 24U);
    tmp[1] = static_cast<uint8_t>(value >> 16U);
    tmp[2] = static_cast<uint8_t>(value >> 8U);
    tmp[3] = static_cast<uint8_t>(value);
    write(&tmp, sizeof(tmp));
    return *this;
}

} // namespace lsr
