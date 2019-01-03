//
//  DemoAudioMeetingDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoApp.h"
#include "DemoAudioMeetingDlg.h"
#include "DemoMainDlg.h"
#include "afxdialogex.h"
#include "DemoCommonTools.h"
#include "DemoMeetingAddMemDlg.h"
#include "DemoCallDtmfDlg.h"
#include "service_call_interface.h"
#include "service_conf_interface.h"
#include "service_tools.h"
#include "service_os_adapt.h"
#include <string>
#include <vector>

extern CString g_sipNumber;
extern CString g_shortNumber;

#define  DLG_CONF_WIDE            570
#define  DLG_CONF_AUDIO_HEI        320
#define  DLG_CONF_VIDEO_HEI        480

// CDemoAudioMeetingDlg dialog
IMPLEMENT_DYNAMIC(CDemoAudioMeetingDlg, CDialogEx)

CDemoAudioMeetingDlg::CDemoAudioMeetingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoAudioMeetingDlg::IDD, pParent)
    , ischairman(false)
    , ispresenter(false)
    , m_confID(0)
    , m_callID(0)
    , m_handle(0)
    , m_confType(AUDIO_CONF)
{

}

CDemoAudioMeetingDlg::~CDemoAudioMeetingDlg()
{
}

void CDemoAudioMeetingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MEMBER_LIST, m_listMember);
    DDX_Control(pDX, IDC_BT_MUTE, m_bt_Mute);
    DDX_Control(pDX, IDC_BT_LOCK, m_bt_Lock);
    DDX_Control(pDX, IDC_BT_DATACONF, m_bt_DataConf);
    DDX_Control(pDX, IDC_BT_HAND_UP, m_bt_Handup);
    DDX_Control(pDX, IDC_BT_APPLY_FOR_CHAIRMAN, m_bt_Apply);
    DDX_Control(pDX, IDC_BT_RELEASE_CHAIRMAN, m_bt_Release);
    DDX_Control(pDX, IDC_BT_ADD_MEMBER, m_bt_Add);
    DDX_Control(pDX, IDC_BT_CONF_DTMF, m_bt_Dtmf);
    DDX_Control(pDX, IDC_BT_END_CONF,m_bt_End_Conf);
    DDX_Control(pDX, IDC_BT_LEAVE_CONF, m_bt_Leave_Conf);
    DDX_Control(pDX, IDC_STATIC_SUBJECT, m_static_subject);
    DDX_Control(pDX, IDC_COM_CONF_MODE, m_cbxVideoConfMode);
    DDX_Control(pDX, IDC_EDIT_CHAIRMAN_PWD,m_edit_chairman_pwd);
}


BEGIN_MESSAGE_MAP(CDemoAudioMeetingDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BT_ADD_MEMBER, &CDemoAudioMeetingDlg::OnBnClickedBtAddMember)
    ON_BN_CLICKED(IDC_BT_MUTE, &CDemoAudioMeetingDlg::OnBnClickedBtMute)
    ON_BN_CLICKED(IDC_BT_LOCK, &CDemoAudioMeetingDlg::OnBnClickedBtLock)
    ON_BN_CLICKED(IDC_BT_APPLY_FOR_CHAIRMAN, &CDemoAudioMeetingDlg::OnBnClickedBtApplyChairman)
    ON_BN_CLICKED(IDC_BT_RELEASE_CHAIRMAN, &CDemoAudioMeetingDlg::OnBnClickedBtReleaseChairman)
    ON_BN_CLICKED(IDC_BT_HAND_UP, &CDemoAudioMeetingDlg::OnBnClickedBtHandUp)
    ON_BN_CLICKED(IDC_BT_DATACONF, &CDemoAudioMeetingDlg::OnBnClickedBtDataconf)
    ON_BN_CLICKED(IDC_BT_CONF_DTMF, &CDemoAudioMeetingDlg::OnBnClickedBtDtmf)
    ON_BN_CLICKED(IDC_BT_END_CONF, &CDemoAudioMeetingDlg::OnBnClickedBtEndConf)
    ON_BN_CLICKED(IDC_BT_LEAVE_CONF, &CDemoAudioMeetingDlg::OnBnClickedBtLeaveConf)
    ON_CBN_SELCHANGE(IDC_COM_CONF_MODE, &CDemoAudioMeetingDlg::OnCbnSelchangeComboSetConfMode)
    ON_NOTIFY(NM_RCLICK, IDC_MEMBER_LIST, &CDemoAudioMeetingDlg::OnNMRClickMemberList)
    ON_COMMAND_RANGE(ID_CONF_DEL_MEM_MENU, ID_DCONF_APPLY_AS_PRESENT_MENU, &CDemoAudioMeetingDlg::OnClickListMemMenuItem)
    ON_MESSAGE(WM_CONF_CTRL_INFO_AND_STATUS_UPDATE, &CDemoAudioMeetingDlg::OnConfInfoAndStatusUpdate)
    ON_MESSAGE(WM_CONF_CTRL_ADDRESSER_UPDATE_IND, &CDemoAudioMeetingDlg::OnConfSpeakerUpdate)
    ON_MESSAGE(WM_CONF_CTRL_OPERATION_RESULT,&CDemoAudioMeetingDlg::OnConfOperationResult)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDemoAudioMeetingDlg handle function
