#ifndef LUXOFTSAFERENDERER_TIMER_H
#define LUXOFTSAFERENDERER_TIMER_H

/******************************************************************************
**
**   File:        Timer.h
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

#include "LsrTypes.h"
#include "LSREngineError.h"
#include "pil.h"

#include <cstddef>

namespace lsr
{

/**
 * Utility to calculate elapsed times
 */
class Timer
{
public:
    Timer();

    /**
     * Starts the timer.
     */
    void start();

    /**
     * Returns the time in milliseconds since the timer was started / restarted
     */
    U32 getElapsed() const;

    /**
     * Combination of getElapsed() and start() in a single call
     */
    U32 restart();

    /**
     * returns true if timeout milliseconds (or more) have elapsed since the timer was (re)started
     */
    bool hasExpired(const U32 timeout) const;

private:
    U32 getDiff(const U32 currentTime) const;
    U32 m_startTime;
};

inline Timer::Timer()
: m_startTime(0U)
{
}

inline void Timer::start()
{
    m_startTime = pilGetMonotonicTime();
}

inline U32 Timer::getElapsed() const
{
    return getDiff(pilGetMonotonicTime());
}

inline U32 Timer::restart()
{
    const U32 currentTime = pilGetMonotonicTime();
    const U32 elapsed = getDiff(currentTime);
    m_startTime = currentTime;
    return elapsed;
}

inline bool Timer::hasExpired(const U32 timeout) const
{
    return (getElapsed() >= timeout);
}

inline U32 Timer::getDiff(const U32 currentTime) const
{
    const U32 diff = (currentTime >= m_startTime)
        ? (currentTime - m_startTime)
        : ((0xffffffffU - (m_startTime - currentTime)) + 1U);
    return diff;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_TIMER_H
