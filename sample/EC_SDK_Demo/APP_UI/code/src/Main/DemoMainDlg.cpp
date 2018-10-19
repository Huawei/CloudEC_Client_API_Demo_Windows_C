//
//  DemoMainDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoMainDlg.h"
#include "DemoShare.h"
#include "DemoCallCtrlDlg.h"
#include "DemoCallDlgManager.h"
#include "DemoPromptDlg.h"
#include "service_conf_handle_global.h"
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
    , m_videoDlg(NULL)
    , m_callDlg(NULL)
    , m_dataconfCtrlDlg(NULL)
	, m_dtmfDlg(NULL)
    , m_incommingdlg(NULL)
    , m_confHandle(0)
	, m_callId(0)
    , m_isConfChairman(false)
    , m_isConfPresenter(false)
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
    SAFE_DELETE(m_audioConfDlg);
    SAFE_DELETE(m_videoDlg);
    SAFE_DELETE(m_callDlg)
    SAFE_DELETE(m_dataconfCtrlDlg);
	SAFE_DELETE(m_dtmfDlg);
    SAFE_DELETE(m_incommingdlg);
    m_audioConfDlg = NULL;
    m_videoDlg = NULL;
    m_callDlg = NULL;
    m_dataconfCtrlDlg = NULL;
	m_dtmfDlg = NULL;
    m_incommingdlg = NULL;
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
    ON_BN_CLICKED(IDC_BUTTON_SYSMENU, &CDemoMainDlg::OnBnClickedBtSysmenu)
    ON_COMMAND_RANGE(ID_MAIN_SETTING_MENU, ID_MAIN_EXIT_MENU, &CDemoMainDlg::OnClickMainMenuItem)
    ON_MESSAGE(WM_LOGOUT_RESULT, &CDemoMainDlg::OnLogout)
    ON_MESSAGE(WM_FORCE_LOGOUT, &CDemoMainDlg::OnForceLogout)
    ON_MESSAGE(WM_CALL_STARTCALL, &CDemoMainDlg::OnStartCall)
    ON_MESSAGE(WM_CALL_END, &CDemoMainDlg::OnCallEnd)
    ON_MESSAGE(WM_CALL_INCOMMING, &CDemoMainDlg::OnCallIncoming)
    ON_MESSAGE(WM_CALL_ADD_VIDEO, &CDemoMainDlg::OnCallAddVideo)
    ON_MESSAGE(WM_CALL_OPEN_VIDEO, &CDemoMainDlg::OnCallOpenVideo)
    ON_MESSAGE(WM_CALL_CLOSE_VIDEO, &CDemoMainDlg::OnCallCloseVideo)
    ON_MESSAGE(WM_CALL_REFUSE_OPEN_VIDEO, &CDemoMainDlg::OnCallRefuseOpenVideo)
    ON_MESSAGE(WM_CONF_CTRL_JOIN_RESULT, &CDemoMainDlg::OnJoinConf)
    ON_MESSAGE(WM_CONF_CTRL_CONF_COMMING, &CDemoMainDlg::OnConfInComming)
    ON_MESSAGE(WM_CONF_CTRL_GET_DATA_CONF_PARAM, &CDemoMainDlg::OnGetDataConfParamResult)
    ON_MESSAGE(WM_CONF_CTRL_JOIN_DATACONF_RESULT, &CDemoMainDlg::OnJoinDataConfResult)
    ON_MESSAGE(WM_CALL_CONF_CLOSE_DLG, &CDemoMainDlg::OnCloseConfDlg)
    ON_MESSAGE(WM_CALL_INCOMMING_DLG_CLOSE, &CDemoMainDlg::OnCloseIncommingDlg)
	ON_MESSAGE(WM_CALL_TRANS_TO_CONF_RESULT, &CDemoMainDlg::OnTransToConfResult)
    ON_MESSAGE(WM_DATACONF_MODULE_PRESENTERCHG, &CDemoMainDlg::OnConfPresenterChange)
	ON_MESSAGE(WM_CALL_DTMF, &CDemoMainDlg::OnOpenDtmfDlg)
    ON_MESSAGE(WM_CALL_VIDEO_CREATE, &CDemoMainDlg::OnCreateVideoDlg)
    ON_MESSAGE(WM_CALL_VIDEO_CLOSE, &CDemoMainDlg::OnCloseVideoDlg)
    ON_MESSAGE(WM_CALL_DLG_CREATE, &CDemoMainDlg::OnCreateCallDlg)
    ON_MESSAGE(WM_CALL_DLG_CLOSE, &CDemoMainDlg::OnCloseCallDlg)
    ON_MESSAGE(WM_CALL_CONF_REFRESH, &CDemoMainDlg::OnRefreshConf)
    ON_MESSAGE(WM_CLOSE, &CDemoMainDlg::OnClose)
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
    (void)m_DialPadDlg.Create(IDD_CALL_DIAL_PAD_DLG, &m_TabItem);
    (void)m_MeetingDlg.Create(IDD_CONF_DLG, &m_TabItem);
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
LRESULT CDemoMainDlg::OnLogout(WPARAM wParam, LPARAM lParam)
{
    OnOK();
    return 0L;
}

