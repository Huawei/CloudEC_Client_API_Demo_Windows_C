//
//  DemoDataMeetingDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "resource.h"
#include "DemoData.h"
#include "DemoApp.h"
#include "DemoMainDlg.h"
#include "DemoDataMeetingDlg.h"
#include "DemoMeetingAddMemDlg.h"
#include "DemoAudioMeetingDlg.h"
#include "DemoCommonTools.h"
#include "DemoPromptDlg.h"
#include "service_tools.h"
#include "service_call_interface.h"
#include "service_os_adapt.h"


#define TUP_OK                          0x0000
#define AS_ACTION_DELETE                0x0000
#define AS_ACTION_ADD                   0x0001

extern CString g_sipNumber;
extern CString g_shortNumber;

// CDemoDataMeetingDlg dialog
IMPLEMENT_DYNAMIC(CDemoDataMeetingDlg, CDialogEx)

CDemoDataMeetingDlg::CDemoDataMeetingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoDataMeetingDlg::IDD, pParent)
    , isallmute(0)
    , m_handle(0)
    , m_appshareDlg(NULL)
    , ispresenter(false)
    , ischairman(false)
    , userid(0)
    , m_callID(0)
    , m_confID(0)
    , m_Tab_CurSel(0)
{
    for (unsigned int i = 0; i < DATACONF_DLG_NUM; i++)
    {
        pDlg[i] = NULL;
    }
}

CDemoDataMeetingDlg::~CDemoDataMeetingDlg()
{
    /*service_data_conf_release();*/
    isallmute = 0;
    m_handle = 0;
    SAFE_DELETE(m_appshareDlg);
}

void CDemoDataMeetingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ST_STATUS, m_st_status);
    DDX_Control(pDX, IDC_BT_ALLMUTE, m_bt_mute);
    DDX_Control(pDX, IDC_BT_ADD, m_bt_add);
    DDX_Control(pDX, IDC_ST_HOST, m_static_present);
    DDX_Control(pDX, IDC_ST_LOCAL, m_static_local);
    DDX_Control(pDX, IDC_DATD_LIST_MEMBER, m_confmemblist);
    DDX_Control(pDX, IDC_DATA_TAB, m_dataconf_tab);
    DDX_Control(pDX, IDC_EDIT_SPEAKER, m_conf_speaker);
}


BEGIN_MESSAGE_MAP(CDemoDataMeetingDlg, CDialogEx)
    ON_WM_CLOSE()
    ON_CONTROL_RANGE(BN_CLICKED,ID_DCONF_SETPRESENT_MEM_MENU,ID_DCONF_REINVITE_MEM_MENU,&CDemoDataMeetingDlg::OnClickListMemMenu)
    ON_BN_CLICKED(IDC_BT_ALLMUTE, &CDemoDataMeetingDlg::OnBnClickedBtAllmute)
    ON_BN_CLICKED(IDC_BUTTON_DATA_CONF_LOCK, &CDemoDataMeetingDlg::OnBnClickedBtLock)
    ON_BN_CLICKED(IDC_BT_ADD, &CDemoDataMeetingDlg::OnBnClickedBtAdd)
    ON_BN_CLICKED(IDC_BUTTON_DATA_CONF_APPLY, &CDemoDataMeetingDlg::OnBnClickedBtApply)
    ON_BN_CLICKED(IDC_BUTTON_DATA_CONF_RELEASE, &CDemoDataMeetingDlg::OnBnClickedBtRelease)
    ON_BN_CLICKED(IDC_BUTTON_DATA_CONF_HANDUP, &CDemoDataMeetingDlg::OnBnClickedBtHandup)
    ON_BN_CLICKED(IDC_BUTTON_DATA_CONF_MODAL, &CDemoDataMeetingDlg::OnBnClickedBtConfMode)
    ON_NOTIFY(NM_RCLICK, IDC_DATD_LIST_MEMBER, &CDemoDataMeetingDlg::OnNMClickListMember)
    ON_MESSAGE(WM_DATACONF_MODULE_END,&CDemoDataMeetingDlg::OnDataConfeEnd)
    ON_MESSAGE(WM_DATACONF_MODULE_SHARING_SESSION,&CDemoDataMeetingDlg::OnShareSession)
    ON_MESSAGE(WM_DATACONF_MODULE_SHARING_STATE,&CDemoDataMeetingDlg::OnShareState)
    ON_MESSAGE(WM_DATACONF_MODULE_SCREEN_DATA,&CDemoDataMeetingDlg::OnDataConfASUpdateScreen)
    ON_MESSAGE(WM_CONF_CTRL_INFO_AND_STATUS_UPDATE, &CDemoDataMeetingDlg::OnConfInfoAndStatusUpdate)
    ON_MESSAGE(WM_DATACONF_MODULE_PRESENTERCHG, &CDemoDataMeetingDlg::OnConfPresenterChange)
	ON_MESSAGE(WM_CONF_CTRL_ADDRESSER_UPDATE_IND, &CDemoDataMeetingDlg::OnConfAddresserUpdate)
