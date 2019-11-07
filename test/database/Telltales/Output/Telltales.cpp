/******************************************************************************
**
**   File:        Telltales.cpp
**   Description: Serialized Database
**
**   Copyright (C) 2017 Luxoft GmbH
******************************************************************************/

#include "Telltales.h"
#include "Telltales.hpp"
#include "Telltales_images.cpp"

#include "DDHType.h"
#include "PageDatabaseType.h"
#include "PageType.h"
#include "AreaType.h"
#include "ExpressionTermType.h"
#include "ExpressionType.h"
#include "DynamicDataType.h"
#include "BitmapIdTableType.h"
#include "EnumerationBitmapMapType.h"
#include "PanelDatabaseType.h"
#include "PanelType.h"
#include "BaseFieldChoiceType.h"
#include "ReferenceBitmapFieldType.h"
#include "StaticBitmapFieldType.h"
#include "HMIGlobalSettingsType.h"
#include "DisplaySizeType.h"
#include "ColorSetType.h"
#include "ColorDatabaseType.h"
#include "SkinDatabaseType.h"
#include "SkinType.h"
#include "ColorMapType.h"
#include "BitmapDefinitionType.h"
#include "BitmapStateDefinitionType.h"
#include "FUClassType.h"
#include "DynamicDataEntryType.h"

using namespace lsr;

/// "Telltales.ddh:Default Page"
const U16 ddh_pageDatabase_page0_panelId[] = {
    1,
    2,
};

/// "Telltales.ddh:Default Page"
const PageType ddh_pageDatabase_page0 = {
    ddh_pageDatabase_page0_panelId, // attr: panelId (list)
    2, // attr: panelId (list size)
    NULL, // ref: area
    NULL, // ref: visible
};

const PageType* ddh_pageDatabase_page[] = {
    &ddh_pageDatabase_page0,
};

const PageDatabaseType ddh_pageDatabase = {
    ddh_pageDatabase_page, // ref: page (list)
    1, // ref: page (list size)
};