LRESULT CDemoMainDlg::OnForceLogout(WPARAM wParam, LPARAM lParam)
{
    Logout();
    OnOK();
    AfxMessageBox(_T(" Your account has logged in somewhere else."));
    return 0L;
}

void CDemoMainDlg::ShowSetDlg()
{
    if (NULL == m_settingDlg)
    {
        m_settingDlg = new CDemoSettingDlg();
    }
    if (!::IsWindow(m_settingDlg->GetSafeHwnd()))
    {
        (void)m_settingDlg->Create(CDemoSettingDlg::IDD, CWnd::FromHandle(::GetDesktopWindow()));
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

    ////通知来电界面关闭/////
    if (NULL != m_incommingdlg)
    {
        service_call_media_stopplay(m_incommingdlg->GetPlayHandle());
        m_incommingdlg->OnCloseDlg();
    }

    ////通知呼叫界面关闭/////
    CDemoCallCtrlDlg* pCallDlg;
    pCallDlg = CallDlgManager::GetInstance().GetCallDlgBySIPnumber(notifyInfo->peer_number);
    CHECK_POINTER_RETURN(pCallDlg, -1L);
    pCallDlg->PostMessage(WM_CALL_END, NULL, NULL);

    delete (notifyInfo);
    return 0L;
}

LRESULT CDemoMainDlg::OnCallIncoming(WPARAM wParam, LPARAM lParam)
{
    TSDK_S_CALL_INFO* notifyInfo = (TSDK_S_CALL_INFO*)wParam;
    CHECK_POINTER_RETURN(notifyInfo, -1L);
    m_callId = notifyInfo->call_id;
    unsigned int is_video = notifyInfo->is_video_call;
    std::string tel_number(notifyInfo->peer_number);

    if (NULL == m_incommingdlg)
    {
        m_incommingdlg = new CDemoCallInCommingDlg(this);
    }
    if (!::IsWindow(m_incommingdlg->GetSafeHwnd()))
    {
        m_incommingdlg->SetCallID(m_callId);
        /*m_incommingdlg->DoModal();*/
    }

    if (is_video)
    {
        m_incommingdlg->GetInitParam(VIDEO_CALL, tel_number, m_callId);
    }
    else
    {
        m_incommingdlg->GetInitParam(AUDIO_CALL, tel_number, m_callId);
    }

    INT_PTR nResponse = m_incommingdlg->DoModal();

    if (nResponse == IDOK)
    {
        CDemoCallCtrlDlg* pCallDlg;
        pCallDlg = CallDlgManager::GetInstance().GetCallDlgByNumber(tel_number);
        CHECK_POINTER_RETURN(pCallDlg, -1L);
        if (m_incommingdlg->istransfe)
        {
            //// be transfered to others////
            pCallDlg->PostMessage(WM_CALL_END, NULL, NULL);
            return 0L;
        }

        pCallDlg->SetCallID(m_callId);

        if (is_video && VIDEO_BUTTON == m_incommingdlg->m_buttonType)
        {
            pCallDlg->SetCallDlgtype(VIDEO_DLG);
            pCallDlg->SendMessage(WM_CALL_ANSWER_VIDEO, NULL, NULL);
        }
        else
        {
            pCallDlg->SetCallDlgtype(AUDIO_DLG);
            pCallDlg->PostMessage(WM_CALL_ANSWER_AUDIO, NULL, NULL);
        }
        pCallDlg->ShowWindow(SW_SHOW);
    }
    else
    {
        service_call_end(m_callId);
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

    if (IDOK == nResponse)
    {
        //创建视频窗口
        ::PostMessage(GetSafeHwnd(), WM_CALL_VIDEO_CREATE, (WPARAM)callID, NULL);
        service_call_reply_add_video(m_callId, TRUE);
        CALL_DLG_TYPE type = VIDEO_DLG;
        pCallDlg->ChangeDlgType(type);
        pCallDlg->m_bt_addVideo.SetWindowText(_T("Add audio"));
    }
    if (IDCANCEL == nResponse || IDCLOSE == nResponse)
    {
        service_call_reply_add_video(m_callId, FALSE);
        CALL_DLG_TYPE type = AUDIO_DLG;
        pCallDlg->ChangeDlgType(type);
        pCallDlg->m_bt_addVideo.SetWindowText(_T("Add video"));
    }
    return 0L;
}

LRESULT CDemoMainDlg::OnCallOpenVideo(WPARAM wParam, LPARAM lparam)
{
    unsigned int callID = (unsigned int)wParam;
    CDemoCallCtrlDlg* pCallDlg;
    pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(callID);
    CHECK_POINTER_RETURN(pCallDlg, -1L);

    CALL_DLG_TYPE type;
    type = VIDEO_DLG;

    pCallDlg->SendMessage(WM_CALL_MODIFY_VIDEO, WPARAM(type), NULL);

    return 0L;
}


LRESULT CDemoMainDlg::OnCallCloseVideo(WPARAM wParam, LPARAM lparam)
{
    unsigned int callID = (unsigned int)wParam;
    CDemoCallCtrlDlg* pCallDlg;
    pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(callID);
    CHECK_POINTER_RETURN(pCallDlg, -1L);

    CALL_DLG_TYPE type;
    type = AUDIO_DLG;

    pCallDlg->SendMessage(WM_CALL_MODIFY_VIDEO, WPARAM(type), NULL);

    return 0L;
}

LRESULT CDemoMainDlg::OnCallRefuseOpenVideo(WPARAM wParam, LPARAM lparam)
{
    unsigned int callID = (unsigned int)wParam;
    CDemoCallCtrlDlg* pCallDlg;
    pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(callID);
    CHECK_POINTER_RETURN(pCallDlg, -1L);

    CALL_DLG_TYPE type;
    type = AUDIO_DLG;

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

	if (NULL != m_dtmfDlg)
	{
		m_dtmfDlg->OnCloseDlg();
	}

	if (NULL == m_audioConfDlg)
	{
		m_audioConfDlg = new CDemoAudioMeetingDlg(this);
		if (!::IsWindow(m_audioConfDlg->GetSafeHwnd()))
		{
            (void)m_audioConfDlg->Create(IDD_AUDIO_CONF);
		}
	}
	m_audioConfDlg->SetCallID(notify->call_id);
	m_audioConfDlg->SetConfHandle(m_confHandle);
	m_audioConfDlg->ShowWindow(SW_NORMAL);

	if (TSDK_E_CONF_MEDIA_VOICE == notify->conf_media_type)
	{
		m_audioConfDlg->m_confType = AUDIO_CONF;
	}
	else if (TSDK_E_CONF_MEDIA_VOICE_DATA == notify->conf_media_type)
	{
		m_audioConfDlg->m_confType = AUDIO_DATA_CONF;
	}
	else if (TSDK_E_CONF_MEDIA_VIDEO == notify->conf_media_type)
	{
		m_audioConfDlg->m_confType = VIDEO_CONF;
	}
	else if (TSDK_E_CONF_MEDIA_VIDEO_DATA == notify->conf_media_type)
	{
		m_audioConfDlg->m_confType = VIDEO_DATA_CONF;
	}

    if (TSDK_E_CONF_MEDIA_VIDEO == notify->conf_media_type || TSDK_E_CONF_MEDIA_VIDEO_DATA == notify->conf_media_type)
    {
        ::PostMessage(GetSafeHwnd(), WM_CALL_VIDEO_CREATE, (WPARAM)m_callId, NULL);
    }

	CDemoCallCtrlDlg* pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(notify->call_id);
	if (NULL != pCallDlg)
	{
        pCallDlg->PostMessage(WM_CLOSE, NULL, NULL);
	}

	return 0L;
}

LRESULT CDemoMainDlg::OnConfInComming(WPARAM wparam, LPARAM lparam)
{
    TSDK_S_CONF_INCOMING_INFO* notifyInfo = (TSDK_S_CONF_INCOMING_INFO*)wparam;
    CHECK_POINTER_RETURN(notifyInfo, 0L);
    unsigned int handle = (unsigned int)lparam;
    std::string strchairman = notifyInfo->number;
    unsigned int conf_id = (unsigned int)CTools::str2num(notifyInfo->conf_id);
    /*SetConfChairman(false);*/

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
        if (VIDEO_BUTTON == incommingDlg.m_buttonType)
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
	unsigned int dataConfHandle = (unsigned int)wparam;
    TSDK_RESULT result = (TSDK_RESULT)lparam;

    if (TSDK_SUCCESS == result)
    {
        //设置会议handle
        m_confHandle = dataConfHandle;
        set_data_conf_handle(m_confHandle);

        if (NULL == m_dataconfCtrlDlg)
        {
            m_dataconfCtrlDlg = new CDemoDataconfCtrlDlg(this);
            if (!::IsWindow(m_dataconfCtrlDlg->GetSafeHwnd()))
            {
                (void)m_dataconfCtrlDlg->Create(IDD_DATA_CONF_CTRL);
            }

            m_dataconfCtrlDlg->ShowWindow(SW_NORMAL);
        }
       
        if (NULL != m_audioConfDlg)
        {
            if (NULL != m_dataconfCtrlDlg)
            {
                m_dataconfCtrlDlg->SetChairman(m_audioConfDlg->ischairman);
                m_dataconfCtrlDlg->SetPresent(m_audioConfDlg->ispresenter);
                m_dataconfCtrlDlg->updateShareDlg();
            }

            //pbx组网下，主席拉起会议
            if (m_audioConfDlg->m_confType == AUDIO_CONF)
            {
                m_audioConfDlg->m_confType = AUDIO_DATA_CONF;
            }
        }
    }
    else
    {
        //释放数据会议的句柄
        MessageBox(_T("Join Data Conf failed!"));
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

LRESULT CDemoMainDlg::OnConfPresenterChange(WPARAM wparam, LPARAM lparam)
{
    if (NULL != m_dataconfCtrlDlg)
    {
        m_dataconfCtrlDlg->updateShareDlg();
    }
    MessageBox(_T("You are presenter!"));
    return 0L;
}

LRESULT CDemoMainDlg::OnOpenDtmfDlg(WPARAM wparam, LPARAM lparam)
{
	if (NULL == m_dtmfDlg)
	{
		m_dtmfDlg = new CDemoCallDtmfDlg(this);
	}

	if (!::IsWindow(m_dtmfDlg->GetSafeHwnd()))
	{
		m_dtmfDlg->SetCallid(m_callId);
        /*(void)m_dtmfDlg->DoModal();*/
        if (!::IsWindow(m_dtmfDlg->GetSafeHwnd()))
        {
            (void)m_dtmfDlg->Create(IDD_CALL_DTMF_DLG);
        }
    }
    m_dtmfDlg->ShowWindow(SW_NORMAL);

	return 0L;
}

LRESULT CDemoMainDlg::OnCreateVideoDlg(WPARAM wparam, LPARAM lparam)
{
    m_callId = unsigned int(wparam);
    if (NULL == m_videoDlg)
    {
        m_videoDlg = new CDemoVideoDlg(this);
        if (!::IsWindow(m_videoDlg->GetSafeHwnd()))
        {
            (void)m_videoDlg->Create(IDD_VIDEO_DLG);
        }
    }
    m_videoDlg->SetCallID(m_callId);
    m_videoDlg->BindVideoWindow();
    m_videoDlg->ShowWindow(SW_NORMAL);

    return 0L;
}

LRESULT CDemoMainDlg::OnCreateCallDlg(WPARAM wparam, LPARAM lparam)
{
    m_callId = unsigned int(wparam);
    if (NULL == m_callDlg)
    {
        m_callDlg = new CDemoCallCtrlDlg(this);
        if (!::IsWindow(m_callDlg->GetSafeHwnd()))
        {
            (void)m_callDlg->Create(IDD_CALL_CTRL_DLG);
        }
    }
    m_callDlg->SetCallID(m_callId);
    m_callDlg->ShowWindow(SW_NORMAL);

    return 0L;
}

LRESULT CDemoMainDlg::OnCloseVideoDlg(WPARAM wparam, LPARAM lparam)
{
    if (NULL != m_videoDlg && ::IsWindow(m_videoDlg->GetSafeHwnd()))
    {
        (void)m_videoDlg->ShowWindow(SW_HIDE);
        (void)m_videoDlg->DestroyWindow();
        delete m_videoDlg;
        m_videoDlg = NULL;
    }
    return 0L;
}

LRESULT CDemoMainDlg::OnCloseCallDlg(WPARAM wparam, LPARAM lparam)
{
    if (NULL != m_callDlg && ::IsWindow(m_callDlg->GetSafeHwnd()))
    {
        (void)m_callDlg->ShowWindow(SW_HIDE);
        (void)m_callDlg->DestroyWindow();
        delete m_callDlg;
        m_callDlg = NULL;
    }
    return 0L;
}

LRESULT CDemoMainDlg::OnRefreshConf(WPARAM wparam, LPARAM lparam)
{
    if (NULL != m_audioConfDlg)
    {
        if (NULL != m_dataconfCtrlDlg)
        {
            m_dataconfCtrlDlg->SetChairman(m_audioConfDlg->ischairman);
            m_dataconfCtrlDlg->SetPresent(m_audioConfDlg->ispresenter);
            m_dataconfCtrlDlg->updateShareDlg();
        }
    }
    else
    {
        return -1L;
    }

    return 0L;
}

LRESULT CDemoMainDlg::OnCloseConfDlg(WPARAM, LPARAM)
{
    if (NULL != m_dataconfCtrlDlg && ::IsWindow(m_dataconfCtrlDlg->GetSafeHwnd()))
    {
        m_dataconfCtrlDlg->SetCallID(0);
        (void)m_dataconfCtrlDlg->ShowWindow(SW_HIDE);
        (void)m_dataconfCtrlDlg->DestroyWindow();
        delete m_dataconfCtrlDlg;
        m_dataconfCtrlDlg = NULL;
    }

    if (NULL != m_videoDlg && ::IsWindow(m_videoDlg->GetSafeHwnd()))
    {
        m_videoDlg->m_callID = 0;
        (void)m_videoDlg->ShowWindow(SW_HIDE);
        (void)m_videoDlg->DestroyWindow();
        delete m_videoDlg;
        m_videoDlg = NULL;
    }

    if (NULL != m_audioConfDlg && ::IsWindow(m_audioConfDlg->GetSafeHwnd()))
    {
        m_audioConfDlg->CloseDlg();
        (void)m_audioConfDlg->ShowWindow(SW_HIDE);
        (void)m_audioConfDlg->DestroyWindow();
        delete m_audioConfDlg;
        m_audioConfDlg = NULL;
    }

    if (NULL != m_dtmfDlg && ::IsWindow(m_dtmfDlg->GetSafeHwnd()))
    {
        m_dtmfDlg->SetCallid(0);
        (void)m_dtmfDlg->ShowWindow(SW_HIDE);
        (void)m_dtmfDlg->DestroyWindow();
        delete m_dtmfDlg;
        m_dtmfDlg = NULL;
    }

    m_callId = 0;
    m_confHandle = 0;
    return 0L;
}

LRESULT CDemoMainDlg::OnCloseIncommingDlg(WPARAM wParam, LPARAM lParam)
{
    if (NULL != m_incommingdlg && ::IsWindow(m_incommingdlg->GetSafeHwnd()))
    {
        m_incommingdlg->SetCallID(0);
        (void)m_incommingdlg->ShowWindow(SW_HIDE);
        (void)m_incommingdlg->DestroyWindow();
        delete m_incommingdlg;
        m_incommingdlg = NULL;
    }
    return 0L;
}

LRESULT CDemoMainDlg::OnClose(WPARAM wParam, LPARAM lParam)
{
    (void)OnCloseConfDlg(NULL,NULL);
    (void)OnCloseIncommingDlg(NULL, NULL);
    (void)OnCloseCallDlg(NULL, NULL);
    Logout();
    CDialogEx::OnClose();
    return 0L;
}
