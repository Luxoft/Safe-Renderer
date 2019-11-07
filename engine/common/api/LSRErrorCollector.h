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

#include "LSRError.h"

namespace lsr
{

/**
 * Wrapper for LSRError values.
 *
 * Keeps the worst error value if multiple error values are assigned.
 * This helps to avoid accidental no-error cases if a function has
 * different sources of error:
 *
 * Example:
 *
 * LSRErrorCollector err = LSR_NO_ERROR;
 * err = LSR_UNKNOWN_ERROR; // value is assigned
 * err = LSR_NO_ERROR;      // value is NOT assigned
 */
class LSRErrorCollector
{
public:
    /**
     * Creates an error collector with an initial error value
     */
    LSRErrorCollector(const LSRError err) : m_error(err)
    {}

    /**
     * Assigns an error value if the new error is more severe than the current.
     * Otherwise the new error value is ignored.
     * @param err new error value
     * @return reference to this
     */
    LSRErrorCollector& operator=(const LSRError err)
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
    LSRError get() const
    {
        return m_error;
    }
private:
    LSRError m_error;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_LSR_ERROR_COLLECTOR_H
