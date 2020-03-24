#ifndef _LSR_DDHTYPE_H_
#define _LSR_DDHTYPE_H_

/******************************************************************************
**
**   File:        DDHType.h
**   Description:
**   Generator:   7db08a476f8107a993e0bf7183b0cf60031dad3e
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
    const PanelDatabaseType* const m_panelDatabase;
    const BitmapDatabaseType* const m_bitmapDatabase;
    const HMIGlobalSettingsType* const m_hMIGlobalSettings;

    static const U32 SERIALIZER_VERSION = 0x50500U;  ///< Version of the serializer
    static const U32 SCHEMA_VERSION = 0x50500U;  ///< Version of the schema
    static const U32 SCHEMA_CHECKSUM = 0xA70903E4U;  ///< Checksum of the schema

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
            errorMessage = "Data has been generated from a schema version with another checksum than the HMI Engine expects (Expecting Schema checksum: 0xa70903e4)";
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
     * Returns a pointer to the panelDatabase child reference.
     * Contains definitions of panels. Panels can be reused in different pages
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const PanelDatabaseType* GetPanelDatabase() const
    {
        return m_panelDatabase;
    }

    /**
     * Returns a pointer to the bitmapDatabase child reference.
     * Database of all bitmaps in the DDH
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const BitmapDatabaseType* GetBitmapDatabase() const
    {
        return m_bitmapDatabase;
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

};

} // namespace lsr

#endif // #ifndef _LSR_DDHTYPE_H_
