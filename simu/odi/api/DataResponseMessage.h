#ifndef LUXOFTSAFERENDERER_DATARESPONSEMESSAGE_H
#define LUXOFTSAFERENDERER_DATARESPONSEMESSAGE_H

/******************************************************************************
**
**   File:        DataResponseMessage.h
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
#include <ddh_defs.h>

namespace lsr
{

class DataResponseMessage;

InputStream& operator>>(InputStream& stream, DataResponseMessage& msg);
OutputStream& operator<<(OutputStream& stream, const DataResponseMessage& msg);

/**
 * The message holds the dynamic data as a response to some request.
 * It holds the ID of the data, its type, value, flag of correctness, and the FU ID which
 * delivers this information.
 * Serialization and deserialization functions should be implemented as friend functions:
 * @c InputStream& operator>>(InputStream&, AliveMessage&) and
 * @c OutputStream& operator<<(OutputStream&, const AliveMessage&)
 *
 * @reqid SW_ENG_136, SW_ENG_137, SW_ENG_139, SW_ENG_141, SW_ENG_145
 */
class DataResponseMessage
{
public:
    explicit DataResponseMessage();

    static DataResponseMessage fromStream(InputStream& stream);

    U16 getSize() const;

    MessageTypes::Val getType() const;

    void setDataId(const DataId id);
    void setDataType(const DynamicDataTypeEnumeration type);
    void setFuId(const FUClassId id);
    void setInvalidFlag(const bool isInvalid);
    void setDataValue(const U32 value);

    DataId getDataId() const;
    DynamicDataTypeEnumeration getDataType() const;
    FUClassId getFuId() const;
    bool getInvalidFlag() const;
    U32 getDataValue() const;

private:
    friend InputStream& operator>>(InputStream& stream, DataResponseMessage& msg);
    friend OutputStream& operator<<(OutputStream& stream, const DataResponseMessage& msg);

    DataId m_dataId;
    DynamicDataTypeEnumeration m_dataType;
    FUClassId m_fuId;
    bool m_invalidFlag;
    U32 m_value;
};

inline MessageTypes::Val DataResponseMessage::getType() const
{
    return MessageTypes::ODI;
}

inline DataId DataResponseMessage::getDataId() const
{
    return m_dataId;
}

inline DynamicDataTypeEnumeration DataResponseMessage::getDataType() const
{
    return m_dataType;
}

inline FUClassId DataResponseMessage::getFuId() const
{
    return m_fuId;
}

inline bool DataResponseMessage::getInvalidFlag() const
{
    return m_invalidFlag;
}

inline U32 DataResponseMessage::getDataValue() const
{
    return m_value;
}

inline void DataResponseMessage::setDataId(const DataId id)
{
    m_dataId = id;
}

inline void DataResponseMessage::setDataType(const DynamicDataTypeEnumeration type)
{
    m_dataType = type;
}

inline void DataResponseMessage::setFuId(const FUClassId id)
{
    m_fuId = id;
}

inline void DataResponseMessage::setInvalidFlag(const bool isInvalid)
{
    m_invalidFlag = isInvalid;
}

inline void DataResponseMessage::setDataValue(const U32 value)
{
    m_value = value;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_DATARESPONSEMESSAGE_H
