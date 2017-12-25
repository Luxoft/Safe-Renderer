/******************************************************************************
**
**   File:        DdhPanelBuilder.cpp
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

#include "DdhPanelBuilder.h"
#include "DdhStaticBitmapFieldBuilder.h"
#include "DdhReferenceBitmapFieldBuilder.h"

#include <PscLimits.h>

#include <ExpressionTermTypeFactory.h>
#include <FieldTypeFactory.h>
#include <FieldsTypeFactory.h>

namespace framehandlertests
{

DdhPanelBuilder::DdhPanelBuilder()
{}

void DdhPanelBuilder::create(const psc::AreaType& area,
                             const bool isVisible,
                             U16 fieldsCount,
                             const psc::DynamicDataType* bitmapId)
{
    addArea(area);
    addVisibility(isVisible);
    addFields(fieldsCount, isVisible, area, psc::FieldType::STATICBITMAPFIELD_CHOICE, bitmapId);
}

void DdhPanelBuilder::createWithRefBitmaps(const psc::AreaType& area,
                                           const bool isVisible,
                                           U16 fieldsCount)
{
    addArea(area);
    addVisibility(isVisible);
    addFields(fieldsCount, isVisible, area, psc::FieldType::REFERENCEBITMAPFIELD_CHOICE, NULL);
}

void DdhPanelBuilder::createWithoutArea(const psc::AreaType& area,
                                        const bool isVisible,
                                        U16 fieldsCount)
{
    addVisibility(isVisible);
    addFields(fieldsCount, isVisible, area, psc::FieldType::STATICBITMAPFIELD_CHOICE, NULL);
}

void DdhPanelBuilder::createWithoutVisibility(const psc::AreaType& area,
                                              const bool isVisible,
                                              U16 fieldsCount)
{
    addArea(area);
    addFields(fieldsCount, isVisible, area, psc::FieldType::STATICBITMAPFIELD_CHOICE, NULL);
}

void DdhPanelBuilder::createWithoutFields(const psc::AreaType& area,
                                          const bool isVisible)
{
    addArea(area);
    addVisibility(isVisible);
}

void DdhPanelBuilder::createWithFieldWithWrongType(const psc::AreaType& area,
                                                   const bool isVisible,
                                                   U16 fieldsCount)
{
    addArea(area);
    addVisibility(isVisible);
    addFields(fieldsCount, isVisible, area, psc::FieldType::STATICBITMAPFIELD_CHOICE + 2U, NULL);
}

void DdhPanelBuilder::createWithWrongField(const psc::AreaType& area,
                                           const bool isVisible,
                                           U16 fieldsCount)
{
    addArea(area);
    addVisibility(isVisible);
    addWrongFields(fieldsCount, area, psc::FieldType::STATICBITMAPFIELD_CHOICE);
}

void DdhPanelBuilder::createWithTooManyFields(const psc::AreaType& area,
                                              const bool isVisible)
{
    addArea(area);
    addVisibility(isVisible);
    addFields(MAX_WIDGET_CHILDREN_COUNT + 1,
              isVisible,
              area,
              psc::FieldType::STATICBITMAPFIELD_CHOICE,
              NULL);
}

void DdhPanelBuilder::addArea(const psc::AreaType& area)
{
    m_factory.addArea(area);
}

void DdhPanelBuilder::addVisibility(const bool isVisible)
{
    ExpressionTermTypeFactory visibilityExpr;
    visibilityExpr.createBoolExprTerm(isVisible);

    m_factory.addVisibleExpr(visibilityExpr.getDdh(), visibilityExpr.getSize());
}

void DdhPanelBuilder::addFields(const U16 fieldsCount,
                                const bool isVisible,
                                const psc::AreaType& fieldArea,
                                const U16 fieldsType,
                                const psc::DynamicDataType* bitmapId)
{
    FieldsTypeFactory fieldsFactory;
    fieldsFactory.create(fieldsCount);

    for (U16 i = 0U; i < fieldsCount; ++i)
    {
        FieldTypeFactory fieldFactory;
        fieldFactory.create(fieldsType);

        switch (fieldsType)
        {
        case psc::FieldType::REFERENCEBITMAPFIELD_CHOICE:
        {
            const U16 errorCounterId = 43U;
            DdhReferenceBitmapFieldBuilder bitmapBuilder;
            if (NULL == bitmapId)
            {
                bitmapBuilder.create(errorCounterId, fieldArea, isVisible, i);
            }
            else
            {
                bitmapBuilder.create(errorCounterId, fieldArea, isVisible, *bitmapId);
            }

            fieldFactory.addBitmap(bitmapBuilder.getDdh(), bitmapBuilder.getSize());
        }
        // all other including psc::FieldType::STATICBITMAPFIELD_CHOICE:
        default:
        {
            DdhStaticBitmapFieldBuilder bitmapBuilder;
            if (NULL == bitmapId)
            {
                bitmapBuilder.create(fieldArea, isVisible, i);
            }
            else
            {
                bitmapBuilder.create(fieldArea, isVisible, *bitmapId);
            }

            fieldFactory.addBitmap(bitmapBuilder.getDdh(), bitmapBuilder.getSize());
        }
        }

        fieldsFactory.addField(fieldFactory.getDdh(), fieldFactory.getSize());
    }

    m_factory.addFields(fieldsFactory.getDdh(), fieldsFactory.getSize());
}

void DdhPanelBuilder::addWrongFields(const U16 fieldsCount,
                                     const psc::AreaType& fieldArea,
                                     const U16 fieldsType)
{
    FieldsTypeFactory fieldsFactory;
    fieldsFactory.create(fieldsCount);

    for (U16 i = 0U; i < fieldsCount; ++i)
    {
        DdhStaticBitmapFieldBuilder bitmapBuilder;
        bitmapBuilder.createWithoutVisibility(fieldArea, i);

        FieldTypeFactory fieldFactory;
        fieldFactory.create(fieldsType);
        fieldFactory.addBitmap(bitmapBuilder.getDdh(), bitmapBuilder.getSize());

        fieldsFactory.addField(fieldFactory.getDdh(), fieldFactory.getSize());
    }

    m_factory.addFields(fieldsFactory.getDdh(), fieldsFactory.getSize());
}


} // namespace framehandlertests
