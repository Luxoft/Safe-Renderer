#ifndef LUXOFTSAFERENDERER_MESSAGEHEADER_H
#define LUXOFTSAFERENDERER_MESSAGEHEADER_H

/******************************************************************************
**
**   File:        MessageHeader.h
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

#include <OdiTypes.h>
#include <LsrTypes.h>
#include <InputStream.h>
#include <OutputStream.h>

namespace lsr
{

class MessageHeader;

InputStream& operator>>(InputStream& stream, MessageHeader& header);
OutputStream& operator<<(OutputStream& stream, const MessageHeader& header);

/**
 * Class MessageHeader is designed for representation of the header which should be added
 * to each message.
 * It encapsulates the type and the length of the data which it headers and provides interface
 * for using these values.
 * Serialization and deserialization functions should be implemented as friend functions:
 * @c InputStream& operator>>(InputStream&, MessageHeader&) and
 * @c OutputStream& operator<<(OutputStream&, const MessageHeader&).
 *
 * @reqid SW_ENG_128, SW_ENG_131
 */
class MessageHeader
{
public:
    MessageHeader(const MessageTypes::Val msgType, const U32 dataSize);

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

} // namespace lsr

#endif // LUXOFTSAFERENDERER_MESSAGEHEADER_H
