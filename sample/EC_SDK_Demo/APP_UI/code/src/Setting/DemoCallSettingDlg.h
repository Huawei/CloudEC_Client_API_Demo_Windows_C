//
//  DemoCallSettingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "DemoMediaSettingDlg.h"


// CDemoCallSettingDlg dialog

class CDemoCallSettingDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoCallSettingDlg)

public:
    CDemoCallSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDemoCallSettingDlg();

    // dialog Data
    enum { IDD = IDD_CALLSET_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
public:
    CTreeCtrl m_callsetTree;
    CDemoMediaSettingDlg m_mediaDlg;

    afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
