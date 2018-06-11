//
//  DemoMainDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoMainDlg.h"
#include "DemoShare.h"
#include "DemoCallCtrlDlg.h"
#include "DemoCallDlgManager.h"
#include "DemoPromptDlg.h"
#include "DemoCallInCommingDlg.h"
#include "service_data_conf_global_data.h"
#include "service_logout.h"
#include "service_call_interface.h"
#include "service_conf_interface.h"

extern CString g_loginAccount;
extern CString g_sipNumber;

// CDemoMainDlg dialog

IMPLEMENT_DYNAMIC(CDemoMainDlg, CDialogEx)

CDemoMainDlg::CDemoMainDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoMainDlg::IDD, pParent)
    , m_settingDlg(NULL)
    , m_audioConfDlg(NULL)
    , m_videoConfDlg(NULL)
    , m_dataConfDlg(NULL)
    , m_confHandle(0)
	, m_callId(0)
    , m_isConfChairman(true)
    , m_CurSelTab(0)
{
    for (unsigned int i = 0; i < NUM; i++)
    {
        m_Dlg[i] = NULL;
    }
}

CDemoMainDlg::~CDemoMainDlg()
{
    SAFE_DELETE(m_settingDlg);
    m_videoConfDlg = NULL;
    m_dataConfDlg = NULL;
    m_audioConfDlg = NULL;
}

void CDemoMainDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_MAIN, m_TabItem);
    DDX_Control(pDX, IDC_PICTURE_MY_PHOTO, m_MyPhoto);
    DDX_Control(pDX, IDC_STATIC_MY_NAME, m_MyName);
    DDX_Control(pDX, IDC_STATIC_MY_NUM, m_MyNumber);
    DDX_Control(pDX, IDC_BUTTON_SYSMENU, m_btnSysMenu);
}

BEGIN_MESSAGE_MAP(CDemoMainDlg, CDialogEx)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CDemoMainDlg::OnTcnSelchangeTabFunction)
    /*ON_BN_CLICKED(IDC_BUTTON_ENT_ADDR, &CDemoMainDlg::OnBnClickedButtonEntaddr)*/
    ON_BN_CLICKED(IDC_BUTTON_SYSMENU, &CDemoMainDlg::OnBnClickedBtSysmenu)
    ON_COMMAND_RANGE(ID_MAIN_SETTING_MENU, ID_MAIN_EXIT_MENU, &CDemoMainDlg::OnClickMainMenuItem)
    ON_MESSAGE(WM_FORCE_LOGOUT, &CDemoMainDlg::OnForceLogout)
    ON_MESSAGE(WM_CALL_STARTCALL, &CDemoMainDlg::OnStartCall)
    ON_MESSAGE(WM_CALL_END, &CDemoMainDlg::OnCallEnd)
    ON_MESSAGE(WM_CALL_CONNECTED, &CDemoMainDlg::OnConnected)
    ON_MESSAGE(WM_CALL_INCOMMING, &CDemoMainDlg::OnCallIncoming)
    ON_MESSAGE(WM_CALL_ADD_VIDEO, &CDemoMainDlg::OnCallAddVideo)
    ON_MESSAGE(WM_CALL_OPEN_VIDEO, &CDemoMainDlg::OnCallOpenVideo)
    ON_MESSAGE(WM_CALL_CLOSE_VIDEO, &CDemoMainDlg::OnCallCloseVideo)
    ON_MESSAGE(WM_CALL_REFUSE_OPEN_VIDEO, &CDemoMainDlg::OnCallRefuseOpenVideo)
    ON_MESSAGE(WM_CONF_CTRL_JOIN_RESULT, &CDemoMainDlg::OnJoinConf)
    ON_MESSAGE(WM_CALL_CONF_END, &CDemoMainDlg::OnConfEnd)
    ON_MESSAGE(WM_CONF_CTRL_CONF_COMMING, &CDemoMainDlg::OnConfInComming)
    ON_MESSAGE(WM_CONF_CTRL_GET_DATA_CONF_PARAM, &CDemoMainDlg::OnGetDataConfParamResult)
    ON_MESSAGE(WM_CONF_CTRL_JOIN_DATACONF_RESULT, &CDemoMainDlg::OnJoinDataConfResult)
    ON_MESSAGE(WM_CALL_CONF_CLOSE_DLG, &CDemoMainDlg::OnCloseConfDlg)
    ON_MESSAGE(WM_DATACONF_MODULE_CLOSE, &CDemoMainDlg::OnCloseDataConfDlg)
	ON_MESSAGE(WM_CALL_TRANS_TO_CONF_RESULT, &CDemoMainDlg::OnTransToConfResult)
