#ifndef POPULUSSC_MESSAGEHEADER_H
#define POPULUSSC_MESSAGEHEADER_H

/******************************************************************************
**
**   File:        MessageHeader.h
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

#include <OdiTypes.h>
#include <PscTypes.h>
#include <InputStream.h>
#include <OutputStream.h>

namespace psc
{

class MessageHeader;

InputStream& operator>>(InputStream& stream, MessageHeader& msg);
OutputStream& operator<<(OutputStream& stream, const MessageHeader& msg);

/**
 * Class MessageHeader is designed for representation of the header which should be added
 * to each message.
 * It encapsulates the type and the length of the data which it headers and provides interface
 * for using these values.
 * Serialization and deserialization functions should be implemented as friend functions:
 * @c InputStream& operator>>(InputStream&, MessageHeader&) and
 * @c OutputStream& operator<<(OutputStream&, const MessageHeader&).
 */
class MessageHeader
{
public:
    MessageHeader(MessageTypes::Val msgType, U32 dataSize);

    static MessageHeader fromStream(InputStream& stream);

    /**
     * Returns value of the message type field from the message header struct.
     * @return value of the message type. see @c MessageTypes
     */
    MessageTypes::Val getType() const;

    /**
     * Returns the size of the data which follows message header.
     * @return the size of the data in bytes.
     */
    U32 getDataSize() const;

    /**
     * Returns size of the @c MessageHeader in serialized form.
     * @return size in bytes.
     */
    U32 getSize() const;

private:
    friend InputStream& operator>>(InputStream& stream, MessageHeader& header);
    friend OutputStream& operator<<(OutputStream& stream, const MessageHeader& header);

    MessageHeader();

    MessageTypes::Val m_type;
    U32 m_dataSize;
};

inline MessageTypes::Val MessageHeader::getType() const
{
    return m_type;
}

inline U32 MessageHeader::getDataSize() const
{
    return m_dataSize;
}

inline U32 MessageHeader::getSize() const
{
    return static_cast<U32>(sizeof(U8) /* sizeof m_type field */ + sizeof(m_dataSize));
}

} // namespace psc

#endif // POPULUSSC_MESSAGEHEADER_H
