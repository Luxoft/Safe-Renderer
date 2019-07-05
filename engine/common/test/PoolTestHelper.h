#ifndef LUXOFTSAFERENDERER_POOLTESTHELPER_H
#define LUXOFTSAFERENDERER_POOLTESTHELPER_H

/******************************************************************************
**
**   File:        PoolTestHelper.h
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

class PoolTestHelperBase
{
public:
    PoolTestHelperBase()
        : m_var1(5u)
    {
    }

    virtual ~PoolTestHelperBase()
    {}

private:
    U8 m_var1;
    U8 m_array1[127];
};

class PoolTestHelperSmall: public PoolTestHelperBase
{
public:
    PoolTestHelperSmall()
        : m_var2(123u)
    {}

private:
    U8 m_var2;
};

class PoolTestHelperLarge: public PoolTestHelperBase
{
public:
    PoolTestHelperSmall()
    {
        memset(m_array2, 0xAA, sizeof(m_array2));
    }

private:
    U8 m_array2;
};

#endif // LUXOFTSAFERENDERER_POOLTESTHELPER_H
