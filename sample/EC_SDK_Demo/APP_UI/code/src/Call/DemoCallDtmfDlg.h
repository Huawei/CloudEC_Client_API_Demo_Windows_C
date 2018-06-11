//
//  DemoCallDtmfDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "tsdk_call_def.h"

// CDemoCallDtmfDlg dialog

class CDemoCallDtmfDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoCallDtmfDlg)

public:
    CDemoCallDtmfDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoCallDtmfDlg();

    // Dialog Data
    enum { IDD = IDD_CALL_DTMF_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

public:
    //message handle function
    afx_msg void OnBnClickedDtmfButton1();
    afx_msg void OnBnClickedDtmfButton2();
    afx_msg void OnBnClickedDtmfButton3();
    afx_msg void OnBnClickedDtmfButton4();
    afx_msg void OnBnClickedDtmfButton5();
    afx_msg void OnBnClickedDtmfButton6();
    afx_msg void OnBnClickedDtmfButton7();
    afx_msg void OnBnClickedDtmfButton8();
    afx_msg void OnBnClickedDtmfButton9();
    afx_msg void OnBnClickedDtmfButton0();
    afx_msg void OnBnClickedDtmfButtonStar();
    afx_msg void OnBnClickedDtmfButtonPound();

    //member function
    void SendDTMF(TSDK_E_DTMF_TONE Tone, CString tonepath);
    void ProcessInputNumber(CString number);
    void SetCallid(unsigned int id) { callId = id; };

private:
    CEdit m_edit_number;
    unsigned int callId;
    CString m_apppath;
};
