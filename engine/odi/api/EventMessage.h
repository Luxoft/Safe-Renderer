#ifndef POPULUSSC_EVENTMESSAGE_H
#define POPULUSSC_EVENTMESSAGE_H

/******************************************************************************
**
**   File:        EventMessage.h
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

#include "OdiTypes.h"

#include <InputStream.h>
#include <OutputStream.h>
#include <PscTypes.h>
#include <PSCError.h>

namespace psc
{

class EventMessage;

InputStream& operator>>(InputStream& stream, EventMessage& msg);
OutputStream& operator<<(OutputStream& stream, const EventMessage& msg);

/**
 * Message is needed to encapsulate data about events.
 * It holds one event from one FU, whose IDs can be returned by
 * appropriate getters.
 * Serialization and deserialization functions should be implemented as friend functions:
 * @c InputStream& operator>>(InputStream&, AliveMessage&) and
 * @c OutputStream& operator<<(OutputStream&, const AliveMessage&)
 */
class EventMessage
{
public:
    explicit EventMessage();

    static EventMessage fromStream(InputStream& stream);

    U16 getSize() const;

    MessageTypes::Val getType() const;

    void setFuId(const FUClassId id);
    void setEvent(const EventId id);

    FUClassId getFuId() const;
    EventId getEventId() const;

private:
    friend InputStream& operator>>(InputStream& stream, EventMessage& msg);
    friend OutputStream& operator<<(OutputStream& stream, const EventMessage& msg);

    FUClassId m_fuClassId;
    EventId m_eventId;
};

inline MessageTypes::Val EventMessage::getType() const
{
    return MessageTypes::ODI;
}

inline FUClassId EventMessage::getFuId() const
{
    return m_fuClassId;
}

inline EventId EventMessage::getEventId() const
{
    return m_eventId;
}

inline void EventMessage::setFuId(const FUClassId id)
{
    m_fuClassId = id;
}

inline void EventMessage::setEvent(const EventId id)
{
    m_eventId = id;
}

} // namespace psc

#endif // POPULUSSC_EVENTMESSAGE_H
