//
//  DemoMeetingJoinDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoMeetingJoinDlg.h"
#include "DemoApp.h"
#include "DemoMainDlg.h"
#include "DemoCommonTools.h"
#include "service_conf_interface.h"

bool g_bIsJoinConf;
extern CString g_loginAccount;
extern CString g_sipNumber;

IMPLEMENT_DYNAMIC(CConnectDlg, CDialog)

CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CConnectDlg::IDD, pParent)
    , m_confJoinId(_T(""))
    , m_confJoinNum(_T(""))
    , m_confJoinPwd(_T(""))
{
}

CConnectDlg::~CConnectDlg()
{
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_JOIN_CONF_ID, m_confJoinId);
    DDX_Text(pDX, IDC_EDIT_JOIN_CONF_NUM, m_confJoinNum);
    DDX_Text(pDX, IDC_EDIT_JOIN_CONF_PWD, m_confJoinPwd);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
    ON_BN_CLICKED(IDOK, &CConnectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CConnectDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    UpdateData(FALSE);
    return TRUE;
}

void CConnectDlg::OnBnClickedOk()
{
    UpdateData(TRUE);

    char confId[TSDK_D_MAX_CONF_ID_LEN];
    char confJoinNum[TSDK_D_MAX_CONF_ACCESS_LEN];
    char confJoinPwd[TSDK_D_MAX_CONF_PASSWORD_LEN];

    CTools::CString2Char(m_confJoinId, confId, TSDK_D_MAX_CONF_ID_LEN);
    CTools::CString2Char(m_confJoinNum, confJoinNum, TSDK_D_MAX_CONF_ACCESS_LEN);
    CTools::CString2Char(m_confJoinPwd, confJoinPwd, TSDK_D_MAX_CONF_PASSWORD_LEN);


    TSDK_S_CONF_JOIN_PARAM confJoinParam;
    strcpy_s(confJoinParam.access_number, TSDK_D_MAX_CONF_ACCESS_LEN + 1, confJoinNum);
    strcpy_s(confJoinParam.conf_id, TSDK_D_MAX_CONF_ID_LEN + 1, confId);
    strcpy_s(confJoinParam.conf_password, TSDK_D_MAX_CONF_PASSWORD_LEN + 1, confJoinPwd);

    unsigned int _callId = 0;
    int result = -1;
    CString selfNumber = CTools::GetSipNumber(g_sipNumber);
    TSDK_CHAR strSelfNumber[TSDK_D_MAX_NUMBER_LEN + 1];
    CTools::CString2Char(selfNumber, strSelfNumber, TSDK_D_MAX_NUMBER_LEN);
    result = service_conf_join(&confJoinParam, strSelfNumber, TSDK_TRUE, &_callId);
    if (0 == result)
    {
        g_bIsJoinConf = true;
    }

    OnOK();
}
