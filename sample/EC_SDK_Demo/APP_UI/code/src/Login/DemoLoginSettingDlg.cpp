//
//  CDemoLoginSettingDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoLoginSettingDlg.h"
#include "DemoCommonTools.h"


// CDemoLoginSettingDlg dialog

IMPLEMENT_DYNAMIC(CDemoLoginSettingDlg, CDialogEx)

CDemoLoginSettingDlg::CDemoLoginSettingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoLoginSettingDlg::IDD, pParent)
{
    m_strServerAddress = _T("");
    m_strServerPort = _T("");
}

CDemoLoginSettingDlg::~CDemoLoginSettingDlg()
{
}

void CDemoLoginSettingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_SERVER_ADDRESS, m_editServerAddress);
    DDX_Control(pDX, IDC_EDIT_SERVER_PORT, m_editServerPort);
}


BEGIN_MESSAGE_MAP(CDemoLoginSettingDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDemoLoginSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDemoLoginSettingDlg message handlers
BOOL CDemoLoginSettingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CTools::GetIniConfigParam(_T("ServerConfig"), _T("serverIP"), m_strServerAddress);
    CTools::GetIniConfigParam(_T("ServerConfig"), _T("serverPort"), m_strServerPort);
    m_editServerAddress.SetWindowText(m_strServerAddress);
    m_editServerPort.SetWindowText(m_strServerPort);

    return TRUE;
}

void CDemoLoginSettingDlg::OnBnClickedOk()
{
    // TODO: Add your control notification handler code here
    SaveServer();
    CDialogEx::OnOK();
}

void CDemoLoginSettingDlg::SaveServer()
{
    m_editServerAddress.GetWindowText(m_strServerAddress);
    m_editServerPort.GetWindowText(m_strServerPort);
    CTools::WriteIniConfigParam(_T("ServerConfig"), _T("serverIP"), m_strServerAddress);
    CTools::WriteIniConfigParam(_T("ServerConfig"), _T("serverPort"), m_strServerPort);
}
