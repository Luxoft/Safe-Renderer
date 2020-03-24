/******************************************************************************
**
**   File:        Telltales.cpp
**   Description: Serialized Database
**
**   Copyright (C) 2017 Luxoft GmbH
******************************************************************************/

#include "Telltales.hpp"
#include "TelltalesHMI.hpp"
#include "Telltales_images.cpp"

#include "DDHType.h"
#include "PanelDatabaseType.h"
#include "PanelType.h"
#include "AreaType.h"
#include "ExpressionTermType.h"
#include "BaseFieldChoiceType.h"
#include "ReferenceBitmapFieldType.h"
#include "StaticBitmapFieldType.h"
#include "BitmapDatabaseType.h"
#include "BitmapType.h"
#include "SkinnedBitmapType.h"
#include "BitmapStateDefinitionType.h"
#include "HMIGlobalSettingsType.h"
#include "DisplaySizeType.h"

using namespace lsr;

namespace
{

/// "Telltales.ddh:ContentPanel"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const AreaType ddh_panelDatabase_panel0_area = {
    10, //attr: xCoord
    153, //attr: yCoord
    371, //attr: width
    72, //attr: height
};

/// "Telltales.ddh:ContentPanel"
const ExpressionTermType ddh_panelDatabase_panel0_visible = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    1, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const AreaType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_area = {
    20, //attr: xCoord
    2, //attr: yCoord
    100, //attr: width
    69, //attr: height
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    0, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_bitmap = {
    ExpressionTermType::BITMAPID_CHOICE, // choice type
    3, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
/// This telltale is rendered by the PopulusSC engine.
/// It's visibility is controlled by 2 redundant flags. If there is any error detected (any data not received or the redundant values are not equal), the telltale will be displayed.
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const StaticBitmapFieldType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType = {
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_area, // ref: area
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible, // ref: visible
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_bitmap, // ref: bitmap
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const BaseFieldChoiceType ddh_panelDatabase_panel0_field0 = {
    BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE, // choice type
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const AreaType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_area = {
    130, //attr: xCoord
    2, //attr: yCoord
    102, //attr: width
    68, //attr: height
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    0, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_bitmap = {
    ExpressionTermType::BITMAPID_CHOICE, // choice type
    1, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
/// This telltale is usually rendered by another instance (QM engine).
/// PopulusSC will render it only as a fallback, i.e if the video output check fails.
/// Therefore it checks 2 conditions: 1) The visibility state of the icon, 2) The output of the image verification
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const StaticBitmapFieldType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType = {
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_area, // ref: area
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible, // ref: visible
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_bitmap, // ref: bitmap
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const BaseFieldChoiceType ddh_panelDatabase_panel0_field1 = {
    BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE, // choice type
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType, // choice reference
};

/// "Telltales.ddh:ContentPanel"
const BaseFieldChoiceType* ddh_panelDatabase_panel0_field[] = {
    &ddh_panelDatabase_panel0_field0,
    &ddh_panelDatabase_panel0_field1,
};

/// "Telltales.ddh:ContentPanel"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const PanelType ddh_panelDatabase_panel0 = {
    &ddh_panelDatabase_panel0_area, // ref: area
    &ddh_panelDatabase_panel0_visible, // ref: visible
    ddh_panelDatabase_panel0_field, // ref: field (list)
    2, // ref: field (list size)
};

/// "Telltales.ddh:ReferencePanel"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const AreaType ddh_panelDatabase_panel1_area = {
    10, //attr: xCoord
    153, //attr: yCoord
    371, //attr: width
    72, //attr: height
};

/// "Telltales.ddh:ReferencePanel"
const ExpressionTermType ddh_panelDatabase_panel1_visible = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    1, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const AreaType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_area = {
    20, //attr: xCoord
    2, //attr: yCoord
    100, //attr: width
    69, //attr: height
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    0, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_bitmap = {
    ExpressionTermType::BITMAPID_CHOICE, // choice type
    4, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
/// Reference Bitmap for output verification. Verifies expected content of ContentPanel->Break.
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const ReferenceBitmapFieldType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType = {
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_area, // ref: area
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible, // ref: visible
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_bitmap, // ref: bitmap
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const BaseFieldChoiceType ddh_panelDatabase_panel1_field0 = {
    BaseFieldChoiceType::REFERENCEBITMAPFIELD_CHOICE, // choice type
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const AreaType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_area = {
    130, //attr: xCoord
    2, //attr: yCoord
    102, //attr: width
    68, //attr: height
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    0, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_bitmap = {
    ExpressionTermType::BITMAPID_CHOICE, // choice type
    2, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const ReferenceBitmapFieldType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType = {
    &ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_area, // ref: area
    &ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible, // ref: visible
    &ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_bitmap, // ref: bitmap
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const BaseFieldChoiceType ddh_panelDatabase_panel1_field1 = {
    BaseFieldChoiceType::REFERENCEBITMAPFIELD_CHOICE, // choice type
    &ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType, // choice reference
};

/// "Telltales.ddh:ReferencePanel"
const BaseFieldChoiceType* ddh_panelDatabase_panel1_field[] = {
    &ddh_panelDatabase_panel1_field0,
    &ddh_panelDatabase_panel1_field1,
};

/// "Telltales.ddh:ReferencePanel"
/// Contains verification widgets for video output checks
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const PanelType ddh_panelDatabase_panel1 = {
    &ddh_panelDatabase_panel1_area, // ref: area
    &ddh_panelDatabase_panel1_visible, // ref: visible
    ddh_panelDatabase_panel1_field, // ref: field (list)
    2, // ref: field (list size)
};

const PanelType* ddh_panelDatabase_panel[] = {
    &ddh_panelDatabase_panel0,
    &ddh_panelDatabase_panel1,
};

// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const PanelDatabaseType ddh_panelDatabase = {
    ddh_panelDatabase_panel, // ref: panel (list)
    2, // ref: panel (list size)
};

/// "Telltales.ddh:Airbag_Warning"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapStateDefinitionType ddh_bitmapDatabase_bitmap0_skinnedBitmap0_default = {
    1U, //attr: stateBitmapId
    __Telltales_Bitmaps_Airbag_Warning, //attr: file
};

/// "Telltales.ddh:Airbag_Warning"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const SkinnedBitmapType ddh_bitmapDatabase_bitmap0_skinnedBitmap0 = {
    &ddh_bitmapDatabase_bitmap0_skinnedBitmap0_default, // ref: default
};

/// "Telltales.ddh:Airbag_Warning"
const SkinnedBitmapType* ddh_bitmapDatabase_bitmap0_skinnedBitmap[] = {
    &ddh_bitmapDatabase_bitmap0_skinnedBitmap0,
};

/// "Telltales.ddh:Airbag_Warning"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapType ddh_bitmapDatabase_bitmap0 = {
    ddh_bitmapDatabase_bitmap0_skinnedBitmap, // ref: skinnedBitmap (list)
    1, // ref: skinnedBitmap (list size)
};

/// "Telltales.ddh:Airbag_Warning_palette"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapStateDefinitionType ddh_bitmapDatabase_bitmap1_skinnedBitmap0_default = {
    2U, //attr: stateBitmapId
    __Telltales_Bitmaps_Airbag_Warning_palette, //attr: file
};

/// "Telltales.ddh:Airbag_Warning_palette"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const SkinnedBitmapType ddh_bitmapDatabase_bitmap1_skinnedBitmap0 = {
    &ddh_bitmapDatabase_bitmap1_skinnedBitmap0_default, // ref: default
};

/// "Telltales.ddh:Airbag_Warning_palette"
const SkinnedBitmapType* ddh_bitmapDatabase_bitmap1_skinnedBitmap[] = {
    &ddh_bitmapDatabase_bitmap1_skinnedBitmap0,
};

/// "Telltales.ddh:Airbag_Warning_palette"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapType ddh_bitmapDatabase_bitmap1 = {
    ddh_bitmapDatabase_bitmap1_skinnedBitmap, // ref: skinnedBitmap (list)
    1, // ref: skinnedBitmap (list size)
};

/// "Telltales.ddh:Parking_Break"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapStateDefinitionType ddh_bitmapDatabase_bitmap2_skinnedBitmap0_default = {
    3U, //attr: stateBitmapId
    __Telltales_Bitmaps_Parking_Break, //attr: file
};

/// "Telltales.ddh:Parking_Break"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const SkinnedBitmapType ddh_bitmapDatabase_bitmap2_skinnedBitmap0 = {
    &ddh_bitmapDatabase_bitmap2_skinnedBitmap0_default, // ref: default
};

/// "Telltales.ddh:Parking_Break"
const SkinnedBitmapType* ddh_bitmapDatabase_bitmap2_skinnedBitmap[] = {
    &ddh_bitmapDatabase_bitmap2_skinnedBitmap0,
};

/// "Telltales.ddh:Parking_Break"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapType ddh_bitmapDatabase_bitmap2 = {
    ddh_bitmapDatabase_bitmap2_skinnedBitmap, // ref: skinnedBitmap (list)
    1, // ref: skinnedBitmap (list size)
};

/// "Telltales.ddh:Parking_Break_palette"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapStateDefinitionType ddh_bitmapDatabase_bitmap3_skinnedBitmap0_default = {
    4U, //attr: stateBitmapId
    __Telltales_Bitmaps_Parking_Break_palette, //attr: file
};

/// "Telltales.ddh:Parking_Break_palette"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const SkinnedBitmapType ddh_bitmapDatabase_bitmap3_skinnedBitmap0 = {
    &ddh_bitmapDatabase_bitmap3_skinnedBitmap0_default, // ref: default
};

