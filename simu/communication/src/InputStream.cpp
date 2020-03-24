/******************************************************************************
**
**   File:        InputStream.cpp
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

#include "InputStream.h"

#include <cstring>
#include <algorithm>

namespace lsr
{

InputStream::InputStream(const void* const pBuffer, const uint32_t bufferSize)
    : m_pBuffer(static_cast<const uint8_t*>(pBuffer))
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

uint32_t InputStream::bytesToRead() const
{
    return (m_bufferSize > m_pos) ? (m_bufferSize - m_pos) : 0U;
}

uint32_t InputStream::read(void* const pData, const uint32_t dataSize)
{
    uint32_t sizeOfReadData = 0U;
    if (m_error == COM_NO_ERROR)
    {
        if ((NULL == pData) || (0U == dataSize))
        {
            m_error = COM_NOT_ENOUGH_INPUT_DATA;
        }
        else
        {
            if (dataSize > bytesToRead())
            {
                m_error = COM_NOT_ENOUGH_BUFFER_SIZE;
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

    value = (0U != tmp);

    return *this;
}

InputStream& InputStream::operator>>(int8_t& value)
{
    uint8_t tmp = 0U;
    *this >> tmp;

    value = static_cast<int8_t>(tmp);

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

    value = static_cast<int16_t>(tmp);

    return *this;
}

InputStream& InputStream::operator>>(uint16_t& value)
{
    uint8_t tmp[2] = {0U};
    read(&tmp, sizeof(tmp));

    const uint16_t msb = tmp[0];
    const uint16_t lsb = tmp[1];
    value = static_cast<uint16_t>(msb << 8U) | lsb;

    return *this;
}

InputStream& InputStream::operator>>(int32_t& value)
{
    uint32_t tmp = 0U;
    *this >> tmp;

    value = static_cast<int32_t>(tmp);

    return *this;
}

InputStream& InputStream::operator>>(uint32_t& value)
{
    uint8_t tmp[4] = {0U};
    read(&tmp, sizeof(tmp));

    const uint32_t byte3 = tmp[0];
    const uint32_t byte2 = tmp[1];
    const uint32_t byte1 = tmp[2];
    const uint32_t byte0 = tmp[3];

    value = static_cast<uint32_t>(byte3 << 24U);
    value |= static_cast<uint32_t>(byte2 << 16U);
    value |= static_cast<uint32_t>(byte1 << 8U);
    value |= byte0;

    return *this;
}

} // namespace lsr
