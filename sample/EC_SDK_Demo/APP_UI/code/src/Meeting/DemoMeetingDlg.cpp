//
//  DemoMeetingDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoMeetingDlg.h"
#include "DemoCallCtrlDlg.h"
#include "DemoData.h"
#include "DemoCommonTools.h"
#include "DemoCallDlgManager.h"
#include "service_conf_interface.h"
#include "service_tools.h"
#include "service_call_interface.h"
#include "service_os_adapt.h"

MAP_CONFINFO g_mapConfInfo;
extern CString g_loginAccount;
extern CString g_sipNumber;
extern bool g_bIsJoinConf;
extern CString g_shortNumber;

// CDemoMeetingDlg dialog

IMPLEMENT_DYNAMIC(CDemoMeetingDlg, CDialogEx)

CDemoMeetingDlg::CDemoMeetingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoMeetingDlg::IDD, pParent)
{
    m_pConfConnectDlg = NULL;
    m_pConfCreateDlg = NULL;
    m_pConfDetailDlg = NULL;
}

CDemoMeetingDlg::~CDemoMeetingDlg()
{
}

void CDemoMeetingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_MEETINGLIST, m_treeMeetingList);
}


BEGIN_MESSAGE_MAP(CDemoMeetingDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BT_GET_CONFLIST, &CDemoMeetingDlg::OnBnClickedGetConflist)
    ON_BN_CLICKED(IDC_BT_CREATE_CONF, &CDemoMeetingDlg::OnBnClickedCreateConf)
    ON_BN_CLICKED(IDC_BT_JOIN_CONF, &CDemoMeetingDlg::OnBnClickedJoinConf)
    ON_NOTIFY(NM_DBLCLK, IDC_TREE_MEETINGLIST, &CDemoMeetingDlg::OnNMDblclkTreeMeetingList)
    ON_NOTIFY(NM_RCLICK, IDC_TREE_MEETINGLIST, &CDemoMeetingDlg::OnNMRClickTreeMeetingList)
    ON_COMMAND_RANGE(ID_CONF_JOIN_MENU, ID_CONF_DETAIL_MENU, &CDemoMeetingDlg::OnClickMeetingMenuItem)
    ON_MESSAGE(WM_CONF_CTRL_GET_CONF_LIST_RESULT, &CDemoMeetingDlg::OnGetConfList)
    ON_MESSAGE(WM_CONF_CTRL_GET_CONF_INFO_RESULT, &CDemoMeetingDlg::OnGetConfDetail)
END_MESSAGE_MAP()


// CDemoMeetingDlg message handlers
BOOL CDemoMeetingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    if (NULL == m_pConfConnectDlg)
    {
        m_pConfConnectDlg = new CConnectDlg(this);
        if (!::IsWindow(m_pConfConnectDlg->GetSafeHwnd()))
        {
            (void)m_pConfConnectDlg->Create(IDD_CONF_CONNECT_DIALOG);
        }
    }

    if (NULL == m_pConfDetailDlg)
    {
        m_pConfDetailDlg = new CDemoMeetingDetailDlg(this);
        if (!::IsWindow(m_pConfDetailDlg->GetSafeHwnd()))
        {
            (void)m_pConfDetailDlg->Create(IDD_CONF_DETAIL_DLG);
        }
    }

    if (NULL == m_pConfCreateDlg)
    {
        m_pConfCreateDlg = new CDemoMeetingCreateDlg(this);
        if (!::IsWindow(m_pConfCreateDlg->GetSafeHwnd()))
        {
            (void)m_pConfCreateDlg->Create(IDD_CONF_CREATE_DLG);
        }
    }

    return TRUE;
}

void CDemoMeetingDlg::OnBnClickedGetConflist()
{
    (void)service_conf_get_list();
    m_treeMeetingList.DeleteAllItems();
    g_mapConfInfo.clear();
}


void CDemoMeetingDlg::OnBnClickedCreateConf()
{
    if (NULL == m_pConfCreateDlg)
    {
        m_pConfCreateDlg = new CDemoMeetingCreateDlg(this);
        if (!::IsWindow(m_pConfCreateDlg->GetSafeHwnd()))
        {
            (void)m_pConfCreateDlg->Create(IDD_CONF_CREATE_DLG);
        }
    }
    m_pConfCreateDlg->InitAllConrol();
    m_pConfCreateDlg->ShowWindow(SW_SHOW);
}


void CDemoMeetingDlg::OnBnClickedJoinConf()
{
    if (NULL == m_pConfConnectDlg)
    {
        m_pConfConnectDlg = new CConnectDlg(this);
        if (!::IsWindow(m_pConfConnectDlg->GetSafeHwnd()))
        {
            (void)m_pConfConnectDlg->Create(IDD_CONF_CONNECT_DIALOG);
        }
    }
    else
    {
        m_pConfConnectDlg->m_confJoinId = _T("");
        m_pConfConnectDlg->m_confJoinNum = _T("");
        m_pConfConnectDlg->m_confJoinPwd = _T("");
        m_pConfConnectDlg->UpdateData(FALSE);
        m_pConfConnectDlg->ShowWindow(SW_SHOW);
    }
}

