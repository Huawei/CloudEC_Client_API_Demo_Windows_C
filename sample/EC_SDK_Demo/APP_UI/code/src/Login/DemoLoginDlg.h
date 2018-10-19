//
//  DemoLoginDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "afxwin.h"
#include <string>
#include "DemoLoginSettingDlg.h"
#include "DemoLoginJoinConfDlg.h"
#include "DemoCustomMessage.h"
#include "DemoCommonTools.h"
#include "DemoApp.h"
#include "DemoMainDlg.h"
#include "tsdk_login_def.h"
using namespace std;


// CDemoLoginDlg dialog
class CDemoLoginDlg : public CDialogEx
{
    // Construction
public:
    CDemoLoginDlg(CWnd* pParent = NULL);	// standard constructor
    virtual BOOL OnInitDialog();

    // Dialog Data
    enum { IDD = IDD_LOGIN };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

    DECLARE_MESSAGE_MAP()

    // Implementation
protected:
    HICON m_hIcon;

public:
    // Generated message map functions
    bool GetLoginFlag() { return m_bLoginFlag; }
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg void OnBnClickedButtonLogin();
    afx_msg void OnBnClickedButtonLoginSetting();
    afx_msg void OnBnClickedButtonLoginJoinConf();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg LRESULT OnLoginAuthResult(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnLoginResult(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnLoginTokenRefreshFailed(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnSaveSelfInfo(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnLoginGetTempUserResult(WPARAM wParam, LPARAM lParam);
private:
    int Login();
    bool m_bLoginFlag;

public:
    CEdit m_EditAccount;
    CEdit m_EditPwd;
    CString m_Account;
    CString m_Password;
    CString m_ServerAdress;
    unsigned short m_ServerPort;
    CDemoLoginSettingDlg *m_pLoginSetting;
    CDemoLoginJoinConfDlg *m_pLoginJoinConf;
};
