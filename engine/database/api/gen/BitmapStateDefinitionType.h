#ifndef _LSR_BITMAPSTATEDEFINITIONTYPE_H_
#define _LSR_BITMAPSTATEDEFINITIONTYPE_H_

/******************************************************************************
**
**   File:        BitmapStateDefinitionType.h
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
 * BitmapStateDefinitionType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct BitmapStateDefinitionType
{
    const U16 m_stateBitmapId;
    const LsrImage* const m_file;


    /**
     * Returns the value of the stateBitmapId attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetStateBitmapId() const
    {
        return m_stateBitmapId;
    }

    /**
     * Returns the value of the file attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const LsrImage* GetFile() const
    {
        return m_file;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_BITMAPSTATEDEFINITIONTYPE_H_
