//
//  DemoVideoMeetingDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoApp.h"
#include "DemoVideoMeetingDlg.h"
#include "DemoMainDlg.h"
#include "afxdialogex.h"
#include "DemoCommonTools.h"
#include "DemoDataMeetingDlg.h"
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
extern MAP_CONFINFO g_mapConfInfo;

#define  DLG_CONF_WIDE            570
#define  DLG_CONF_AUDIO_HEI        320
#define  DLG_CONF_VIDEO_HEI        480

// CDemoAudioMeetingDlg dialog
IMPLEMENT_DYNAMIC(CDemoVideoMeetingDlg, CDialogEx)

CDemoVideoMeetingDlg::CDemoVideoMeetingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoVideoMeetingDlg::IDD, pParent)
    , ischairman(false)
    , m_confID(0)
    , m_callID(0)
    , m_handle(0)
{

}

CDemoVideoMeetingDlg::~CDemoVideoMeetingDlg()
{
}

void CDemoVideoMeetingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MEMBER_LIST, m_listMember);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_MUTE, m_bt_Mute);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_LOCK, m_bt_Lock);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_DATACONF, m_bt_DataConf);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_BROADCAST, m_bt_Broadcast);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_MODAL, m_bt_Model);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_HANDUP, m_bt_Handup);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_APPLY, m_bt_Apply);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_RELEASE, m_bt_Release);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_DTMF, m_bt_Dtmf);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_MIC, m_bt_MicMute);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_CAMERA, m_bt_Camera);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_CONF_ADD_MEMBER, m_bt_AddMember);
    DDX_Control(pDX, IDC_STATIC_VIDEO_CONF_SUBJECT, m_static_subject);
    DDX_Control(pDX, IDC_STATIC_VIDEO1, m_attendeeVideoCtrl1);
    DDX_Control(pDX, IDC_STATIC_VIDEO2, m_LocalVideoCtrl);
}


BEGIN_MESSAGE_MAP(CDemoVideoMeetingDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_ADD_MEMBER, &CDemoVideoMeetingDlg::OnBnClickedAddMember)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_CAMERA, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfCamera)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_MIC, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfMicMute)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_DTMF, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfDtmf)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_DATACONF, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfDataconf)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_MUTE, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfMute)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_LOCK, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfLock)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_APPLY, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfApply)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_RELEASE, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfRelease)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_HANDUP, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfHandup)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_CONF_MODAL, &CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfMode)
    ON_NOTIFY(NM_RCLICK, IDC_MEMBER_LIST, &CDemoVideoMeetingDlg::OnNMRClickMemberList)
    ON_COMMAND_RANGE(ID_CONF_DEL_MEM_MENU, ID_CONF_UNMUTE_MEM_MENU, &CDemoVideoMeetingDlg::OnClickListMemMenuItem)
    ON_MESSAGE(WM_CONF_CTRL_INFO_AND_STATUS_UPDATE, &CDemoVideoMeetingDlg::OnConfInfoAndStatusUpdate)
    ON_MESSAGE(WM_CONF_CTRL_ADDRESSER_UPDATE_IND, &CDemoVideoMeetingDlg::OnConfAddresserUpdate)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDemoAudioMeetingDlg handle function
