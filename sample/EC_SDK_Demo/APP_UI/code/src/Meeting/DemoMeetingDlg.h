//
//  DemoMeetingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "DemoMeetingJoinDlg.h"
#include "DemoMeetingDetailDlg.h"
#include "DemoMeetingCreateDlg.h"

// CDemoMeetingDlg dialog

class CDemoMeetingDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoMeetingDlg)

public:
    CDemoMeetingDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoMeetingDlg();

    // DialogÊý¾Ý
    enum { IDD = IDD_MEETING_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()

    virtual BOOL OnInitDialog();

public:
    afx_msg void OnBnClickedGetConflist();
    afx_msg void OnBnClickedCreateConf();
    afx_msg void OnBnClickedJoinConf();
    afx_msg void OnNMDblclkTreeMeetingList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMRClickTreeMeetingList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnClickMeetingMenuItem(UINT nID);
    afx_msg LRESULT OnGetConfList(WPARAM wParam, LPARAM lparam);
    afx_msg LRESULT OnGetConfDetail(WPARAM wParam, LPARAM lparam);
    void ShowMeetingDetail(TSDK_S_CONF_DETAIL_INFO* confDetail);

public:
    CConnectDlg *m_pConfConnectDlg;
    CDemoMeetingDetailDlg *m_pConfDetailDlg;
    CDemoMeetingCreateDlg *m_pConfCreateDlg;

private:
    CTreeCtrl m_treeMeetingList;
};
