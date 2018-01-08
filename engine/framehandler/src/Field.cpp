/******************************************************************************
**
**   File:        Field.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
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

#include "Field.h"
#include "BitmapField.h"
#include "ReferenceBitmapField.h"

#include <FieldType.h>

namespace psc
{

Field* Field::create(WidgetPool& widgetPool,
                     const Database& db,
                     const FieldType* pDdh,
                     DataContext* pContext,
                     PSCErrorCollector& error)
{
    Field* field = NULL;
    switch (pDdh->GetFieldTypeChoice())
    {
    case FieldType::STATICBITMAPFIELD_CHOICE:
    {
        field = BitmapField::create(widgetPool,
                                    db,
                                    pDdh->GetStaticBitmapField(),
                                    pContext,
                                    error);
        break;
    }
    case FieldType::REFERENCEBITMAPFIELD_CHOICE:
    {
        field = ReferenceBitmapField::create(widgetPool,
                                             db,
                                             pDdh->GetReferenceBitmapField(),
                                             pContext,
                                             error);
        break;
    }
    default:
    {
        error = PSC_DB_INCONSISTENT;
        break;
    }
    }
    return field;
}

Field::Field()
{}

} // namespace psc
