#ifndef LUXOFTSAFERENDERER_REGISTRATIONMSGREADER_H
#define LUXOFTSAFERENDERER_REGISTRATIONMSGREADER_H

/******************************************************************************
**
**   File:        RegistrationMsgReader.h
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
#include "RegistrationMsgBuilder.h"
#include "RegistrationMsgConstants.h"

#include <InputStream.h>
#include <LsrTypes.h>
#include <ComError.h>

namespace lsr
{

/**
 * This reader provides functionality to read @c InputStream with serialized
 * @c RegistrationMsgBuilder in it.
 * It provides several functions to get information from stream such as to get major version,
 * registration mode, etc.
 *
 * Size of the message should be checked by execute method @c checkMsgSize() before calling all
 * other getters.
 *
 * If errors are encountered during deserialization, the error flag inside the stream will be set.
 * See @c InputStream::getError() method.
 * If @c InputStream::getError() returns @c COM_NO_ERROR value, the value
 * of the parameters can be considered correct;
 * in case the error flag has any other value, the value of the parameters shall be considered incorrect.
 *
 * @reqid SW_ENG_136, SW_ENG_137, SW_ENG_139, SW_ENG_141, SW_ENG_146
 */
class RegistrationMsgReader
{
public:
    /**
     * Method constructs an object and tries to get from the stream the information about
     * versions, registration mode, remote ids and count of fu.
     * If errors are encountered during deserialization, the error flag inside the stream will be set.
     *
     * @param[in] stream reference to the stream with registration message inside it.
     *                   While the @c RegistrationmsgReader object is in use, error flag inside
     *                   @c stream can be set.
     */
    explicit RegistrationMsgReader(InputStream& stream);

    /**
     * These methods provide functionality to get values of parameters, which were previously
     * parsed in constructor.
     */
    U8 getMajorVersion() const;
    U8 getMinorVersion() const;
    RegistrationMode::Val getRegistrationMode() const;
    U32 getRemoteUid() const;
    U8 getFuCount() const;

    /**
     * Method returns the next unread FU identifier from the message.
     * Monitoring the FU count (see @c getFuCount) and deciding whether @c getNextFu
     * shall/can be called is the caller's responsibility.
     *
     * @return FU identifier.
     */
    FUClassId getNextFu() const;

private:
    U8 m_majorVersion;
    U8 m_minorVersion;
    RegistrationMode::Val m_mode;
    U32 m_remoteUid;
    U8 m_fuCount;
    InputStream& m_stream;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_REGISTRATIONMSGREADER_H
