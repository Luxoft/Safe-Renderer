#ifndef _LSR_DDHTYPE_H_
#define _LSR_DDHTYPE_H_

/******************************************************************************
**
**   File:        DDHType.h
**   Description:
**   Generator:   c78c5138ac2e7c6506a52bfc6fbc0ef05f7ad869
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

/**
 * DDHType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct DDHType
{
    const U32 m_imagesChecksum;
    const U32 m_schemaChecksum;
    const U32 m_schemaVersion;
    const U32 m_serializerVersion;
    const PageDatabaseType* const m_pageDatabase;
    const PanelDatabaseType* const m_panelDatabase;
    const HMIGlobalSettingsType* const m_hMIGlobalSettings;
    const ColorDatabaseType* const m_colorDatabase;
    const SkinDatabaseType* const m_skinDatabase;
    const FUClassType* const* const m_fU;
    const U16 m_fUCount;

    static const U32 SERIALIZER_VERSION = 0x50500U;  ///< Version of the serializer
    static const U32 SCHEMA_VERSION = 0x50500U;  ///< Version of the schema
    static const U32 SCHEMA_CHECKSUM = 0x9FA75F84U;  ///< Checksum of the schema

    bool IsVersionOK() const
    {
        return (GetSerializerVersion() == SERIALIZER_VERSION) &&
            (GetSchemaVersion() == SCHEMA_VERSION) &&
            (GetSchemaChecksum() == SCHEMA_CHECKSUM);
    }

    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const char_t* GetErrorMessage() const
    {
        const char_t* errorMessage = "";
        if (GetSerializerVersion() != SERIALIZER_VERSION)
        {
            static_cast<void>(errorMessage);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            errorMessage = "Data has been serialized with another version of the serializer than what the HMI Engine expects (Expecting Serializer version: 5.5.0)";
        }
        else if (GetSchemaVersion() != SCHEMA_VERSION)
        {
            static_cast<void>(errorMessage);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            errorMessage = "Data has been generated from another schema version than the HMI Engine expects (Expecting Schema Version: 5.5.x)";
        }
        else if (GetSchemaChecksum() != SCHEMA_CHECKSUM)
        {
            static_cast<void>(errorMessage);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            errorMessage = "Data has been generated from a schema version with another checksum than the HMI Engine expects (Expecting Schema checksum: 0x9fa75f84)";
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
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U32 GetImagesChecksum() const
    {
        return m_imagesChecksum;
    }

    /**
     * Returns the value of the schemaChecksum attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U32 GetSchemaChecksum() const
    {
        return m_schemaChecksum;
    }

    /**
     * Returns the value of the schemaVersion attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U32 GetSchemaVersion() const
    {
        return m_schemaVersion;
    }

    /**
     * Returns the value of the serializerVersion attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U32 GetSerializerVersion() const
    {
        return m_serializerVersion;
    }

    /**
     * Returns a pointer to the pageDatabase child reference.
     * Contains definitions of pages. Every page belongs to a specific profile
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const PageDatabaseType* GetPageDatabase() const
    {
        return m_pageDatabase;
    }

    /**
     * Returns a pointer to the panelDatabase child reference.
     * Contains definitions of panels. Panels can be reused in different pages
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const PanelDatabaseType* GetPanelDatabase() const
    {
        return m_panelDatabase;
    }

    /**
     * Returns a pointer to the hMIGlobalSettings child reference.
     * The global settings for the project. Contains definitions of several settings needed for the HMI Engine and for the Editor to operate correctly
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const HMIGlobalSettingsType* GetHMIGlobalSettings() const
    {
        return m_hMIGlobalSettings;
    }

    /**
     * Returns a pointer to the colorDatabase child reference.
     * Contains definitions of colors. Only required on systems with color displays
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const ColorDatabaseType* GetColorDatabase() const
    {
        return m_colorDatabase;
    }

    /**
     * Returns a pointer to the skinDatabase child reference.
     *
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const SkinDatabaseType* GetSkinDatabase() const
    {
        return m_skinDatabase;
    }

    /**
     * Returns the number of fU elements.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetFUCount() const
    {
        return m_fUCount;
    }

    /**
     * Returns a pointer to the fU child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     * This is the list of all Functional Units known by the Engine
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const FUClassType* GetFU(const U16 i) const
    {
        // coverity[misra_cpp_2008_rule_5_0_15_violation]
        return (i < m_fUCount) ? m_fU[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_DDHTYPE_H_
