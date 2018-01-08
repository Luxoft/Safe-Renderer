#ifndef POPULUSSC_PSC_ERROR_COLLECTOR_H
#define POPULUSSC_PSC_ERROR_COLLECTOR_H

/******************************************************************************
**
**   File:        PSCErrorCollector.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "PSCError.h"

namespace psc
{

/**
 * Wrapper for PSCError values.
 *
 * Keeps the worst error value if multiple error values are assigned.
 * This helps to avoid accidental no-error cases if a function has
 * different sources of error:
 *
 * Example:
 *
 * PSCErrorCollector err = PSC_NO_ERROR;
 * err = PSC_UNKNOWN_ERROR; // value is assigned
 * err = PSC_NO_ERROR;      // value is NOT assigned
 */
class PSCErrorCollector
{
public:
    /**
     * Creates an error collector with an initial error value
     */
    PSCErrorCollector(PSCError err) : m_error(err)
    {}

    /**
     * Assigns an error value if the new error is more severe than the current.
     * Otherwise the new error value is ignored.
     * @param err new error value
     * @return reference to this
     */
    PSCErrorCollector& operator=(PSCError err)
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
    PSCError get() const
    {
        return m_error;
    }
private:
    PSCError m_error;
};

} // namespace psc

#endif // POPULUSSC_PSC_ERROR_COLLECTOR_H
