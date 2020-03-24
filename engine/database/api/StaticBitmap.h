#ifndef LUXOFTSAFERENDERER_STATIC_BITMAP_H
#define LUXOFTSAFERENDERER_STATIC_BITMAP_H

/******************************************************************************
**
**   File:        StaticBitmap.h
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

#include "ResourceBuffer.h"
#include "BitmapStateDefinitionType.h"

namespace lsr
{

/**
 * @brief Provides access to a static bitmap in the database
 */
class StaticBitmap
{
public:
    StaticBitmap(const BitmapStateDefinitionType* const bmp);

    /**
     * Returns the image data
     */
    const LsrImage* getData() const;

    /**
     * Returns a unique numeric identifier for this StaticBitmap
     */
    U16 getId() const;

private:
    const BitmapStateDefinitionType* m_bmp;
};

inline StaticBitmap::StaticBitmap(const BitmapStateDefinitionType* const bmp)
: m_bmp(bmp)
{
}

inline U16 StaticBitmap::getId() const
{
    return (NULL != m_bmp) ? m_bmp->GetStateBitmapId() : 0U;
}

inline const LsrImage* StaticBitmap::getData() const
{
    return (m_bmp != NULL) ? m_bmp->GetFile() : NULL;
}

}

#endif //RESOURCE_STATIC_BITMAP_H