/// "Telltales.ddh:ContentPanel"
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
const AreaType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_area = {
    20, //attr: xCoord
    2, //attr: yCoord
    100, //attr: width
    69, //attr: height
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const DynamicDataType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term0_dynamicData = {
    2752513, //attr: fUDataId
    DATATYPE_BOOLEAN, //attr: type
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term0 = {
    ExpressionTermType::DYNAMICDATA_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term0_dynamicData, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const DynamicDataType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1_expression_term0_dynamicData = {
    2752514, //attr: fUDataId
    DATATYPE_BOOLEAN, //attr: type
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1_expression_term0 = {
    ExpressionTermType::DYNAMICDATA_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1_expression_term0_dynamicData, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType* ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1_expression_term[] = {
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1_expression_term0,
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1_expression = {
    EXPRESSION_OPERATOR_NOT, //attr: operator
    ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1_expression_term, // ref: term (list)
    1, // ref: term (list size)
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1 = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1_expression, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType* ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term[] = {
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term0,
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term1,
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression = {
    EXPRESSION_OPERATOR_OR, //attr: operator
    ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression_term, // ref: term (list)
    2, // ref: term (list size)
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0 = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0_expression, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term1 = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    1, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType* ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term[] = {
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term0,
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term1,
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression = {
    EXPRESSION_OPERATOR_FALLBACK, //attr: operator
    ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression_term, // ref: term (list)
    2, // ref: term (list size)
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field0_StaticBitmapFieldType_visible_expression, // choice reference
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
const AreaType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_area = {
    130, //attr: xCoord
    2, //attr: yCoord
    102, //attr: width
    68, //attr: height
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const DynamicDataType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression_term0_dynamicData = {
    16711682, //attr: fUDataId
    DATATYPE_INTEGER, //attr: type
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression_term0 = {
    ExpressionTermType::DYNAMICDATA_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression_term0_dynamicData, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression_term1 = {
    ExpressionTermType::INTEGER_CHOICE, // choice type
    10, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType* ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression_term[] = {
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression_term0,
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression_term1,
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression = {
    EXPRESSION_OPERATOR_GREATER, //attr: operator
    ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression_term, // ref: term (list)
    2, // ref: term (list size)
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0 = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0_expression, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const DynamicDataType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression_term0_dynamicData = {
    2752515, //attr: fUDataId
    DATATYPE_BOOLEAN, //attr: type
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression_term0 = {
    ExpressionTermType::DYNAMICDATA_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression_term0_dynamicData, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression_term1 = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    1, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType* ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression_term[] = {
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression_term0,
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression_term1,
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression = {
    EXPRESSION_OPERATOR_FALLBACK, //attr: operator
    ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression_term, // ref: term (list)
    2, // ref: term (list size)
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1 = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1_expression, // choice reference
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType* ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term[] = {
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term0,
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term1,
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression = {
    EXPRESSION_OPERATOR_AND, //attr: operator
    ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression_term, // ref: term (list)
    2, // ref: term (list size)
};

/// "Telltales.ddh:ContentPanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel0_field1_StaticBitmapFieldType_visible_expression, // choice reference
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
const PanelType ddh_panelDatabase_panel0 = {
    &ddh_panelDatabase_panel0_area, // ref: area
    &ddh_panelDatabase_panel0_visible, // ref: visible
    ddh_panelDatabase_panel0_field, // ref: field (list)
    2, // ref: field (list size)
};

/// "Telltales.ddh:ReferencePanel"
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
const AreaType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_area = {
    20, //attr: xCoord
    2, //attr: yCoord
    100, //attr: width
    69, //attr: height
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const DynamicDataType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term0_dynamicData = {
    2752513, //attr: fUDataId
    DATATYPE_BOOLEAN, //attr: type
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term0 = {
    ExpressionTermType::DYNAMICDATA_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term0_dynamicData, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const DynamicDataType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1_expression_term0_dynamicData = {
    2752514, //attr: fUDataId
    DATATYPE_BOOLEAN, //attr: type
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1_expression_term0 = {
    ExpressionTermType::DYNAMICDATA_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1_expression_term0_dynamicData, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType* ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1_expression_term[] = {
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1_expression_term0,
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1_expression = {
    EXPRESSION_OPERATOR_NOT, //attr: operator
    ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1_expression_term, // ref: term (list)
    1, // ref: term (list size)
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1 = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1_expression, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType* ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term[] = {
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term0,
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term1,
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression = {
    EXPRESSION_OPERATOR_OR, //attr: operator
    ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression_term, // ref: term (list)
    2, // ref: term (list size)
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0 = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0_expression, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term1 = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    1, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType* ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term[] = {
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term0,
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term1,
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression = {
    EXPRESSION_OPERATOR_FALLBACK, //attr: operator
    ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression_term, // ref: term (list)
    2, // ref: term (list size)
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_visible_expression, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
const ExpressionTermType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType_bitmap = {
    ExpressionTermType::BITMAPID_CHOICE, // choice type
    4, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Break"
/// Reference Bitmap for output verification. Verifies expected content of ContentPanel->Break.
const ReferenceBitmapFieldType ddh_panelDatabase_panel1_field0_ReferenceBitmapFieldType = {
    16711681, //attr: errorCounterFUDataId
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
const AreaType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_area = {
    130, //attr: xCoord
    2, //attr: yCoord
    102, //attr: width
    68, //attr: height
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const DynamicDataType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression_term0_dynamicData = {
    2752515, //attr: fUDataId
    DATATYPE_BOOLEAN, //attr: type
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression_term0 = {
    ExpressionTermType::DYNAMICDATA_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression_term0_dynamicData, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression_term1 = {
    ExpressionTermType::BOOLEAN_CHOICE, // choice type
    1, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const ExpressionTermType* ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression_term[] = {
    &ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression_term0,
    &ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression_term1,
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const ExpressionType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression = {
    EXPRESSION_OPERATOR_FALLBACK, //attr: operator
    ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression_term, // ref: term (list)
    2, // ref: term (list size)
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible = {
    ExpressionTermType::EXPRESSION_CHOICE, // choice type
    0, // choice attribute
    &ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_visible_expression, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const ExpressionTermType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType_bitmap = {
    ExpressionTermType::BITMAPID_CHOICE, // choice type
    2, // choice attribute
    NULL, // choice reference
};

/// "Telltales.ddh:ReferencePanel" > "Telltales.ddh:Airbag"
const ReferenceBitmapFieldType ddh_panelDatabase_panel1_field1_ReferenceBitmapFieldType = {
    16711682, //attr: errorCounterFUDataId
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

const PanelDatabaseType ddh_panelDatabase = {
    ddh_panelDatabase_panel, // ref: panel (list)
    2, // ref: panel (list size)
};

const DisplaySizeType ddh_hMIGlobalSettings_displaySize = {
    400U, //attr: width
    240U, //attr: height
};

const ColorSetType ddh_hMIGlobalSettings_colorSet = {
    1, //attr: defaultDisplayBackgroundColorId
    2, //attr: defaultPageBackgroundColorId
    2, //attr: defaultPanelBackgroundColorId
};

const HMIGlobalSettingsType ddh_hMIGlobalSettings = {
    &ddh_hMIGlobalSettings_displaySize, // ref: displaySize
    &ddh_hMIGlobalSettings_colorSet, // ref: colorSet
};

const ColorDatabaseType ddh_colorDatabase = {
};

/// "Default"
const ColorMapType ddh_skinDatabase_skin0_colorMap0 = {
};

/// "Default"
const ColorMapType ddh_skinDatabase_skin0_colorMap1 = {
};

/// "Default"
const ColorMapType* ddh_skinDatabase_skin0_colorMap[] = {
    &ddh_skinDatabase_skin0_colorMap0,
    &ddh_skinDatabase_skin0_colorMap1,
};

/// "Default"
const BitmapStateDefinitionType ddh_skinDatabase_skin0_bitmap0_default = {
    1U, //attr: stateBitmapId
    __Telltales_Bitmaps_Airbag_Warning, //attr: file
};

/// "Default"
const BitmapDefinitionType ddh_skinDatabase_skin0_bitmap0 = {
    1, //attr: bitmapId
    &ddh_skinDatabase_skin0_bitmap0_default, // ref: default
};

/// "Default"
const BitmapStateDefinitionType ddh_skinDatabase_skin0_bitmap1_default = {
    2U, //attr: stateBitmapId
    __Telltales_Bitmaps_Airbag_Warning_palette, //attr: file
};

/// "Default"
const BitmapDefinitionType ddh_skinDatabase_skin0_bitmap1 = {
    2, //attr: bitmapId
    &ddh_skinDatabase_skin0_bitmap1_default, // ref: default
};

/// "Default"
const BitmapStateDefinitionType ddh_skinDatabase_skin0_bitmap2_default = {
    3U, //attr: stateBitmapId
    __Telltales_Bitmaps_Parking_Break, //attr: file
};

/// "Default"
const BitmapDefinitionType ddh_skinDatabase_skin0_bitmap2 = {
    3, //attr: bitmapId
    &ddh_skinDatabase_skin0_bitmap2_default, // ref: default
};

/// "Default"
const BitmapStateDefinitionType ddh_skinDatabase_skin0_bitmap3_default = {
    4U, //attr: stateBitmapId
    __Telltales_Bitmaps_Parking_Break_palette, //attr: file
};

/// "Default"
const BitmapDefinitionType ddh_skinDatabase_skin0_bitmap3 = {
    4, //attr: bitmapId
    &ddh_skinDatabase_skin0_bitmap3_default, // ref: default
};

/// "Default"
const BitmapStateDefinitionType ddh_skinDatabase_skin0_bitmap4_default = {
    5U, //attr: stateBitmapId
    __Telltales_Bitmaps_palette, //attr: file
};

/// "Default"
const BitmapDefinitionType ddh_skinDatabase_skin0_bitmap4 = {
    5, //attr: bitmapId
    &ddh_skinDatabase_skin0_bitmap4_default, // ref: default
};

/// "Default"
const BitmapDefinitionType* ddh_skinDatabase_skin0_bitmap[] = {
    &ddh_skinDatabase_skin0_bitmap0,
    &ddh_skinDatabase_skin0_bitmap1,
    &ddh_skinDatabase_skin0_bitmap2,
    &ddh_skinDatabase_skin0_bitmap3,
    &ddh_skinDatabase_skin0_bitmap4,
};

/// "Default"
const SkinType ddh_skinDatabase_skin0 = {
    ddh_skinDatabase_skin0_colorMap, // ref: colorMap (list)
    2, // ref: colorMap (list size)
    ddh_skinDatabase_skin0_bitmap, // ref: bitmap (list)
    5, // ref: bitmap (list size)
};

const SkinType* ddh_skinDatabase_skin[] = {
    &ddh_skinDatabase_skin0,
};

const SkinDatabaseType ddh_skinDatabase = {
    ddh_skinDatabase_skin, // ref: skin (list)
    1, // ref: skin (list size)
};

/// "PopupTextId"
/// The TextId of the currently displayed popup. This data entry is provided to allow reuse of the same panel for many popups. If the panel includes a field referencing this data ID, the text of the popup which is currently granted the display will be shown. This value is context specific and only valid for a popup and its child elements. 
const DynamicDataEntryType ddh_fU0_dynamicDataEntry0 = {
    1U, //attr: dataId
    DATATYPE_TEXT_ID, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "PopupBitmapId"
/// The BitmapId of the currently displayed popup. This data entry is provided to allow reuse of the same panel for many popups. If the panel includes a field referencing this data ID, the bitmap of the popup which is currently granted the display will be shown. This value is context specific and only valid for a popup and its child elements. 
const DynamicDataEntryType ddh_fU0_dynamicDataEntry1 = {
    2U, //attr: dataId
    DATATYPE_BITMAP_ID, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "NumberActivePopups"
/// The number of popups that are currently requesting access to the display and are stacked in the priority stack, including the popup with the highest priority that might be currently displayed. This data value can be used to show graphically how many popups are pending to the user.
const DynamicDataEntryType ddh_fU0_dynamicDataEntry2 = {
    3U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "NumberOfPagesInPageTraversalOrder"
/// This is the number of valid pages that are part of the PageTraversalOrder list of the current profile. A valid page is one whose guard evaluates to true. If PageTraversalOrder is not used for the profile, it is set to 0.<br><b>Attention:</b> This entry in FU 0x00 is only valid for the currently active frame and is kept only for backward compatibility. It is recommended to use FU 0xFF instead since it provides the ability to store the data for each frame when multiple frames are used.
const DynamicDataEntryType ddh_fU0_dynamicDataEntry3 = {
    4U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "PageTraversalIndexOfCurrentPage"
/// If the currently active page is part of the PageTraversalOrder, this data entry is set to be the page's index in the PageTraversalOrder list, only taking into account the pages currently valid in the list after evaluating their guards. The first valid page is index 0. A valid page is one whose guard evaluates to true. If the active page is not part of the PageTraversalOrder, the data entry is set to -1 and is considered to be invalid.<br><b>Attention:</b> This entry in FU 0x00 is only valid for the currently active frame and is kept only for backward compatibility. It is recommended to use FU 0xFF instead since it provides the ability to store the data for each frame when multiple frames are used.
const DynamicDataEntryType ddh_fU0_dynamicDataEntry4 = {
    5U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "PopupTitleTextId"
/// The TitleTextId of the currently displayed popup. This data entry is provided to allow reuse of the same panel for many popups. If the panel includes a field referencing this data ID, the title text of the popup which is currently granted the display will be shown. This value is context specific and only valid for a popup and its child elements. 
const DynamicDataEntryType ddh_fU0_dynamicDataEntry5 = {
    6U, //attr: dataId
    DATATYPE_TEXT_ID, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "FrameRate"
/// Current FPS - the number of frames rendered during the last second in the main thread. The value is updated once per second.
const DynamicDataEntryType ddh_fU0_dynamicDataEntry6 = {
    7U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "HeapSize"
/// Current memory heap size, in bytes, occupied by the Populus Engine. The value is updated once per second.
const DynamicDataEntryType ddh_fU0_dynamicDataEntry7 = {
    8U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "MaxHeapSize"
/// Maximum memory heap size, in bytes, occupied by the Populus Engine. The value is measured for the current Engine session and updated once per second.
const DynamicDataEntryType ddh_fU0_dynamicDataEntry8 = {
    9U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "PopupZOrder"
/// Returns the displayed z-order for the current popup. This value is context specific and only valid for a popup and its child elements. The topmost popup gets the value 0, the next behind gets value 1 and so on.
const DynamicDataEntryType ddh_fU0_dynamicDataEntry9 = {
    10U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "FocusVisible"
/// Indicates the focus visible state.
const DynamicDataEntryType ddh_fU0_dynamicDataEntry10 = {
    11U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "DisplayUnits"
/// Indicates the currently set display units (metric, us, imperial)
const DynamicDataEntryType ddh_fU0_dynamicDataEntry11 = {
    12U, //attr: dataId
    DATATYPE_ENUMERATION_VALUE, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

const DynamicDataEntryType* ddh_fU0_dynamicDataEntry[] = {
    &ddh_fU0_dynamicDataEntry0,
    &ddh_fU0_dynamicDataEntry1,
    &ddh_fU0_dynamicDataEntry2,
    &ddh_fU0_dynamicDataEntry3,
    &ddh_fU0_dynamicDataEntry4,
    &ddh_fU0_dynamicDataEntry5,
    &ddh_fU0_dynamicDataEntry6,
    &ddh_fU0_dynamicDataEntry7,
    &ddh_fU0_dynamicDataEntry8,
    &ddh_fU0_dynamicDataEntry9,
    &ddh_fU0_dynamicDataEntry10,
    &ddh_fU0_dynamicDataEntry11,
};

/// This is the FU Class definition for the <i>FU Populus Engine</i> (HMIEngine FU), FU 0x00. The Events, Indications and Dynamic Data supported by this FU are hard-coded into the Populus Engine software.
const FUClassType ddh_fU0 = {
    0U, //attr: fUClassId
    0, //attr: internal
    ddh_fU0_dynamicDataEntry, // ref: dynamicDataEntry (list)
    12, // ref: dynamicDataEntry (list size)
};

/// "DisplayUnits"
/// The current DisplayUnits setting for the HMIEngine. The DisplayUnits setting is either received externally from another FU or set internally by a particular display.
const DynamicDataEntryType ddh_fU1_dynamicDataEntry0 = {
    1U, //attr: dataId
    DATATYPE_ENUMERATION_VALUE, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "DisplayLanguage"
/// This is the currently active language.
const DynamicDataEntryType ddh_fU1_dynamicDataEntry1 = {
    2U, //attr: dataId
    DATATYPE_ENUMERATION_VALUE, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "DisplayTimeNotation"
/// This shows the current setting of how time of day is displayed.
const DynamicDataEntryType ddh_fU1_dynamicDataEntry2 = {
    3U, //attr: dataId
    DATATYPE_ENUMERATION_VALUE, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "SkinValue"
/// The current skin value for the display. The value of this data affects which colors, bitmaps and fonts shall be used by the display.
const DynamicDataEntryType ddh_fU1_dynamicDataEntry3 = {
    4U, //attr: dataId
    DATATYPE_ENUMERATION_VALUE, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "TimeOfDay"
/// The current time value containing hours, minutes, seconds and hundredths of seconds.
const DynamicDataEntryType ddh_fU1_dynamicDataEntry4 = {
    5U, //attr: dataId
    DATATYPE_TIME, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "CurrentDate"
/// The current date containing year, month, day of week and day.
const DynamicDataEntryType ddh_fU1_dynamicDataEntry5 = {
    6U, //attr: dataId
    DATATYPE_DATE, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

const DynamicDataEntryType* ddh_fU1_dynamicDataEntry[] = {
    &ddh_fU1_dynamicDataEntry0,
    &ddh_fU1_dynamicDataEntry1,
    &ddh_fU1_dynamicDataEntry2,
    &ddh_fU1_dynamicDataEntry3,
    &ddh_fU1_dynamicDataEntry4,
    &ddh_fU1_dynamicDataEntry5,
};

const FUClassType ddh_fU1 = {
    1U, //attr: fUClassId
    0, //attr: internal
    ddh_fU1_dynamicDataEntry, // ref: dynamicDataEntry (list)
    6, // ref: dynamicDataEntry (list size)
};

/// "BreakOn"
const DynamicDataEntryType ddh_fU2_dynamicDataEntry0 = {
    1U, //attr: dataId
    DATATYPE_BOOLEAN, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    100U, //attr: repeatTimeout
};

/// "BreakOff"
/// Inverted redundant value for "BreakOn"
const DynamicDataEntryType ddh_fU2_dynamicDataEntry1 = {
    2U, //attr: dataId
    DATATYPE_BOOLEAN, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "Airbag"
const DynamicDataEntryType ddh_fU2_dynamicDataEntry2 = {
    3U, //attr: dataId
    DATATYPE_BOOLEAN, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    200U, //attr: repeatTimeout
};

const DynamicDataEntryType* ddh_fU2_dynamicDataEntry[] = {
    &ddh_fU2_dynamicDataEntry0,
    &ddh_fU2_dynamicDataEntry1,
    &ddh_fU2_dynamicDataEntry2,
};

const FUClassType ddh_fU2 = {
    42U, //attr: fUClassId
    0, //attr: internal
    ddh_fU2_dynamicDataEntry, // ref: dynamicDataEntry (list)
    3, // ref: dynamicDataEntry (list size)
};

/// "BreakErrorCount"
const DynamicDataEntryType ddh_fU3_dynamicDataEntry0 = {
    1U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

/// "AirbagErrorCount"
const DynamicDataEntryType ddh_fU3_dynamicDataEntry1 = {
    2U, //attr: dataId
    DATATYPE_INTEGER, //attr: dataType
    0, //attr: minimum
    0, //attr: maximum
    0U, //attr: repeatTimeout
};

const DynamicDataEntryType* ddh_fU3_dynamicDataEntry[] = {
    &ddh_fU3_dynamicDataEntry0,
    &ddh_fU3_dynamicDataEntry1,
};

const FUClassType ddh_fU3 = {
    255U, //attr: fUClassId
    1, //attr: internal
    ddh_fU3_dynamicDataEntry, // ref: dynamicDataEntry (list)
    2, // ref: dynamicDataEntry (list size)
};

const FUClassType* ddh_fU[] = {
    &ddh_fU0,
    &ddh_fU1,
    &ddh_fU2,
    &ddh_fU3,
};

const DDHType ddh = {
    1793021406U, //attr: imagesChecksum
    1238911288U, //attr: schemaChecksum
    328704U, //attr: schemaVersion
    328704U, //attr: serializerVersion
    &ddh_pageDatabase, // ref: pageDatabase
    &ddh_panelDatabase, // ref: panelDatabase
    &ddh_hMIGlobalSettings, // ref: hMIGlobalSettings
    &ddh_colorDatabase, // ref: colorDatabase
    &ddh_skinDatabase, // ref: skinDatabase
    ddh_fU, // ref: fU (list)
    4, // ref: fU (list size)
};


namespace Telltales
{
    const DDHType* getDDH()
    {
        return &ddh;
    }
} // namespace Telltales

extern "C"
{
    LSRDatabase getTelltalesDDH()
    {
        return &ddh;
    }
} // extern "C"
