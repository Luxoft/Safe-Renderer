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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
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
