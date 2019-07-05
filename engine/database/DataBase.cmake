cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

if(NOT DEFINED DATABASE_BASE)
    set(DATABASE_BASE "${LSRENGINE}/database")
    message(STATUS "--> DATABASE_BASE: ${DATABASE_BASE}")
endif()

include_directories(
    ${LSRROOT}/pil/api
    ${LSRENGINE}/common/api
    ${DATABASE_BASE}/api
    ${DATABASE_BASE}/api/gen
    ${DATABASE_BASE}/src
)

set(DATABASE_HEADERS
    ${DATABASE_BASE}/api/Area.h
    ${DATABASE_BASE}/api/BitmapAccess.h
    ${DATABASE_BASE}/api/Color.h
    ${DATABASE_BASE}/api/Database.h
    ${DATABASE_BASE}/api/FonBinReader.h
    ${DATABASE_BASE}/api/ImageAttributes.h
    ${DATABASE_BASE}/api/LsrImage.h
    ${DATABASE_BASE}/api/ResourceBuffer.h
    ${DATABASE_BASE}/api/StaticBitmap.h
    ${DATABASE_BASE}/api/gen/AreaType.h
    ${DATABASE_BASE}/api/gen/BitmapDefinitionType.h
    ${DATABASE_BASE}/api/gen/BitmapIdTableType.h
    ${DATABASE_BASE}/api/gen/BitmapStateDefinitionType.h
    ${DATABASE_BASE}/api/gen/ColorDatabaseType.h
    ${DATABASE_BASE}/api/gen/ColorMapType.h
    ${DATABASE_BASE}/api/gen/ColorSetType.h
    ${DATABASE_BASE}/api/gen/ddh_defs.h
    ${DATABASE_BASE}/api/gen/DDHType.h
    ${DATABASE_BASE}/api/gen/DisplaySizeType.h
    ${DATABASE_BASE}/api/gen/DynamicDataType.h
    ${DATABASE_BASE}/api/gen/DynamicIndicationIdType.h
    ${DATABASE_BASE}/api/gen/EnumerationBitmapMapType.h
    ${DATABASE_BASE}/api/gen/EnumerationValueType.h
    ${DATABASE_BASE}/api/gen/ExpressionTermType.h
    ${DATABASE_BASE}/api/gen/ExpressionType.h
    ${DATABASE_BASE}/api/gen/FieldsType.h
    ${DATABASE_BASE}/api/gen/FieldType.h
    ${DATABASE_BASE}/api/gen/HMIGlobalSettingsType.h
    ${DATABASE_BASE}/api/gen/PageDatabaseType.h
    ${DATABASE_BASE}/api/gen/PageType.h
    ${DATABASE_BASE}/api/gen/PanelDatabaseType.h
    ${DATABASE_BASE}/api/gen/PanelType.h
    ${DATABASE_BASE}/api/gen/SkinDatabaseType.h
    ${DATABASE_BASE}/api/gen/SkinType.h
    ${DATABASE_BASE}/api/gen/StaticBitmapFieldType.h
)

set(DATABASE_SOURCES
    ${DATABASE_BASE}/src/Area.cpp
    ${DATABASE_BASE}/src/BitmapAccess.cpp
    ${DATABASE_BASE}/src/Database.cpp
    ${DATABASE_BASE}/src/FonBinReader.cpp
    ${DATABASE_BASE}/src/LsrImage.cpp
    ${DATABASE_BASE}/src/StaticBitmap.cpp
    ${DATABASE_BASE}/src/gen/DDHType.cpp
)

if(UNIT_TESTS)
    add_subdirectory(test)

    set(DATABASE_HEADERS
        ${DATABASE_HEADERS}
        ${DATABASE_BASE}/test/BitmapIdTableTypeFactory.h
        ${DATABASE_BASE}/test/DDHTypeFactory.h
        ${DATABASE_BASE}/test/DdhArrayObject.h
        ${DATABASE_BASE}/test/DdhObject.h
        ${DATABASE_BASE}/test/EnumerationBitmapMapTypeFactory.h
        ${DATABASE_BASE}/test/ExpressionTermTypeFactory.h
        ${DATABASE_BASE}/test/ExpressionTypeFactory.h
        ${DATABASE_BASE}/test/FieldTypeFactory.h
        ${DATABASE_BASE}/test/FieldsTypeFactory.h
        ${DATABASE_BASE}/test/FonBinWriter.h
        ${DATABASE_BASE}/test/HMIGlobalSettingsTypeFactory.h
        ${DATABASE_BASE}/test/PageDatabaseTypeFactory.h
        ${DATABASE_BASE}/test/PanelDatabaseTypeFactory.h
        ${DATABASE_BASE}/test/PageTypeFactory.h
        ${DATABASE_BASE}/test/PanelTypeFactory.h
        ${DATABASE_BASE}/test/ReferenceBitmapFieldTypeFactory.h
        ${DATABASE_BASE}/test/StaticBitmapFieldTypeFactory.h
    )
endif()
