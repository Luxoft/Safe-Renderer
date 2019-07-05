#ifndef _DDHTYPE_H_
#define _DDHTYPE_H_

/******************************************************************************
**
**   File:        DDHType.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "ddh_defs.h"
#include "LsrTypes.h"  // for P_STATIC_ASSERT


namespace lsr
{
struct PageDatabaseType;
struct PanelDatabaseType;
struct HMIGlobalSettingsType;
struct ColorDatabaseType;
struct SkinDatabaseType;
struct FUDatabaseType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct DDHType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the DDHType.
     * Each element of this type has this exact image in ROM memory.
     */
    U32 imagesChecksum :32;
    U32 schemaChecksum :32;
    U32 schemaVersion :32;
    U32 serializerVersion :32;
    U32 pageDatabaseOffset :32;
    U32 panelDatabaseOffset :32;
    U32 hMIGlobalSettingsOffset :32;
    U32 colorDatabaseOffset :32;
    U32 skinDatabaseOffset :32;
    U32 fUDatabaseOffset :32;
    //----------------------------------------------------------------

    static const char* const serializerVersionError;
    static const char* const schemaVersionError;
    static const char* const schemaChecksumError;

public:
    // used for checking consistency between API and data
    static const U32 SERIALIZER_VERSION = 0x42900;  ///< Version of the serializer
    static const U32 SCHEMA_VERSION = 0x43a00;  ///< Version of the schema
    static const U32 SCHEMA_CHECKSUM = 0x6ed7ab2d;  ///< Checksum of the schema

    bool IsVersionOK() const;
    const char* GetErrorMessage() const;


    /**
     * Returns the value of the imagesChecksum attribute
     */
    U32 GetImagesChecksum() const;

    /**
     * Returns the value of the schemaChecksum attribute
     */
    U32 GetSchemaChecksum() const;

    /**
     * Returns the value of the schemaVersion attribute
     */
    U32 GetSchemaVersion() const;

    /**
     * Returns the value of the serializerVersion attribute
     */
    U32 GetSerializerVersion() const;

    /**
     * Returns a pointer to the pageDatabase child reference.
     * Contains definitions of pages. Every page belongs to a specific profile
     */
    const PageDatabaseType* GetPageDatabase() const;

    /**
     * Returns a pointer to the panelDatabase child reference.
     * Contains definitions of panels. Panels can be reused in different pages
     */
    const PanelDatabaseType* GetPanelDatabase() const;

    /**
     * Returns a pointer to the hMIGlobalSettings child reference.
     * The global settings for the project. Contains definitions of several
     * settings needed for the HMI Engine and for the Editor to operate
     * correctly
     */
    const HMIGlobalSettingsType* GetHMIGlobalSettings() const;

    /**
     * Returns a pointer to the colorDatabase child reference.
     * Contains definitions of colors. Only required on systems with color
     * displays
     */
    const ColorDatabaseType* GetColorDatabase() const;

    /**
     * Returns a pointer to the skinDatabase child reference.
     */
    const SkinDatabaseType* GetSkinDatabase() const;

    /**
     * Returns a pointer to the fUDatabase child reference.
     * Contains information about functional units.
     */
    const FUDatabaseType* GetFUDatabase() const;
};

P_STATIC_ASSERT((sizeof(DDHType)) == 40, "DDHType size")


inline U32 DDHType::GetImagesChecksum() const
{
    return imagesChecksum;
}

inline U32 DDHType::GetSchemaChecksum() const
{
    return schemaChecksum;
}

inline U32 DDHType::GetSchemaVersion() const
{
    return schemaVersion;
}

inline U32 DDHType::GetSerializerVersion() const
{
    return serializerVersion;
}

inline const PageDatabaseType* DDHType::GetPageDatabase() const
{
    const PageDatabaseType* pResult = NULL;
    if (pageDatabaseOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const PageDatabaseType*>(pThis + pageDatabaseOffset * 4);
    }
    return pResult;
}

inline const PanelDatabaseType* DDHType::GetPanelDatabase() const
{
    const PanelDatabaseType* pResult = NULL;
    if (panelDatabaseOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const PanelDatabaseType*>(pThis + panelDatabaseOffset * 4);
    }
    return pResult;
}

inline const HMIGlobalSettingsType* DDHType::GetHMIGlobalSettings() const
{
    const HMIGlobalSettingsType* pResult = NULL;
    if (hMIGlobalSettingsOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const HMIGlobalSettingsType*>(pThis + hMIGlobalSettingsOffset * 4);
    }
    return pResult;
}

inline const ColorDatabaseType* DDHType::GetColorDatabase() const
{
    const ColorDatabaseType* pResult = NULL;
    if (colorDatabaseOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const ColorDatabaseType*>(pThis + colorDatabaseOffset * 4);
    }
    return pResult;
}

inline const SkinDatabaseType* DDHType::GetSkinDatabase() const
{
    const SkinDatabaseType* pResult = NULL;
    if (skinDatabaseOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const SkinDatabaseType*>(pThis + skinDatabaseOffset * 4);
    }
    return pResult;
}

inline const FUDatabaseType* DDHType::GetFUDatabase() const
{
    const FUDatabaseType* pResult = NULL;
    if (fUDatabaseOffset != 0U)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const FUDatabaseType*>(pThis + fUDatabaseOffset * 4);
    }
    return pResult;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _DDHTYPE_H_
