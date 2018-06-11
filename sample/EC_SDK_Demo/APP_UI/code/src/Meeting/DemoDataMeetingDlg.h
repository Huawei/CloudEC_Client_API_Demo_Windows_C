//
//  DemoDataMeetingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include <string>
#include "afxcmn.h"
#include "DemoDataConfAppShareDlg.h"

#define DATACONF_DLG_NUM  1

// CDemoDataMeetingDlg Dialog
class CDemoDataMeetingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDemoDataMeetingDlg)

public:
	CDemoDataMeetingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDemoDataMeetingDlg();


// Dialog Data
	enum { IDD = IDD_DATA_CONF_CTRL };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();

private:
	bool ischairman;
	bool ispresenter;
	unsigned int isallmute;
	unsigned int userid;
	unsigned int m_callID;
	unsigned int m_confID;
	unsigned int m_handle;
	CStatic m_st_status;
	CListCtrl m_confmemblist;
	CButton m_bt_right;
	CButton m_bt_mute;
    CButton m_bt_lock;
	CButton m_bt_add;
	CStatic m_static_present;
	CStatic m_static_local;
	CTabCtrl m_dataconf_tab;
    CEdit m_conf_speaker;
	CDemoDataConfAppShareDlg* m_appshareDlg;

	CDialog* pDlg[DATACONF_DLG_NUM];
	int m_Tab_CurSel;
public:
	void SetSubDlgPosion( CRect rect, int index );
	void SetChairman(bool chairman){ischairman = chairman;};
    void SetPresenter(bool bIsPresenter) { ispresenter = bIsPresenter; };
	bool GetChairman(void){return ischairman;};
	void SetUserId(unsigned int id){userid = id;};
	void SetCallID(unsigned int callid){m_callID = callid;};
    void SetConfHandle(unsigned int confHandle) { m_handle = confHandle; };
	void SetConfId(unsigned int confid){m_confID = confid;};
	void InitUI();
    void UpdateUI();
	void OnClickListMemMenu(UINT nID);
	void BindVideoWindow();
	BOOL FindColum(const CString& cstrKey,int iColnum,int& iLine);
	BOOL FindColumByUserID(unsigned int& id,int& iLine);
    std::string GetUserStatus(TSDK_E_CONF_PARTICIPANT_STATUS status);

public:
	////UI function////
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtAllmute();
    afx_msg void OnBnClickedBtLock();
    afx_msg void OnBnClickedBtAdd();
    afx_msg void OnBnClickedBtApply();
    afx_msg void OnBnClickedBtRelease();
    afx_msg void OnBnClickedBtHandup();
    afx_msg void OnBnClickedBtConfMode();
	afx_msg void OnNMClickListMember(NMHDR *pNMHDR, LRESULT *pResult);
	
	//message handle function
	afx_msg LRESULT OnDataConfeEnd(WPARAM,LPARAM);
	afx_msg LRESULT OnShareSession(WPARAM,LPARAM);
	afx_msg LRESULT OnShareState(WPARAM,LPARAM);
	afx_msg LRESULT OnDataConfASUpdateScreen(WPARAM,LPARAM);
    afx_msg LRESULT OnConfInfoAndStatusUpdate(WPARAM, LPARAM);
    afx_msg LRESULT OnConfPresenterChange(WPARAM, LPARAM);
	afx_msg LRESULT OnConfAddresserUpdate(WPARAM wparam, LPARAM lparam);
};
