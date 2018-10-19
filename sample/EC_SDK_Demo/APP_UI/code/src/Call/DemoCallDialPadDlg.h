//
//  DemoCallDialPadDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include <string>

// CDemoCallDialPadDlg dialog

class CDemoCallDialPadDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoCallDialPadDlg)

public:
    CDemoCallDialPadDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoCallDialPadDlg();

    // Dialog Data
    enum { IDD = IDD_CALL_DIAL_PAD_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
public:
    //message handle function
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButton6();
    afx_msg void OnBnClickedButton7();
    afx_msg void OnBnClickedButton8();
    afx_msg void OnBnClickedButton9();
    afx_msg void OnBnClickedButton0();
    afx_msg void OnBnClickedButtonStar();
    afx_msg void OnBnClickedButtonPound();
    afx_msg void OnBnClickedButtonAudio();
    afx_msg void OnBnClickedButtonVideo();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnBnClickedButtonPlus();

    void StartCall(std::string sipnumber, BOOL isVideo);

protected:
    CEdit m_PhoneNumber;
    CString m_PhoneString;
    CFont font;
    unsigned int m_callid;
};
