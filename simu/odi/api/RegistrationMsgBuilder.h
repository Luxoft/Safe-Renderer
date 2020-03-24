#ifndef LUXOFTSAFERENDERER_REGISTRATIONMSGBUILDER_H
#define LUXOFTSAFERENDERER_REGISTRATIONMSGBUILDER_H

/******************************************************************************
**
**   File:        RegistrationMsgBuilder.h
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
#include "RegistrationMsgConstants.h"

#include <OutputStream.h>
#include <LsrTypes.h>
#include <ComError.h>

namespace lsr
{

class RegistrationMsgBuilder;

OutputStream& operator<<(OutputStream& stream, const RegistrationMsgBuilder& msg);

/**
 * Message is needed to register FU in the Engine.
 * It provides data about protocol version, FU ID and registration mode.
 * It is used in the beginning of the communication.
 * Serialization function should be implemented as friend function:
 * @c OutputStream& operator<<(OutputStream&, RegistrationMsgBuilder&)
 * while deserialization should be done via @c RegistrationMessageReader object.
 */
class RegistrationMsgBuilder
{
public:
    explicit RegistrationMsgBuilder();

    U16 getSize() const;

    MessageTypes::Val getType() const;

    void setRegistrationMode(const RegistrationMode::Val mode);
    void setRemoteUid(const U32 uid);

    /**
     * Method can be used to insert FuID into the message.
     * Operation can fail if the message already contains the maximum number of FUs
     * defined by @c registrationmsgconstants::MAX_FU_COUNT.
     * See @c registrationmsgconstants::MAX_FU_COUNT.
     *
     * @param[in] fu the identificator of FU which needs to be inserted.
     *
     * @return @c true if operation succeeded, @c false otherwise.
     */
    bool addFu(const FUClassId fu);

private:
    friend OutputStream& operator<<(OutputStream& stream, const RegistrationMsgBuilder& msg);

    U8 m_majorVersion;
    U8 m_minorVersion;
    RegistrationMode::Val m_registrationMode;
    U32 m_remoteUid;
    U8 m_fuCount;
    FUClassId m_fuArray[registrationmsgconstants::MAX_FU_COUNT];
};

inline MessageTypes::Val RegistrationMsgBuilder::getType() const
{
    return MessageTypes::REGISTRATION;
}

inline void RegistrationMsgBuilder::setRegistrationMode(const RegistrationMode::Val mode)
{
    m_registrationMode = mode;
}

inline void RegistrationMsgBuilder::setRemoteUid(const U32 uid)
{
    m_remoteUid = uid;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_REGISTRATIONMSGBUILDER_H
