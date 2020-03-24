/******************************************************************************
**
**   File:        EventMessage.cpp
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

#include "EventMessage.h"

namespace lsr
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

} // namespace lsr
