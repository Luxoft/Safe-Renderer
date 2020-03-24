#ifndef LUXOFTSAFERENDERER_ODIMSGHEADER_H
#define LUXOFTSAFERENDERER_ODIMSGHEADER_H

/******************************************************************************
**
**   File:        OdiMsgHeader.h
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

class OdiMsgHeader;

InputStream& operator>>(InputStream& stream, OdiMsgHeader& header);
OutputStream& operator<<(OutputStream& stream, const OdiMsgHeader& header);

/**
 * @reqid SW_ENG_136, SW_ENG_137, SW_ENG_140, SW_ENG_141
 */
class OdiMsgHeader
{
public:
    explicit OdiMsgHeader(const DataMessageTypes::Val type);

    static OdiMsgHeader fromStream(InputStream& stream);

    U16 getSize() const;

    /**
     * Returns value of the data message type field from the lsr header struct.
     *
     * @return value of the data message type. see @c DataMessageTypes
     */
    DataMessageTypes::Val getOdiType() const;

private:
    OdiMsgHeader();

    friend InputStream& operator>>(InputStream& stream, OdiMsgHeader& header);
    friend OutputStream& operator<<(OutputStream& stream, const OdiMsgHeader& header);

    DataMessageTypes::Val m_type;
};

inline DataMessageTypes::Val OdiMsgHeader::getOdiType() const
{
    return m_type;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_ODIMSGHEADER_H
