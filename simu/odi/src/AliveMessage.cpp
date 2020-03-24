/******************************************************************************
**
**   File:        AliveMessage.cpp
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

#include "AliveMessage.h"

namespace lsr
{

AliveMessage::AliveMessage(const U8 id)
    : m_id(id)
{
}

AliveMessage::AliveMessage()
    : m_id(0U)
{
}

AliveMessage AliveMessage::fromStream(InputStream& stream)
{
    AliveMessage msg;
    stream >> msg;
    return msg;
}

U16 AliveMessage::getSize() const
{
    return static_cast<U16>(sizeof(m_id));
}

InputStream& operator>>(InputStream& stream, AliveMessage& msg)
{
    stream >> msg.m_id;

    return stream;
}

OutputStream& operator<<(OutputStream& stream, const AliveMessage& msg)
{
    stream << msg.m_id;

    return stream;
}

} // namespace lsr