END_MESSAGE_MAP()


// CDemoMainDlg message handlers
BOOL CDemoMainDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_MyName.SetWindowText(g_loginAccount);
    m_MyNumber.SetWindowText(g_sipNumber);

    CString strImage = _T(".\\res\\face\\0.png");
    m_MyPhoto.SetImageFile(strImage);
    m_MyPhoto.ShowWindow(SW_SHOW);

    m_TabItem.InsertItem(0, _T("Dial"));
    m_TabItem.InsertItem(1, _T("Meeting"));
    /*m_TabItem.InsertItem(2, _T("Contacts"));
    m_TabItem.InsertItem(3, _T("Group"));
    m_TabItem.InsertItem(4, _T("History"));*/

    m_CurSelTab = 0;

    InitialSubDlgPositon();

    return TRUE;  // return TRUE unless you set the focus to a control
}


void CDemoMainDlg::OnTcnSelchangeTabFunction(NMHDR *pNMHDR, LRESULT *pResult)
{
    CRect rect;
    m_TabItem.GetClientRect(&rect);

    m_Dlg[m_CurSelTab]->ShowWindow(SW_HIDE);
    m_CurSelTab = m_TabItem.GetCurSel();
    m_Dlg[m_CurSelTab]->ShowWindow(SW_SHOW);

    *pResult = 0;
}


void CDemoMainDlg::InitialSubDlgPositon()
{
    CRect rect;
    m_TabItem.GetClientRect(&rect);
    m_DialPadDlg.Create(IDD_CALL_DIAL_PAD_DLG, &m_TabItem);
    m_MeetingDlg.Create(IDD_MEETING_DLG, &m_TabItem);
    /*m_ContactDlg.Create(IDD_IM_CONTACTS_DLG, &m_TabItem);
    m_GroupDlg.Create(IDD_IM_GROUP_DLG, &m_TabItem);
    m_HistoryDlg.Create(IDD_IM_HISTORY_DLG, &m_TabItem);*/

    m_Dlg[0] = &m_DialPadDlg;
    m_Dlg[1] = &m_MeetingDlg;
    /*m_Dlg[2] = &m_ContactDlg;
    m_Dlg[3] = &m_GroupDlg;
    m_Dlg[4] = &m_HistoryDlg;*/

    for (int i = 0; i < NUM; i++)
    {
        SetSubDlgPosion(rect, i);
    }
    m_Dlg[m_CurSelTab]->ShowWindow(SW_SHOW);
}


void CDemoMainDlg::SetSubDlgPosion(CRect rect, int index)
{
    rect.top += 20;
    m_Dlg[index]->MoveWindow(&rect);
    m_Dlg[index]->ShowWindow(SW_HIDE);
}

//void CDemoMainDlg::OnBnClickedButtonEntaddr()
//{
//    if (!::IsWindow(m_entAddrDlg.GetSafeHwnd()))
//    {
//        m_entAddrDlg.Create(CEntAddrDlg::IDD, CWnd::FromHandle(::GetDesktopWindow()));
//    }
//    else
//    {
//        m_entAddrDlg.RefreshControl();
//    }
//    m_entAddrDlg.ShowWindow(SW_SHOW);
//}

