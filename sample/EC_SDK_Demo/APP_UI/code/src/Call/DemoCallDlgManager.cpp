//
//  DemoCallDlgManager.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "StdAfx.h"
#include "resource.h"
#include "DemoCallDlgManager.h"
#include "DemoData.h"

CallDlgManager::CallDlgManager(void)
{
}

CallDlgManager::~CallDlgManager(void)
{
}

CDemoCallCtrlDlg* CallDlgManager::CreateCallDlgBySIPnumber(const std::string& sipnumber)
{
    CDemoCallCtrlDlg* pCallDlg = new CDemoCallCtrlDlg;
    pCallDlg->Create(CDemoCallCtrlDlg::IDD, CWnd::FromHandle(::GetDesktopWindow()));
    pCallDlg->SetSIPnumber(sipnumber);
    m_vecCallDlg.push_back(pCallDlg);
    return pCallDlg;
}

CDemoCallCtrlDlg* CallDlgManager::GetCallDlgBySIPnumber(const std::string& sipnumber)
{
    auto it = m_vecCallDlg.begin();
    auto itEnd = m_vecCallDlg.end();
    for (; it != itEnd; it++)
    {
        CDemoCallCtrlDlg* pCallDlg = *it;
        if (pCallDlg && sipnumber.compare(pCallDlg->GetSIPnumber()) == 0)
        {
            return pCallDlg;
        }
    }
    return NULL;
}

CDemoCallCtrlDlg* CallDlgManager::GetCallDlgByNumber(const std::string& sipnumber)
{
    CDemoCallCtrlDlg* pCallDlg = CallDlgManager::GetInstance().GetCallDlgBySIPnumber(sipnumber);
    if (NULL == pCallDlg)
    {
        pCallDlg = CallDlgManager::GetInstance().CreateCallDlgBySIPnumber(sipnumber);
    }

    return pCallDlg;
}

CDemoCallCtrlDlg* CallDlgManager::GetCallDlgByCallID(const unsigned int& callid)
{
    auto it = m_vecCallDlg.begin();
    auto itEnd = m_vecCallDlg.end();
    for (; it != itEnd; it++)
    {
        CDemoCallCtrlDlg* pCallDlg = *it;
        if (pCallDlg && pCallDlg->GetCallID() == callid)
        {
            return pCallDlg;
        }
    }
    return NULL;
}

void CallDlgManager::DeleteCallDlgByCallDlg(CDemoCallCtrlDlg* pDlg)
{
    auto it = m_vecCallDlg.begin();
    auto itEnd = m_vecCallDlg.end();
    for (; it != itEnd; it++)
    {
        CDemoCallCtrlDlg* pCallDlg = *it;
        if (NULL != pCallDlg && pDlg == pCallDlg)
        {
            m_vecCallDlg.erase(it);
            delete (pCallDlg);
            break;
        }
    }
}
