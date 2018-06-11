//
//  DemoMainDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "DemoCallDialPadDlg.h"
#include "DemoMeetingDlg.h"
#include "DemoData.h"
#include "DemoCustomMessage.h"
#include "DemoImageStatic.h"
#include "DemoSettingDlg.h"
#include "DemoVideoMeetingDlg.h"
#include "DemoDataMeetingDlg.h"

const int NUM = 2;

struct  MyMsgParam
{
    unsigned int ulParam1;
    unsigned int ulParam2;
    void *pData;
};

// CDemoMainDlg dialog

class CDemoMainDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoMainDlg)

public:
    CDemoMainDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoMainDlg();

    // Dialog Data
    enum { IDD = IDD_MAIN_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnTcnSelchangeTabFunction(NMHDR *pNMHDR, LRESULT *pResult);
    /*afx_msg void OnBnClickedButtonEntaddr();*/
    afx_msg void OnBnClickedBtSysmenu();
    afx_msg void OnClickMainMenuItem(UINT nID);

    //call message handle function
    afx_msg LRESULT OnForceLogout(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnStartCall(WPARAM, LPARAM);
    afx_msg LRESULT OnCallEnd(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnConnected(WPARAM wParam, LPARAM);
    afx_msg LRESULT OnCallIncoming(WPARAM, LPARAM);
    afx_msg LRESULT OnCallAddVideo(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnCallOpenVideo(WPARAM wParam, LPARAM lparam);
    afx_msg LRESULT OnCallCloseVideo(WPARAM wParam, LPARAM lparam);
    afx_msg LRESULT OnCallRefuseOpenVideo(WPARAM wParam, LPARAM lparam);
    afx_msg LRESULT OnJoinConf(WPARAM wParam, LPARAM lparam);
    afx_msg LRESULT OnConfEnd(WPARAM, LPARAM);
    afx_msg LRESULT OnConfInComming(WPARAM, LPARAM);
    afx_msg LRESULT OnGetDataConfParamResult(WPARAM, LPARAM);
    afx_msg LRESULT OnJoinDataConfResult(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnCloseConfDlg(WPARAM, LPARAM);
    afx_msg LRESULT OnCloseDataConfDlg(WPARAM, LPARAM);
	afx_msg LRESULT OnTransToConfResult(WPARAM wparam, LPARAM lparam);


    CDemoAudioMeetingDlg* GetDemoAudioMeetingDlg() { return m_audioConfDlg; }
    CDemoVideoMeetingDlg* GetDemoVideoMeetingDlg() { return m_videoConfDlg; }
    CDemoDataMeetingDlg* GetDemoDataMeetingDlg() { return m_dataConfDlg; }
    CDemoMeetingDlg* GetDemoMeetingDlg() { return &m_MeetingDlg; }

    void SetConfChairman(bool ischairman) { m_isConfChairman = ischairman; };
    void InitialSubDlgPositon();
    void SetSubDlgPosion(CRect rect, int index);
    void Logout(void);
    void ShowSetDlg();

    CDialog* m_Dlg[NUM];
    int m_CurSelTab;

    CTabCtrl m_TabItem;
    CDemoCallDialPadDlg m_DialPadDlg;
    CDemoMeetingDlg m_MeetingDlg;
    /*CDemoImContactsDlg m_ContactDlg;
    CDemoImGroupDlg m_GroupDlg;
    CDemoImHistoryDlg m_HistoryDlg;*/
    /*CEntAddrDlg m_entAddrDlg;*/
    CDemoSettingDlg* m_settingDlg;

    CButton m_btnSysMenu;
    CImageStatic m_MyPhoto;
    CStatic m_MyName;
    CStatic m_MyNumber;

private:
    CDemoAudioMeetingDlg* m_audioConfDlg;
    CDemoVideoMeetingDlg* m_videoConfDlg;
    CDemoDataMeetingDlg* m_dataConfDlg;

    bool m_isConfChairman;

protected:
    unsigned int m_confHandle;
	unsigned int m_callId;
};
