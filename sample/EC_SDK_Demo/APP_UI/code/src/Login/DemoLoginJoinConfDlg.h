//
//  DemoLoginJoinConfDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"

// CDemoLoginJoinConfDlg dialog

class CDemoLoginJoinConfDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoLoginJoinConfDlg)

public:
    CDemoLoginJoinConfDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoLoginJoinConfDlg();
    virtual BOOL OnInitDialog();

    // Dialog Data
    enum { IDD = IDD_LOGIN_JOIN_CONF };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();

public:
    CEdit m_editConfServerAddress;
    CEdit m_editConfServerPort;
    CEdit m_editConfId;
    CEdit m_editJoinPwd;
    CEdit m_editNickname;
    CString m_strConfServerAddress;
    CString m_strConfServerPort;
    CString m_strConfId;
    CString m_strJoinPwd;
    CString m_strNickname;

};
