#ifndef LUXOFTSAFERENDERER_POOLMARKER_H
#define LUXOFTSAFERENDERER_POOLMARKER_H

/******************************************************************************
**
**   File:        PoolMarker.h
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

#include "LsrTypes.h"

#include <cstddef>

namespace lsr
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
 * @reqid SW_ENG_037, SW_ENG_034
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
inline PoolMarker<MarkerSize>::PoolMarker(const U8 data)
{
    static_cast<void>(std::memset(m_marker, static_cast<I32>(data), MarkerSize));  // ignore return value
}

template <std::size_t MarkerSize>
inline PoolMarker<MarkerSize>::PoolMarker(const PoolMarker<MarkerSize>& rhs)
{
    static_cast<void>(std::memcpy(m_marker, rhs.m_marker, MarkerSize));  // ignore return value
}

template <std::size_t MarkerSize>
inline const PoolMarker<MarkerSize>& PoolMarker<MarkerSize>::operator=(const PoolMarker<MarkerSize>& rhs)
{
    if (this != &rhs)
    {
        static_cast<void>(std::memcpy(m_marker, rhs.m_marker, MarkerSize));  // ignore return value
    }
    return *this;
}

template <std::size_t MarkerSize>
inline bool PoolMarker<MarkerSize>::operator==(const PoolMarker<MarkerSize>& rhs) const
{
    return (0 == memcmp(m_marker, rhs.m_marker, MarkerSize));
}

template<std::size_t MarkerSize>
inline bool PoolMarker<MarkerSize>::isEqualToPattern(const PoolMarker<MarkerSize>& marker,
                                              const U8 markerPattern)
{
    const PoolMarker<MarkerSize> tmpMarker(markerPattern);
    return marker == tmpMarker;
}

} // namespace impl

} // namespace lsr

#endif // LUXOFTSAFERENDERER_POOLMARKER_H