/// "Telltales.ddh:Parking_Break_palette"
const SkinnedBitmapType* ddh_bitmapDatabase_bitmap3_skinnedBitmap[] = {
    &ddh_bitmapDatabase_bitmap3_skinnedBitmap0,
};

/// "Telltales.ddh:Parking_Break_palette"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapType ddh_bitmapDatabase_bitmap3 = {
    ddh_bitmapDatabase_bitmap3_skinnedBitmap, // ref: skinnedBitmap (list)
    1, // ref: skinnedBitmap (list size)
};

/// "Telltales.ddh:palette"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const BitmapStateDefinitionType ddh_bitmapDatabase_bitmap4_skinnedBitmap0_default = {
    5U, //attr: stateBitmapId
    __Telltales_Bitmaps_palette, //attr: file
};

/// "Telltales.ddh:palette"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const SkinnedBitmapType ddh_bitmapDatabase_bitmap4_skinnedBitmap0 = {
    &ddh_bitmapDatabase_bitmap4_skinnedBitmap0_default, // ref: default
};

/// "Telltales.ddh:palette"
const SkinnedBitmapType* ddh_bitmapDatabase_bitmap4_skinnedBitmap[] = {
    &ddh_bitmapDatabase_bitmap4_skinnedBitmap0,
};

