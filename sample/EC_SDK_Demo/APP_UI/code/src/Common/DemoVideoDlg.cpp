//
//  DemoVideoDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoVideoDlg.h"


// CDemoVideoDlg dialog

IMPLEMENT_DYNAMIC(CDemoVideoDlg, CDialogEx)

	CDemoVideoDlg::CDemoVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemoVideoDlg::IDD, pParent)
    , m_callID(0)
{

}

CDemoVideoDlg::~CDemoVideoDlg()
{
    m_callID = 0;
}

void CDemoVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REMOTE_VIDEO, m_remoteVideo);
	DDX_Control(pDX, IDC_LOCAL_VIDEO, m_localVideo);
	DDX_Control(pDX, IDC_TITLE_REMOTE_VIDEO, m_title_remote);
	DDX_Control(pDX, IDC_TITLE_LOCAL_VIDEO, m_title_local);
    DDX_Control(pDX, IDC_BT_CONTROL_VIDEO, m_bt_video_control);
}

BEGIN_MESSAGE_MAP(CDemoVideoDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BT_CONTROL_VIDEO,CDemoVideoDlg::OnClickedBtControlVideo)
END_MESSAGE_MAP()


// CDemoRunInfoDlg message handlers
BOOL CDemoVideoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
	return TRUE;
}


void CDemoVideoDlg::BindVideoWindow(TSDK_S_JOIN_CONF_IND_INFO* conf_ind_info)
{
    HWND localVideo = m_localVideo.GetSafeHwnd();
    HWND remoteVideo = m_remoteVideo.GetSafeHwnd();
    if (conf_ind_info == TSDK_NULL_PTR)
    {
        (void)service_set_video_window(m_callID, (unsigned int)localVideo, (unsigned int)remoteVideo);
    }
    else
    {
        if (TSDK_TRUE == conf_ind_info->is_svc_conf)
        {
            (void)service_set_svc_video_window(m_callID, conf_ind_info->svc_label[0], (unsigned int)localVideo, (unsigned int)remoteVideo);
        }
        else
        {
            (void)service_set_video_window(m_callID, (unsigned int)localVideo, (unsigned int)remoteVideo);
        }
    }
    
}

void CDemoVideoDlg::OnClickedBtControlVideo()
{
    CString csMIc;
    m_bt_video_control.GetWindowText(csMIc);
    if (m_callID)
    {
        if (_T("Stop Video") == csMIc)
        {
            m_bt_video_control.SetWindowText(_T("Start Video"));
            service_call_video_control(m_callID, TRUE);
        }
        else
        {
            m_bt_video_control.SetWindowText(_T("Stop Video"));
            service_call_video_control(m_callID, FALSE);
        }
    }
}
