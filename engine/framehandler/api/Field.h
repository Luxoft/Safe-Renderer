#ifndef POPULUSSC_FIELD_H
#define POPULUSSC_FIELD_H

/******************************************************************************
**
**   File:        Field.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

namespace psc
{

struct FieldType;
class Database;
class DataContext;
class WidgetPool;

/**
 * @reqid SW_ENG_076
 */
class Field : public Widget
{
public:
    /**
     * Method creates a @c Field object with given @c widgetPool according
     * to configuration @c ddh.
     *
     * @param[in]  widgetPool pool which provides allocation objects.
     * @param[in]  db         object provides work with database.
     * @param[in]  pDdh       @c FieldType ddh configuration.
     * @param[in]  pContext   data context, which shall be used for evaluation.
     * @param[out] error      error state will be equal to @c PSC_NO_ERROR if
     *                        operation succeeded, other @c PSCError values otherwise.
     *
     * @return pointer to @c Field object if initialization of object was successful,
     *         @c NULL otherwise.
     */
    static Field* create(WidgetPool& widgetPool,
                         const Database& db,
                         const FieldType* pDdh,
                         DataContext* pContext,
                         PSCErrorCollector& error);

protected:
    Field();
};

} // namespace psc

#endif // POPULUSSC_FIELD_H
