/******************************************************************************
**
**   File:        IndicationDataMessage.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

namespace psc
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

U8 IndicationDataMessage::createMask(U8 index) const
{
    return 0x80 >> (index % 8);
}

bool IndicationDataMessage::getIndication(IndicationId indicationId) const
{
    bool result = false;
    if (0 != indicationId && indicationId <= NUMBER_INDICATORS)
    {
        U8 index = static_cast<U8>((indicationId-1)/8);
        U8 mask = createMask(indicationId-1);
        result = (m_indications[index] & mask) > 0;
    }
    return result;
}

void IndicationDataMessage::setIndication(const IndicationId indicationId, const bool value)
{
    if (0 != indicationId && indicationId <= NUMBER_INDICATORS)
    {
        U8 index = static_cast<U8>((indicationId-1)/8);
        U8 mask = createMask(indicationId-1);
        if (value)
        {
            m_indications[index] = m_indications[index] | mask;
        }
        else
        {
            m_indications[index] = m_indications[index] & ~mask;
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

} // namespace psc
