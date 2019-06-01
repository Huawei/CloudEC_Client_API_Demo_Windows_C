//
//  DemoCallCtrlDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoCallCtrlDlg.h"
#include "DemoCallDlgManager.h"
#include "DemoMainDlg.h"

#include "DemoCallTransferDlg.h"
#include "DemoCommonTools.h"
#include "DemoData.h"
#include "DemoApp.h"
#include "service_init.h"
#include "service_call_interface.h"
#include "service_tools.h"
#include "service_os_adapt.h"

extern CString g_sipNumber;

// Define CallCtrlDlg wide and height
#define  DLG_WIDE_AUDIO        480
#define  DLG_HEIGHT_AUDIO     160
#define  DLG_WIDE_VIDEO    480
#define  DLG_HEIGHT_VIDEO  650
#define  IS_AUDIO          0

// CDemoCallCtrlDlg dialog
IMPLEMENT_DYNAMIC(CDemoCallCtrlDlg, CDialogEx)

CDemoCallCtrlDlg::CDemoCallCtrlDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoCallCtrlDlg::IDD, pParent)
    , m_sipnumber("")
    , m_calleeNum("")
    , m_CallID(0)
    , m_state(NO_CALL)
    , m_DlgType(AUDIO_DLG)
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
    DDX_Control(pDX, IDC_BUTTON_CONF, m_bt_conference);
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

    ON_MESSAGE(WM_CALL_UI_PLUGIN_CLICK_HANGUP_CALL, &CDemoCallCtrlDlg::OnUiPluginClickHangupCall)
    
END_MESSAGE_MAP()


// CDemoCallCtrlDlg message handlers

//DTMF
void CDemoCallCtrlDlg::OnBnClickedButtonDtmfPad()
{
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return;
    }
    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER(maindlg);
    ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_DTMF, NULL, NULL);
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
    if (VIDEO_DLG == m_DlgType)
    {
        book_conf_info.conf_media_type = TSDK_E_CONF_MEDIA_VIDEO;
    }
    else
    {
        book_conf_info.conf_media_type = TSDK_E_CONF_MEDIA_VOICE;
    }
 
    //是否自动闭音
    book_conf_info.is_auto_mute = FALSE;

    ////与会者列表
    //CString strChairmanNum = CTools::GetSipNumber(g_sipNumber);
    //CString strCalleeNum = CTools::UTF2UNICODE(m_calleeNum);

    book_conf_info.attendee_list = (TSDK_S_ATTENDEE_BASE_INFO*)malloc(2*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
    if (NULL == book_conf_info.attendee_list)
    {
        AfxMessageBox(_T("book_conf_info.attendee_list is NULL"));
        return;
    }
    service_memset_s(book_conf_info.attendee_list, 2*sizeof(TSDK_S_ATTENDEE_BASE_INFO), 0, 2*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
    //(void)strncpy_s(book_conf_info.attendee_list[0].number, TSDK_D_MAX_PARTICIPANTID_LEN + 1, CTools::UNICODE2UTF(strChairmanNum).c_str(), _TRUNCATE);
    //book_conf_info.attendee_list[0].role = TSDK_E_CONF_ROLE_CHAIRMAN;
    //(void)strncpy_s(book_conf_info.attendee_list[1].number, TSDK_D_MAX_PARTICIPANTID_LEN + 1, m_calleeNum.c_str(), _TRUNCATE);
    book_conf_info.attendee_list[0].role = TSDK_E_CONF_ROLE_ATTENDEE;

    //与会者个数
    book_conf_info.attendee_num = 1;

    //转会议
    (void)service_p2p_transfer_to_conference(m_CallID,&book_conf_info);

    free(book_conf_info.attendee_list);
}

//挂断
void CDemoCallCtrlDlg::OnBnClickedBtHangup()
{
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return;
    }
    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER(maindlg);

    if (!CheckStatusReturn(NO_CALL))
    {
        if (m_CallID)
        {
            ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_VIDEO_CLOSE, NULL, NULL);
            service_call_end(m_CallID);
            m_CallID = 0;
            OnClose();
        }
    }
}

void CDemoCallCtrlDlg::OnClose()
{
    CDemoCallCtrlDlg* pCallDlg = (CDemoCallCtrlDlg*)this;
    CallDlgManager::GetInstance().DeleteCallDlgByCallDlg(this);
}

