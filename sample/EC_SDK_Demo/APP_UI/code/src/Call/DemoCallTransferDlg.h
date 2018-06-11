//
//  DemoCallTransferDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include <fstream>

// CDemoCallTransferDlg dialog

class CDemoCallTransferDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoCallTransferDlg)

public:
    CDemoCallTransferDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoCallTransferDlg();

    // Dialog Data
    enum { IDD = IDD_CALL_TRANSFER_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

private:
    CEdit m_edit_number;
    std::string m_number;

public:
    afx_msg void OnBnClickedOk();
    std::string GetNumber() { return m_number; };
};