BOOL CDemoVideoMeetingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_listMember.ModifyStyle(0, LVS_SINGLESEL);
    m_listMember.InsertColumn(COL_MEM_COMPERE, _T("Chirman"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_NAME, _T("Name"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_ACCOUNT, _T("Account"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_CALLNO, _T("Number"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_CALLSTATE, _T("CallStatus"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_SPK, _T("Speaker"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_MUTE, _T("Mute"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_HANDUP, _T("HandUp"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_BROADCAST, _T("Broadcast"), LVCFMT_JUSTIFYMASK, 78);
    m_listMember.InsertColumn(COL_MEM_PRESENT, _T("Present"), LVCFMT_JUSTIFYMASK, 78);
    DWORD dwStyle = m_listMember.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;    //选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;        //网格线（只适用与report风格的listctrl）
    m_listMember.SetExtendedStyle(dwStyle); //设置扩展风格
    return TRUE;  // return TRUE unless you set the focus to a control
}


void CDemoVideoMeetingDlg::OnClose()
{
    /*End Call*/
    if (m_callID != 0)
    {
        service_call_end(m_callID);
        m_callID = 0;
    }

    /*End Conference*/
    if (ischairman)
    {
        service_conf_end(m_handle);
    }
    else
    {
        service_conf_leave(m_handle);
    }
    m_handle = 0;

    /////close confDlg/////
    ::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(), WM_CALL_CONF_CLOSE_DLG, NULL, NULL);
    CDialogEx::OnClose();
}

void CDemoVideoMeetingDlg::OnNMRClickMemberList(NMHDR *pNMHDR, LRESULT *pResult)
{
    if ((NULL == pNMHDR) || (NULL == pResult))
    {
        return;
    }

    /*lint -e826 */
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    /*lint +e826 */

    *pResult = 0;
    if (!ischairman)
    {
        return;
    }

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

        //delete attendee
        menu.AppendMenu(MF_STRING, ID_CONF_DEL_MEM_MENU, _T("Delete Attendee"));
        CString strCompere = m_listMember.GetItemText(hSelectedItem, COL_MEM_COMPERE);
        CString cstrCallState = m_listMember.GetItemText(hSelectedItem, COL_MEM_CALLSTATE);

        if (strCompere.Compare(_T("Yes")) == 0 || cstrCallState == _T("Leave"))
        {
            menu.EnableMenuItem(ID_CONF_DEL_MEM_MENU, MF_DISABLED | MF_GRAYED);
        }

        //mute or hangup attendee
        if (cstrCallState == _T("InConf") || cstrCallState == _T("Inviting"))
        {
            CString cstrMute = m_listMember.GetItemText(hSelectedItem, COL_MEM_MUTE);
            if (cstrMute != _T("Mute"))
            {
                menu.AppendMenu(MF_STRING, ID_CONF_MUTE_MEM_MENU, _T("Mute"));
            }
            else
            {
                menu.AppendMenu(MF_STRING, ID_CONF_UNMUTE_MEM_MENU, _T("Unmute"));
            }

            CString strCompere = m_listMember.GetItemText(hSelectedItem, COL_MEM_COMPERE);
            if (strCompere.Compare(_T("Yes")) != 0)
            {
                menu.AppendMenu(MF_STRING, ID_CONF_HANGUP_MEM_MENU, _T("HangUp"));

                CString cstrMute = m_listMember.GetItemText(hSelectedItem, COL_MEM_BROADCAST);
                if (cstrMute != _T("Broadcast"))
                {
                    menu.AppendMenu(MF_STRING, ID_CONF_BROADCAST_MEM_MENU, _T("Broadcast"));
                }
                else
                {
                    menu.AppendMenu(MF_STRING, ID_CONF_UNBROADCAST_MEM_MENU, _T("UnBroadcast"));
                }

                menu.AppendMenu(MF_STRING, ID_CONF_WATCH_MEM_MENU, _T("Watch"));
            }
        }
        else
        {
            menu.AppendMenu(MF_STRING, ID_CONF_RECALL_MEM_MENU, _T("ReCall"));
        }
        menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
    }
}


void CDemoVideoMeetingDlg::OnClickListMemMenuItem(UINT nID)
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
        (void)service_conf_mem_delete(m_handle, strCallNo.c_str());
        ::SendMessage(m_listMember.m_hWnd, LVM_DELETEITEM, (unsigned int)nItem, 0);
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
        (void)service_conf_mem_add(m_handle, &addAttendeeInfo);
        SAFE_DELETE_ARRAY(pTempAttendee);
        break;
    }
    case ID_CONF_MUTE_MEM_MENU:
    {
        (void)service_conf_mem_mute(m_handle, strCallNo.c_str(), TRUE);
        break;
    }
    case ID_CONF_UNMUTE_MEM_MENU:
    {
        (void)service_conf_mem_mute(m_handle, strCallNo.c_str(), FALSE);
        break;
    }
    case ID_CONF_HANGUP_MEM_MENU:
    {
        (void)service_conf_mem_hangup(m_handle, strCallNo.c_str());
        break;
    }
    case ID_CONF_BROADCAST_MEM_MENU:
    {
        (void)service_conf_broadcast_attendee(m_handle, const_cast<char*>(strCallNo.c_str()), TRUE);
        break;
    }
    case ID_CONF_UNBROADCAST_MEM_MENU:
    {
        (void)service_conf_broadcast_attendee(m_handle, const_cast<char*>(strCallNo.c_str()), FALSE);
        break;
    }
    case ID_CONF_WATCH_MEM_MENU:
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
    default:
        break;
    }
}


LRESULT CDemoVideoMeetingDlg::OnConfInfoAndStatusUpdate(WPARAM wparam, LPARAM lparam)
{
    CHECK_POINTER_RETURN(wparam, 0L);
    TSDK_S_CONF_STATUS_INFO* notifyInfo = (TSDK_S_CONF_STATUS_INFO*)wparam;
    TSDK_S_ATTENDEE* participants = notifyInfo->attendee_list;

    /* conferecne lock status*/
    if (notifyInfo->is_lock)
    {
        m_bt_Lock.SetWindowText(_T("Unlock"));
    }
    else
    {
        m_bt_Lock.SetWindowText(_T("Lock"));
    }

    /* Conferecne lock status */
    if (notifyInfo->is_all_mute)
    {
        m_bt_Mute.SetWindowText(_T("Unmute"));
    }
    else
    {
        m_bt_Mute.SetWindowText(_T("Mute"));
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
                m_listMember.SetItemText(j, COL_MEM_MUTE, _T("Unmute"));
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

            if (TSDK_E_CONF_ROLE_CHAIRMAN == participants->base_info.role &&  participants->status_info.is_self)
            {
                ischairman = true;
            }
        }
        else
        {
            break;
        }
        participants++;
    }

    UpdateVideoConfButtonStatus();

    free(notifyInfo->attendee_list);
    notifyInfo->attendee_list = NULL;
    delete (notifyInfo);
    return 0L;
}

BOOL CDemoVideoMeetingDlg::FindColum(const CString& cstrKey, int iColnum, int& iFind)
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

void CDemoVideoMeetingDlg::GetAttendes(std::vector<CString> &_member)
{
    auto iSize = m_listMember.GetItemCount();
    for (auto i = 0; i < iSize; i++)
    {
        CString cstr(_T(""));
        cstr = m_listMember.GetItemText(i, COL_MEM_CALLNO);
        _member.push_back(cstr);
    }
    m_listMember.DeleteAllItems();
}

void CDemoVideoMeetingDlg::CloseDlg()
{
    /////data clear////
    m_confID = 0;
    m_callID = 0;
    m_handle = 0;
    ischairman = false;
    OnOK();
}

void CDemoVideoMeetingDlg::SetDlgtype(MettingType videotype)
{
    int cxFrame = ::GetSystemMetrics(SM_CXSCREEN);
    int cyFrame = ::GetSystemMetrics(SM_CYSCREEN);
    if (VIDEO_METTING == videotype)
    {
        MoveWindow((cxFrame - DLG_CONF_WIDE) / 2, (cyFrame - DLG_CONF_VIDEO_HEI) / 2, DLG_CONF_WIDE, DLG_CONF_VIDEO_HEI);
    }
    else
    {
        MoveWindow((cxFrame - DLG_CONF_WIDE) / 2, (cyFrame - DLG_CONF_AUDIO_HEI) / 2, DLG_CONF_WIDE, DLG_CONF_AUDIO_HEI);
    }

}

//发言方通知
LRESULT CDemoVideoMeetingDlg::OnConfAddresserUpdate(WPARAM wparam, LPARAM)
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

    delete (notifyInfo);
    return 0L;
}


