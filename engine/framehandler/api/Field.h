#ifndef LUXOFTSAFERENDERER_FIELD_H
#define LUXOFTSAFERENDERER_FIELD_H

/******************************************************************************
**
**   File:        Field.h
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

#include "Widget.h"

namespace lsr
{

/**
 * @reqid SW_ENG_076
 */
class Field : public Widget
{
public:
    /**
     * Connects the Field with the Database component
     * @param[in] db database provides access to the bitmap resources
     * @return error state will be equal to @c LSR_NO_ENGINE_ERROR if
     *                      operation succeeded, other @c LSREngineError values otherwise.
     */
    virtual LSREngineError setup(const Database& db) = 0;

protected:
    Field();

private:
    // coverity[misra_cpp_2008_rule_3_2_2_violation] common pattern to forbid copies
    // coverity[misra_cpp_2008_rule_3_2_4_violation] common pattern to forbid copies
    Field(const Field&);
    // coverity[misra_cpp_2008_rule_3_2_2_violation] common pattern to forbid assignment
    // coverity[misra_cpp_2008_rule_3_2_4_violation] common pattern to forbid assignment
    Field& operator=(const Field&);
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_FIELD_H
