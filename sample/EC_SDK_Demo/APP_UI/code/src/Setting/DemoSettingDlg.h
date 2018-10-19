//
//  DemoSettingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"		// 主符号
#include "afxcmn.h"
#include "DemoCallSettingDlg.h"

// CDemoSettingDlg dialog

class CDemoSettingDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoSettingDlg)

public:
    CDemoSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDemoSettingDlg();

    // dialog Data
    enum { IDD = IDD_SETTING_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
private:
    CTabCtrl m_SetTable;
    CDemoCallSettingDlg* m_callsetDlg;
public:
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedOk();
};
