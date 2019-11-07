/******************************************************************************
**
**   File:        IndicationDataMessage.cpp
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

#include "IndicationDataMessage.h"

namespace lsr
{

IndicationDataMessage::IndicationDataMessage()
    : m_fuClassId(0U)
{
    memset(m_indications, 0, NUMBER_INDICATION_BYTES);
}

IndicationDataMessage IndicationDataMessage::fromStream(InputStream& stream)
{
    IndicationDataMessage msg;
    stream >> msg;
    return msg;
}

U8 IndicationDataMessage::createMask(const U8 index) const
{
    return 0x80U >> (index % 8U);
}

bool IndicationDataMessage::getIndication(const IndicationId indicationId) const
{
    bool result = false;
    if ((0U != indicationId) && (indicationId <= NUMBER_INDICATORS))
    {
        const U8 index = static_cast<U8>((indicationId - 1U) / 8U);
        const U8 mask = createMask(indicationId - 1U);
        result = (m_indications[index] & mask) > 0U;
    }
    return result;
}

void IndicationDataMessage::setIndication(const IndicationId indicationId, const bool value)
{
    if ((0U != indicationId) && (indicationId <= NUMBER_INDICATORS))
    {
        const U8 index = static_cast<U8>((indicationId - 1U) / 8U);
        const U8 mask = createMask(indicationId - 1U);
        if (value)
        {
            m_indications[index] = m_indications[index] | mask;
        }
        else
        {
            const U8 invertedMask = ~mask;
            m_indications[index] = m_indications[index] & invertedMask;
        }
    }
}

U16 IndicationDataMessage::getSize() const
{
    return static_cast<U16>(sizeof(m_fuClassId) + NUMBER_INDICATION_BYTES);
}

InputStream& operator>>(InputStream& stream, IndicationDataMessage& msg)
{
    stream >> msg.m_fuClassId;

    for (U16 i = 0U; i < IndicationDataMessage::NUMBER_INDICATION_BYTES; ++i)
    {
        U8 curIndicator = 0U;
        stream >> curIndicator;
        msg.m_indications[i] = curIndicator;
    }

    return stream;
}

OutputStream& operator<<(OutputStream& stream, const IndicationDataMessage& msg)
{
    stream << msg.m_fuClassId;
    for (U16 i = 0U; i < IndicationDataMessage::NUMBER_INDICATION_BYTES; ++i)
    {
        stream << msg.m_indications[i];
    }

    return stream;
}

} // namespace lsr