std::string CDemoVideoMeetingDlg::GetUserStatus(TSDK_E_CONF_PARTICIPANT_STATUS status)
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


void CDemoVideoMeetingDlg::OnBnClickedAddMember()
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
    (void)service_conf_mem_add(m_handle, &addAttendeeInfo);
    SAFE_DELETE_ARRAY(pTempAttendee);
}

void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfDataconf()
{
    TSDK_S_CONF_UPGRADE_PARAM upParam = { 0 };
    strcpy_s(upParam.group_uri, TSDK_D_MAX_GROUP_URI_LEN + 1, "");
    (void)service_conf_update_deta_conf(m_handle, &upParam);
}


void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfMute()
{
    CString cstrtxt;
    m_bt_Mute.GetWindowText(cstrtxt);
    if (_T("Mute") == cstrtxt)
    {
        //// mute conf
        service_conf_mute(m_handle, 1);
        m_bt_Mute.SetWindowText(_T("Unmute"));
    }
    else
    {
        /////unmute conf
        service_conf_mute(m_handle, 0);
        m_bt_Mute.SetWindowText(_T("Mute"));
    }
}


void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfLock()
{
    CString cstrtxt;
    m_bt_Lock.GetWindowText(cstrtxt);
    if (_T("Lock") == cstrtxt)
    {
        ////Lock conf
        service_conf_lock(m_handle, 1);
        m_bt_Lock.SetWindowText(_T("Unlock"));
    }
    else
    {
        ////Unlock conf
        service_conf_lock(m_handle, 0);
        m_bt_Lock.SetWindowText(_T("Lock"));
    }
}


