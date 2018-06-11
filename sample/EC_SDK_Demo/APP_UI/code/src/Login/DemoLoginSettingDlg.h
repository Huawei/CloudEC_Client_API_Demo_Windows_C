//
//  CDemoLoginSettingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"

// CDemoLoginSettingDlg dialog

class CDemoLoginSettingDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoLoginSettingDlg)

public:
    CDemoLoginSettingDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoLoginSettingDlg();
    virtual BOOL OnInitDialog();

    // Dialog Data
    enum { IDD = IDD_LOGIN_SETTING };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    void SaveServer();

public:
    CEdit m_editServerAddress;
    CEdit m_editServerPort;
    CString m_strServerAddress;
    CString m_strServerPort;
};