//添加视频
void CDemoCallCtrlDlg::OnBnClickedBtAddVideo()
{
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return;
    }
    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER(maindlg);

    CString csMIc;
    m_bt_addVideo.GetWindowText(csMIc);
    if (m_CallID)
    {
        if (_T("Add video") == csMIc)
        {
            /////音频通话转视频////
            ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_VIDEO_CREATE, (WPARAM)m_CallID, NULL);
            if (0 == service_call_add_video(m_CallID))
            {
                m_bt_addVideo.SetWindowText(_T("Del video"));
            }
        }
        else
        {
            if (VIDEO_DLG == m_DlgType)
            {
                if (0 == service_call_delete_video(m_CallID))
                {
                    m_bt_addVideo.SetWindowText(_T("Add video"));
                    ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_VIDEO_CLOSE, NULL, NULL);
                }
            }
        }
    }
    else
    {
        /////直接发起视频通话////
        m_DlgType = VIDEO_DLG;
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
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return 0L;
    }
    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER_RETURN(maindlg,0L);

    char* pszNUmber = (char*)wparam;
    std::string sipnumber = pszNUmber;
    m_calleeNum = sipnumber;
    BOOL isVideo = lparam;
    unsigned int callId = 0;
    int result;

    if (isVideo)
    {
        m_bt_addVideo.SetWindowText(_T("Del video"));
        result = service_call_start(&callId, sipnumber.c_str(),TRUE);

        if (1 != service_is_use_ui_plugin())
        {
            //创建视频窗口
            ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_VIDEO_CREATE, (WPARAM)callId, NULL);
        }
    }
    else
    {
        result = service_call_start(&callId, sipnumber.c_str(),FALSE);
    }
    //////改变界面///// 
    m_CallID = callId;
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
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return 0L;
    }
    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER_RETURN(maindlg, 0L);

    TSDK_S_CALL_INFO* notifyInfo = (TSDK_S_CALL_INFO*)wParam;
    CHECK_POINTER_RETURN(notifyInfo, -1L);
    
    /////检查呼叫类型/////
    if (notifyInfo->is_video_call)
    {
        m_DlgType = VIDEO_DLG;
    }
    else
    {
        m_DlgType = AUDIO_DLG;
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_VIDEO_CLOSE, NULL, NULL);
        m_bt_addVideo.SetWindowText(_T("Add video"));
    }

    string strPeerNum = notifyInfo->peer_number;
    string strPeerName = notifyInfo->peer_display_name;
    m_peerNum.SetWindowText(CTools::UTF2UNICODE(strPeerNum));
    m_peerName.SetWindowText(CTools::UTF2UNICODE(strPeerName));

    m_CallID = notifyInfo->call_id;
    ChangeDlgType(m_DlgType);
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
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return 0L;
    }
    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER_RETURN(maindlg, 0L);

    INT_PTR nResponse = (INT_PTR)wParam;
    if (IDOK == nResponse)
    {
        //创建视频窗口
        ::PostMessage(maindlg->GetSafeHwnd(),WM_CALL_VIDEO_CREATE,(WPARAM)m_CallID,NULL);
        service_call_reply_add_video(m_CallID, TRUE);
        CALL_DLG_TYPE type = VIDEO_DLG;
        ChangeDlgType(type);
        m_bt_addVideo.SetWindowText(_T("Del video"));
    }
    else
    {
        service_call_reply_add_video(m_CallID, FALSE);
        CALL_DLG_TYPE type = AUDIO_DLG;
        ChangeDlgType(type);
        m_bt_addVideo.SetWindowText(_T("Add video"));
    }
    return 0L;
}

LRESULT CDemoCallCtrlDlg::OnCallModify(WPARAM wParam, LPARAM)
{
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return 0L;
    }
    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER_RETURN(maindlg, 0L);

    CALL_DLG_TYPE type = (CALL_DLG_TYPE)wParam;
    ChangeDlgType(type);
    if (AUDIO_DLG == type)
    {
        m_bt_addVideo.SetWindowText(_T("Add video"));
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_VIDEO_CLOSE, NULL, NULL);
    }
    else
    {
        m_bt_addVideo.SetWindowText(_T("Del video"));
    }
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
    MoveWindow((cxFrame - DLG_WIDE_AUDIO) / 2, (cyFrame - DLG_HEIGHT_AUDIO) / 2, DLG_WIDE_AUDIO, DLG_HEIGHT_AUDIO, TRUE);

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
    MoveWindow((cxFrame - DLG_WIDE_AUDIO) / 2, (cyFrame - DLG_HEIGHT_AUDIO) / 2, DLG_WIDE_AUDIO, DLG_HEIGHT_AUDIO, TRUE);

    return 0L;
}

LRESULT CDemoCallCtrlDlg::OnUiPluginClickHangupCall(WPARAM, LPARAM)
{
    OnBnClickedBtHangup();
    return 0L;
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
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return;
    }
    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER(maindlg);

    if (IS_AUDIO != isvideo)
    {
        m_bt_addVideo.SetWindowText(_T("Del video"));

        //创建视频窗口
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_VIDEO_CREATE, (WPARAM)m_CallID, NULL);
    }
    service_call_accept(m_CallID, isvideo);
    SetCallState(CALLING);
}

void CDemoCallCtrlDlg::ChangeDlgType(CALL_DLG_TYPE& type)
{
    m_DlgType = type;
}


