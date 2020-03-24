#ifndef LUXOFTSAFERENDERER_INDICATIONDATAMESSAGE_H
#define LUXOFTSAFERENDERER_INDICATIONDATAMESSAGE_H

/******************************************************************************
**
**   File:        IndicationDataMessage.h
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

class IndicationDataMessage;

InputStream& operator>>(InputStream& stream, IndicationDataMessage& msg);
OutputStream& operator<<(OutputStream& stream, const IndicationDataMessage& msg);

/**
 * Message is used to send information about indications.
 * It holds information about all indications of one FU.
 * Each indicator is represented as two values: "0" and "1".
 * Serialization and deserialization functions should be implemented as friend functions:
 * @c InputStream& operator>>(InputStream&, AliveMessage&) and
 * @c OutputStream& operator<<(OutputStream&, const AliveMessage&)
 *
 * @reqid SW_ENG_136, SW_ENG_137, SW_ENG_139, SW_ENG_141, SW_ENG_143
 */
class IndicationDataMessage
{
public:
    enum Constants
    {
        NUMBER_INDICATION_BYTES = 12,
        NUMBER_INDICATORS = NUMBER_INDICATION_BYTES * 8
    };

    explicit IndicationDataMessage();

    static IndicationDataMessage fromStream(InputStream& stream);

    U16 getSize() const;

    MessageTypes::Val getType() const;

    void setFuId(const FUClassId id);
    void setIndication(const IndicationId indicationId, const bool value);

    FUClassId getFuId() const;
    bool getIndication(const IndicationId indicationId) const;

private:
    friend InputStream& operator>>(InputStream& stream, IndicationDataMessage& msg);
    friend OutputStream& operator<<(OutputStream& stream, const IndicationDataMessage& msg);

    U8 createMask(const U8 index) const;

    FUClassId m_fuClassId;

    /**
     * There can be @c NUMBER_INDICATION_BYTES * 8 count of indications.
     * Each indicator is stored using one bit.
     * Meanwhile it is stored as such pair:
     * the 0th indicator is stored in the 7th bit of the byte,
     * the 1st indicator is stored in the 6th bit of the byte, etc.
     */
    U8 m_indications[NUMBER_INDICATION_BYTES];
};

inline MessageTypes::Val IndicationDataMessage::getType() const
{
    return MessageTypes::ODI;
}

inline FUClassId IndicationDataMessage::getFuId() const
{
    return m_fuClassId;
}

inline void IndicationDataMessage::setFuId(const FUClassId id)
{
    m_fuClassId = id;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_INDICATIONDATAMESSAGE_H