END_MESSAGE_MAP()


// CDemoDataMeetingDlg message handle
BOOL CDemoDataMeetingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    InitUI();
    UpdateData(FALSE);
    return TRUE; 
}

void CDemoDataMeetingDlg::OnClose()
{
    /*End Data conference*/
    
    if (m_handle)
    {
        if (ischairman)
        {
            service_conf_end(m_handle);
        }
        else
        {
            service_conf_leave(m_handle);
        }
        m_handle = 0;
    }


    /*End Call*/
    if (m_callID != 0)
    {
        service_call_end(m_callID);
        m_callID = 0;
    }

    m_confID = 0;

    OnOK();
    ::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_DATACONF_MODULE_CLOSE,(WPARAM)this,NULL);
    CDialogEx::OnClose();
    
}

void CDemoDataMeetingDlg::InitUI()
{
    m_confmemblist.DeleteAllItems();
    m_confmemblist.ModifyStyle(0,LVS_SINGLESEL);
    m_confmemblist.InsertColumn(COL_DATACONFMEM_NUMBER, _T("number"), LVCFMT_LEFT, 50);
    m_confmemblist.InsertColumn(COL_DATACONFMEM_NAME, _T("name"), LVCFMT_LEFT, 60);
    m_confmemblist.InsertColumn(COL_DATACONFMEM_STATUS, _T("status"), LVCFMT_LEFT, 100);
    DWORD dwStyle = m_confmemblist.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;    //选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;        //网格线（只适用与report风格的listctrl）
    m_confmemblist.SetExtendedStyle(dwStyle); //设置扩展风格

    /*Init Dlg*/
    m_dataconf_tab.InsertItem(0, _T("Screen&APPS"));    

    CRect rect;
    m_dataconf_tab.GetClientRect(&rect);
    if (NULL == m_appshareDlg)
    {
        m_appshareDlg = new CDemoDataConfAppShareDlg;
    }
    if(!::IsWindow(m_appshareDlg->GetSafeHwnd()))
    {
        m_appshareDlg->Create(IDD_DATA_CONF_SCREEN_APP, &m_dataconf_tab);
    }

    pDlg[0] = m_appshareDlg;

    for (int i = 0; i <DATACONF_DLG_NUM; i++)
    {
        SetSubDlgPosion(rect, i);
    }
    m_Tab_CurSel = 0;
    pDlg[m_Tab_CurSel]->ShowWindow(SW_SHOW);
}

void CDemoDataMeetingDlg::SetSubDlgPosion( CRect rect, int index )
{
    rect.top += 24;
    pDlg[index]->MoveWindow(&rect);
    pDlg[index]->ShowWindow(SW_HIDE);
}

