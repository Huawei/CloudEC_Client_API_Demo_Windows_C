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
    CDemoMeetingAddMemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDemoMeetingAddMemDlg();

// dialog Data
	enum { IDD = IDD_MEETTING_ADD_MEMBER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:	
    //static 控件
	CStatic m_stcTopic; 

    //Edit 控件
	CEdit m_edtAddMember;    

    CString addMemSipNum;
	
protected:
    CFont font;

public:
	virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedAdd();
    afx_msg void OnClose();
};
