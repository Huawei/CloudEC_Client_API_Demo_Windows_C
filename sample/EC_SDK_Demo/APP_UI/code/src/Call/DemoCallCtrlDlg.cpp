//
//  DemoCallCtrlDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoCallCtrlDlg.h"
#include "DemoCallDlgManager.h"
#include "DemoCallDtmfDlg.h"
#include "DemoCallTransferDlg.h"
#include "DemoCommonTools.h"
#include "DemoData.h"
#include "DemoApp.h"
#include "service_call_interface.h"
#include "service_tools.h"
#include "service_os_adapt.h"

extern CString g_sipNumber;

// Define CallCtrlDlg wide and height
#define  DLG_WIDE_AUDIO        480
#define  DLG_HEIGHT_AUDIO     160
#define  DLG_WIDE_VIDEO    480
#define  DLG_HEIGHT_VIDEO  650

// CDemoCallCtrlDlg dialog
IMPLEMENT_DYNAMIC(CDemoCallCtrlDlg, CDialogEx)

CDemoCallCtrlDlg::CDemoCallCtrlDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoCallCtrlDlg::IDD, pParent)
    , m_sipnumber("")
    , m_calleeNum("")
    , m_CallID(0)
    , m_state(NO_CALL)
    , m_DlgType(UC_SIGNLE_CHAT)
{
}

CDemoCallCtrlDlg::~CDemoCallCtrlDlg()
{
}

void CDemoCallCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_HOLD, m_bt_hold);
    DDX_Control(pDX, IDC_BUTTON_MUTE_MIC, m_bt_muteMic);
    DDX_Control(pDX, IDC_BUTTON_DTMF_PAD, m_bt_dtmf);
    DDX_Control(pDX, IDC_BUTTON_TRANSFER, m_bt_transfer);
    DDX_Control(pDX, IDC_BUTTON_HUNGUP, m_bt_hangup);
    DDX_Control(pDX, IDC_BUTTON_ADD_VIDEO, m_bt_addVideo);
    DDX_Control(pDX, IDC_BUTTON_CONTROL_VIDEO, m_bt_control);
    DDX_Control(pDX, IDC_BUTTON_CONF, m_bt_conference);
    DDX_Control(pDX, IDC_REMOTE_VIDEO, m_remotevideoCtrl);
    DDX_Control(pDX, IDC_LOCAL_VIDEO, m_localvideoCtrl);
    DDX_Control(pDX, IDC_TITLE_REMOTE_VIDEO, m_static_remote);
    DDX_Control(pDX, IDC_TITLE_LOCAL_VIDEO, m_static_local);
    DDX_Control(pDX, IDC_SEG_LINE, m_seg_line);
    DDX_Control(pDX, IDC_CALL_STATE, m_stcCalling);
    DDX_Control(pDX, IDC_PEER_NUM, m_peerNum);
    DDX_Control(pDX, IDC_PEER_NAME, m_peerName);
}

