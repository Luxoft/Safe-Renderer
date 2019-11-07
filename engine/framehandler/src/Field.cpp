/******************************************************************************
**
**   File:        Field.cpp
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

#include "Field.h"
#include "BitmapField.h"
#include "ReferenceBitmapField.h"

#include <BaseFieldChoiceType.h>

namespace lsr
{

Field* Field::create(WidgetPool& widgetPool,
                     const Database& db,
                     const BaseFieldChoiceType* const pDdh,
                     DataContext* const pContext,
                     LSRErrorCollector& error)
{
    Field* field = NULL;
    switch (pDdh->GetBaseFieldChoiceTypeChoice())
    {
    case BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE:
    {
        field = BitmapField::create(widgetPool,
                                    db,
                                    pDdh->GetStaticBitmapField(),
                                    pContext,
                                    error);
        break;
    }
    case BaseFieldChoiceType::REFERENCEBITMAPFIELD_CHOICE:
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
        error = LSR_DB_INCONSISTENT;
        break;
    }
    }
    return field;
}

Field::Field()
: Widget()
{}

} // namespace lsr
