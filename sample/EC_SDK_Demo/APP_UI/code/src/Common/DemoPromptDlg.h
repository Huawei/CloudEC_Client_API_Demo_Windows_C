//
//  DemoPromptDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"

// CDemoPromptDlg dialog

class CDemoPromptDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoPromptDlg)

public:
    CDemoPromptDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoPromptDlg();
    virtual BOOL OnInitDialog();

    // Dialog Data
    enum { IDD = IDD_PROMPT_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

    CFont font;
public:
    CStatic m_content;
    CButton m_btnAgree;
    CButton m_btnCancel;

    CString strContentText;

    void SetTextOfContent(CString strText);
};
