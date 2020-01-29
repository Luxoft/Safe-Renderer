#ifndef _LSR_BASEFIELDCHOICETYPE_H_
#define _LSR_BASEFIELDCHOICETYPE_H_

/******************************************************************************
**
**   File:        BaseFieldChoiceType.h
**   Description:
**   Generator:   c78c5138ac2e7c6506a52bfc6fbc0ef05f7ad869
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   Luxoft Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
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