void CDemoMainDlg::OnBnClickedBtSysmenu()
{
    CRect rc;
    m_btnSysMenu.GetWindowRect(&rc);
    CMenu menu;
    menu.CreatePopupMenu();
    menu.AppendMenu(MF_STRING, ID_MAIN_SETTING_MENU, _T("Setting"));
    menu.AppendMenu(MF_STRING, ID_MAIN_LOGOUT_MENU, _T("Cancellation"));
    menu.AppendMenu(MF_STRING, ID_MAIN_EXIT_MENU, _T("Quite"));
    menu.TrackPopupMenu(TPM_BOTTOMALIGN, rc.left, rc.top, this);
}

void CDemoMainDlg::OnClickMainMenuItem(UINT nID)
{
    switch (nID)
    {
    case ID_MAIN_SETTING_MENU:
    {
        ShowSetDlg();
        break;
    }
    case ID_MAIN_LOGOUT_MENU:
    {
        Logout();
        OnOK();
        break;
    }
    case ID_MAIN_EXIT_MENU:
    {
        PostMessage(WM_CLOSE, NULL, NULL);
        break;
    }
    default:
        break;
    }
}

void CDemoMainDlg::Logout(void)
{
    int ret;
    ret = ServiceLogout();
    if (ret)
    {
        AfxMessageBox(_T("Logout failed !"));
    }
}


LRESULT CDemoMainDlg::OnForceLogout(WPARAM wParam, LPARAM lParam)
{
    Logout();
    OnOK();
    AfxMessageBox(_T(" Your account has logged in somewhere else."));
    return 0;
}

void CDemoMainDlg::ShowSetDlg()
{
    if (NULL == m_settingDlg)
    {
        m_settingDlg = new CDemoSettingDlg();
    }
    if (!::IsWindow(m_settingDlg->GetSafeHwnd()))
    {
        m_settingDlg->Create(CDemoSettingDlg::IDD, CWnd::FromHandle(::GetDesktopWindow()));
    }

    m_settingDlg->ShowWindow(SW_SHOW);
}

LRESULT CDemoMainDlg::OnStartCall(WPARAM wparam, LPARAM)
{
    TSDK_S_CALL_INFO* notifyInfo = (TSDK_S_CALL_INFO*)wparam;
    CHECK_POINTER_RETURN(notifyInfo, -1L);
    std::string sipnumber = notifyInfo->peer_number;
	m_callId = notifyInfo->call_id;
    CDemoCallCtrlDlg* pDlg;
    pDlg = CallDlgManager::GetInstance().GetCallDlgBySIPnumber(sipnumber);
    CHECK_POINTER_RETURN(pDlg, -1L);
    pDlg->SetCallID(notifyInfo->call_id);
    delete (notifyInfo);
    return 0L;
}

LRESULT CDemoMainDlg::OnCallEnd(WPARAM wParam, LPARAM lParam)
{
    TSDK_S_CALL_INFO* notifyInfo = (TSDK_S_CALL_INFO*)wParam;
    CHECK_POINTER_RETURN(notifyInfo, -1L);
    ////通知IM界面关闭呼叫/////
    CDemoCallCtrlDlg* pCallDlg;
    pCallDlg = CallDlgManager::GetInstance().GetCallDlgBySIPnumber(notifyInfo->peer_number);
    CHECK_POINTER_RETURN(pCallDlg, -1L);
    pCallDlg->PostMessage(WM_CALL_END, NULL, NULL);
    delete (notifyInfo);
    return 0L;
}

LRESULT CDemoMainDlg::OnConnected(WPARAM wParam, LPARAM)
{
    TSDK_S_CALL_INFO* notifyInfo = (TSDK_S_CALL_INFO*)wParam;
    CHECK_POINTER_RETURN(notifyInfo, -1L);
    CDemoCallCtrlDlg* pCallDlg;
    pCallDlg = CallDlgManager::GetInstance().GetCallDlgBySIPnumber(notifyInfo->peer_number);
    CHECK_POINTER_RETURN(pCallDlg, -1L);

    /////检查呼叫类型/////
    DLG_TYPE type;
    if (notifyInfo->is_video_call)
    {
        type = SIP_SIGNLE_VIDEO;
    }
    else
    {
        type = SIP_SIGNLE_CALL;
    }
    /////检查呼叫类型/////
    pCallDlg->SendMessage(WM_CALL_CONNECTED, WPARAM(type), LPARAM(notifyInfo->call_id));

    delete (notifyInfo);
    return 0L;
}

