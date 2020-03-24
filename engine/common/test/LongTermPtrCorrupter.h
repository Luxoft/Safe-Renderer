#ifndef LUXOFTSAFERENDERER_LONGTERMPTRCORRUPTER_H
#define LUXOFTSAFERENDERER_LONGTERMPTRCORRUPTER_H

/******************************************************************************
**
**   File:        LongTermPtrCorrupter.h
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

#include <cstddef>

template <class T>
class LongTermPtrCorrupter
{
public:
    LongTermPtrCorrupter();

    void setPtr(T* ptr)
    {
        m_ptr = ptr;
    }

    void setInvertedPtr(std::size_t value)
    {
        m_invertedPtr = value;
    }

private:
    T* m_ptr;
    std::size_t m_invertedPtr;
};

#endif // LUXOFTSAFERENDERER_LONGTERMPTRCORRUPTER_H
