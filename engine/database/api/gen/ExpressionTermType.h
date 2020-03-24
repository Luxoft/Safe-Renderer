#ifndef _LSR_EXPRESSIONTERMTYPE_H_
#define _LSR_EXPRESSIONTERMTYPE_H_

/******************************************************************************
**
**   File:        ExpressionTermType.h
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
 * ExpressionTermType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct ExpressionTermType
{
    /** Choice constants enumeration */
    typedef enum ExpressionTermTypeChoice_Tag
    {
        NONE = 0,
        BOOLEAN_CHOICE,
        BITMAPID_CHOICE,
    } ExpressionTermTypeChoice;

    const ExpressionTermTypeChoice choiceTag;
    const U32 choiceAttribute;
    const void* const ptr;


    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    ExpressionTermTypeChoice GetExpressionTermTypeChoice() const
    {
        return choiceTag;
    }
    /**
     * Returns the value of the boolean choice option.
     * Returns 0 if this choice is not the selected option
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    bool GetBoolean() const
    {
        return (choiceTag == BOOLEAN_CHOICE) ?
            (choiceAttribute != 0U) : false;
    }
    /**
     * Returns the value of the bitmapId choice option.
     * Returns 0 if this choice is not the selected option
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetBitmapId() const
    {
        return (choiceTag == BITMAPID_CHOICE) ?
            static_cast<U16>(choiceAttribute) : 0U;
    }
};

} // namespace lsr

#endif // #ifndef _LSR_EXPRESSIONTERMTYPE_H_