LRESULT CDemoMainDlg::OnCallIncoming(WPARAM wParam, LPARAM lParam)
{
    TSDK_S_CALL_INFO* notifyInfo = (TSDK_S_CALL_INFO*)wParam;
    CHECK_POINTER_RETURN(notifyInfo, -1L);
    unsigned int call_id = notifyInfo->call_id;
    unsigned int is_video = notifyInfo->is_video_call;
    std::string tel_number(notifyInfo->peer_number);

    CDemoCallInCommingDlg incommingdlg;
    if (is_video)
    {
        incommingdlg.GetInitParam(VIDEO_CALL, tel_number, call_id);
    }
    else
    {
        incommingdlg.GetInitParam(AUDIO_CALL, tel_number, call_id);
    }

    INT_PTR nResponse = incommingdlg.DoModal();

    if (nResponse == IDOK)
    {
        CDemoCallCtrlDlg* pCallDlg;
        pCallDlg = CallDlgManager::GetInstance().GetCallDlgByNumber(tel_number);
        CHECK_POINTER_RETURN(pCallDlg, -1L);
        if (incommingdlg.istransfe)
        {
            //// be transfered to others////
            pCallDlg->PostMessage(WM_CALL_END, NULL, NULL);
            return 0L;
        }

        pCallDlg->SetCallID(call_id);

        if (is_video && VIDEO_BUTTON == incommingdlg.m_buttonType)
        {
            pCallDlg->SetCallDlgtype(SIP_SIGNLE_VIDEO);
            pCallDlg->SendMessage(WM_CALL_ANSWER_VIDEO, NULL, NULL);
        }
        else
        {
            pCallDlg->SetCallDlgtype(SIP_SIGNLE_CALL);
            pCallDlg->PostMessage(WM_CALL_ANSWER_AUDIO, NULL, NULL);
        }
        pCallDlg->ShowWindow(SW_SHOW);
    }
    else
    {
        service_call_end(call_id);
    }
    delete (notifyInfo);
    return 0L;
}


LRESULT CDemoMainDlg::OnCallAddVideo(WPARAM wParam, LPARAM lParam)
{
    unsigned int callID = (unsigned int)wParam;
    CDemoCallCtrlDlg* pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(callID);
    CHECK_POINTER_RETURN(pCallDlg, -1L);

    CDemoPromptDlg dlg;
    dlg.SetTextOfContent(_T("The peer party request add video,do you agree?"));
    INT_PTR nResponse = dlg.DoModal();

    if (IDCANCEL == nResponse || IDOK == nResponse || IDCLOSE == nResponse)
    {
        pCallDlg->PostMessage(WM_CALL_ADD_VIDEO, (WPARAM)nResponse, NULL);
    }
    return 0L;
}

LRESULT CDemoMainDlg::OnCallOpenVideo(WPARAM wParam, LPARAM lparam)
{
    unsigned int callID = (unsigned int)wParam;
    CDemoCallCtrlDlg* pCallDlg;
    pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(callID);
    CHECK_POINTER_RETURN(pCallDlg, -1L);

    DLG_TYPE type;
    type = SIP_SIGNLE_VIDEO;

    pCallDlg->SendMessage(WM_CALL_MODIFY_VIDEO, WPARAM(type), NULL);

    return 0L;
}


