//
//  DemoRunInfoDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"

// CDemoRunInfoDlg dialog

class CDemoRunInfoDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoRunInfoDlg)

public:
    CDemoRunInfoDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoRunInfoDlg();

    // Dialog Data
    enum { IDD = IDD_RUN_INFO_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_NotifyListCtrl;
    void SetScrollBottom(void) { m_NotifyListCtrl.PostMessage(WM_VSCROLL, SB_BOTTOM); };
    afx_msg void OnClose();
};
