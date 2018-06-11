//
//  DemoCallInCommingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "DemoData.h"
#include "DemoCommonTools.h"

// CDemoCallInCommingDlg dialog

class CDemoCallInCommingDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoCallInCommingDlg)

public:
    CDemoCallInCommingDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoCallInCommingDlg();
    virtual BOOL OnInitDialog();

    // Dialog Data
    enum { IDD = IDD_CALL_INCOMMING_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

private:
    int play_handle;
public:
    CEdit m_TelNum;
    CEdit m_Type;
    CEdit m_edit_transferNnmber;
    CButton m_bt_transfer;
    CButton m_bt_videoAccept;
    CButton m_bt_audioAccept;

    BUTTON_TYPE m_buttonType;
    COMMINTCALL_TYPE  m_commingcallType;  /// audio,video and conference//////

    CString m_tel_number;
    unsigned int callid;
    bool istransfe;
    void PlayPhoneRinging();

    void GetInitParam(COMMINTCALL_TYPE callType, std::string tel_number, unsigned int id)
    {
        m_commingcallType = callType;
        m_tel_number = CString(tel_number.c_str());
        callid = id;
    };

    //message handle function
    afx_msg void OnBnClickedReject();
    afx_msg void OnBnClickedAudioAccept();
    afx_msg void OnBnClickedVideoAccept();
    afx_msg void OnBnClickedTransfer();
};
