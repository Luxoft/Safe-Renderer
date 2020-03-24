#ifndef LUXOFTSAFERENDERER_DATABASE_TYPES_H
#define LUXOFTSAFERENDERER_DATABASE_TYPES_H

/******************************************************************************
**
**   File:        DatabaseTypes.h
**   Description: Forward declarations for the database (to avoid MISRA 3-2-3).
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

namespace lsr
{
typedef U16 BitmapId;

struct AreaType;
struct BaseFieldChoiceType;
struct BitmapStateDefinitionType;
struct DDHType;
struct DisplaySizeType;
struct ExpressionTermType;
struct HMIGlobalSettingsType;
struct LsrImage;
struct PanelDatabaseType;
struct PanelType;
struct ReferenceBitmapFieldType;
struct BitmapDatabaseType;
struct BitmapType;
struct SkinnedBitmapType;
struct StaticBitmapFieldType;

} // namespace lsr

#endif // LUXOFTSAFERENDERER_DATABASE_TYPES_H