BOOL CDemoAudioMeetingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //初始化combox控件
    m_cbxVideoConfMode.InsertString(0, _T("Broadcast"));
    m_cbxVideoConfMode.InsertString(1, _T("Vas"));
    m_cbxVideoConfMode.InsertString(2, _T("Free"));

    //初始化与会者列表
    m_listMember.ModifyStyle(0, LVS_SINGLESEL);
    m_listMember.InsertColumn(COL_MEM_COMPERE, _T("Chirman"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_PRESENT, _T("Present"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_NAME, _T("Name"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_ACCOUNT, _T("Account"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_CALLNO, _T("Number"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_CALLSTATE, _T("CallStatus"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_SPK, _T("Speaker"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_MUTE, _T("Mute"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_HANDUP, _T("HandUp"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_BROADCAST, _T("Broadcast"), LVCFMT_JUSTIFYMASK, 78);
    DWORD dwStyle = m_listMember.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;    //选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;        //网格线（只适用与report风格的listctrl）
    m_listMember.SetExtendedStyle(dwStyle); //设置扩展风格
    return TRUE;  // return TRUE unless you set the focus to a control
}

void CDemoAudioMeetingDlg::OnBnClickedBtAddMember()
{
    CDemoMeetingAddMemDlg dlg;
    INT_PTR nResponse = dlg.DoModal();

    //new attendee insert to list
    if (IDOK != nResponse)
    {
        return;
    }

    //use the service interface of add member
    TSDK_S_ADD_ATTENDEES_INFO addAttendeeInfo = { 0 };
    addAttendeeInfo.attendee_num = 1;
    TSDK_UINT32 count = addAttendeeInfo.attendee_num;
    addAttendeeInfo.attendee_list = (TSDK_S_ATTENDEE_BASE_INFO*)malloc(count*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
    if (NULL == addAttendeeInfo.attendee_list)
    {
        AfxMessageBox(_T("addAttendeeInfo.attendee_list is NULL"));
        return;
    }
    (void)service_memset_s(addAttendeeInfo.attendee_list, count*sizeof(TSDK_S_ATTENDEE_BASE_INFO), 0, count*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
    TSDK_S_ATTENDEE_BASE_INFO* pTempAttendee = addAttendeeInfo.attendee_list;
    for (unsigned int i = 0; i < count; i++)
    {
        if (pTempAttendee)
        {
            (void)strncpy_s(pTempAttendee->number, TSDK_D_MAX_PARTICIPANTID_LEN + 1, CTools::UNICODE2UTF(dlg.addMemSipNum).c_str(), TSDK_D_MAX_PARTICIPANTID_LEN - 1);
            pTempAttendee->role = TSDK_E_CONF_ROLE_ATTENDEE;
        }
        else
        {
            break;
        }

        pTempAttendee++;
    }
    (void)service_conf_add_attendee(m_handle, &addAttendeeInfo);
    free(addAttendeeInfo.attendee_list);
    addAttendeeInfo.attendee_list = NULL;
}

void CDemoAudioMeetingDlg::OnBnClickedBtMute()
{
    CString cstrtxt;
    m_bt_Mute.GetWindowText(cstrtxt);
    if (_T("Mute Conf") == cstrtxt)
    {
        //// mute conf
        service_conf_mute(m_handle, 1);
    }
    else
    {
        /////unmute conf
        service_conf_mute(m_handle, 0);
    }
}

void CDemoAudioMeetingDlg::OnBnClickedBtLock()
{
    CString cstrtxt;
    m_bt_Lock.GetWindowText(cstrtxt);
    if (_T("Lock Conf") == cstrtxt)
    {
        ////Lock conf
        service_conf_lock(m_handle, 1);
    }
    else
    {
        ////Unlock conf
        service_conf_lock(m_handle, 0);
    }
}

void CDemoAudioMeetingDlg::OnBnClickedBtHandUp()
{
    /*CString attendeeNum = CTools::GetSipNumber(g_sipNumber);*/
    std::string strAttendeeNum = CTools::UNICODE2UTF(g_sipNumber);

    CString cstrtxt;
    m_bt_Handup.GetWindowText(cstrtxt);
    if (_T("Hand Up") == cstrtxt)
    {
        (void)service_conf_handup(m_handle, TRUE, const_cast<char*>(strAttendeeNum.c_str()));
    }
    else
    {
        (void)service_conf_handup(m_handle, FALSE, const_cast<char*>(strAttendeeNum.c_str()));
    }
}

void CDemoAudioMeetingDlg::OnBnClickedBtDataconf()
{
    (void)service_conf_upgrade_conf(m_handle);
}

void CDemoAudioMeetingDlg::OnBnClickedBtApplyChairman()
{
    CString cstrPwd;
    m_edit_chairman_pwd.GetWindowText(cstrPwd);
    (void)service_conf_request_chairman(m_handle, const_cast<char*>(CTools::UNICODE2UTF(cstrPwd).c_str()));
}

void CDemoAudioMeetingDlg::OnBnClickedBtReleaseChairman()
{
    (void)service_conf_release_chairman(m_handle);
}

void CDemoAudioMeetingDlg::OnBnClickedBtDtmf()
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

void CDemoAudioMeetingDlg::OnBnClickedBtEndConf()
{
    (void)service_conf_end(m_handle);

    /*End Call*/
    if (m_callID != 0)
    {
        service_call_end(m_callID);
        m_callID = 0;
    }

    m_handle = 0;

    /////close confDlg/////
    ::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(), WM_CALL_CONF_CLOSE_DLG, NULL, NULL);
    CDialogEx::OnClose();
}

void CDemoAudioMeetingDlg::OnBnClickedBtLeaveConf()
{
    (void)service_conf_leave(m_handle);

    /*End Call*/
    if (m_callID != 0)
    {
        service_call_end(m_callID);
        m_callID = 0;
    }

    m_handle = 0;

    /////close confDlg/////
    ::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(), WM_CALL_CONF_CLOSE_DLG, NULL, NULL);
    CDialogEx::OnClose();
}

void CDemoAudioMeetingDlg::OnCbnSelchangeComboSetConfMode()
{
    CString strVideoModeType;
    m_cbxVideoConfMode.GetLBText(m_cbxVideoConfMode.GetCurSel(),strVideoModeType);
    m_cbxVideoConfMode.SetWindowText(strVideoModeType);

    if (_T("Broadcast") == strVideoModeType)
    {
        (void)service_conf_set_video_mode(m_handle, TSDK_E_CONF_VIDEO_BROADCAST);
    }
    else if (_T("Vas") == strVideoModeType)
    {
        (void)service_conf_set_video_mode(m_handle, TSDK_E_CONF_VIDEO_VAS);
    }
    else if (_T("Free") == strVideoModeType)
    {
        (void)service_conf_set_video_mode(m_handle, TSDK_E_CONF_VIDEO_FREE);
    }
    else
    {
        return;
    }
}

void CDemoAudioMeetingDlg::OnNMRClickMemberList(NMHDR *pNMHDR, LRESULT *pResult)
{
    if ((NULL == pNMHDR) || (NULL == pResult))
    {
        return;
    }

    /*lint -e826 */
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    /*lint +e826 */

    *pResult = 0;

    CPoint pt, pmenu;
    ::GetCursorPos(&pt);
    ::GetCursorPos(&pmenu);
    m_listMember.ScreenToClient(&pt);
    UINT uFlag = 0;
    int hSelectedItem = m_listMember.HitTest(pt, &uFlag);
    if (0 <= hSelectedItem)
    {
        CMenu menu;
        menu.CreatePopupMenu();

        CString cstrIsChairman = m_listMember.GetItemText(hSelectedItem, COL_MEM_COMPERE);
        CString cstrIsPresenter = m_listMember.GetItemText(hSelectedItem, COL_MEM_PRESENT);
        CString cstrCallState = m_listMember.GetItemText(hSelectedItem, COL_MEM_CALLSTATE);
        CString cstrMute = m_listMember.GetItemText(hSelectedItem, COL_MEM_MUTE);
        CString cstrHandup = m_listMember.GetItemText(hSelectedItem, COL_MEM_HANDUP);
        CString cstrBroadcast = m_listMember.GetItemText(hSelectedItem, COL_MEM_BROADCAST);

        //菜单选项全部列出，未区分主席和与会者，待后续优化
        //闭音与会者
        if (cstrMute != _T("Mute"))
        {
            menu.AppendMenu(MF_STRING, ID_CONF_MUTE_MEM_MENU, _T("Mute"));
        }
        else
        {
            menu.AppendMenu(MF_STRING, ID_CONF_UNMUTE_MEM_MENU, _T("UnMute"));
        }

        //举手
        if (cstrHandup == _T("HandUp"))
        {
            menu.AppendMenu(MF_STRING, ID_CONF_UNHANDUP_MEM_MENU, _T("unHandUp"));
        }

        //挂断与会者
        menu.AppendMenu(MF_STRING, ID_CONF_HANGUP_MEM_MENU, _T("HangUp"));

        //重呼
        menu.AppendMenu(MF_STRING, ID_CONF_RECALL_MEM_MENU, _T("ReCall"));

        //删除与会者
        menu.AppendMenu(MF_STRING, ID_CONF_DEL_MEM_MENU, _T("Delete Attendee"));

        //选看
        menu.AppendMenu(MF_STRING, ID_DCONF_WATCH_MENU, _T("Watch"));

        //广播
        if (cstrBroadcast == _T("Broadcast"))
        {
            menu.AppendMenu(MF_STRING, ID_CONF_UNBROADCAST_MEM_MENU, _T("unBroadcast"));
        }
        else
        {
            menu.AppendMenu(MF_STRING, ID_CONF_BROADCAST_MEM_MENU, _T("Broadcast"));
        }

        //邀请共享
        menu.AppendMenu(MF_STRING, ID_DCONF_SHARE_DESKTOP_MEM_MENU, _T("invite share"));

        //设置为主讲人
        menu.AppendMenu(MF_STRING, ID_DCONF_SETPRESENT_MEM_MENU, _T("To be Present"));

        menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
    }
}


void CDemoAudioMeetingDlg::OnClickListMemMenuItem(UINT nID)
{
    int nItem = -1;
    POSITION pos = m_listMember.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        TRACE0("No items were selected!\n");
        return;
    }
    else
    {
        while (pos)
        {
            nItem = m_listMember.GetNextSelectedItem(pos);
            TRACE1("Item %d was selected!\n", nItem);
            break;
        }
    }
    CString cstrAccount = m_listMember.GetItemText(nItem, COL_MEM_ACCOUNT);
    CString cstrBindNo = m_listMember.GetItemText(nItem, COL_MEM_CALLNO);
    std::string strCallNo = CTools::UNICODE2UTF(cstrBindNo);
    switch (nID)
    {
    case ID_CONF_DEL_MEM_MENU:
    {
        (void)service_conf_delete_attendee(m_handle, strCallNo.c_str());
        break;
    }
    case ID_CONF_RECALL_MEM_MENU:
    {
        //use the service interface of add member
        TSDK_S_ADD_ATTENDEES_INFO addAttendeeInfo = { 0 };
        addAttendeeInfo.attendee_num = 1;
        TSDK_UINT32 count = addAttendeeInfo.attendee_num;
        addAttendeeInfo.attendee_list = (TSDK_S_ATTENDEE_BASE_INFO*)malloc(count*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
        if (NULL == addAttendeeInfo.attendee_list)
        {
            AfxMessageBox(_T("addAttendeeInfo.attendee_list is NULL"));
            return;
        }
        (void)service_memset_s(addAttendeeInfo.attendee_list, count*sizeof(TSDK_S_ATTENDEE_BASE_INFO), 0, count*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
        TSDK_S_ATTENDEE_BASE_INFO* pTempAttendee = addAttendeeInfo.attendee_list;
        for (unsigned int i = 0; i < count; i++)
        {
            if (pTempAttendee)
            {
                (void)strncpy_s(pTempAttendee->number, TSDK_D_MAX_PARTICIPANTID_LEN + 1, strCallNo.c_str(), TSDK_D_MAX_PARTICIPANTID_LEN - 1);
                pTempAttendee->role = TSDK_E_CONF_ROLE_ATTENDEE;
            }
            else
            {
                break;
            }

            pTempAttendee++;
        }
        (void)service_conf_add_attendee(m_handle, &addAttendeeInfo);
        free(addAttendeeInfo.attendee_list);
        addAttendeeInfo.attendee_list = NULL;
        break;
    }
    case ID_CONF_MUTE_MEM_MENU:
    {
        (void)service_conf_mute_attendee(m_handle, strCallNo.c_str(), TRUE);
        break;
    }
    case ID_CONF_UNMUTE_MEM_MENU:
    {
        (void)service_conf_mute_attendee(m_handle, strCallNo.c_str(), FALSE);
        break;
    }
    case ID_CONF_HANGUP_MEM_MENU:
    {
        (void)service_conf_hangup_attendee(m_handle, strCallNo.c_str());
        break;
    }
	case ID_CONF_UNHANDUP_MEM_MENU:
	{
		(void)service_conf_handup(m_handle, FALSE, const_cast<char*>(strCallNo.c_str()));
		break;
	}
    case ID_DCONF_WATCH_MENU:
    {
        TSDK_S_WATCH_ATTENDEES_INFO watchAttendeesInfo = { 0 };
        watchAttendeesInfo.watch_attendee_num = 1;
        watchAttendeesInfo.watch_attendee_list = (TSDK_S_WATCH_ATTENDEES*)malloc(watchAttendeesInfo.watch_attendee_num * sizeof(TSDK_S_WATCH_ATTENDEES));
        if (NULL == watchAttendeesInfo.watch_attendee_list)
        {
            return;
        }
        (void)service_memset_s(watchAttendeesInfo.watch_attendee_list, watchAttendeesInfo.watch_attendee_num * sizeof(TSDK_S_WATCH_ATTENDEES), 0, watchAttendeesInfo.watch_attendee_num * sizeof(TSDK_S_WATCH_ATTENDEES));
        strncpy_s(watchAttendeesInfo.watch_attendee_list->number, TSDK_D_MAX_NUMBER_LEN + 1, strCallNo.c_str(), _TRUNCATE);
        (void)service_conf_watch_attendee(m_handle, &watchAttendeesInfo);
        break;
    }
    case ID_CONF_BROADCAST_MEM_MENU:
    {
        (void)service_conf_broadcast_attendee(m_handle, const_cast<char*>(strCallNo.c_str()), TRUE);
        break;
    }
    case ID_CONF_UNBROADCAST_MEM_MENU:
    {
        std::string attendNum = "";
        (void)service_conf_broadcast_attendee(m_handle, const_cast<char*>(attendNum.c_str()), FALSE);
        break;
    }
    case ID_DCONF_SETPRESENT_MEM_MENU:
    {
        (void)service_data_conf_set_presenter(m_handle, const_cast<char*>(strCallNo.c_str()));
        break;
    }
    case ID_DCONF_SHARE_DESKTOP_MEM_MENU:
    {
        (void)service_data_conf_app_share_set_owner(const_cast<char*>(strCallNo.c_str()), TSDK_E_CONF_AS_ACTION_ADD);
        break;
    }
    case ID_DCONF_STOP_SHARE_DESKTOP_MEM_MENU:
    {
        (void)service_data_conf_app_share_set_owner(const_cast<char*>(strCallNo.c_str()), TSDK_E_CONF_AS_ACTION_DELETE);
        break;
    }
    default:
        break;
    }
}

LRESULT CDemoAudioMeetingDlg::OnConfInfoAndStatusUpdate(WPARAM wparam, LPARAM lparam)
{
    CHECK_POINTER_RETURN(wparam, 0L);
    TSDK_S_CONF_STATUS_INFO* notifyInfo = (TSDK_S_CONF_STATUS_INFO*)wparam;
    TSDK_S_ATTENDEE* participants = notifyInfo->attendee_list;

    /* conferecne lock status*/
    if (notifyInfo->is_lock)
    {
        m_bt_Lock.SetWindowText(_T("UnLock Conf"));
    }
    else
    {
        m_bt_Lock.SetWindowText(_T("Lock Conf"));
    }

    /* Conferecne lock status */
    if (notifyInfo->is_all_mute)
    {
        m_bt_Mute.SetWindowText(_T("UnMute Conf"));
    }
    else
    {
        m_bt_Mute.SetWindowText(_T("Mute Conf"));
    }

    /*Conferecne subject*/
    if (strlen(notifyInfo->subject))
    {
        m_static_subject.SetWindowText(CTools::UTF2UNICODE(notifyInfo->subject));
    }

    /* Update participant */
    for (unsigned int i = 0; i < notifyInfo->attendee_num; i++)
    {
        if (participants)
        {
            CString cstrNum = CTools::UTF2UNICODE(participants->base_info.number);
            CString cstrStatus = CTools::UTF2UNICODE(GetUserStatus(participants->status_info.state));
            int j = -1;
            if (!FindColum(cstrNum, COL_MEM_CALLNO, j))
            {
                int iSize = m_listMember.GetItemCount();
                m_listMember.InsertItem(iSize, _T(""));
                j = iSize;
            }

            /*User role*/
            if (TSDK_E_CONF_ROLE_CHAIRMAN == participants->base_info.role)
            {
                m_listMember.SetItemText(j, COL_MEM_COMPERE, _T("Yes"));
            }
            else
            {
                m_listMember.SetItemText(j, COL_MEM_COMPERE, _T(""));
            }

            m_listMember.SetItemText(j, COL_MEM_NAME, CTools::UTF2UNICODE(participants->base_info.display_name));
            m_listMember.SetItemText(j, COL_MEM_ACCOUNT, CTools::UTF2UNICODE(participants->base_info.account_id));
            m_listMember.SetItemText(j, COL_MEM_CALLNO, cstrNum);
            m_listMember.SetItemText(j, COL_MEM_CALLSTATE, cstrStatus);

            /*mic mute*/
            if (participants->status_info.is_mute)
            {
                m_listMember.SetItemText(j, COL_MEM_MUTE, _T("Mute"));
            }
            else
            {
                m_listMember.SetItemText(j, COL_MEM_MUTE, _T("UnMute"));
            }

            /*hand up*/
            if (participants->status_info.is_handup)
            {
                m_listMember.SetItemText(j, COL_MEM_HANDUP, _T("HandUp"));
            }
            else
            {
                m_listMember.SetItemText(j, COL_MEM_HANDUP, _T("UnHandUp"));
            }

            /*broadcast*/
            if (participants->status_info.is_broadcast)
            {
                m_listMember.SetItemText(j, COL_MEM_BROADCAST, _T("Broadcast"));
            }
            else
            {
                m_listMember.SetItemText(j, COL_MEM_BROADCAST, _T("UnBroadcast"));
            }

            /*present*/
            if (participants->status_info.is_present)
            {
                m_listMember.SetItemText(j, COL_MEM_PRESENT, _T("Yes"));
            }
            else
            {
                m_listMember.SetItemText(j, COL_MEM_PRESENT, _T(""));
            }

            if (participants->status_info.is_self)
            {
                g_sipNumber = participants->base_info.number;

                if (TSDK_E_CONF_ROLE_CHAIRMAN == participants->base_info.role)
                {
                    ischairman = true;
                }

                if (participants->status_info.is_present)
                {
                    ispresenter = true;
                }
            }          
        }
        else
        {
            break;
        }
        participants++;
    }

    UpdateAudioConfButtonStatus();

    free(notifyInfo->attendee_list);
    notifyInfo->attendee_list = NULL;
    delete notifyInfo;

    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return 0L;
    }
    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    if (NULL == maindlg)
    {
        return 0L;
    }
    ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_CONF_REFRESH, NULL, NULL);

    return 0L;
}

BOOL CDemoAudioMeetingDlg::FindColum(const CString& cstrKey, int iColnum, int& iFind)
{
    int iSize = m_listMember.GetItemCount();
    for (int i = 0; i < iSize; i++)
    {
        if (cstrKey.Compare(m_listMember.GetItemText(i, iColnum)) == 0)
        {
            iFind = i;
            return TRUE;
        }
    }
    return FALSE;
}

void CDemoAudioMeetingDlg::GetAttendes(std::vector<CString> &_member)
{
    auto iSize = m_listMember.GetItemCount();
    for (auto i = 0; i < iSize; i++)
    {
        CString cstr(L"");
        cstr = m_listMember.GetItemText(i, COL_MEM_CALLNO);
        _member.push_back(cstr);
    }
    m_listMember.DeleteAllItems();
}

void CDemoAudioMeetingDlg::CloseDlg()
{
    /////data clear////
    m_confID = 0;
    m_callID = 0;
    m_handle = 0;
    ischairman = false;
    ispresenter = false;
    OnOK();
}

//会控操作结果处理
LRESULT CDemoAudioMeetingDlg::OnConfOperationResult(WPARAM wparam, LPARAM)
{
    TSDK_S_CONF_OPERATION_RESULT* notifyInfo = (TSDK_S_CONF_OPERATION_RESULT*)wparam;
    CHECK_POINTER_RETURN(notifyInfo, -1L);

    if (TSDK_SUCCESS != notifyInfo->reason_code)
    {
        MessageBox(_T("operation failed!"));
        return -1L;
    }
   
    switch (notifyInfo->operation_type)
    {
    case TSDK_E_CONF_MUTE_CONF:
    {
        m_bt_Mute.SetWindowText(_T("UnMute Conf"));
        break;
    }
    case TSDK_E_CONF_UNMUTE_CONF:
    {
        m_bt_Mute.SetWindowText(_T("Mute Conf"));
        break;
    }
    case TSDK_E_CONF_LOCK_CONF:
    {
        m_bt_Lock.SetWindowText(_T("UnLock Conf"));
        break;
    }
    case TSDK_E_CONF_UNLOCK_CONF:
    {
        m_bt_Lock.SetWindowText(_T("Lock Conf"));
        break;
    }
    case TSDK_E_CONF_SET_HANDUP:
	case TSDK_E_CONF_CANCLE_HANDUP:
    {
		CString csHandup;
		m_bt_Handup.GetWindowText(csHandup);
		if (_T("Hand Up") == csHandup)
		{
			m_bt_Handup.SetWindowText(_T("unHand Up"));
		}
		else
		{
			m_bt_Handup.SetWindowText(_T("Hand Up"));
		}
        
        break;
    }
    case TSDK_E_CONF_REQUEST_CHAIRMAN:
    {
		ischairman = true;
        m_bt_Apply.EnableWindow(FALSE);
        m_bt_Release.EnableWindow(TRUE);
        break;
    }
    case TSDK_E_CONF_RELEASE_CHAIRMAN:
    {
		ischairman = false;
        m_bt_Apply.EnableWindow(TRUE);
        m_bt_Release.EnableWindow(FALSE);
        break;
    }
    default:
        break;
    }
    
    return 0L;
}

//发言方通知
LRESULT CDemoAudioMeetingDlg::OnConfSpeakerUpdate(WPARAM wparam, LPARAM)
{
    TSDK_S_CONF_SPEAKER_INFO* notifyInfo = (TSDK_S_CONF_SPEAKER_INFO*)wparam;
    CHECK_POINTER_RETURN(notifyInfo, -1L);
    unsigned int number = notifyInfo->speaker_num;
    for (unsigned int i = 0; i < number; i++)
    {
        std::string attendeesnumber = notifyInfo->speakers[i].base_info.number;
        int iColumn;
        if (!FindColum(CTools::UTF2UNICODE(attendeesnumber), COL_MEM_CALLNO, iColumn))
        {
            continue;
        }
        if (notifyInfo->speakers[i].is_speaking)
        {
            m_listMember.SetItemText(iColumn, COL_MEM_SPK, _T("Speaking"));
        }
        else
        {
            m_listMember.SetItemText(iColumn, COL_MEM_SPK, _T(""));
        }
    }

    delete notifyInfo;
    return 0L;
}

std::string CDemoAudioMeetingDlg::GetUserStatus(TSDK_E_CONF_PARTICIPANT_STATUS status)
{
    std::string strStatus;
    switch (status)
    {

    case TSDK_E_CONF_PARTICIPANT_STATUS_IN_CONF:  /**< in conference*/
    {
        strStatus = "InConf";
        break;
    }
    case TSDK_E_CONF_PARTICIPANT_STATUS_CALLING: /**< calling */
    {
        strStatus = "Inviting";
        break;
    }
    case TSDK_E_CONF_PARTICIPANT_STATUS_JOINING: /**< joining conference */
    {
        strStatus = "Joining";
        break;
    }
    case TSDK_E_CONF_PARTICIPANT_STATUS_LEAVED:  /**< leave conference */
    {
        strStatus = "Leave";
        break;
    }
    case TSDK_E_CONF_PARTICIPANT_STATUS_NO_EXIST: /**< this participant is not exist */
    {
        strStatus = "None";
        break;
    }
    case TSDK_E_CONF_PARTICIPANT_STATUS_BUSY:     /**< busy */
    {
        strStatus = "Busy";
        break;
    }
    default:
        strStatus = "Add Fail";
        break;
    }
    return strStatus;
}


void CDemoAudioMeetingDlg::UpdateAudioConfButtonStatus()
{
    if (ischairman)
    {
        m_bt_Mute.EnableWindow(TRUE);
        m_bt_Lock.EnableWindow(TRUE);
        m_bt_DataConf.EnableWindow(TRUE);
        m_bt_Handup.EnableWindow(FALSE);
        m_bt_Apply.EnableWindow(FALSE);
        m_bt_Release.EnableWindow(TRUE);
        m_bt_Add.EnableWindow(TRUE);
        m_bt_Dtmf.EnableWindow(TRUE);
        m_cbxVideoConfMode.EnableWindow(TRUE);
        m_bt_End_Conf.EnableWindow(TRUE);
        m_bt_Leave_Conf.EnableWindow(TRUE);
    }
    else
    {
        m_bt_Mute.EnableWindow(FALSE);
        m_bt_Lock.EnableWindow(FALSE);
        m_bt_DataConf.EnableWindow(FALSE);
        m_bt_Handup.EnableWindow(TRUE);
        m_bt_Apply.EnableWindow(TRUE);
        m_bt_Release.EnableWindow(FALSE);
        m_bt_Add.EnableWindow(FALSE);
        m_bt_Dtmf.EnableWindow(TRUE);
        m_cbxVideoConfMode.EnableWindow(FALSE);
        m_bt_End_Conf.EnableWindow(FALSE);
        m_bt_Leave_Conf.EnableWindow(TRUE);
    }

    if (AUDIO_DATA_CONF == m_confType || VIDEO_DATA_CONF == m_confType)
    {
        m_bt_DataConf.EnableWindow(FALSE);
    }
}
