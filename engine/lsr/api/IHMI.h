#ifndef LUXOFTSAFERENDERER_IHMI_H
#define LUXOFTSAFERENDERER_IHMI_H

/******************************************************************************
**
**   File:        IHMI.h
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

#include <ddh_defs.h>

namespace lsr
{

// coverity[misra_cpp_2008_rule_12_8_2_violation] fix would raise 0-1-10 warnings
class IHMI
{
public:
    virtual Frame* getFrame() = 0;

protected:
    ~IHMI()
    {
    }
};


} // namespace lsr

#endif // LUXOFTSAFERENDERER_IHMI_H
