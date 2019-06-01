//
//  DemoCallCtrlDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "DemoData.h"
#include "DemoVideoDlg.h"
// CDemoCallCtrlDlg dialog

class CDemoCallCtrlDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoCallCtrlDlg)

public:
    CDemoCallCtrlDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoCallCtrlDlg();

    // Dialog Data
    enum { IDD = IDD_CALL_CTRL_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnBnClickedButtonDtmfPad();
    afx_msg void OnBnClickedBtTransfer();
    afx_msg void OnBnClickedBtHold();
    afx_msg void OnBnClickedBtMuteMic();
    afx_msg void OnBnClickedBtHangup();
    afx_msg void OnClickedBtTransferToConf();
    afx_msg void OnBnClickedBtAddVideo();
    afx_msg void OnClose();

public:
    CButton m_bt_dtmf;
    CButton m_bt_transfer;
    CButton m_bt_hold;
    CButton m_bt_muteMic;
    CButton m_bt_hangup;
    CButton m_bt_addVideo;
    CButton m_bt_conference;
    CALLSTATUS m_state;
    CStatic m_stcCalling;
    CStatic m_peerName;
    CStatic m_peerNum;

private:
    std::string m_sipnumber;
    unsigned int m_CallID;
    CALL_DLG_TYPE m_DlgType;
    std::string m_calleeNum;
public:
    void SetSIPnumber(std::string strSipnumber) { m_sipnumber = strSipnumber; };
    std::string GetSIPnumber(void) { return m_sipnumber; };
    void SetCallID(unsigned int callid) { m_CallID = callid; };
    unsigned int GetCallID(void) { return m_CallID; };
    void SetCallState(CALLSTATUS istate);
    bool CheckStatusReturn(CALLSTATUS status) { return m_state == status; };
    void ChangeDlgType(CALL_DLG_TYPE& type);
    void SetCallDlgtype(CALL_DLG_TYPE dlgtype) { m_DlgType = dlgtype; };
    void AcceptCall(unsigned int isvideo);
	
    //message handle function
    LRESULT OnStartCall(WPARAM wparam, LPARAM lparam);
    LRESULT OnCallEnd(WPARAM wparam, LPARAM lparam);
    LRESULT OnConnected(WPARAM wParam, LPARAM lparam);
    LRESULT OnAcceptAudioCall(WPARAM wParam, LPARAM lparam);
    LRESULT OnAcceptVideoCall(WPARAM wParam, LPARAM lparam);
    LRESULT OnAddVideo(WPARAM wParam, LPARAM lparam);
    LRESULT OnCallModify(WPARAM wParam, LPARAM lparam);
    LRESULT OnHoldSucess(WPARAM wParam, LPARAM lparam);
    LRESULT OnUnHoldSucess(WPARAM wParam, LPARAM lparam);

    LRESULT OnUiPluginClickHangupCall(WPARAM, LPARAM);
};
