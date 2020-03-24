/******************************************************************************
**
**   File:        RegistrationMsgReader.cpp
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

#include "RegistrationMsgReader.h"
#include "OdiMessageUtils.h"
#include "RegistrationMsgConstants.h"

namespace lsr
{

RegistrationMsgReader::RegistrationMsgReader(InputStream& stream)
    : m_majorVersion(0U)
    , m_minorVersion(0U)
    , m_mode(RegistrationMode::UNKNOWN)
    , m_remoteUid(0U)
    , m_fuCount(0U)
    , m_stream(stream)
{
    m_stream >> m_majorVersion;
    m_stream >> m_minorVersion;

    U8 tmpMode = 0U;
    m_stream >> tmpMode;
    if (!messageutils::checkRegistrationMode(tmpMode))
    {
        m_stream.setError(COM_INVALID_FIELD_IN_MSG);
    }
    else
    {
        m_mode = static_cast<RegistrationMode::Val>(tmpMode);
        m_stream >> m_remoteUid;
        m_stream >> m_fuCount;
    }
}

U8 RegistrationMsgReader::getMajorVersion() const
{
    return m_majorVersion;
}

U8 RegistrationMsgReader::getMinorVersion() const
{
    return m_minorVersion;
}

RegistrationMode::Val RegistrationMsgReader::getRegistrationMode() const
{
    return m_mode;
}

U32 RegistrationMsgReader::getRemoteUid() const
{
    return m_remoteUid;
}

U8 RegistrationMsgReader::getFuCount() const
{
    return m_fuCount;
}

FUClassId RegistrationMsgReader::getNextFu() const
{
    FUClassId fu = 0U;
    m_stream >> fu;
    return fu;
}

} // namespace lsr
