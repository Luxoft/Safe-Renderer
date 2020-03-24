/******************************************************************************
**
**   File:        TelltalesDisplayTest.cpp
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
#include "TelltalesDisplayTest.h"

namespace TelltalesDisplayNoBmp
{
const BitmapType* ddh_bitmapDatabase_bitmap[] = {
    &ddh_bitmapDatabase_bitmap0,
    NULL,
    &ddh_bitmapDatabase_bitmap2,
    &ddh_bitmapDatabase_bitmap3,
    &ddh_bitmapDatabase_bitmap4,
};

// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapDatabaseType ddh_bitmapDatabase = {
    ddh_bitmapDatabase_bitmap, // ref: bitmap (list)
    5, // ref: bitmap (list size)
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

const lsr::DDHType* getDDH()
{
    return &ddh;
}

} // TelltalesDisplayNoSkin

namespace TelltalesDisplayNoSkin
{
const SkinnedBitmapType* ddh_bitmapDatabase_bitmap1_skinnedBitmap[] = {
    &ddh_bitmapDatabase_bitmap1_skinnedBitmap0,
};

const BitmapType ddh_bitmapDatabase_bitmap1 = {
    ddh_bitmapDatabase_bitmap1_skinnedBitmap, // ref: skinnedBitmap (list)
    0, // ref: skinnedBitmap (list size)
};

const BitmapType* ddh_bitmapDatabase_bitmap[] = {
    &ddh_bitmapDatabase_bitmap0,
    &ddh_bitmapDatabase_bitmap1,
    &ddh_bitmapDatabase_bitmap2,
    &ddh_bitmapDatabase_bitmap3,
    &ddh_bitmapDatabase_bitmap4,
};

// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapDatabaseType ddh_bitmapDatabase = {
    ddh_bitmapDatabase_bitmap, // ref: bitmap (list)
    5, // ref: bitmap (list size)
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

const lsr::DDHType* getDDH()
{
    return &ddh;
}

} // TelltalesDisplayNoSkin

namespace TelltalesDisplayNoState
{

const SkinnedBitmapType ddh_bitmapDatabase_bitmap4_skinnedBitmap0 = {
    NULL,
};

const SkinnedBitmapType* ddh_bitmapDatabase_bitmap4_skinnedBitmap[] = {
    &ddh_bitmapDatabase_bitmap4_skinnedBitmap0,
};

const BitmapType ddh_bitmapDatabase_bitmap4 = {
    ddh_bitmapDatabase_bitmap4_skinnedBitmap, // ref: skinnedBitmap (list)
    1, // ref: skinnedBitmap (list size)
};

const BitmapType* ddh_bitmapDatabase_bitmap[] = {
    &ddh_bitmapDatabase_bitmap0,
    &ddh_bitmapDatabase_bitmap1,
    &ddh_bitmapDatabase_bitmap2,
    &ddh_bitmapDatabase_bitmap3,
    &ddh_bitmapDatabase_bitmap4,
};

// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapDatabaseType ddh_bitmapDatabase = {
    ddh_bitmapDatabase_bitmap, // ref: bitmap (list)
    5, // ref: bitmap (list size)
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

} // namespace TelltalesDisplayNoState
