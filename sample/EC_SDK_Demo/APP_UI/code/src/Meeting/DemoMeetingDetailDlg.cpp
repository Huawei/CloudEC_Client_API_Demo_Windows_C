//
//  DemoMeetingDetailDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoCommonTools.h"
#include "DemoMeetingDetailDlg.h"
#include "DemoData.h"
#include "service_conf_interface.h"
#include "service_os_adapt.h"

extern MAP_CONFINFO g_mapConfInfo;
extern CString g_loginAccount;
extern CString g_sipNumber;
extern bool g_bIsJoinConf;
extern CString g_shortNumber;

// CDetailDlg dialog
IMPLEMENT_DYNAMIC(CDemoMeetingDetailDlg, CDialogEx)

CDemoMeetingDetailDlg::CDemoMeetingDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemoMeetingDetailDlg::IDD, pParent)
{

}

CDemoMeetingDetailDlg::~CDemoMeetingDetailDlg()
{
}

void CDemoMeetingDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CONF_TOPIC, m_stcConfTopic);
	DDX_Control(pDX, IDC_STATIC_CONF_STATUS, m_stcConfStatus);
	DDX_Control(pDX, IDC_STATIC_START_TIME, m_stcStartTime);
	DDX_Control(pDX, IDC_STATIC_END_TIME, m_stcEndTime);
	DDX_Control(pDX, IDC_STATIC_HOST_PWD, m_stcHostPwd);
	DDX_Control(pDX, IDC_STATIC_ATTEND_PWD, m_stcAttendPwd);
	DDX_Control(pDX, IDC_STATIC_CONF_HOST_NAME, m_stcConfHostName);
	DDX_Control(pDX, IDC_STATIC_CONF_MEETING_TYPE, m_stcMeetingType);
	DDX_Control(pDX, IDC_STATIC_CONF_ACCESS_NUM, m_stcAccessNum); 
	DDX_Control(pDX, IDC_STATIC_CONF_ID, m_stcConfID); 
	DDX_Control(pDX, IDC_STATIC_CONF_SELF_NUM, m_stcSelfNum);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_stcTips);
	DDX_Control(pDX, IDC_EDIT_CONF_TOPIC, m_edtConfTopic);
	DDX_Control(pDX, IDC_EDIT_CONF_STATUS, m_edtConfStatus);
	DDX_Control(pDX, IDC_EDIT_START_TIME, m_edtStartTime);
	DDX_Control(pDX, IDC_EDIT_END_TIME, m_edtEndTime);
	DDX_Control(pDX, IDC_EDIT_HOST_PWD, m_edtHostPwd);
	DDX_Control(pDX, IDC_EDIT_ATTEND_PWD, m_edtAttendPwd);
	DDX_Control(pDX, IDC_EDIT_CONF_HOST_NAME, m_edtConfHostName);
	DDX_Control(pDX, IDC_EDIT_CONF_MEETING_TYPE, m_edtMeetingType);
	DDX_Control(pDX, IDC_EDIT_CONF_ACCESS_NUM, m_edtAccessNum); 
	DDX_Control(pDX, IDC_EDIT_CONF_ID, m_edtConfID); 
	DDX_Control(pDX, IDC_EDIT_SELF_NUM, m_edtSelfNum);
}

BEGIN_MESSAGE_MAP(CDemoMeetingDetailDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_JOIN_CONF, &CDemoMeetingDetailDlg::OnBnClickedButtonJoinConf)
END_MESSAGE_MAP()


// CDetailDlg 消息处理程序

BOOL CDemoMeetingDetailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDemoMeetingDetailDlg::OnClose()
{
	CDialog::OnClose();
}

//一键入会
void CDemoMeetingDetailDlg::OnBnClickedButtonJoinConf()
{
	CString confId;
	m_edtConfID.GetWindowText(confId);
    unsigned int confID = 0;
    confID = (unsigned int)CTools::str2num(CTools::UNICODE2UTF(confId));

	CString selfNumber;
	m_edtSelfNum.GetWindowText(selfNumber);
	if(selfNumber.IsEmpty())
	{
		AfxMessageBox(_T("self number is empty,must input it!"));
		return;
	}

	TSDK_S_CONF_BASE_INFO confInfo;
    service_memset_s(&confInfo, sizeof(confInfo),0,sizeof(confInfo));
	confInfo = g_mapConfInfo[(long long)confID];

	TSDK_S_CONF_JOIN_PARAM confJoinParam;
	strcpy_s(confJoinParam.access_number, TSDK_D_MAX_CONF_ACCESS_LEN + 1, confInfo.access_number);
	strcpy_s(confJoinParam.conf_id, TSDK_D_MAX_CONF_ID_LEN + 1, confInfo.conf_id);

	if (confInfo.scheduser_name == g_loginAccount || confInfo.scheduser_account == g_loginAccount)
	{
		strcpy_s(confJoinParam.conf_password, TSDK_D_MAX_CONF_PASSWORD_LEN + 1, confInfo.chairman_pwd);
	}
	else
	{
		strcpy_s(confJoinParam.conf_password, TSDK_D_MAX_CONF_PASSWORD_LEN + 1, confInfo.guest_pwd);
	}

	unsigned int _callId = 0;
	int result = -1;
	TSDK_CHAR strSelfNumber[TSDK_D_MAX_NUMBER_LEN + 1];
	CTools::CString2Char(selfNumber, strSelfNumber, TSDK_D_MAX_NUMBER_LEN);
	if (TSDK_E_CONF_MEDIA_VOICE == confInfo.conf_media_type || TSDK_E_CONF_MEDIA_VOICE_DATA == confInfo.conf_media_type)
	{
		result = service_conf_join(&confJoinParam, strSelfNumber, FALSE, &_callId);
	}
	else if (TSDK_E_CONF_MEDIA_VIDEO == confInfo.conf_media_type || TSDK_E_CONF_MEDIA_VIDEO_DATA == confInfo.conf_media_type)
	{
		result = service_conf_join(&confJoinParam, strSelfNumber, TRUE, &_callId);
	}

	if (0 == result)
	{
		g_bIsJoinConf = true;
	}
	CDialog::OnOK();
}
