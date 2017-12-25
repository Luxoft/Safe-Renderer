/******************************************************************************
**
**   File:        EventMessage.cpp
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

#include "EventMessage.h"

namespace psc
{

EventMessage::EventMessage()
    : m_fuClassId(0U)
    , m_eventId(0U)
{
}

EventMessage EventMessage::fromStream(InputStream& stream)
{
    EventMessage msg;
    stream >> msg;
    return msg;
}

U16 EventMessage::getSize() const
{
    return static_cast<U16>(sizeof(m_fuClassId) + sizeof(m_eventId));
}

InputStream& operator>>(InputStream& stream, EventMessage& msg)
{
    stream >> msg.m_fuClassId;
    stream >> msg.m_eventId;

    return stream;
}

OutputStream& operator<<(OutputStream& stream, const EventMessage& msg)
{
    stream << msg.m_fuClassId;
    stream << msg.m_eventId;

    return stream;
}

} // namespace psc
