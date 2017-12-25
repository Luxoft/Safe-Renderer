#ifndef POPULUSSC_POOLMARKER_H
#define POPULUSSC_POOLMARKER_H

/******************************************************************************
**
**   File:        PoolMarker.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

#include "PscTypes.h"

#include <cstddef>

namespace psc
{

namespace impl
{

/**
 * Class stores an array of U8 data with size @c MarkerSize.
 * This data can be set with constructor (see @c PoolMarker::PoolMarker(const U8 data)),
 * copy constructor (see @c PoolMarker) or assignment operator (see @c operator=).
 * All bytes in the array contain the same value.
 *
 * Also this class provides comparison operator (see @c operator==)
 * to identify if two objects are equal or not.
 *
 * @tparam MarkerSize size of the marker in bytes.
 */
template <std::size_t MarkerSize>
class PoolMarker
{
public:
    /**
     * Constructor sets internal array to the specified value: @c data.
     *
     * @param[in] data value which needs to be assigned to the internal array.
     */
    explicit PoolMarker(const U8 data);

    PoolMarker(const PoolMarker& rhs);

    const PoolMarker& operator=(const PoolMarker& rhs);

    bool operator==(const PoolMarker& rhs) const;

    static bool isEqualToPattern(const PoolMarker<MarkerSize>& marker, const U8 markerPattern);

private:
    U8 m_marker[MarkerSize];
};

template <std::size_t MarkerSize>
PoolMarker<MarkerSize>::PoolMarker(const U8 data)
{
    memset(m_marker, data, MarkerSize);
}

template <std::size_t MarkerSize>
PoolMarker<MarkerSize>::PoolMarker(const PoolMarker<MarkerSize>& rhs)
{
    memcpy(m_marker, rhs.m_marker, MarkerSize);
}

template <std::size_t MarkerSize>
const PoolMarker<MarkerSize>& PoolMarker<MarkerSize>::operator=(const PoolMarker<MarkerSize>& rhs)
{
    if (this != &rhs)
    {
        memcpy(m_marker, rhs.m_marker, MarkerSize);
    }
    return *this;
}

template <std::size_t MarkerSize>
bool PoolMarker<MarkerSize>::operator==(const PoolMarker<MarkerSize>& rhs) const
{
    return (0 == memcmp(m_marker, rhs.m_marker, MarkerSize));
}

template<std::size_t MarkerSize>
bool PoolMarker<MarkerSize>::isEqualToPattern(const PoolMarker<MarkerSize>& marker,
                                              const U8 markerPattern)
{
    const PoolMarker<MarkerSize> tmpMarker(markerPattern);
    return marker == tmpMarker;
}

} // namespace impl

} // namespace psc

#endif // POPULUSSC_POOLMARKER_H
