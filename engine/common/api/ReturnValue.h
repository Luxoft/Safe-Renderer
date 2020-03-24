#ifndef LUXOFTSAFERENDERER_RETURN_VALUE_H
#define LUXOFTSAFERENDERER_RETURN_VALUE_H

/******************************************************************************
**
**   File:        ReturnValue.h
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

namespace lsr
{

/**
 * Helper template class to avoid misra warning 0-1-6 for return values
 * and still guarantee value intialization
 */
template <class T, T DefaultValue>
class ReturnValue
{
public:
    ReturnValue()
        : m_val(DefaultValue)
    {}

    ReturnValue(const T& val)
        : m_val(val)
    {}

    ReturnValue& operator=(const T& val)
    {
        m_val = val;
        return *this;
    }

    operator T() const
    {
        return m_val;
    }

private:
    T m_val;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_RETURN_VALUE_H
