#ifndef LUXOFTSAFERENDERER_DATABASE_H
#define LUXOFTSAFERENDERER_DATABASE_H

/******************************************************************************
**
**   File:        Database.h
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

#include "ddh_defs.h"
#include "LSREngineError.h"
#include "StaticBitmap.h"

namespace lsr
{

/**
 * Provides access to the static HMI configuration
 */
class Database
{
public:
    Database(const DDHType* const ddh);

    LSREngineError getError() const;

    const DDHType* getDdh() const;

    StaticBitmap getBitmap(const BitmapId id) const;

private:
    const DDHType* m_ddh;
    LSREngineError m_error;
};

inline LSREngineError Database::getError() const
{
    return m_error;
}

inline const DDHType* Database::getDdh() const
{
    return m_ddh;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_DATABASE_H
