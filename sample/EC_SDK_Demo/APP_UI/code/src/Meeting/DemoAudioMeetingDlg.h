//
//  DemoAudioMeetingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "afxwin.h"
#include "vector"
#include "string"
#include "DemoData.h"
#include "DemoVideoDlg.h"


// CDemoAudioMeetingDlg dialog
class CDemoAudioMeetingDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoAudioMeetingDlg)

public:
    CDemoAudioMeetingDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDemoAudioMeetingDlg();

    // Dialog Data
    enum { IDD = IDD_AUDIO_CONF };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
protected:
    virtual BOOL OnInitDialog();

public:
    CListCtrl m_listMember;
    CButton m_bt_Mute;
    CButton m_bt_Lock;
    CButton m_bt_Add;
    CButton m_bt_Dtmf;
    CButton m_bt_DataConf;
    CButton m_bt_Handup;
    CButton m_bt_Apply;
    CButton m_bt_Release;
    CButton m_bt_End_Conf;
    CButton m_bt_Leave_Conf;
    CComboBox m_cbxVideoConfMode;
    CEdit m_edit_chairman_pwd;

    bool ischairman;
    bool ispresenter;
    unsigned int m_confID;
    unsigned int m_callID;
    unsigned int m_handle;
    unsigned int m_confType;
    CStatic m_static_subject;

public:
    void SetCallID(unsigned int callid) { m_callID = callid; };
    void SetConfId(unsigned int confid) { m_confID = confid; };
    void SetConfHandle(unsigned int handle) { m_handle = handle; };
    BOOL FindColum(const CString& cstrKey, int iColnum, int& iFind);
    void GetAttendes(std::vector<CString> &_member);
    void CloseDlg();
    std::string GetUserStatus(TSDK_E_CONF_PARTICIPANT_STATUS status);
    void UpdateAudioConfButtonStatus();
    unsigned int GetConfID(void) { return m_confID; };
public:
    afx_msg void OnBnClickedBtAddMember();
    afx_msg void OnBnClickedBtMute();
    afx_msg void OnBnClickedBtLock();
    afx_msg void OnBnClickedBtHandUp();
    afx_msg void OnBnClickedBtDataconf();
    afx_msg void OnBnClickedBtApplyChairman();
    afx_msg void OnBnClickedBtReleaseChairman();
    afx_msg void OnBnClickedBtDtmf();
    afx_msg void OnBnClickedBtEndConf();
    afx_msg void OnBnClickedBtLeaveConf();
    afx_msg void OnCbnSelchangeComboSetConfMode();
    afx_msg void OnNMRClickMemberList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnClickListMemMenuItem(UINT nID);

    afx_msg LRESULT OnConfOperationResult(WPARAM, LPARAM);
    afx_msg LRESULT OnConfSpeakerUpdate(WPARAM, LPARAM);
    afx_msg LRESULT OnConfInfoAndStatusUpdate(WPARAM, LPARAM);


    afx_msg LRESULT OnConfUiPluginClickLeaveConf(WPARAM wparam, LPARAM);
    afx_msg LRESULT OnConfUiPluginClickEndConf(WPARAM wparam, LPARAM);
    afx_msg LRESULT OnConfUiPluginClickStartShare(WPARAM wparam, LPARAM);
    

};
