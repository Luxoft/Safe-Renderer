#ifndef LUXOFTSAFERENDERER_SELFCHECKERCLASS_H
#define LUXOFTSAFERENDERER_SELFCHECKERCLASS_H

/******************************************************************************
**
**   File:        SelfCheckerClass.h
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

#include <cstddef>

/**
 * Class can check if it was created properly.
 */

class SelfCheckerClass
{
public:
    SelfCheckerClass()
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1)
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1, std::size_t arg2)
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1, std::size_t arg2, std::size_t arg3)
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1, std::size_t arg2, std::size_t arg3, std::size_t arg4)
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1, std::size_t arg2, std::size_t arg3, std::size_t arg4, std::size_t arg5)
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1, std::size_t arg2, std::size_t arg3, std::size_t arg4, std::size_t arg5, std::size_t arg6)
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1, std::size_t arg2, std::size_t arg3, std::size_t arg4, std::size_t arg5, std::size_t arg6, std::size_t arg7)
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1, std::size_t arg2, std::size_t arg3, std::size_t arg4, std::size_t arg5, std::size_t arg6, std::size_t arg7, std::size_t arg8)
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1, std::size_t arg2, std::size_t arg3, std::size_t arg4, std::size_t arg5, std::size_t arg6, std::size_t arg7, std::size_t arg8, std::size_t arg9)
        : m_wasConstructed(true)
    {}

    SelfCheckerClass(std::size_t arg1, std::size_t arg2, std::size_t arg3, std::size_t arg4, std::size_t arg5, std::size_t arg6, std::size_t arg7, std::size_t arg8, std::size_t arg9, std::size_t arg10)
        : m_wasConstructed(true)
    {}

    inline bool wasConstructed() const
    {
        return m_wasConstructed;
    }

    ~SelfCheckerClass()
    {}

private:
    bool m_wasConstructed;
};

#endif // LUXOFTSAFERENDERER_SELFCHECKERCLASS_H
