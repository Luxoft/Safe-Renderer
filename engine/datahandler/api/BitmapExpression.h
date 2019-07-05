#ifndef LUXOFTSAFERENDERER_BITMAPEXPRESSION_H
#define LUXOFTSAFERENDERER_BITMAPEXPRESSION_H

/******************************************************************************
**
**   File:        BitmapExpression.h
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

#include "NumberExpression.h"

#include <ddh_defs.h>

namespace lsr
{

/**
 * Represents an expression of type @c BitmapId.
 *
 * Bitmap expressions can get dynamic data, constants or calculate nested expressions.
 *
 * @reqid SW_ENG_065
 */
class BitmapExpression P_FINAL: public NumberExpression
{
public:
    BitmapExpression();

    /**
     * Returns the current value.
     *
     * @param[out] value the output value.
     *
     * @return status of @c value, see @c DataStatus.
     */
    DataStatus getValue(BitmapId& value) const;

private:
    BitmapExpression(const BitmapExpression&);
    BitmapExpression& operator=(const BitmapExpression&);
};

} // namespace datahandler;

#endif // LUXOFTSAFERENDERER_BITMAPEXPRESSION_H
