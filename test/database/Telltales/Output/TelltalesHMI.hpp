#ifndef _TELLTALES_HMI_H_
#define _TELLTALES_HMI_H_
/******************************************************************************
**
**   File:        TelltalesHMI.h
**   Description: Runtime HMI objects (generated)
**
**   Copyright (C) 2017 Luxoft GmbH
******************************************************************************/

#include <LsrTypes.h>
#include <IHMI.h>
#include <Frame.h>
#include <Panel.h>
#include <BitmapField.h>
#include <ReferenceBitmapField.h>

namespace Telltales
{

/**
 * HMI runtime objects
 * @generated
 */
class HMI : public lsr::IHMI
{
public:
    HMI();

    virtual lsr::Frame* getFrame() P_OVERRIDE
    {
        // coverity[misra_cpp_2008_rule_9_3_2_violation] intended access
        return &m_frame;
    }

    /**
     */
    lsr::Panel& getContentPanel()
    {
        // coverity[misra_cpp_2008_rule_9_3_2_violation] intended access
        return m_ContentPanel;
    }

    /**
    This telltale is rendered by the PopulusSC engine.
    It's visibility is controlled by 2 redundant flags. If there is any error detected (any data not received or the redundant values are not equal), the telltale will be displayed.
     */
    lsr::BitmapField& getContentPanel_Break()
    {
        // coverity[misra_cpp_2008_rule_9_3_2_violation] intended access
        return m_ContentPanel_Break;
    }

    /**
    This telltale is usually rendered by another instance (QM engine).
    PopulusSC will render it only as a fallback, i.e if the video output check fails.
    Therefore it checks 2 conditions: 1) The visibility state of the icon, 2) The output of the image verification
     */
    lsr::BitmapField& getContentPanel_Airbag()
    {
        // coverity[misra_cpp_2008_rule_9_3_2_violation] intended access
        return m_ContentPanel_Airbag;
    }

    /**
     Contains verification widgets for video output checks
     */
    lsr::Panel& getReferencePanel()
    {
        // coverity[misra_cpp_2008_rule_9_3_2_violation] intended access
        return m_ReferencePanel;
    }

    /**
    Reference Bitmap for output verification. Verifies expected content of ContentPanel->Break.
     */
    lsr::ReferenceBitmapField& getReferencePanel_Break()
    {
        // coverity[misra_cpp_2008_rule_9_3_2_violation] intended access
        return m_ReferencePanel_Break;
    }

    /**
     */
    lsr::ReferenceBitmapField& getReferencePanel_Airbag()
    {
        // coverity[misra_cpp_2008_rule_9_3_2_violation] intended access
        return m_ReferencePanel_Airbag;
    }

private:
    lsr::Frame m_frame;
    lsr::Panel m_ContentPanel;
    lsr::BitmapField m_ContentPanel_Break;
    lsr::BitmapField m_ContentPanel_Airbag;
    lsr::Panel m_ReferencePanel;
    lsr::ReferenceBitmapField m_ReferencePanel_Break;
    lsr::ReferenceBitmapField m_ReferencePanel_Airbag;
};

} // namespace Telltales

#endif // _TELLTALES_HMI_H_