BEGIN_MESSAGE_MAP(CDemoCallCtrlDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_PAD, &CDemoCallCtrlDlg::OnBnClickedButtonDtmfPad)
    ON_BN_CLICKED(IDC_BUTTON_TRANSFER, &CDemoCallCtrlDlg::OnBnClickedBtTransfer)
    ON_BN_CLICKED(IDC_BUTTON_HOLD, &CDemoCallCtrlDlg::OnBnClickedBtHold)
    ON_BN_CLICKED(IDC_BUTTON_MUTE_MIC, &CDemoCallCtrlDlg::OnBnClickedBtMuteMic)
    ON_BN_CLICKED(IDC_BUTTON_HUNGUP, &CDemoCallCtrlDlg::OnBnClickedBtHangup)
    ON_BN_CLICKED(IDC_BUTTON_ADD_VIDEO, &CDemoCallCtrlDlg::OnBnClickedBtAddVideo)
    ON_BN_CLICKED(IDC_BUTTON_CONTROL_VIDEO, &CDemoCallCtrlDlg::OnClickedBtControlVideo)
    ON_BN_CLICKED(IDC_BUTTON_CONF, &CDemoCallCtrlDlg::OnClickedBtTransferToConf)
    ON_MESSAGE(WM_CALL_START_CALL, &CDemoCallCtrlDlg::OnStartCall)
    ON_MESSAGE(WM_CALL_END, &CDemoCallCtrlDlg::OnCallEnd)
    ON_MESSAGE(WM_CALL_CONNECTED, &CDemoCallCtrlDlg::OnConnected)
    ON_MESSAGE(WM_CALL_ANSWER_VIDEO, &CDemoCallCtrlDlg::OnAcceptVideoCall)
    ON_MESSAGE(WM_CALL_ANSWER_AUDIO, &CDemoCallCtrlDlg::OnAcceptAudioCall)
    ON_MESSAGE(WM_CALL_ADD_VIDEO, &CDemoCallCtrlDlg::OnAddVideo)
    ON_MESSAGE(WM_CALL_MODIFY_VIDEO, &CDemoCallCtrlDlg::OnCallModify)
    ON_MESSAGE(WM_CALL_HOLD_SUCESS, &CDemoCallCtrlDlg::OnHoldSucess)
    ON_MESSAGE(WM_CALL_UNHOLD_SUCESS, &CDemoCallCtrlDlg::OnUnHoldSucess)
END_MESSAGE_MAP()


// CDemoCallCtrlDlg message handlers

//DTMF
void CDemoCallCtrlDlg::OnBnClickedButtonDtmfPad()
{
    CDemoCallCtrlDlg* pCallDlg = (CDemoCallCtrlDlg*)this;
    CHECK_POINTER(pCallDlg);
    CDemoCallDtmfDlg dlg;
    dlg.SetCallid(pCallDlg->GetCallID());
    (void)dlg.DoModal();
}

//忙转
void CDemoCallCtrlDlg::OnBnClickedBtTransfer()
{
    CDemoCallTransferDlg dlg;
    INT_PTR nResponse = dlg.DoModal();
    std::string transfernumber = dlg.GetNumber();
    if (IDOK == nResponse)
    {
        ////start blind transfer
        if (transfernumber.length())
        {
            service_call_transfer(m_CallID, transfernumber.c_str());
        }
        else
        {
            AfxMessageBox(_T("Transfer Number is null"));
        }
    }
}

//呼叫保持
void CDemoCallCtrlDlg::OnBnClickedBtHold()
{
    if (CheckStatusReturn(CALL_CONNECTED) || CheckStatusReturn(CALL_HOLD))
    {
        CDemoCallCtrlDlg* pCallDlg = (CDemoCallCtrlDlg*)this;
        CHECK_POINTER(pCallDlg);

        CString csHold;
        m_bt_hold.GetWindowText(csHold);
        if (_T("Hold") == csHold)
        {
            service_call_hold(m_CallID);
            m_bt_hold.SetWindowText(_T("unHold"));
        }
        else
        {
            service_call_unhold(m_CallID);
            m_bt_hold.SetWindowText(_T("Hold"));
        }
    }
}

//静音麦克风
void CDemoCallCtrlDlg::OnBnClickedBtMuteMic()
{
    if (CheckStatusReturn(CALL_CONNECTED) || CheckStatusReturn(CALL_HOLD))
    {
        CDemoCallCtrlDlg* pCallDlg = (CDemoCallCtrlDlg*)this;
        CHECK_POINTER(pCallDlg);
        CString csMIc;
        m_bt_muteMic.GetWindowText(csMIc);
        if (_T("Mute mic") == csMIc)
        {
            m_bt_muteMic.SetWindowText(_T("unMute mic"));
            service_call_mic_mute(m_CallID, TRUE);
        }
        else
        {
            m_bt_muteMic.SetWindowText(_T("Mute mic"));
            service_call_mic_mute(m_CallID, FALSE);
        }
    }
}

