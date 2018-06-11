//
//  DemoMeetingCreateDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoMeetingCreateDlg.h"
#include "DemoCommonTools.h"
#include "DemoMeetingAddMemDlg.h"
#include "DemoData.h"
#include "service_conf_interface.h"
#include "service_os_adapt.h"

extern CString g_loginAccount;
extern CString g_sipNumber;

// CDemoMeetingCreateDlg dialog
IMPLEMENT_DYNAMIC(CDemoMeetingCreateDlg, CDialogEx)

CDemoMeetingCreateDlg::CDemoMeetingCreateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemoMeetingCreateDlg::IDD, pParent)
{

}

CDemoMeetingCreateDlg::~CDemoMeetingCreateDlg()
{
}

void CDemoMeetingCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TITLE_MEETING_SUBJECT, m_stcMeetingSubject);
	DDX_Control(pDX, IDC_TITLE_START_TIME, m_stcBeginTime);
	DDX_Control(pDX, IDC_TITLE_MEETING_TYPE, m_stcMeetingType);
	DDX_Control(pDX, IDC_TITLE_CREATOR_NUM, m_stcCreatorNum);
	DDX_Control(pDX, IDC_TITLE_MEMBERS_LIST, m_stc_Members);
	DDX_Control(pDX, IDC_EDIT_MEETING_SUBJECT, m_edtMeetingSubject);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN_DATA,m_timeBeginDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN_TIME, m_timeBeginTime);
	DDX_Control(pDX, IDC_COMBO_MEETING_TYPE, m_comMeetingType);
	DDX_Control(pDX, IDC_STATIC_CREATOR_NUM, m_stcCreatorNo);
	DDX_Control(pDX, IDC_LIST_MEETING_MEMBER_LIST, m_meetingMemberList);
    DDX_Control(pDX, IDC_RADIO_BEGIN_NOW, m_radioConfBeginNow);
}

BEGIN_MESSAGE_MAP(CDemoMeetingCreateDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDemoMeetingCreateDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDOK, &CDemoMeetingCreateDlg::OnBnClickedButtonOk)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RADIO_BEGIN_NOW,IDC_RADIO_BEGIN_LATER,&CDemoMeetingCreateDlg::OnBnClickedRadio)
END_MESSAGE_MAP()


// CDemoMeetingCreateDlg message handlers
BOOL CDemoMeetingCreateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
   
	m_comMeetingType.InsertString(0, _T("Video+Data"));
	m_comMeetingType.InsertString(0, _T("Voice+Data"));
	m_comMeetingType.InsertString(0, _T("Video"));
	m_comMeetingType.InsertString(0, _T("Audio"));

    m_meetingMemberList.ModifyStyle(0, LVS_SINGLESEL);
    m_meetingMemberList.InsertColumn(1, _T("Members"), LVCFMT_LEFT, 100);

    InitAllConrol();

	return TRUE;  
}

void CDemoMeetingCreateDlg::InitAllConrol()
{
    //标题为空
    m_edtMeetingSubject.SetWindowText(g_sipNumber + _T("'s conference"));

    //默认显示主席号码
    CString chairmanNum = CTools::GetSipNumber(g_sipNumber);
    m_stcCreatorNo.SetWindowText(chairmanNum);

    //会议开始时间,默认创建即时会议
	CheckRadioButton(IDC_RADIO_BEGIN_NOW,IDC_RADIO_BEGIN_LATER,IDC_RADIO_BEGIN_NOW);

    //默认日期可选
    m_timeBeginDate.EnableWindow(FALSE);
    m_timeBeginTime.EnableWindow(FALSE);

    //会议类型
    m_comMeetingType.SetWindowText(_T("Audio"));

    //与会者列表默认插入主席
    m_meetingMemberList.DeleteAllItems();
    int nRow = m_meetingMemberList.InsertItem(1, chairmanNum);
    m_meetingMemberList.SetItemText(nRow, 1, chairmanNum);

    UpdateData(FALSE);
}

void CDemoMeetingCreateDlg::OnClose()
{
	CDialog::OnClose();
}

void CDemoMeetingCreateDlg::OnBnClickedButtonAdd()
{
    CDemoMeetingAddMemDlg dlg;
    INT_PTR nResponse = dlg.DoModal();

    if (nResponse == IDOK)
    {
        int iSize = m_meetingMemberList.GetItemCount();

        if(dlg.addMemSipNum != "")
        { 
            int nRow = m_meetingMemberList.InsertItem(iSize, dlg.addMemSipNum);
            m_meetingMemberList.SetItemText(nRow, 1, dlg.addMemSipNum);
        }
    }
}