BOOL CDemoDataMeetingDlg::FindColum(const CString& cstrKey,int iColnum,int& iLine)
{
    /////Fine user/////
    int iSize = m_confmemblist.GetItemCount();
    for(int i = 0; i< iSize; i++)
    {
        if(cstrKey.Compare(m_confmemblist.GetItemText(i,iColnum)) == 0)
        {
            iLine = i;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CDemoDataMeetingDlg::FindColumByUserID(unsigned int& id,int& iLine)
{
    int iSize = m_confmemblist.GetItemCount();
    for (int i = 0;i < iSize;i++)
    {
        if (id == m_confmemblist.GetItemData(i))
        {
            iLine = i;
            return TRUE;
        }
    }
    return FALSE;
}

void CDemoDataMeetingDlg::OnClickListMemMenu(UINT nID)
{
    int nItem = -1;
    POSITION pos = m_confmemblist.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        TRACE0("No items were selected!\n");
        return;
    }
    else
    {
        while (pos)
        {
            nItem = m_confmemblist.GetNextSelectedItem(pos);
            TRACE1("Item %d was selected!\n", nItem);
            break;
        }
    }

    std::string strCallNum = CTools::UNICODE2UTF(m_confmemblist.GetItemText(nItem,COL_DATACONFMEM_NUMBER));
    unsigned int id = m_confmemblist.GetItemData(nItem);
    

    switch (nID)
    {
    case ID_DCONF_SETPRESENT_MEM_MENU:
    {
        (void)service_data_conf_set_presenter(m_handle, const_cast<char*>(strCallNum.c_str()));
        break;
    }
    case ID_DCONF_SHARE_DESKTOP_MEM_MENU:
    {
        (void)service_data_conf_app_share_set_owner(m_handle, const_cast<char*>(strCallNum.c_str()), TSDK_E_CONF_AS_ACTION_ADD);
        break;
    }
    case ID_DCONF_STOP_SHARE_DESKTOP_MEM_MENU:
    {
        (void)service_data_conf_app_share_set_owner(m_handle, const_cast<char*>(strCallNum.c_str()), TSDK_E_CONF_AS_ACTION_DELETE);
        break;
    }
    default:
        break;
    }
}


void CDemoDataMeetingDlg::OnNMClickListMember(NMHDR *pNMHDR, LRESULT *pResult)
{
    if ((NULL == pNMHDR) || (NULL == pResult))
    {
        return;
    }
    
    /*lint -e826 */
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    /*lint +e826 */
    
    *pResult = 0;
    //////Response to chairman//////
    if (!ischairman)
    {
        return;
    }

    CPoint pt, pmenu;
    ::GetCursorPos(&pt);
    ::GetCursorPos(&pmenu);
    m_confmemblist.ScreenToClient(&pt);
    UINT uFlag = 0;
    int hSelectedItem = m_confmemblist.HitTest(pt,&uFlag);
    if (0 <= hSelectedItem)
    {
        CMenu menu;
        menu.CreatePopupMenu();

        CString cstrCallState = m_confmemblist.GetItemText(hSelectedItem, COL_DATACONFMEM_STATUS);
        if (cstrCallState == L"In Conference")
        {
            if (ispresenter)
            {
                menu.AppendMenu(MF_STRING, ID_DCONF_SETPRESENT_MEM_MENU, _T("To be Present"));
            }

            //if (ischairman)
            //{
            menu.AppendMenu(MF_STRING, ID_DCONF_SHARE_DESKTOP_MEM_MENU, _T("invite share"));
            //}
        }
        

        /*CString cstrCallState = m_confmemblist.GetItemText(hSelectedItem,COL_DATACONFMEM_STATUS);
        if(cstrCallState != L"In Conference")
        {

            menu.AppendMenu(MF_STRING, ID_DCONF_REINVITE_MEM_MENU, _T("ReInvite"));
        }*/
        menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);                         
    }
}

void CDemoDataMeetingDlg::OnBnClickedBtAllmute()
{
    CString cstrtxt;
    m_bt_mute.GetWindowText(cstrtxt);
    if (_T("Mute") == cstrtxt)
    {
        /////Set all mute////
        (void)service_conf_mute(m_handle, 1);
        m_bt_mute.SetWindowText(_T("Unmute"));
    }
    else
    {
        /////unmute conf
        (void)service_conf_mute(m_handle, 0);
        m_bt_mute.SetWindowText(_T("Mute"));
    }
}

void CDemoDataMeetingDlg::OnBnClickedBtLock()
{
    CString cstrtxt;
    m_bt_lock.GetWindowText(cstrtxt);
    if (_T("Lock") == cstrtxt)
    {
        ////Lock conf
        service_conf_lock(m_handle, 1);
        m_bt_lock.SetWindowText(_T("Unlock"));
    }
    else
    {
        ////Unlock conf
        service_conf_lock(m_handle, 0);
        m_bt_lock.SetWindowText(_T("Lock"));
    }
}

void CDemoDataMeetingDlg::OnBnClickedBtAdd()
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

void CDemoDataMeetingDlg::OnBnClickedBtApply()
{
    std::string strPwd = "";
    (void)service_conf_request_chairman(m_handle, const_cast<char*>(strPwd.c_str()));
}

void CDemoDataMeetingDlg::OnBnClickedBtRelease()
{
    (void)service_conf_release_chairman(m_handle);
}

void CDemoDataMeetingDlg::OnBnClickedBtHandup()
{
    CString attendeeNum = CTools::GetSipNumber(g_sipNumber);
    std::string strAttendeeNum = CTools::UNICODE2UTF(attendeeNum);
    (void)service_conf_handup(m_handle, TRUE, const_cast<char*>(strAttendeeNum.c_str()));
}

void CDemoDataMeetingDlg::OnBnClickedBtConfMode()
{
    (void)service_conf_set_video_mode(m_handle, TSDK_E_CONF_VIDEO_FREE);
}

LRESULT CDemoDataMeetingDlg::OnDataConfeEnd(WPARAM,LPARAM)
{
    OnClose();
    return 0L;
}

LRESULT CDemoDataMeetingDlg::OnShareSession(WPARAM wparam,LPARAM lparam)
{
    CHECK_POINTER_RETURN(m_appshareDlg, -1L);
    TSDK_E_CONF_AS_ACTION_TYPE actionType = (TSDK_E_CONF_AS_ACTION_TYPE)wparam;
    std::string shareOwnerNum =(TSDK_CHAR *)lparam;
    
    CString cstxt = CTools::UTF2UNICODE(shareOwnerNum);
    cstxt += _T("has the right to share");
    m_st_status.SetWindowText(cstxt);

    CString selfNumber = CTools::GetSipNumber(g_sipNumber);
    TSDK_CHAR strSelfNumber[TSDK_D_MAX_NUMBER_LEN + 1];
    CTools::CString2Char(selfNumber, strSelfNumber, TSDK_D_MAX_NUMBER_LEN);

    if (TSDK_E_CONF_AS_ACTION_ADD == actionType)
    {
        if (shareOwnerNum == strSelfNumber)
        {
            if (ispresenter)
            {
                if (m_appshareDlg->isShareDesktop)
                {
                    (void)service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_DESKTOP);
                }
                else
                {
                    (void)service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_PROGRAM);
                }
            }
            else
            {
                CDemoPromptDlg promptDlg;
                promptDlg.SetTextOfContent(_T("The Chairman invite share desktop,do you agree?"));
                INT_PTR nResponse = promptDlg.DoModal();
                if (IDOK == nResponse)
                {
                    (void)service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_DESKTOP);
                }
                else
                {
                    return 0L;
                }
            }
        }
    }
    else if (TSDK_E_CONF_AS_ACTION_DELETE == actionType)
    {
        if (shareOwnerNum == strSelfNumber)
        {
            if (!ispresenter)
            {
                (void)service_data_conf_app_share_stop(m_handle);
            }
        }
    }

    return 0L;
}

