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

Field* Field::create(WidgetPool& factory,
                     const Database& db,
                     const BaseFieldChoiceType* const pDdh,
                     DataContext* const pContext,
                     LSRErrorCollector& error)
{
    Field* pField = NULL;
    switch (pDdh->GetBaseFieldChoiceTypeChoice())
    {
    case BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE:
    {
        static_cast<void>(pField);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        pField = BitmapField::create(factory,
                                    db,
                                    pDdh->GetStaticBitmapField(),
                                    pContext,
                                    error);
        break;
    }
    case BaseFieldChoiceType::REFERENCEBITMAPFIELD_CHOICE:
    {
        static_cast<void>(pField);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        pField = ReferenceBitmapField::create(factory,
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
    return pField;
}

Field::Field()
: Widget()
{}

} // namespace lsr