void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfApply()
{
    std::string strPwd = "";
    (void)service_conf_request_chairman(m_handle, const_cast<char*>(strPwd.c_str()));
}


void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfRelease()
{
    (void)service_conf_release_chairman(m_handle);
}


void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfHandup()
{
    CString attendeeNum = CTools::GetSipNumber(g_sipNumber);
    std::string strAttendeeNum = CTools::UNICODE2UTF(attendeeNum);
    (void)service_conf_handup(m_handle, TRUE, const_cast<char*>(strAttendeeNum.c_str()));
}

void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfDtmf()
{
    CDemoVideoMeetingDlg* pVideoConfDlg = (CDemoVideoMeetingDlg*)this;
    CHECK_POINTER(pVideoConfDlg);
    CDemoCallDtmfDlg dlg;
    dlg.SetCallid(m_callID);
    (void)dlg.DoModal();
}

void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfMicMute()
{
    CDemoVideoMeetingDlg* pVideoConfDlg = (CDemoVideoMeetingDlg*)this;
    CHECK_POINTER(pVideoConfDlg);
    CString csMIc;
    m_bt_MicMute.GetWindowText(csMIc);
    if (_T("Mute mic") == csMIc)
    {
        m_bt_MicMute.SetWindowText(_T("unMute mic"));
        service_call_mic_mute(m_callID, TRUE);
    }
    else
    {
        m_bt_MicMute.SetWindowText(_T("Mute mic"));
        service_call_mic_mute(m_callID, FALSE);
    }
}

void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfCamera()
{
    CString csMIc;
    m_bt_Camera.GetWindowText(csMIc);
    if (_T("Open Local camera") == csMIc)
    {
        m_bt_Camera.SetWindowText(_T("Close Local camera"));
        service_call_video_control(m_callID, FALSE);
    }
    else
    {
        m_bt_Camera.SetWindowText(_T("Open Local camera"));
        service_call_video_control(m_callID, TRUE);
    }
}

void CDemoVideoMeetingDlg::OnBnClickedButtonVideoConfMode()
{
    (void)service_conf_set_video_mode(m_handle, TSDK_E_CONF_VIDEO_FREE);
}

void CDemoVideoMeetingDlg::BindVideoWindow()
{
    HWND localVideo = m_LocalVideoCtrl.GetSafeHwnd();
    HWND attendeeVideo1 = m_attendeeVideoCtrl1.GetSafeHwnd();
    (void)service_set_video_window(m_callID, (unsigned int)localVideo, (unsigned int)attendeeVideo1);
}

void CDemoVideoMeetingDlg::UpdateVideoConfButtonStatus()
{
    if (ischairman)
    {
        m_bt_AddMember.EnableWindow(TRUE);
        m_bt_Mute.EnableWindow(TRUE);
        m_bt_Lock.EnableWindow(TRUE);
        m_bt_DataConf.EnableWindow(TRUE);
        m_bt_Broadcast.EnableWindow(TRUE);
        m_bt_Model.EnableWindow(TRUE);
        m_bt_Handup.EnableWindow(FALSE);
        m_bt_Apply.EnableWindow(FALSE);
        m_bt_Release.EnableWindow(TRUE);
        m_bt_Dtmf.EnableWindow(TRUE);
        m_bt_MicMute.EnableWindow(TRUE);
        m_bt_Camera.EnableWindow(TRUE);
    }
    else
    {
        m_bt_AddMember.EnableWindow(FALSE);
        m_bt_Mute.EnableWindow(FALSE);
        m_bt_Lock.EnableWindow(FALSE);
        m_bt_DataConf.EnableWindow(FALSE);
        m_bt_Broadcast.EnableWindow(FALSE);
        m_bt_Model.EnableWindow(FALSE);
        m_bt_Handup.EnableWindow(TRUE);
        m_bt_Apply.EnableWindow(TRUE);
        m_bt_Release.EnableWindow(FALSE);
        m_bt_Dtmf.EnableWindow(TRUE);
        m_bt_MicMute.EnableWindow(TRUE);
        m_bt_Camera.EnableWindow(TRUE);
    }
}
