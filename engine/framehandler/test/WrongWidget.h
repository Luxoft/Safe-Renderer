#ifndef POPULUSSC_WRONGWIDGET_H
#define POPULUSSC_WRONGWIDGET_H

/******************************************************************************
**
**   File:        WrongWidget.h
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

#include "MockWidget.h"

class WrongWidget: public MockWidget
{
public:
    WrongWidget()
    {}

    virtual Widget::WidgetType getType() const P_OVERRIDE
    {
        return static_cast<Widget::WidgetType>(Widget::WIDGET_TYPE_BITMAP_FIELD + 32U);
    }
};

#endif // POPULUSSC_WRONGWIDGET_H
