//
//  DemoMeetingCreateDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h"
#include "DemoData.h"
#include "DemoAudioMeetingDlg.h"
#include <vector>

class CDemoMeetingCreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDemoMeetingCreateDlg)

public:
	CDemoMeetingCreateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDemoMeetingCreateDlg();

	// Dialog数据
	enum { IDD = IDD_MEETING_CREATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	//CStatic control
	CStatic m_stcMeetingSubject;    //会议主题
	CStatic m_stcBeginTime;         //会议开始时间
	CStatic m_stcMeetingType;       //会议类型
	CStatic m_stcCreatorNum;        //与会号码
	CStatic m_stc_Members;          //与会者
	CStatic m_stcCreatorNo;         //创建者号码
	CButton m_bt_addMember;         //添加与会者

	//other control
	CEdit m_edtMeetingSubject;
	CComboBox m_comMeetingType;
	CDateTimeCtrl m_timeBeginDate;
	CDateTimeCtrl m_timeBeginTime;
    CButton m_radioConfBeginNow;

	//List control
	CListCtrl m_meetingMemberList;

    //CString
    std::vector<CString> m_confMember;

public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnClose();
	afx_msg void OnBnClickedRadio(UINT idCtl);

    void GetConfMembers(std::vector<CString> &_member);
    void ClearAllControl();
    void InitAllConrol();
};
