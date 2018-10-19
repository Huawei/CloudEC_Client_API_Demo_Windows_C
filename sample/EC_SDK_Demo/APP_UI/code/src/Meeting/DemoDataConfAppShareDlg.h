//
//  DemoDataConfAppShareDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "DemoShareStatic.h"
#include "service_conf_interface.h"


// CDemoDataConfAppShareDlg Dialog

class CDemoDataConfAppShareDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoDataConfAppShareDlg)

public:
    CDemoDataConfAppShareDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDemoDataConfAppShareDlg();

    // Dialog Data
    enum { IDD = IDD_DATA_CONF_SCREEN_APP };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

private:
    bool ischairman;
    bool ispresenter;
    unsigned int m_handle;
    unsigned int m_callID;
    CShareStatic m_stcDeskTop;
    CListBox m_list_apps;
    CButton m_bt_select;
    CButton m_bt_remove;
    CListBox m_list_selected;
    CButton m_bt_getapps;
    CButton m_bt_share;
    CStatic m_st_status;

public:
    afx_msg LRESULT OnDataConfASUpdateScreen(WPARAM, LPARAM);
    afx_msg LRESULT OnShareSession(WPARAM, LPARAM);
    afx_msg LRESULT OnShareState(WPARAM, LPARAM);

    afx_msg void OnBnClickedBtShare();
    
    void SetChairman(bool isChairman) { ischairman = isChairman; };
    void SetPresent(bool isPresent) { ispresenter = isPresent; };
    void OnBnClickedRadio(UINT idCtl);
    void SetBitmapNULL(void);
    void updateShareDlg();
    bool isShareDesktop;
    void setShareType(bool isDesktop);
};