void CDemoMeetingDlg::OnNMDblclkTreeMeetingList(NMHDR *pNMHDR, LRESULT *pResult)
{

}

void CDemoMeetingDlg::OnNMRClickTreeMeetingList(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;
    CPoint pt, pmenu;
    unsigned int confId;
    ::GetCursorPos(&pt);
    ::GetCursorPos(&pmenu);
    m_treeMeetingList.ScreenToClient(&pt);

    UINT uFlag = 0;
    HTREEITEM hSelectedItem = m_treeMeetingList.HitTest(pt, &uFlag);
    if (NULL == hSelectedItem || !(TVHT_ONITEM & uFlag))
    {
        return;
    }

    m_treeMeetingList.SelectItem(hSelectedItem);

    CMenu menu;
    menu.CreatePopupMenu();
    HTREEITEM item = m_treeMeetingList.GetSelectedItem();
    confId = (unsigned int)m_treeMeetingList.GetItemData(item);

    menu.AppendMenu(MF_STRING, ID_CONF_DETAIL_MENU, _T("Conf Detail"));
    menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);
}

void CDemoMeetingDlg::OnClickMeetingMenuItem(UINT nID)
{
    HTREEITEM item = m_treeMeetingList.GetSelectedItem();
    unsigned int confId = 0;
    if (NULL != item)
    {
        confId = (unsigned int)m_treeMeetingList.GetItemData(item);
    }

    TSDK_S_CONF_BASE_INFO confInfo;
    service_memset_s(&confInfo, sizeof(confInfo), 0, sizeof(confInfo));
    confInfo = g_mapConfInfo[(long long)confId];

    switch (nID)
    {
    case ID_CONF_DETAIL_MENU:
    {
        ////查看会议详情
		string strConfId;
		strConfId = CTools::num2str((int)confId);
        (void)service_conf_query_conference_detail(const_cast<char*>(strConfId.c_str()));
        break;
    }
    default:
        break;
    }
}

void CDemoMeetingDlg::ShowMeetingDetail(TSDK_S_CONF_DETAIL_INFO* confDetail)
{
    if (NULL != m_pConfDetailDlg)
    {
        m_pConfDetailDlg->m_stcConfTopic.SetWindowText(_T("Conf Subject"));
        m_pConfDetailDlg->m_stcConfStatus.SetWindowText(_T("Conf Status"));
        m_pConfDetailDlg->m_stcStartTime.SetWindowText(_T("Start Time"));
        m_pConfDetailDlg->m_stcEndTime.SetWindowText(_T("End Time"));
        m_pConfDetailDlg->m_stcHostPwd.SetWindowText(_T("Host Pwd"));
        m_pConfDetailDlg->m_stcAttendPwd.SetWindowText(_T("Attend Pwd"));
        m_pConfDetailDlg->m_stcConfHostName.SetWindowText(_T("Conf Host Name"));
        m_pConfDetailDlg->m_stcMeetingType.SetWindowText(_T("Conf Type"));
        m_pConfDetailDlg->m_stcAccessNum.SetWindowText(_T("Access Num"));
        m_pConfDetailDlg->m_stcConfID.SetWindowText(_T("Conf ID"));
        m_pConfDetailDlg->m_stcSelfNum.SetWindowText(_T("Self Num"));

        m_pConfDetailDlg->m_edtConfTopic.SetWindowText(CTools::UTF2UNICODE(confDetail->conf_info.subject));
        if (TSDK_E_CONF_STATE_SCHEDULE == confDetail->conf_info.conf_state)
        {
            m_pConfDetailDlg->m_edtConfStatus.SetWindowText(_T("Schedule"));
        }
        else if (TSDK_E_CONF_STATE_CREATING == confDetail->conf_info.conf_state)
        {
            m_pConfDetailDlg->m_edtConfStatus.SetWindowText(_T("Creating"));
        }
        else if (TSDK_E_CONF_STATE_GOING == confDetail->conf_info.conf_state)
        {
            m_pConfDetailDlg->m_edtConfStatus.SetWindowText(_T("Going"));
        }
        else if (TSDK_E_CONF_STATE_DESTROYED == confDetail->conf_info.conf_state)
        {
            m_pConfDetailDlg->m_edtConfStatus.SetWindowText(_T("Destroyed"));
        }

        m_pConfDetailDlg->m_edtStartTime.SetWindowText(CTools::UTCTime2LocalTime(confDetail->conf_info.start_time));
        m_pConfDetailDlg->m_edtEndTime.SetWindowText(CTools::UTCTime2LocalTime(confDetail->conf_info.end_time));
        m_pConfDetailDlg->m_edtHostPwd.SetWindowText(CTools::UTF2UNICODE(confDetail->conf_info.chairman_pwd));
        m_pConfDetailDlg->m_edtAttendPwd.SetWindowText(CTools::UTF2UNICODE(confDetail->conf_info.guest_pwd));
        m_pConfDetailDlg->m_edtConfHostName.SetWindowText(CTools::UTF2UNICODE(confDetail->conf_info.scheduser_name));
        m_pConfDetailDlg->m_edtAccessNum.SetWindowText(CTools::UTF2UNICODE(confDetail->conf_info.access_number));
        m_pConfDetailDlg->m_edtConfID.SetWindowText(CTools::UTF2UNICODE(confDetail->conf_info.conf_id));
        if (TSDK_E_CONF_MEDIA_VOICE == confDetail->conf_info.conf_media_type)
        {
            m_pConfDetailDlg->m_edtMeetingType.SetWindowText(_T("Audio Conf"));
        }
        else if (TSDK_E_CONF_MEDIA_VIDEO == confDetail->conf_info.conf_media_type)
        {
            m_pConfDetailDlg->m_edtMeetingType.SetWindowText(_T("Video Conf"));
        }
        else if (TSDK_E_CONF_MEDIA_VOICE_DATA == confDetail->conf_info.conf_media_type)
        {
            m_pConfDetailDlg->m_edtMeetingType.SetWindowText(_T("Audio+Data Conf"));
        }
        else if (TSDK_E_CONF_MEDIA_VIDEO_DATA == confDetail->conf_info.conf_media_type)
        {
            m_pConfDetailDlg->m_edtMeetingType.SetWindowText(_T("Video+Data Conf"));
        }
        else
        {
            m_pConfDetailDlg->m_edtMeetingType.SetWindowText(_T(""));
        }

        if( _T("") == g_shortNumber)
        {
            m_pConfDetailDlg->m_edtSelfNum.SetWindowText(g_sipNumber);
        }
        else
        {
            m_pConfDetailDlg->m_edtSelfNum.SetWindowText(g_shortNumber);
        }
        
        m_pConfDetailDlg->UpdateData(FALSE);
        m_pConfDetailDlg->ShowWindow(SW_SHOW);
    }
}

