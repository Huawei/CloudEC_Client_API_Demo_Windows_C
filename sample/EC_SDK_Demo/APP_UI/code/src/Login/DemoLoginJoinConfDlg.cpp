//
//  DemoLoginJoinConfDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoLoginJoinConfDlg.h"
#include "DemoCommonTools.h"
#include "service_conf_interface.h"
#include "service_os_adapt.h"


// CDemoLoginJoinConfDlg dialog

IMPLEMENT_DYNAMIC(CDemoLoginJoinConfDlg, CDialogEx)

CDemoLoginJoinConfDlg::CDemoLoginJoinConfDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoLoginJoinConfDlg::IDD, pParent)
    , m_strConfServerAddress(_T(""))
    , m_strConfServerPort(_T(""))
    , m_strConfId(_T(""))
    , m_strJoinPwd(_T(""))
    , m_strNickname(_T(""))
{
}

CDemoLoginJoinConfDlg::~CDemoLoginJoinConfDlg()
{
}

void CDemoLoginJoinConfDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_CONF_SERVER_ADDRESS, m_editConfServerAddress);
    DDX_Control(pDX, IDC_EDIT_CONF_SERVER_PORT, m_editConfServerPort);
    DDX_Control(pDX, IDC_EDIT_CONF_ID, m_editConfId);
    DDX_Control(pDX, IDC_EDIT_JOIN_PWD, m_editJoinPwd);
    DDX_Control(pDX, IDC_EDIT_NICKNAME, m_editNickname);
}


BEGIN_MESSAGE_MAP(CDemoLoginJoinConfDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDemoLoginJoinConfDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDemoLoginJoinConfDlg message handlers
BOOL CDemoLoginJoinConfDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CTools::GetIniConfigParam(_T("AnonymousConfConfig"), _T("nickname"), m_strNickname);
    CTools::GetIniConfigParam(_T("AnonymousConfConfig"), _T("confServerIP"), m_strConfServerAddress);
    CTools::GetIniConfigParam(_T("AnonymousConfConfig"), _T("confServerPort"), m_strConfServerPort);
    
    m_editNickname.SetWindowText(m_strNickname);
    m_editConfServerAddress.SetWindowText(m_strConfServerAddress);
    m_editConfServerPort.SetWindowText(m_strConfServerPort);

    return TRUE;
}

void CDemoLoginJoinConfDlg::OnBnClickedOk()
{ 
    m_editConfServerAddress.GetWindowText(m_strConfServerAddress);
    m_editConfServerPort.GetWindowText(m_strConfServerPort);
    m_editConfId.GetWindowText(m_strConfId);
    m_editJoinPwd.GetWindowText(m_strJoinPwd);
    m_editNickname.GetWindowText(m_strNickname);

    TSDK_S_CONF_ANONYMOUS_JOIN_PARAM anonymousJoinConfParam;
    service_memset_s(&anonymousJoinConfParam,sizeof(TSDK_S_CONF_ANONYMOUS_JOIN_PARAM),0,sizeof(TSDK_S_CONF_ANONYMOUS_JOIN_PARAM));
    
    anonymousJoinConfParam.user_id = 1;
    CTools::CString2Char(m_strConfId, anonymousJoinConfParam.conf_id, TSDK_D_MAX_CONF_ID_LEN);
    CTools::CString2Char(m_strJoinPwd, anonymousJoinConfParam.conf_password, TSDK_D_MAX_CONF_PASSWORD_LEN);
    CTools::CString2Char(m_strConfServerAddress, anonymousJoinConfParam.server_addr, TSDK_D_MAX_URL_LENGTH);
    CTools::CString2Char(m_strNickname, anonymousJoinConfParam.display_name, TSDK_D_MAX_DISPLAY_NAME_LEN);
    anonymousJoinConfParam.server_port = (unsigned short)CTools::str2num(CTools::UNICODE2UTF(m_strConfServerPort));
    
    (void)service_join_conference_by_anonymous(&anonymousJoinConfParam);
    
    CTools::WriteIniConfigParam(_T("AnonymousConfConfig"), _T("nickname"), m_strNickname);
    CTools::WriteIniConfigParam(_T("AnonymousConfConfig"), _T("confServerIP"), m_strConfServerAddress);
    CTools::WriteIniConfigParam(_T("AnonymousConfConfig"), _T("confServerPort"), m_strConfServerPort);
    
    CDialogEx::OnOK();
}