LRESULT CDemoMainDlg::OnCallCloseVideo(WPARAM wParam, LPARAM lparam)
{
    unsigned int callID = (unsigned int)wParam;
    CDemoCallCtrlDlg* pCallDlg;
    pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(callID);
    CHECK_POINTER_RETURN(pCallDlg, -1L);

    DLG_TYPE type;
    type = SIP_SIGNLE_CALL;

    pCallDlg->SendMessage(WM_CALL_MODIFY_VIDEO, WPARAM(type), NULL);

    return 0L;
}

LRESULT CDemoMainDlg::OnCallRefuseOpenVideo(WPARAM wParam, LPARAM lparam)
{
    unsigned int callID = (unsigned int)wParam;
    CDemoCallCtrlDlg* pCallDlg;
    pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(callID);
    CHECK_POINTER_RETURN(pCallDlg, -1L);

    DLG_TYPE type;
    type = SIP_SIGNLE_CALL;

    pCallDlg->SendMessage(WM_CALL_MODIFY_VIDEO, WPARAM(type), NULL);

    return 0L;
}

LRESULT CDemoMainDlg::OnJoinConf(WPARAM wParam, LPARAM lparam)
{
    CHECK_POINTER_RETURN(wParam, -1L);
    TSDK_S_JOIN_CONF_IND_INFO* notify = (TSDK_S_JOIN_CONF_IND_INFO*)wParam;
    TSDK_UINT32 handle = (TSDK_UINT32)lparam;
    m_confHandle = handle;
	m_callId = notify->call_id;

    if (TSDK_E_CONF_MEDIA_VOICE == notify->conf_media_type)
    {
        if (NULL == m_audioConfDlg)
        {
            m_audioConfDlg = new CDemoAudioMeetingDlg(this);
            if (!::IsWindow(m_audioConfDlg->GetSafeHwnd()))
            {
                m_audioConfDlg->Create(IDD_AUDIO_CONF);
            }
        }
        m_audioConfDlg->SetCallID(notify->call_id);
        m_audioConfDlg->SetConfHandle(m_confHandle);
        m_audioConfDlg->ShowWindow(SW_NORMAL);
    }
    else if (TSDK_E_CONF_MEDIA_VIDEO == notify->conf_media_type)
    {
        if (NULL == m_videoConfDlg)
        {
            m_videoConfDlg = new CDemoVideoMeetingDlg(this);
            if (!::IsWindow(m_videoConfDlg->GetSafeHwnd()))
            {
                m_videoConfDlg->Create(IDD_VIDEO_CONF);
            }
        }
        m_videoConfDlg->SetCallID(notify->call_id);
        m_videoConfDlg->SetConfHandle(m_confHandle);
        m_videoConfDlg->ShowWindow(SW_NORMAL);
        m_videoConfDlg->BindVideoWindow();
    }

    CDemoCallCtrlDlg* pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(notify->call_id);
    if (NULL != pCallDlg)
    {
        pCallDlg->OnClose();
    }

    return 0L;
}

LRESULT CDemoMainDlg::OnConfEnd(WPARAM, LPARAM)
{
    if (m_audioConfDlg)
    {
        m_audioConfDlg->DestroyWindow();
        delete (m_audioConfDlg);
        m_audioConfDlg = NULL;
    }

    if (m_videoConfDlg)
    {
        m_videoConfDlg->DestroyWindow();
        delete (m_videoConfDlg);
        m_videoConfDlg = NULL;
    }
    m_confHandle = 0;
    return 0L;
}