LRESULT CDemoMeetingDlg::OnGetConfList(WPARAM wParam, LPARAM lparam)
{
    CHECK_POINTER_RETURN(wParam, -1L);
    unsigned int confnum = (unsigned int)lparam;
    TSDK_S_CONF_BASE_INFO* notifyInfo = (TSDK_S_CONF_BASE_INFO*)wParam;

    for (unsigned int i = 0; i < confnum; i++)
    {
        TSDK_S_CONF_BASE_INFO confInfo;
        service_memset_s(&confInfo, sizeof(confInfo), 0, sizeof(confInfo));
        memcpy_s(&confInfo, sizeof(TSDK_S_CONF_BASE_INFO), &(notifyInfo[i]), sizeof(TSDK_S_CONF_BASE_INFO));
        g_mapConfInfo[(long long)CTools::str2num(notifyInfo[i].conf_id)] = confInfo;
    }

    //插入所有会议列表
    MAP_CONFINFO::iterator itBegin = g_mapConfInfo.begin();
    MAP_CONFINFO::iterator itEnd = g_mapConfInfo.end();
    for (; itBegin != itEnd; itBegin++)
    {
        TSDK_S_CONF_BASE_INFO conf = (TSDK_S_CONF_BASE_INFO)itBegin->second;
        CString strConfSubject = CTools::UTF2UNICODE(conf.subject);
        HTREEITEM item = m_treeMeetingList.InsertItem(strConfSubject, TVI_ROOT);
        CString strConfId = CTools::UTF2UNICODE(conf.conf_id);
        m_treeMeetingList.SetItemData(item, (DWORD)CTools::str2num(CTools::UNICODE2UTF(strConfId)));
        m_treeMeetingList.SetItemImage(item, 2, 2);
    }

    delete notifyInfo;

    return 0L;
}

LRESULT CDemoMeetingDlg::OnGetConfDetail(WPARAM wParam, LPARAM lparam)
{
    CHECK_POINTER_RETURN(wParam, -1L);
    TSDK_S_CONF_DETAIL_INFO* notifyInfo = (TSDK_S_CONF_DETAIL_INFO*)wParam;
    g_mapConfInfo[(long long)CTools::str2num(notifyInfo->conf_info.conf_id)] = notifyInfo->conf_info;

    if (NULL == m_pConfDetailDlg)
    {
        m_pConfDetailDlg = new CDemoMeetingDetailDlg(this);
        if (!::IsWindow(m_pConfDetailDlg->GetSafeHwnd()))
        {
            (void)m_pConfDetailDlg->Create(IDD_CONF_DETAIL_DLG);
        }
    }

    ShowMeetingDetail(notifyInfo);
    return 0L;
}
