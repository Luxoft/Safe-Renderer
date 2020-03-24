#ifndef _LSR_BASEFIELDCHOICETYPE_H_
#define _LSR_BASEFIELDCHOICETYPE_H_

/******************************************************************************
**
**   File:        BaseFieldChoiceType.h
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
 * BaseFieldChoiceType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct BaseFieldChoiceType
{
    /** Choice constants enumeration */
    typedef enum BaseFieldChoiceTypeChoice_Tag
    {
        NONE = 0,
        REFERENCEBITMAPFIELD_CHOICE,
        STATICBITMAPFIELD_CHOICE,
    } BaseFieldChoiceTypeChoice;

    const BaseFieldChoiceTypeChoice choiceTag;
    const void* const ptr;


    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    BaseFieldChoiceTypeChoice GetBaseFieldChoiceTypeChoice() const
    {
        return choiceTag;
    }
    /**
     * Returns a pointer to the ReferenceBitmapField choice option. Return NULL
     * if this choice is not the selected option.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const ReferenceBitmapFieldType* GetReferenceBitmapField() const
    {
        return (choiceTag == REFERENCEBITMAPFIELD_CHOICE) ?
            // coverity[misra_cpp_2008_rule_5_2_8_violation]
            static_cast<const ReferenceBitmapFieldType*>(ptr) : NULL;
    }

    /**
     * Returns a pointer to the StaticBitmapField choice option. Return NULL
     * if this choice is not the selected option.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const StaticBitmapFieldType* GetStaticBitmapField() const
    {
        return (choiceTag == STATICBITMAPFIELD_CHOICE) ?
            // coverity[misra_cpp_2008_rule_5_2_8_violation]
            static_cast<const StaticBitmapFieldType*>(ptr) : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_BASEFIELDCHOICETYPE_H_