LRESULT CDemoDataMeetingDlg::OnShareState(WPARAM wparam,LPARAM lparam)
{
    TSDK_S_CONF_AS_STATE_INFO* shareState = (TSDK_S_CONF_AS_STATE_INFO*)wparam;
    CHECK_POINTER_RETURN(shareState,-1L);

    TSDK_UINT32 sharetype = (unsigned int)lparam;

    CString cstxt;
    if (sharetype == DESKTOP)
    {
        cstxt = _T("DeskTop Share");
    }
    else if(sharetype == APP)
    {
        cstxt = _T("APP Share");
    }

    switch (shareState->state)
    {
    case TSDK_E_CONF_AS_STATE_NULL:
        {
            cstxt += _T("Status is NULL");
            if (m_appshareDlg)
            {
                m_appshareDlg->SetBitmapNULL();
            }
            break;
        }
    case TSDK_E_CONF_AS_STATE_VIEW:
        {
            cstxt += _T("Status is Viewing");
            break;
        }
    case TSDK_E_CONF_AS_STATE_START:
        {
            cstxt += _T("Status is Start");
            break;;
        }
    case TSDK_E_CONF_AS_STATE_PAUSE:
        {
            cstxt += _T("Status is Pause");
            if (m_appshareDlg)
            {
                m_appshareDlg->SetBitmapNULL();
            }
            break;
        }
    case TSDK_E_CONF_AS_STATE_PAUSEVIEW:
        {
            cstxt += _T("Status is View Pause");
            if (m_appshareDlg)
            {
                m_appshareDlg->SetBitmapNULL();
            }
            break;
        }
    }
    m_st_status.SetWindowText(cstxt);
    delete (shareState);
    return 0L;
}

