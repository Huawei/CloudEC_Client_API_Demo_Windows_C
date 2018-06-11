//
//  DemoSettingDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoSettingDlg.h"
#include "DemoCallSettingDlg.h"
#include "DemoData.h"


// CDemoSettingDlg dialog

IMPLEMENT_DYNAMIC(CDemoSettingDlg, CDialogEx)

CDemoSettingDlg::CDemoSettingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoSettingDlg::IDD, pParent)
    , m_callsetDlg(NULL)
{

}

CDemoSettingDlg::~CDemoSettingDlg()
{
    SAFE_DELETE(m_callsetDlg);
}

void CDemoSettingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB1, m_SetTable);
}


BEGIN_MESSAGE_MAP(CDemoSettingDlg, CDialogEx)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDemoSettingDlg::OnTcnSelchangeTab1)
    ON_BN_CLICKED(IDOK, &CDemoSettingDlg::OnBnClickedOk)
    ON_MESSAGE(WM_CALL_IPT_SUCESS, &CDemoSettingDlg::OnIPTSucess)
    ON_MESSAGE(WM_CALL_IPT_FAILED, &CDemoSettingDlg::OnIPTFailed)
END_MESSAGE_MAP()

BOOL CDemoSettingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    m_SetTable.InsertItem(0, _T("Call "));

    if (NULL == m_callsetDlg)
    {
        m_callsetDlg = new CDemoCallSettingDlg();
    }
    if (!::IsWindow(m_callsetDlg->GetSafeHwnd()))
    {
        m_callsetDlg->Create(CDemoCallSettingDlg::IDD, &m_SetTable);
    }

    CRect rect;
    m_SetTable.GetClientRect(&rect);
    rect.top += 24;
    m_callsetDlg->MoveWindow(rect);
    m_callsetDlg->ShowWindow(SW_SHOW);

    return TRUE;
}


// CDemoSettingDlg 消息处理程序


void CDemoSettingDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    CRect rect;
    m_SetTable.GetClientRect(&rect);
    rect.top += 25;
    switch (m_SetTable.GetCurSel())
    {
    case 0:
        m_callsetDlg->MoveWindow(rect);
        m_callsetDlg->ShowWindow(SW_SHOW);
        break;
    default:
        break;
    }
    *pResult = 0;
}


void CDemoSettingDlg::OnBnClickedOk()
{
    CDialogEx::OnOK();
}

LRESULT CDemoSettingDlg::OnIPTSucess(WPARAM wparam, LPARAM)
{
    /*unsigned int uiType = wparam;
    if (m_callsetDlg)
    {
        m_callsetDlg->m_callforwardDlg.IPTresult(true,uiType);
    }
*/
    return 0L;
}

LRESULT CDemoSettingDlg::OnIPTFailed(WPARAM wparam, LPARAM)
{
    /*unsigned int uiType = wparam;
    if (m_callsetDlg)
    {
        m_callsetDlg->m_callforwardDlg.IPTresult(false,uiType);
    }*/
    return 0L;
}
