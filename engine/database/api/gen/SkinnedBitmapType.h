#ifndef _LSR_SKINNEDBITMAPTYPE_H_
#define _LSR_SKINNEDBITMAPTYPE_H_

/******************************************************************************
**
**   File:        SkinnedBitmapType.h
**   Description:
**   Generator:   7db08a476f8107a993e0bf7183b0cf60031dad3e
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

#include "ddh_defs.h"

namespace lsr
{

/**
 * SkinnedBitmapType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct SkinnedBitmapType
{
    const BitmapStateDefinitionType* const m_default;


    /**
     * Returns a pointer to the default child reference.
     *
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const BitmapStateDefinitionType* GetDefault() const
    {
        return m_default;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_SKINNEDBITMAPTYPE_H_
