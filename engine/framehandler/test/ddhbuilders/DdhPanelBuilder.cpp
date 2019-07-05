/******************************************************************************
**
**   File:        DdhPanelBuilder.cpp
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

#include "DdhPanelBuilder.h"
#include "DdhStaticBitmapFieldBuilder.h"
#include "DdhReferenceBitmapFieldBuilder.h"

#include <LsrLimits.h>

#include <ExpressionTermTypeFactory.h>
#include <FieldTypeFactory.h>
#include <FieldsTypeFactory.h>

namespace framehandlertests
{

DdhPanelBuilder::DdhPanelBuilder()
{}

void DdhPanelBuilder::create(const lsr::AreaType& area,
                             const bool isVisible,
                             U16 fieldsCount,
                             const lsr::DynamicDataType* bitmapId)
{
    addArea(area);
    addVisibility(isVisible);
    addFields(fieldsCount, isVisible, area, lsr::FieldType::STATICBITMAPFIELD_CHOICE, bitmapId);
}

void DdhPanelBuilder::createWithRefBitmaps(const lsr::AreaType& area,
                                           const bool isVisible,
                                           U16 fieldsCount)
{
    addArea(area);
    addVisibility(isVisible);
    addFields(fieldsCount, isVisible, area, lsr::FieldType::REFERENCEBITMAPFIELD_CHOICE, NULL);
}

void DdhPanelBuilder::createWithoutArea(const lsr::AreaType& area,
                                        const bool isVisible,
                                        U16 fieldsCount)
{
    addVisibility(isVisible);
    addFields(fieldsCount, isVisible, area, lsr::FieldType::STATICBITMAPFIELD_CHOICE, NULL);
}

void DdhPanelBuilder::createWithoutVisibility(const lsr::AreaType& area,
                                              const bool isVisible,
                                              U16 fieldsCount)
{
    addArea(area);
    addFields(fieldsCount, isVisible, area, lsr::FieldType::STATICBITMAPFIELD_CHOICE, NULL);
}

void DdhPanelBuilder::createWithoutFields(const lsr::AreaType& area,
                                          const bool isVisible)
{
    addArea(area);
    addVisibility(isVisible);
}

void DdhPanelBuilder::createWithFieldWithWrongType(const lsr::AreaType& area,
                                                   const bool isVisible,
                                                   U16 fieldsCount)
{
    addArea(area);
    addVisibility(isVisible);
    addFields(fieldsCount, isVisible, area, lsr::FieldType::STATICBITMAPFIELD_CHOICE + 2U, NULL);
}

void DdhPanelBuilder::createWithWrongField(const lsr::AreaType& area,
                                           const bool isVisible,
                                           U16 fieldsCount)
{
    addArea(area);
    addVisibility(isVisible);
    addWrongFields(fieldsCount, area, lsr::FieldType::STATICBITMAPFIELD_CHOICE);
}

void DdhPanelBuilder::createWithTooManyFields(const lsr::AreaType& area,
                                              const bool isVisible)
{
    addArea(area);
    addVisibility(isVisible);
    addFields(MAX_WIDGET_CHILDREN_COUNT + 1,
              isVisible,
              area,
              lsr::FieldType::STATICBITMAPFIELD_CHOICE,
              NULL);
}

void DdhPanelBuilder::addArea(const lsr::AreaType& area)
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
                                const lsr::AreaType& fieldArea,
                                const U16 fieldsType,
                                const lsr::DynamicDataType* bitmapId)
{
    FieldsTypeFactory fieldsFactory;
    fieldsFactory.create(fieldsCount);

    for (U16 i = 0U; i < fieldsCount; ++i)
    {
        FieldTypeFactory fieldFactory;
        fieldFactory.create(fieldsType);

        switch (fieldsType)
        {
        case lsr::FieldType::REFERENCEBITMAPFIELD_CHOICE:
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
        // all other including lsr::FieldType::STATICBITMAPFIELD_CHOICE:
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
                                     const lsr::AreaType& fieldArea,
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
