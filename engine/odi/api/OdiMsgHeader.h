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

#include <InputStream.h>
#include <OutputStream.h>
#include <LsrTypes.h>
#include <LSRError.h>

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
    explicit OdiMsgHeader(DataMessageTypes::Val type);

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