/// "Telltales.ddh:palette"
// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
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

// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const DisplaySizeType ddh_hMIGlobalSettings_displaySize = {
    400U, //attr: width
    240U, //attr: height
};

// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const HMIGlobalSettingsType ddh_hMIGlobalSettings = {
    &ddh_hMIGlobalSettings_displaySize, // ref: displaySize
};

// coverity[misra_cpp_2008_rule_3_4_1_violation] global storage required (hidden in anonymous namespace)
const DDHType ddh = {
    1793021406U, //attr: imagesChecksum
    2802385892U, //attr: schemaChecksum
    328960U, //attr: schemaVersion
    328960U, //attr: serializerVersion
    &ddh_panelDatabase, // ref: panelDatabase
    &ddh_bitmapDatabase, // ref: bitmapDatabase
    &ddh_hMIGlobalSettings, // ref: hMIGlobalSettings
};

} // anonymous namespace

namespace Telltales
{
    const DDHType* getDDH()
    {
        return &ddh;
    }
} // namespace Telltales


// implementation for TelltalesHMI.hpp
namespace Telltales
{

HMI::HMI()
: IHMI()
, m_frame()
, m_ContentPanel(&ddh_panelDatabase_panel0)
, m_ContentPanel_Break(&ddh_panelDatabase_panel0_field0_StaticBitmapFieldType)
, m_ContentPanel_Airbag(&ddh_panelDatabase_panel0_field1_StaticBitmapFieldType)
, m_ReferencePanel(&ddh_panelDatabase_panel1)
, m_ReferencePanel_Break(&ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType)
, m_ReferencePanel_Airbag(&ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType)
{
    m_frame.addChild(m_ContentPanel);
    m_ContentPanel.addChild(m_ContentPanel_Break);
    m_ContentPanel.addChild(m_ContentPanel_Airbag);
    m_frame.addChild(m_ReferencePanel);
    m_ReferencePanel.addChild(m_ReferencePanel_Break);
    m_ReferencePanel.addChild(m_ReferencePanel_Airbag);
}

} // namespace Telltales