LRESULT CDemoDataMeetingDlg::OnDataConfASUpdateScreen(WPARAM, LPARAM)
{
    if (m_appshareDlg)
    {
        ::PostMessage(m_appshareDlg->GetSafeHwnd(),WM_DATACONF_MODULE_SCREEN_DATA, NULL,NULL);
    }
    return 0L;
}

LRESULT CDemoDataMeetingDlg::OnConfInfoAndStatusUpdate(WPARAM wparam, LPARAM lparam)
{
    TSDK_UINT32 confHandle = (TSDK_UINT32)lparam;
    m_handle = (unsigned int)confHandle;
    CHECK_POINTER_RETURN(wparam, 0L);
    TSDK_S_CONF_STATUS_INFO* notifyInfo = (TSDK_S_CONF_STATUS_INFO*)wparam;
    TSDK_S_ATTENDEE* participants = notifyInfo->attendee_list;

    /* Conferecne lock status */
    if (notifyInfo->is_all_mute)
    {
        m_bt_mute.SetWindowText(_T("Unmute"));
    }
    else
    {
        m_bt_mute.SetWindowText(_T("Mute"));
    }

    /* Update participant */
    for (unsigned int i = 0; i< notifyInfo->attendee_num; i++)
    {
        if (participants)
        {
            CString cstrNum = CTools::UTF2UNICODE(participants->base_info.number);
            CString cstrStatus = CTools::UTF2UNICODE(GetUserStatus(participants->status_info.state));
            int j = -1;
            if (!FindColum(cstrNum, COL_DATACONFMEM_NUMBER, j))
            {
                int iSize = m_confmemblist.GetItemCount();
                m_confmemblist.InsertItem(iSize, _T(""));
                j = iSize;
            }

            m_confmemblist.SetItemText(j, COL_DATACONFMEM_NAME, CTools::UTF2UNICODE(participants->base_info.display_name));
            m_confmemblist.SetItemText(j, COL_DATACONFMEM_NUMBER, cstrNum);
            m_confmemblist.SetItemText(j, COL_DATACONFMEM_STATUS, cstrStatus);

            /*present*/
            if (participants->status_info.is_present &&  participants->status_info.is_self)
            {
                ispresenter = true;
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

    UpdateUI();
    free(notifyInfo->attendee_list);
    notifyInfo->attendee_list = NULL;
    delete (notifyInfo);
    return 0L;
}

LRESULT CDemoDataMeetingDlg::OnConfPresenterChange(WPARAM wparam, LPARAM lparam)
{
    MessageBox(_T("You are presenter!"));
    return 0L;
}

LRESULT CDemoDataMeetingDlg::OnConfAddresserUpdate(WPARAM wparam, LPARAM lparam)
{
	TSDK_S_CONF_SPEAKER_INFO* notifyInfo = (TSDK_S_CONF_SPEAKER_INFO*)wparam;
	CHECK_POINTER_RETURN(notifyInfo, -1L);
	unsigned int number = notifyInfo->speaker_num;
    for (unsigned int i = 0; i < number; i++)
    {
        std::string strSpeakerNum = notifyInfo->speakers[i].base_info.number;
        m_conf_speaker.SetWindowText(CTools::UTF2UNICODE(strSpeakerNum));
    }
    
	delete(notifyInfo);
	return 0L;
}

std::string CDemoDataMeetingDlg::GetUserStatus(TSDK_E_CONF_PARTICIPANT_STATUS status)
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

void CDemoDataMeetingDlg::UpdateUI()
{
    CHECK_POINTER(m_appshareDlg);

    if (ispresenter || ischairman)
    {
        m_appshareDlg->updateShareDlg(true);
    }
    else
    {
        m_appshareDlg->updateShareDlg(false);
    }

    if (!ischairman)
    {
        m_bt_add.EnableWindow(FALSE);
        m_bt_mute.EnableWindow(FALSE);
    }
}

void CDemoDataMeetingDlg::BindVideoWindow()
{
	HWND localVideo = m_static_local.GetSafeHwnd();
	HWND attendeeVideo1 = m_static_present.GetSafeHwnd();
	(void)service_set_video_window(m_callID, (unsigned int)localVideo, (unsigned int)attendeeVideo1);
}
