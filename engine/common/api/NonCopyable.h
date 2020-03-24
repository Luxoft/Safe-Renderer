#ifndef POPULUSSC_NONCOPYABLE_H
#define POPULUSSC_NONCOPYABLE_H

/******************************************************************************
**
**   File:        NonCopyable.h
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

class NonCopyable
{
protected:
    NonCopyable()
    {}

    ~NonCopyable()
    {}

private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};

} // namespace lsr

#endif // POPULUSSC_NONCOPYABLE_H
