//
//  DemoMeetingJoinDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"

class CConnectDlg : public CDialog
{
    DECLARE_DYNAMIC(CConnectDlg)

public:
    CConnectDlg(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CConnectDlg();

    // dialog����
    enum { IDD = IDD_CONF_CONNECT_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

public:
    CString  m_confJoinId;
    CString  m_confJoinNum;
    CString  m_confJoinPwd;
public:
    afx_msg void OnBnClickedOk();
};
