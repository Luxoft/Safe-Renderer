#ifndef LUXOFTSAFERENDERER_LSR_ERROR_COLLECTOR_H
#define LUXOFTSAFERENDERER_LSR_ERROR_COLLECTOR_H

/******************************************************************************
**
**   File:        LSRErrorCollector.h
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

#include "LSREngineError.h"

namespace lsr
{

/**
 * Wrapper for LSREngineError values.
 *
 * Keeps the highest error value if multiple error values are assigned.
 * This helps to avoid accidental no-error cases if a function has
 * different sources of error:
 *
 * Example:
 *
 * TErrorCollector<LSREngineError> err = LSR_NO_ERROR;
 * err = LSR_UNKNOWN_ERROR; // value is assigned
 * err = LSR_NO_ERROR;      // value is NOT assigned
 */
template <class T>
class TErrorCollector
{
public:
    /**
     * Creates an error collector with an initial error value
     */
    TErrorCollector(const T err) : m_error(err)
    {}

    /**
     * Assigns an error value if the new error is more severe than the current.
     * Otherwise the new error value is ignored.
     * @param err new error value
     * @return reference to this
     */
    TErrorCollector& operator=(const T err)
    {
        if (err > m_error)
        {
            m_error = err;
        }
        return *this;
    }

    /**
     * Returns the stored error value
     * @return resulting error
     */
    T get() const
    {
        return m_error;
    }
private:
    T m_error;
};

typedef TErrorCollector<LSREngineError> LSRErrorCollector;

} // namespace lsr

#endif // LUXOFTSAFERENDERER_LSR_ERROR_COLLECTOR_H
