#ifndef LUXOFTSAFERENDERER_DATASTATUS_H
#define LUXOFTSAFERENDERER_DATASTATUS_H

/******************************************************************************
**
**   File:        DataStatus.h
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

#include <LSRError.h>

namespace lsr
{

/**
 * Struct describes the status of data.
 *
 * - @c NOT_AVAILABLE - the data is invalid because it is not received yet.
 * - @c VALID         - the data is valid, this flag was set by FU;
 * - @c INVALID       - the data is invalid, this flag was set by FU;
 * - @c INCONSISTENT  - the data is invalid because there was some error during evaluation of
 *                      this data on engine side;
 *
 * @reqid SW_ENG_066
 */
struct DataStatus
{
public:
    enum Enum
    {
        NOT_AVAILABLE = 0,
        VALID,
        INVALID,
        INCONSISTENT
    };

    DataStatus();

    DataStatus(const Enum status);

    DataStatus::Enum getValue() const;

    LSRError convertToLSRError() const;

private:
    friend bool operator==(const DataStatus& lhs, const DataStatus& rhs);

    Enum m_status;
};

inline DataStatus::DataStatus(const Enum status)
    : m_status(status)
{}

inline DataStatus::DataStatus()
    : m_status(DataStatus::NOT_AVAILABLE)
{}

inline DataStatus::Enum DataStatus::getValue() const
{
    return m_status;
}

inline LSRError DataStatus::convertToLSRError() const
{
    LSRError res = LSR_UNKNOWN_ERROR;

    switch (m_status)
    {
    case VALID:
        res = LSR_NO_ERROR;
        break;
    case INVALID:
        res = LSR_DATASTATUS_INVALID;
        break;
    case NOT_AVAILABLE:
        res = LSR_DATASTATUS_NOT_AVAIABLE;
        break;
    default:
        res = LSR_DATASTATUS_INCONSISTENT;
        break;
    }

    return res;
}

inline bool operator==(const DataStatus& lhs, const DataStatus& rhs)
{
    return lhs.m_status == rhs.m_status;
}

inline bool operator!=(const DataStatus& lhs, const DataStatus& rhs)
{
    return !(lhs == rhs);
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_DATASTATUS_H
