/******************************************************************************
**
**   File:        InputStream.cpp
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

#include "InputStream.h"

#include <cstring>
#include <algorithm>

namespace lsr
{

InputStream::InputStream(const void* pBuffer, uint32_t bufferSize)
    : m_pBuffer(static_cast<const uint8_t*>(pBuffer))
    , m_bufferSize(bufferSize)
    , m_pos(0U)
    , m_error(LSR_NO_ERROR)
{
    if (NULL == m_pBuffer || 0U == m_bufferSize)
    {
        m_error = LSR_COMM_NOT_ENOUGH_BUFFER_SIZE;
        m_pBuffer = NULL;
        m_bufferSize = 0U;
    }
}

uint32_t InputStream::bytesToRead() const
{
    return (m_bufferSize > m_pos) ? m_bufferSize - m_pos : 0U;
}

uint32_t InputStream::read(void* pData, uint32_t dataSize)
{
    uint32_t sizeOfReadData = 0U;
    if (m_error == LSR_NO_ERROR)
    {
        if (!pData || 0U == dataSize)
        {
            m_error = LSR_COMM_NOT_ENOUGH_INPUT_DATA;
        }
        else
        {
            if (dataSize > bytesToRead())
            {
                m_error = LSR_COMM_NOT_ENOUGH_BUFFER_SIZE;
            }
            else
            {
                memcpy(pData, m_pBuffer + m_pos, dataSize);
                m_pos += dataSize;
                sizeOfReadData = dataSize;
            }
        }
    }

    return sizeOfReadData;
}

InputStream& InputStream::operator>>(bool& value)
{
    value = false;
    uint8_t tmp = 0U;
    *this >> tmp;

    value = (0 != tmp);

    return *this;
}

InputStream& InputStream::operator>>(int8_t& value)
{
    uint8_t tmp = 0U;
    *this >> tmp;

    value = tmp;

    return *this;
}

InputStream& InputStream::operator>>(uint8_t& value)
{
    uint8_t tmp = 0U;
    read(&tmp, sizeof(tmp));

    value = tmp;

    return *this;
}

InputStream& InputStream::operator>>(int16_t& value)
{
    uint16_t tmp = 0U;
    *this >> tmp;

    value = tmp;

    return *this;
}

InputStream& InputStream::operator>>(uint16_t& value)
{
    uint8_t tmp[2] = {0U};
    read(&tmp, sizeof(tmp));

    value = (tmp[0] << 8U) | tmp[1];

    return *this;
}

InputStream& InputStream::operator>>(int32_t& value)
{
    uint32_t tmp = 0U;
    *this >> tmp;

    value = tmp;

    return *this;
}

InputStream& InputStream::operator>>(uint32_t& value)
{
    uint8_t tmp[4] = {0U};
    read(&tmp, sizeof(tmp));

    value = tmp[0] << 24;
    value |= tmp[1] << 16;
    value |= tmp[2] << 8;
    value |= tmp[3];

    return *this;
}

}