//转会议
void CDemoCallCtrlDlg::OnClickedBtTransferToConf()
{
    TSDK_S_BOOK_CONF_INFO book_conf_info = { 0 };

    book_conf_info.size = 2;

    //会议标题
    CString strMeetingSubject = g_sipNumber + _T("'s conference");
    CTools::CString2Char(strMeetingSubject, book_conf_info.subject, TSDK_D_MAX_SUBJECT_LEN);

    //会议群组号，默认空
    strncpy_s(book_conf_info.group_uri, TSDK_D_MAX_GROUP_URI_LEN + 1, "", TSDK_D_MAX_GROUP_URI_LEN - 1);

    //会议类型是立即会议
    book_conf_info.conf_type = TSDK_E_CONF_INSTANT;
    strncpy_s(book_conf_info.start_time, TSDK_D_MAX_TIME_FORMATE_LEN + 1, "", TSDK_D_MAX_TIME_FORMATE_LEN - 1);

    //会议媒体类型
    if (SIP_SIGNLE_VIDEO == m_DlgType)
    {
        book_conf_info.conf_media_type = TSDK_E_CONF_MEDIA_VIDEO;
    }
    else
    {
        book_conf_info.conf_media_type = TSDK_E_CONF_MEDIA_VOICE;
    }
 
    //是否自动闭音
    book_conf_info.is_auto_mute = FALSE;

    //与会者列表
    CString strChairmanNum = CTools::GetSipNumber(g_sipNumber);
    CString strCalleeNum = CTools::UTF2UNICODE(m_calleeNum);

    book_conf_info.attendee_list = (TSDK_S_ATTENDEE_BASE_INFO*)malloc(2*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
    if (NULL == book_conf_info.attendee_list)
    {
        AfxMessageBox(_T("book_conf_info.attendee_list is NULL"));
        return;
    }
    (void)service_memset_s(book_conf_info.attendee_list, 2*sizeof(TSDK_S_ATTENDEE_BASE_INFO), 0, 2*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
    (void)strncpy_s(book_conf_info.attendee_list[0].number, TSDK_D_MAX_PARTICIPANTID_LEN + 1, CTools::UNICODE2UTF(strChairmanNum).c_str(), _TRUNCATE);
    book_conf_info.attendee_list[0].role = TSDK_E_CONF_ROLE_CHAIRMAN;
    (void)strncpy_s(book_conf_info.attendee_list[1].number, TSDK_D_MAX_PARTICIPANTID_LEN + 1, m_calleeNum.c_str(), _TRUNCATE);
    book_conf_info.attendee_list[0].role = TSDK_E_CONF_ROLE_ATTENDEE;

    //与会者个数
    book_conf_info.attendee_num = 2;

    //转会议
    (void)service_p2p_transfer_to_conference(m_CallID,&book_conf_info);
}

//挂断
void CDemoCallCtrlDlg::OnBnClickedBtHangup()
{
    if (!CheckStatusReturn(NO_CALL))
    {
        CDemoCallCtrlDlg* pCallDlg = (CDemoCallCtrlDlg*)this;
        CHECK_POINTER(pCallDlg);
        if (m_CallID)
        {
            service_call_end(m_CallID);
            m_CallID = 0;
            OnClose();
        }
    }
}

void CDemoCallCtrlDlg::OnClose()
{
    CallDlgManager::GetInstance().DeleteCallDlgByCallDlg(this);
    /*CDialogEx::OnClose();*/
}

//添加视频
void CDemoCallCtrlDlg::OnBnClickedBtAddVideo()
{
    CString csMIc;
    m_bt_addVideo.GetWindowText(csMIc);
    if (m_CallID)
    {
        if (_T("Add video") == csMIc)
        {
            m_bt_addVideo.SetWindowText(_T("Add audio"));

            /////音频通话转视频////
            HWND mLocalVideo = m_localvideoCtrl.GetSafeHwnd();
            HWND mRemoteVideo = m_remotevideoCtrl.GetSafeHwnd();
            service_set_video_window(m_CallID, (unsigned int)mLocalVideo, (unsigned int)mRemoteVideo);
            service_call_add_video(m_CallID);
        }
        else
        {
            m_bt_addVideo.SetWindowText(_T("Add video"));
            if (SIP_SIGNLE_VIDEO == m_DlgType)
            {
                service_call_delete_video(m_CallID);
            }
        }
    }
    else
    {
        /////直接发起视频通话////
        m_DlgType = UC_SIGNLE_VIDEO;
        unsigned int nlen = m_sipnumber.length();
        char* psznumber = new char[nlen + 1];
        service_memset_s(psznumber, nlen + 1, 0, nlen + 1);
        unsigned int isVideo = 1;
        strncpy_s(psznumber, nlen + 1, m_sipnumber.c_str(), _TRUNCATE);
        SendMessage(WM_CALL_START_CALL, (WPARAM)(psznumber), (LPARAM)isVideo);
    }
}

//开始呼叫
LRESULT CDemoCallCtrlDlg::OnStartCall(WPARAM wparam, LPARAM lparam)
{
    char* pszNUmber = (char*)wparam;
    std::string sipnumber = pszNUmber;
    m_calleeNum = sipnumber;
    BOOL isVideo = lparam;
    unsigned int callId = 0;
    int result;
    if (isVideo)
    {
        HWND localVideo = m_localvideoCtrl.GetSafeHwnd();
        HWND remoteVideo = m_remotevideoCtrl.GetSafeHwnd();
        result = service_call_video_start(sipnumber.c_str(), (unsigned int)localVideo, (unsigned int)remoteVideo);
    }
    else
    {
        result = service_call_audio_start(callId, sipnumber.c_str());
    }
    //////改变界面///// 
    RefreshWindow();
    SetCallState(CALLING);
    delete pszNUmber;
    return (LRESULT)result;
}

//呼叫结束
LRESULT CDemoCallCtrlDlg::OnCallEnd(WPARAM wparam, LPARAM lparam)
{
    SetCallState(NO_CALL);
    SetCallID(0);
    OnClose();
    return 0L;
}

//呼叫连接
LRESULT CDemoCallCtrlDlg::OnConnected(WPARAM wParam, LPARAM lparam)
{
    DLG_TYPE type = (DLG_TYPE)wParam;
    m_CallID = (unsigned int)lparam;
    ChangeDlgType(type);
    SetCallState(CALL_CONNECTED);
    return 0L;
}

//音频接听
LRESULT CDemoCallCtrlDlg::OnAcceptAudioCall(WPARAM wParam, LPARAM lparam)
{
    AcceptCall(0);
    return 0L;
}

//视频接听
LRESULT CDemoCallCtrlDlg::OnAcceptVideoCall(WPARAM wParam, LPARAM lparam)
{
    AcceptCall(1);
    return 0L;
}

LRESULT CDemoCallCtrlDlg::OnAddVideo(WPARAM wParam, LPARAM lparam)
{
    INT_PTR nResponse = (INT_PTR)wParam;
    HWND mLocalVideo = m_localvideoCtrl.GetSafeHwnd();
    HWND mRemoteVideo = m_remotevideoCtrl.GetSafeHwnd();
    if (IDOK == nResponse)
    {
        service_set_video_window(m_CallID, (unsigned int)mLocalVideo, (unsigned int)mRemoteVideo);
        service_call_reply_add_video(m_CallID, TRUE);
        DLG_TYPE type = SIP_SIGNLE_VIDEO;
        ChangeDlgType(type);
    }
    else
    {
        service_call_reply_add_video(m_CallID, FALSE);
        DLG_TYPE type = SIP_SIGNLE_CALL;
        ChangeDlgType(type);
    }
    RefreshWindow();
    return 0L;
}

LRESULT CDemoCallCtrlDlg::OnCallModify(WPARAM wParam, LPARAM)
{
    DLG_TYPE type = (DLG_TYPE)wParam;
    ChangeDlgType(type);
    return 0L;
}

//保持通话成功
LRESULT CDemoCallCtrlDlg::OnHoldSucess(WPARAM, LPARAM)
{
    m_bt_hold.SetWindowText(_T("unHold"));
    SetCallState(CALL_HOLD);

    //获取屏幕中间的位置
    int cxFrame = ::GetSystemMetrics(SM_CXSCREEN);
    int cyFrame = ::GetSystemMetrics(SM_CYSCREEN);

    if (SIP_SIGNLE_VIDEO == m_DlgType)
    {
        MoveWindow((cxFrame - DLG_WIDE_AUDIO) / 2, (cyFrame - DLG_HEIGHT_AUDIO) / 2, DLG_WIDE_AUDIO, DLG_HEIGHT_AUDIO, TRUE);
        m_seg_line.ShowWindow(SW_HIDE);
        m_remotevideoCtrl.ShowWindow(SW_HIDE);
        m_localvideoCtrl.ShowWindow(SW_HIDE);
        m_static_remote.ShowWindow(SW_HIDE);
        m_static_local.ShowWindow(SW_HIDE);
        m_bt_control.ShowWindow(SW_HIDE);
    }
    return 0L;
}

//恢复通话成功
LRESULT CDemoCallCtrlDlg::OnUnHoldSucess(WPARAM, LPARAM)
{
    m_bt_hold.SetWindowText(_T("Hold"));
    SetCallState(CALL_CONNECTED);

    //获取屏幕中间的位置
    int cxFrame = ::GetSystemMetrics(SM_CXSCREEN);
    int cyFrame = ::GetSystemMetrics(SM_CYSCREEN);

    if (SIP_SIGNLE_VIDEO == m_DlgType)
    {
        MoveWindow((cxFrame - DLG_WIDE_VIDEO) / 2, (cyFrame - DLG_HEIGHT_VIDEO) / 2, DLG_WIDE_VIDEO, DLG_HEIGHT_VIDEO, TRUE);
        m_seg_line.ShowWindow(SW_SHOW);
        m_remotevideoCtrl.ShowWindow(SW_SHOW);
        m_localvideoCtrl.ShowWindow(SW_SHOW);
        m_static_remote.ShowWindow(SW_SHOW);
        m_static_local.ShowWindow(SW_SHOW);
        m_bt_control.ShowWindow(SW_SHOW);
    }
    return 0L;
}

//刷新窗口
void CDemoCallCtrlDlg::RefreshWindow()
{
    //获取屏幕中间的位置
    int cxFrame = ::GetSystemMetrics(SM_CXSCREEN);
    int cyFrame = ::GetSystemMetrics(SM_CYSCREEN);

    CString peerName = CTools::UTF2UNICODE(m_sipnumber);
    m_peerName.SetWindowText(peerName);
    m_peerNum.SetWindowText(peerName);

    switch (m_DlgType)
    {
    case SIP_SIGNLE_VIDEO:
    {
        MoveWindow((cxFrame - DLG_WIDE_VIDEO) / 2, (cyFrame - DLG_HEIGHT_VIDEO) / 2, DLG_WIDE_VIDEO, DLG_HEIGHT_VIDEO, TRUE);
        m_bt_addVideo.ShowWindow(SW_SHOW);
        m_bt_addVideo.SetWindowText(_T("Add audio"));
        m_seg_line.ShowWindow(SW_SHOW);
        m_remotevideoCtrl.ShowWindow(SW_SHOW);
        m_localvideoCtrl.ShowWindow(SW_SHOW);
        m_static_remote.ShowWindow(SW_SHOW);
        m_static_local.ShowWindow(SW_SHOW);
    }break;
    case SIP_SIGNLE_CALL:
    {
        MoveWindow((cxFrame - DLG_WIDE_AUDIO) / 2, (cyFrame - DLG_HEIGHT_AUDIO) / 2, DLG_WIDE_AUDIO, DLG_HEIGHT_AUDIO, TRUE);
        m_bt_addVideo.ShowWindow(SW_SHOW);
        m_bt_addVideo.SetWindowText(_T("Add video"));
        m_seg_line.ShowWindow(SW_HIDE);
        m_remotevideoCtrl.ShowWindow(SW_HIDE);
        m_localvideoCtrl.ShowWindow(SW_HIDE);
        m_static_remote.ShowWindow(SW_HIDE);
        m_static_local.ShowWindow(SW_HIDE);
    }break;
    default: break;
    }
}

//设置呼叫状态
void CDemoCallCtrlDlg::SetCallState(CALLSTATUS istate)
{
    m_bt_hangup.SetWindowText(_T("HungUp"));

    m_state = istate;
    switch (m_state)
    {
    case NO_CALL:
    {
        ShowWindow(SW_HIDE);
    }break;
    case CALLING:
    {
        m_stcCalling.SetWindowText(_T("calling..."));
        m_bt_dtmf.ShowWindow(SW_HIDE);
        m_bt_addVideo.ShowWindow(SW_HIDE);
        m_bt_hold.ShowWindow(SW_HIDE);
        m_bt_muteMic.ShowWindow(SW_HIDE);
        m_bt_transfer.ShowWindow(SW_HIDE);
        m_bt_conference.ShowWindow(SW_HIDE);
        ShowWindow(SW_SHOW);
    }break;
    case CALL_CONNECTED:
    {
        m_stcCalling.SetWindowText(_T("Connected."));
        m_bt_dtmf.ShowWindow(SW_SHOW);
        m_bt_hold.ShowWindow(SW_SHOW);
        m_bt_muteMic.ShowWindow(SW_SHOW);
        m_bt_transfer.ShowWindow(SW_SHOW);
        m_bt_addVideo.ShowWindow(SW_SHOW);
        m_bt_conference.ShowWindow(SW_SHOW);
        m_bt_transfer.EnableWindow(TRUE);
        m_bt_addVideo.EnableWindow(TRUE);
    }break;
    case CALL_HOLD:
    {
        m_stcCalling.SetWindowText(_T("Hold."));
        m_bt_dtmf.ShowWindow(SW_SHOW);
        m_bt_muteMic.ShowWindow(SW_SHOW);
        m_bt_hold.ShowWindow(SW_SHOW);
        m_bt_transfer.EnableWindow(FALSE);
        m_bt_addVideo.EnableWindow(FALSE);
        m_bt_conference.EnableWindow(FALSE);
    }break;
    default: break;
    }
}

void CDemoCallCtrlDlg::AcceptCall(unsigned int isvideo)
{
    if (0 != isvideo)
    {
        HWND mLocalVideo = m_localvideoCtrl.GetSafeHwnd();
        HWND mRemoteVideo = m_remotevideoCtrl.GetSafeHwnd();
        (void)service_set_video_window(m_CallID, (unsigned int)mLocalVideo, (unsigned int)mRemoteVideo);
    }
    service_call_accept(m_CallID, isvideo);
    RefreshWindow();
    SetCallState(CALLING);
}

void CDemoCallCtrlDlg::ChangeDlgType(DLG_TYPE& type)
{
    m_DlgType = type;
    RefreshWindow();
}

void CDemoCallCtrlDlg::OnClickedBtControlVideo()
{
    CString csMIc;
    m_bt_control.GetWindowText(csMIc);
    if (m_CallID && SIP_SIGNLE_VIDEO == m_DlgType)
    {
        if (_T("Stop Video") == csMIc)
        {
            m_bt_control.SetWindowText(_T("Start Video"));
            service_call_video_control(m_CallID, TRUE);
        }
        else
        {
            m_bt_control.SetWindowText(_T("Stop Video"));
            service_call_video_control(m_CallID, FALSE);
        }
    }
}

