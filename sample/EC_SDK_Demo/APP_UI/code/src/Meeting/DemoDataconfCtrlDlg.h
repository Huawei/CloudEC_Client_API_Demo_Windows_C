//
//  DemoDataconfCtrlDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "resource.h"
#include <string>
#include "afxcmn.h"
#include "DemoDataConfAppShareDlg.h"
#include "DemoDocumentsShareDlg.h"

#define  DATACONF_DLG_NUM  2

// CDemoDataconfCtrlDlg dialog

class CDemoDataconfCtrlDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoDataconfCtrlDlg)

public:
    CDemoDataconfCtrlDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoDataconfCtrlDlg();


    // dialog data
    enum { IDD = IDD_DATA_CONF_CTRL};
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
protected:
    virtual BOOL OnInitDialog();

private:
    bool m_isChairman;
    bool m_isPresenter;
    unsigned int m_handle;
    unsigned int m_callID;
    CTabCtrl m_dataconf_tab;
    CDialog* pDlg[DATACONF_DLG_NUM];
    int m_Tab_CurSel;

public:
    void SetSubDlgPosion(CRect rect, int index);
    bool GetChairman(void) { return m_isChairman; };
    void SetChairman(bool isChairman) { m_isChairman = isChairman; };
    void SetPresent(bool isPresent) { m_isPresenter = isPresent; };
    void SetCallID(unsigned int callid) { m_callID = callid; };
    void InitUI();
    
    /*afx_msg void OnNMClickListMember(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtAdd();
    afx_msg void OnBnClickedBtGetpresent();*/
    afx_msg void OnTcnSelchangeDataTab(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg LRESULT OnShareSession(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnShareState(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnDataConfASUpdateScreen(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnDSOpenNew(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnDSPageLoad(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnDSLoaded(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnDataConfDSDrawData(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnDSCurrentPage(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnDSDeleteDoc(WPARAM wparam, LPARAM lparam);
    void updateShareDlg();

public:
    CDemoDataConfAppShareDlg* m_desktopShareDlg;
    CDemoDocumentsShareDlg* m_documentsShareDlg;
};
