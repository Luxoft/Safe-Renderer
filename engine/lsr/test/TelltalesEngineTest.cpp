/******************************************************************************
**
**   File:        TelltalesEngineTest.cpp
**   Description: Test database
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
#include <Telltales.cpp>

namespace TelltalesTestTooManyTextures
{

const BitmapStateDefinitionType ddh_bitmapDatabase_bitmap100_skinnedBitmap0_default = {
    100U, //attr: stateBitmapId
    __Telltales_Bitmaps_palette, //attr: file
};

const SkinnedBitmapType ddh_bitmapDatabase_bitmap100_skinnedBitmap0 = {
    &ddh_bitmapDatabase_bitmap100_skinnedBitmap0_default, // ref: default
};

const SkinnedBitmapType* ddh_bitmapDatabase_bitmap100_skinnedBitmap[] = {
    &ddh_bitmapDatabase_bitmap100_skinnedBitmap0,
};

const BitmapType ddh_bitmapDatabase_bitmap100 = {
    ddh_bitmapDatabase_bitmap100_skinnedBitmap, // ref: skinnedBitmap (list)
    1, // ref: skinnedBitmap (list size)
};

const BitmapType* ddh_bitmapDatabase_bitmap[] = {
    &ddh_bitmapDatabase_bitmap0,
    &ddh_bitmapDatabase_bitmap1,
    &ddh_bitmapDatabase_bitmap2,
    &ddh_bitmapDatabase_bitmap3,
    &ddh_bitmapDatabase_bitmap4,
    &ddh_bitmapDatabase_bitmap100,
};

// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapDatabaseType ddh_bitmapDatabase = {
    ddh_bitmapDatabase_bitmap, // ref: bitmap (list)
    6, // ref: bitmap (list size)
};

const DDHType ddh = {
    1793021406U, //attr: imagesChecksum
    2802385892U, //attr: schemaChecksum
    328960U, //attr: schemaVersion
    328960U, //attr: serializerVersion
    &ddh_panelDatabase, // ref: panelDatabase
    &ddh_bitmapDatabase, // ref: bitmapDatabase
    &ddh_hMIGlobalSettings, // ref: hMIGlobalSettings
};

const DDHType* getDDH()
{
    return &ddh;
}

} // namespace TelltalesTestTooManyTextures
