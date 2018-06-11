//
//  DemoMeetingAddMemDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>

// CDemoMeetingAddMemDlg dialog

class CDemoMeetingAddMemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDemoMeetingAddMemDlg)

public:
    CDemoMeetingAddMemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDemoMeetingAddMemDlg();

// dialog Data
	enum { IDD = IDD_MEETTING_ADD_MEMBER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

public:	
    //static �ؼ�
	CStatic m_stcTopic; 

    //Edit �ؼ�
	CEdit m_edtAddMember;    

    CString addMemSipNum;
	
protected:
    CFont font;

public:
	virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedAdd();
    afx_msg void OnClose();
};