void CDemoMeetingCreateDlg::OnBnClickedButtonOk()
{
    TSDK_S_BOOK_CONF_INFO bookConfInfo = { 0 };

    //与会者个数
    unsigned int iSize = (unsigned int)m_meetingMemberList.GetItemCount();
    bookConfInfo.size = iSize;

    //会议标题
    CString strMeetingSubject;
    m_edtMeetingSubject.GetWindowText(strMeetingSubject);
    CTools::CString2Char(strMeetingSubject, bookConfInfo.subject, TSDK_D_MAX_SUBJECT_LEN);

    //会议群组号，默认空
    strncpy_s(bookConfInfo.group_uri, TSDK_D_MAX_GROUP_URI_LEN + 1, "", TSDK_D_MAX_GROUP_URI_LEN - 1);

    //会议开始时间 //会议类型(立即会议or预约会议)
    int radioState = m_radioConfBeginNow.GetCheck();
    if (radioState)
    {
        bookConfInfo.conf_type = TSDK_E_CONF_INSTANT;
        strncpy_s(bookConfInfo.start_time, TSDK_D_MAX_TIME_FORMATE_LEN + 1, "", TSDK_D_MAX_TIME_FORMATE_LEN - 1);
    }
    else
    {
        bookConfInfo.conf_type = TSDK_E_CONF_RESERVED;
        CString strMeetingStart;
        CString strMeetingStartDate;
        CString strMeetingStartTime;
        m_timeBeginDate.GetWindowText(strMeetingStartDate);
        m_timeBeginTime.GetWindowText(strMeetingStartTime);
        strMeetingStart = strMeetingStartDate +_T(" ")+ strMeetingStartTime;
        strMeetingStart.Replace(_T("/"), _T("-"));
        CTools::CString2Char(strMeetingStart, bookConfInfo.start_time, TSDK_D_MAX_TIME_FORMATE_LEN);
    }

    //会议媒体类型
    CString strConfMediaType;
    m_comMeetingType.GetWindowText(strConfMediaType);
    if (_T("Video+Data") == strConfMediaType)
    {
        bookConfInfo.conf_media_type = TSDK_E_CONF_MEDIA_VIDEO_DATA;
    }
    else if (_T("Voice+Data") == strConfMediaType)
    {
        bookConfInfo.conf_media_type = TSDK_E_CONF_MEDIA_VOICE_DATA;
    }
    else if (_T("Video") == strConfMediaType)
    {
        bookConfInfo.conf_media_type = TSDK_E_CONF_MEDIA_VIDEO;
    }
    else if (_T("Audio") == strConfMediaType)
    {
        bookConfInfo.conf_media_type = TSDK_E_CONF_MEDIA_VOICE;
    }

    //是否自动闭音
    bookConfInfo.is_auto_mute = FALSE;
    
    //与会者列表
    CString strChairmanNum = CTools::GetSipNumber(g_sipNumber);
    
    std::vector<CString> members;
    GetConfMembers(members);
    unsigned int memCount = members.size();
    if (0 == memCount)
    {
        AfxMessageBox(_T("member count is 0"));
        return;
    }
    bookConfInfo.attendee_list = (TSDK_S_ATTENDEE_BASE_INFO*)malloc(memCount*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
    if (NULL == bookConfInfo.attendee_list)
    {
        AfxMessageBox(_T("bookConfInfo.attendee_list is NULL"));
        return;
    }
    (void)service_memset_s(bookConfInfo.attendee_list, memCount*sizeof(TSDK_S_ATTENDEE_BASE_INFO), 0, memCount*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
    TSDK_S_ATTENDEE_BASE_INFO* pTempAttendee = bookConfInfo.attendee_list;
    for (unsigned int i = 0; i < memCount; i++)
    {
        if (pTempAttendee)
        {
            (void)strncpy_s(pTempAttendee->number, TSDK_D_MAX_PARTICIPANTID_LEN + 1, CTools::UNICODE2UTF(members[i]).c_str(), TSDK_D_MAX_PARTICIPANTID_LEN - 1);
            if (members[i] == strChairmanNum)
            {
                pTempAttendee->role = TSDK_E_CONF_ROLE_CHAIRMAN;
            }
            else
            {
                pTempAttendee->role = TSDK_E_CONF_ROLE_ATTENDEE;
            }
        }
        else
        {
            break;
        }

        pTempAttendee++;
    }

    //与会者个数
    bookConfInfo.attendee_num = memCount;


    if (RESULT_SUCCESS != service_conf_book(&bookConfInfo))
    {
        AfxMessageBox(_T("book conf is failed"));
    }
    free(bookConfInfo.attendee_list);
    bookConfInfo.attendee_list = NULL;

    ClearAllControl();
   
    CDialogEx::OnOK();
}

void CDemoMeetingCreateDlg::ClearAllControl()
{
    m_meetingMemberList.DeleteAllItems();
    m_edtMeetingSubject.SetWindowText(_T(""));
    m_comMeetingType.SetWindowText(_T(""));
}

void CDemoMeetingCreateDlg::GetConfMembers(std::vector<CString> &_member)
{
    int iSize = m_meetingMemberList.GetItemCount();
    for (int i = 0; i < iSize; i++)
    {
        CString cstr = m_meetingMemberList.GetItemText(i,0);
        _member.push_back(cstr);
    }
    m_meetingMemberList.DeleteAllItems();
}

void CDemoMeetingCreateDlg::OnBnClickedRadio(UINT idCtl)
{
	if (IDC_RADIO_BEGIN_NOW == idCtl)
	{
		m_timeBeginDate.EnableWindow(FALSE);
		m_timeBeginTime.EnableWindow(FALSE);
	}
	else
	{
		m_timeBeginDate.EnableWindow(TRUE);
		m_timeBeginTime.EnableWindow(TRUE);
	}
}
