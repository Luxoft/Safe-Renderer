#ifndef LUXOFTSAFERENDERER_ALIVEMESSAGE_H
#define LUXOFTSAFERENDERER_ALIVEMESSAGE_H

/******************************************************************************
**
**   File:        AliveMessage.h
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

#include "OdiTypes.h"

#include <InputStream.h>
#include <OutputStream.h>
#include <LsrTypes.h>
#include <LSRError.h>

namespace lsr
{

class AliveMessage;

InputStream& operator>>(InputStream& stream, AliveMessage& msg);
OutputStream& operator<<(OutputStream& stream, const AliveMessage& msg);

/**
 * Alive messages are needed to implement the keepalive communication.
 * The message has only one field - id.
 * Serialization and deserialization functions should be implemented as friend functions:
 * @c InputStream& operator>>(InputStream&, AliveMessage&) and
 * @c OutputStream& operator<<(OutputStream&, const AliveMessage&)
 *
 * @reqid SW_ENG_136, SW_ENG_137, SW_ENG_141, SW_ENG_144, SW_ENG_147
 */
class AliveMessage
{
public:
    explicit AliveMessage(U8 id);

    static AliveMessage fromStream(InputStream& stream);

    U16 getSize() const;

    MessageTypes::Val getType() const;

    U8 getId() const;

private:
    AliveMessage();

    friend InputStream& operator>>(InputStream& stream, AliveMessage& msg);
    friend OutputStream& operator<<(OutputStream& stream, const AliveMessage& msg);

    U8 m_id;
};

inline U8 AliveMessage::getId() const
{
    return m_id;
}

inline MessageTypes::Val AliveMessage::getType() const
{
    return MessageTypes::ALIVE;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_ALIVEMESSAGE_H
