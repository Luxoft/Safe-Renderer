#ifndef LUXOFTSAFERENDERER_EVENTMESSAGE_H
#define LUXOFTSAFERENDERER_EVENTMESSAGE_H

/******************************************************************************
**
**   File:        EventMessage.h
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

#include "OdiTypes.h"

#include <InputStream.h>
#include <OutputStream.h>
#include <LsrTypes.h>
#include <ComError.h>

namespace lsr
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
 *
 * @reqid SW_ENG_136, SW_ENG_137, SW_ENG_139, SW_ENG_141, SW_ENG_142
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

} // namespace lsr

#endif // LUXOFTSAFERENDERER_EVENTMESSAGE_H