LRESULT CDemoMainDlg::OnConfInComming(WPARAM wparam, LPARAM lparam)
{
    TSDK_S_CONF_INCOMING_INFO* notifyInfo = (TSDK_S_CONF_INCOMING_INFO*)wparam;
    CHECK_POINTER_RETURN(notifyInfo, 0L);
    unsigned int handle = (unsigned int)lparam;
    std::string strchairman = notifyInfo->number;
    unsigned int conf_id = (unsigned int)CTools::str2num(notifyInfo->conf_id);
    SetConfChairman(false);

    CDemoCallInCommingDlg incommingDlg;

    if (TSDK_E_CONF_MEDIA_VIDEO == notifyInfo->conf_media_type || TSDK_E_CONF_MEDIA_VIDEO_DATA == notifyInfo->conf_media_type)
    {
        incommingDlg.GetInitParam(VIDEO_CONF_CALL, strchairman, conf_id);
    }
    else
    {
        incommingDlg.GetInitParam(AUDIO_CONF_CALL, strchairman, conf_id);
    }

    INT_PTR nResponse = incommingDlg.DoModal();
    if (IDOK == nResponse)
    {
        if (TSDK_E_CONF_MEDIA_VIDEO == notifyInfo->conf_media_type || TSDK_E_CONF_MEDIA_VIDEO_DATA == notifyInfo->conf_media_type)
        {
            (void)service_conf_mem_accept(handle, TRUE);
        }
        else
        {
            (void)service_conf_mem_accept(handle, FALSE);
        }
    }
    else
    {
        (void)service_conf_mem_reject(handle);
    }
    m_confHandle = handle;
    delete (notifyInfo);
    return 0L;
}

LRESULT CDemoMainDlg::OnGetDataConfParamResult(WPARAM wparam, LPARAM lparam)
{
    unsigned int handle = (unsigned int)wparam;
    (void)service_data_conf_join(handle);
    return 0L;
}

LRESULT CDemoMainDlg::OnJoinDataConfResult(WPARAM wparam, LPARAM lparam)
{
    TSDK_RESULT result = (TSDK_RESULT)lparam;

    if (TSDK_SUCCESS == result)
    {
        if (NULL == m_dataConfDlg)
        {
            m_dataConfDlg = new CDemoDataMeetingDlg(this);
            if (!::IsWindow(m_dataConfDlg->GetSafeHwnd()))
            {
                m_dataConfDlg->Create(IDD_DATA_CONF_CTRL);
            }
        }

		m_dataConfDlg->SetCallID(m_callId);
        m_dataConfDlg->SetConfHandle(m_confHandle);
        m_dataConfDlg->ShowWindow(SW_NORMAL);
		m_dataConfDlg->BindVideoWindow();

        //设置会议handle
        set_data_conf_handle(m_confHandle);

        //////关闭音视频会议的界面
        ::PostMessage(GetSafeHwnd(), WM_CALL_CONF_CLOSE_DLG, NULL, NULL);
    }
    else
    {
        MessageBox(_T("Join Data Conf failed!"));
        //释放数据会议的句柄
    }

    return 0L;
}

LRESULT CDemoMainDlg::OnTransToConfResult(WPARAM wparam, LPARAM lparam)
{
	TSDK_RESULT result = (TSDK_RESULT)lparam;

	if (TSDK_SUCCESS != result)
	{
		MessageBox(_T("Transfer To Conf failed!"));

		CDemoCallCtrlDlg* pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(m_callId);
		if (NULL != pCallDlg)
		{
			CString csHold;
			pCallDlg->m_bt_hold.GetWindowText(csHold);
			if (_T("unHold") == csHold)
			{
				(void)service_call_unhold(m_callId);
				pCallDlg->m_bt_hold.SetWindowText(_T("Hold"));
			}
		}
	}

	return -1L;
}

LRESULT CDemoMainDlg::OnCloseConfDlg(WPARAM, LPARAM)
{
    if (m_audioConfDlg)
    {
        m_audioConfDlg->CloseDlg();
        delete (m_audioConfDlg);
        m_audioConfDlg = NULL;
    }

    if (m_videoConfDlg)
    {
        m_videoConfDlg->CloseDlg();
        delete (m_videoConfDlg);
        m_videoConfDlg = NULL;
    }
	m_callId = 0;
    return 0L;
}

LRESULT CDemoMainDlg::OnCloseDataConfDlg(WPARAM, LPARAM)
{
    if (m_dataConfDlg)
    {
        delete (m_dataConfDlg);
        m_dataConfDlg = NULL;
    }
	m_callId = 0;
    SetConfChairman(false);
    return 0L;
}
