/******************************************************************************
**
**   File:        OutputStream.cpp
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
