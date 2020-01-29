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
**   Luxoft Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Render is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Render.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
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
     * Method creates a @c Field object with given @c WidgetPool according
     * to configuration @c ddh.
     *
     * @param[in]  factory    pool which provides allocation objects.
     * @param[in]  db         object provides work with database.
     * @param[in]  pDdh       @c FieldType ddh configuration.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c LSR_NO_ENGINE_ERROR if
     *                        operation succeeded, other @c LSREngineError values otherwise.
     *
     * @return pointer to @c Field object if initialization of object was successful,
     *         @c NULL otherwise.
     */
    static Field* create(WidgetPool& factory,
                         const Database& db,
                         const BaseFieldChoiceType* const pDdh,
                         DataContext* const pContext,
                         LSRErrorCollector& error);

protected:
    Field();
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_FIELD_H
