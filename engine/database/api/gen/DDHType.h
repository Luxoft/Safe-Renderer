#ifndef _LSR_DDHTYPE_H_
#define _LSR_DDHTYPE_H_

/******************************************************************************
**
**   File:        DDHType.h
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

namespace lsr
{
struct PageDatabaseType;
struct PanelDatabaseType;
struct HMIGlobalSettingsType;
struct ColorDatabaseType;
struct SkinDatabaseType;
struct FUClassType;

struct DDHType
{
    const U32 imagesChecksum;
    const U32 schemaChecksum;
    const U32 schemaVersion;
    const U32 serializerVersion;
    const PageDatabaseType* const pageDatabase;
    const PanelDatabaseType* const panelDatabase;
    const HMIGlobalSettingsType* const hMIGlobalSettings;
    const ColorDatabaseType* const colorDatabase;
    const SkinDatabaseType* const skinDatabase;
    const FUClassType* const *fU;
    const U16 fUCount;

    static const U32 SERIALIZER_VERSION = 0x50400U;  ///< Version of the serializer
    static const U32 SCHEMA_VERSION = 0x50400U;  ///< Version of the schema
    static const U32 SCHEMA_CHECKSUM = 0x49D84938U;  ///< Checksum of the schema

    bool IsVersionOK() const
    {
        return (GetSerializerVersion() == SERIALIZER_VERSION) &&
            (GetSchemaVersion() == SCHEMA_VERSION) &&
            (GetSchemaChecksum() == SCHEMA_CHECKSUM);
    }

    const char* GetErrorMessage() const
    {
        const char* errorMessage = "";
        if (GetSerializerVersion() != SERIALIZER_VERSION)
        {
            errorMessage = "Data has been serialized with another version of the serializer than what the HMI Engine expects (Expecting Serializer version: 5.4.0)";
        }
        else if (GetSchemaVersion() != SCHEMA_VERSION)
        {
            errorMessage = "Data has been generated from another schema version than the HMI Engine expects (Expecting Schema Version: 5.4.x)";
        }
        else if (GetSchemaChecksum() != SCHEMA_CHECKSUM)
        {
            errorMessage = "Data has been generated from a schema version with another checksum than the HMI Engine expects (Expecting Schema checksum: 0x49d84938)";
        }
        else
        {
            // errorMessage is already empty
        }
        return errorMessage;
    }

    /**
     * Returns the value of the imagesChecksum attribute
     */
    U32 GetImagesChecksum() const
    {
        return imagesChecksum;
    }

    /**
     * Returns the value of the schemaChecksum attribute
     */
    U32 GetSchemaChecksum() const
    {
        return schemaChecksum;
    }

    /**
     * Returns the value of the schemaVersion attribute
     */
    U32 GetSchemaVersion() const
    {
        return schemaVersion;
    }

    /**
     * Returns the value of the serializerVersion attribute
     */
    U32 GetSerializerVersion() const
    {
        return serializerVersion;
    }

    /**
     * Returns a pointer to the pageDatabase child reference.
     * Contains definitions of pages. Every page belongs to a specific profile
     */
    const PageDatabaseType* GetPageDatabase() const
    {
        return pageDatabase;
    }

    /**
     * Returns a pointer to the panelDatabase child reference.
     * Contains definitions of panels. Panels can be reused in different pages
     */
    const PanelDatabaseType* GetPanelDatabase() const
    {
        return panelDatabase;
    }

    /**
     * Returns a pointer to the hMIGlobalSettings child reference.
     * The global settings for the project. Contains definitions of several settings needed for the HMI Engine and for the Editor to operate correctly
     */
    const HMIGlobalSettingsType* GetHMIGlobalSettings() const
    {
        return hMIGlobalSettings;
    }

    /**
     * Returns a pointer to the colorDatabase child reference.
     * Contains definitions of colors. Only required on systems with color displays
     */
    const ColorDatabaseType* GetColorDatabase() const
    {
        return colorDatabase;
    }

    /**
     * Returns a pointer to the skinDatabase child reference.
     *
     */
    const SkinDatabaseType* GetSkinDatabase() const
    {
        return skinDatabase;
    }

    /**
     * Returns the number of fU elements.
     */
    U16 GetFUCount() const
    {
        return fUCount;
    }

    /**
     * Returns a pointer to the fU child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     * This is the list of all Functional Units known by the Engine
     */
    const FUClassType* GetFU(const U16 i) const
    {
        return (i < fUCount) ? fU[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_DDHTYPE_H_
