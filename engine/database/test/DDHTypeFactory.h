#ifndef POPULUSSC_DDHTYPEFACTORY_H
#define POPULUSSC_DDHTYPEFACTORY_H

/******************************************************************************
**
**   File:        DDHTypeFactory.h
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

#include "DdhObject.h"

#include <DDHType.h>
#include <DynamicDataType.h>
#include <DynamicIndicationIdType.h>


namespace ddh
{
    struct PageDatabaseType;
    struct PanelDatabaseType;
    struct HMIGlobalSettingsType;
    struct ColorDatabaseType;
    struct SkinDatabaseType;
}

class DDHTypeFactory: public DdhObject<psc::DDHType>
{
public:
    DDHTypeFactory();

    const psc::DDHType* getDdh() const;

    std::size_t getSize() const;

    void setImagesChecksum(U32 value);
    void setSchemaChecksum(U32 value);
    void setSchemaVersion(U32 value);
    void setSerializerVersion(U32 value);

    void addPageDatabase(const psc::PageDatabaseType* type, std::size_t typeSize);
    void addPanelDatabase(const psc::PanelDatabaseType* type, std::size_t typeSize);
    void addHMIGlobalSettings(const psc::HMIGlobalSettingsType* type, std::size_t typeSize);
    void addColorDatabase(const psc::ColorDatabaseType* type, std::size_t typeSize);
    void addSkinDatabase(const psc::SkinDatabaseType* type, std::size_t typeSize);

protected:
    void setPageDatabaseOffset(U32 value);
    void setPanelDatabaseOffset(U32 value);
    void setHMIGlobalSettingsOffset(U32 value);
    void setColorDatabaseOffset(U32 value);
    void setSkinDatabaseOffset(U32 value);
};

inline DDHTypeFactory::DDHTypeFactory()
{
    setPageDatabaseOffset(0U);
    setPanelDatabaseOffset(0U);
    setHMIGlobalSettingsOffset(0U);
    setColorDatabaseOffset(0U);
    setSkinDatabaseOffset(0U);
}

inline const psc::DDHType* DDHTypeFactory::getDdh() const
{
    return reinterpret_cast<const psc::DDHType*>(getData());
}

inline std::size_t DDHTypeFactory::getSize() const
{
    return getDataSize();
}

inline void DDHTypeFactory::setImagesChecksum(U32 value)
{
    psc::DDHType& obj = getObj();
    obj.imagesChecksum = value;
}

inline void DDHTypeFactory::setSchemaChecksum(U32 value)
{
    psc::DDHType& obj = getObj();
    obj.schemaChecksum = value;
}

inline void DDHTypeFactory::setSchemaVersion(U32 value)
{
    psc::DDHType& obj = getObj();
    obj.schemaVersion = value;
}

inline void DDHTypeFactory::setSerializerVersion(U32 value)
{
    psc::DDHType& obj = getObj();
    obj.serializerVersion = value;
}

inline void DDHTypeFactory::setPageDatabaseOffset(U32 value)
{
    psc::DDHType& obj = getObj();
    obj.pageDatabaseOffset = value;
}

inline void DDHTypeFactory::setPanelDatabaseOffset(U32 value)
{
    psc::DDHType& obj = getObj();
    obj.panelDatabaseOffset = value;
}

inline void DDHTypeFactory::setHMIGlobalSettingsOffset(U32 value)
{
    psc::DDHType& obj = getObj();
    obj.hMIGlobalSettingsOffset = value;
}

inline void DDHTypeFactory::setColorDatabaseOffset(U32 value)
{
    psc::DDHType& obj = getObj();
    obj.colorDatabaseOffset = value;
}

inline void DDHTypeFactory::setSkinDatabaseOffset(U32 value)
{
    psc::DDHType& obj = getObj();
    obj.skinDatabaseOffset = value;
}

inline void DDHTypeFactory::addPageDatabase(const psc::PageDatabaseType* type, std::size_t typeSize)
{
    U32 offset = addData(reinterpret_cast<const U8*>(type), typeSize);
    setPageDatabaseOffset(offset / 4U);
}

inline void DDHTypeFactory::addPanelDatabase(const psc::PanelDatabaseType* type, std::size_t typeSize)
{
    U32 offset = addData(reinterpret_cast<const U8*>(type), typeSize);
    setPanelDatabaseOffset(offset / 4U);
}

inline void DDHTypeFactory::addHMIGlobalSettings(const psc::HMIGlobalSettingsType* type, std::size_t typeSize)
{
    U32 offset = addData(reinterpret_cast<const U8*>(type), typeSize);
    setHMIGlobalSettingsOffset(offset / 4U);
}

inline void DDHTypeFactory::addColorDatabase(const psc::ColorDatabaseType* type, std::size_t typeSize)
{
    U32 offset = addData(reinterpret_cast<const U8*>(type), typeSize);
    setColorDatabaseOffset(offset / 4U);
}

inline void DDHTypeFactory::addSkinDatabase(const psc::SkinDatabaseType* type, std::size_t typeSize)
{
    U32 offset = addData(reinterpret_cast<const U8*>(type), typeSize);
    setSkinDatabaseOffset(offset / 4U);
}

#endif // POPULUSSC_DDHTYPEFACTORY_H
