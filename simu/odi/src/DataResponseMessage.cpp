/******************************************************************************
**
**   File:        DataResponseMessage.cpp
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

#include "DataResponseMessage.h"

namespace lsr
{

DataResponseMessage::DataResponseMessage()
    : m_dataId(0U)
    , m_dataType(DATATYPE_ENUM_SIZE)
    , m_fuId(0U)
    , m_invalidFlag(true)
    , m_value(0U)
{
}

DataResponseMessage DataResponseMessage::fromStream(InputStream& stream)
{
    DataResponseMessage msg;
    stream >> msg;
    return msg;
}

U16 DataResponseMessage::getSize() const
{
    return static_cast<U16>(sizeof(m_dataId) +
        sizeof(m_fuId) + sizeof(m_invalidFlag) + sizeof(m_value) +
         + sizeof(U8) /* size of data type*/);
}

InputStream& operator>>(InputStream& stream, DataResponseMessage& msg)
{
    stream >> msg.m_fuId;
    stream >> msg.m_dataId;

    U8 tmp = 0U;
    stream >> tmp;
    msg.m_dataType = static_cast<DynamicDataTypeEnumeration>(tmp);
    stream >> msg.m_invalidFlag;
    stream >> msg.m_value;

    return stream;
}

OutputStream& operator<<(OutputStream& stream, const DataResponseMessage& msg)
{
    stream << msg.m_fuId;
    stream << msg.m_dataId;
    stream << static_cast<U8>(msg.m_dataType);
    stream << msg.m_invalidFlag;
    stream << msg.m_value;

    return stream;
}

} // namespace lsr
