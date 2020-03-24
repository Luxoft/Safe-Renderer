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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include <LSREngineError.h>

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

    LSREngineError convertToLSRError() const;

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

inline LSREngineError DataStatus::convertToLSRError() const
{
    LSREngineError res = LSR_NO_ENGINE_ERROR;

    switch (m_status)
    {
    case VALID:
        static_cast<void>(res);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        res = LSR_NO_ENGINE_ERROR;
        break;
    case INVALID:
        static_cast<void>(res);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        res = LSR_ERR_DATASTATUS_INVALID;
        break;
    case NOT_AVAILABLE:
        static_cast<void>(res);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        res = LSR_ERR_DATASTATUS_NOT_AVAILABLE;
        break;
    default:
        static_cast<void>(res);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        res = LSR_ERR_DATASTATUS_INCONSISTENT;
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
