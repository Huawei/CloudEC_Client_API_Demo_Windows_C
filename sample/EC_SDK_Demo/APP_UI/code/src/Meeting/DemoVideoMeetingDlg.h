//
//  DemoVideoMeetingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "afxwin.h"
#include "vector"
#include "string"
#include "DemoData.h"


// CDemoAudioMeetingDlg dialog
class CDemoVideoMeetingDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoVideoMeetingDlg)

public:
    CDemoVideoMeetingDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDemoVideoMeetingDlg();

    // Dialog数据
    enum { IDD = IDD_VIDEO_CONF };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
protected:
    virtual BOOL OnInitDialog();

protected:
    CListCtrl m_listMember;
    CButton m_bt_AddMember;
    CButton m_bt_Mute;
    CButton m_bt_Lock;
    CButton m_bt_DataConf;
    CButton m_bt_Broadcast;
    CButton m_bt_Model;
    CButton m_bt_Handup;
    CButton m_bt_Apply;
    CButton m_bt_Release;
    CButton m_bt_Dtmf;
    CButton m_bt_MicMute;
    CButton m_bt_Camera;

    CStatic m_static_subject;
    CStatic m_attendeeVideoCtrl1;
    CStatic m_LocalVideoCtrl;

    bool ischairman;
    unsigned int m_confID;
    unsigned int m_callID;
    unsigned int m_handle;
    std::string m_chairmanPwd;

public:
    void SetDlgtype(MettingType videotype);
    void SetChairman(bool chairman) { ischairman = chairman; };
    void SetCallID(unsigned int callid) { m_callID = callid; };
    void SetConfId(unsigned int confid) { m_confID = confid; };
    void SetConfHandle(unsigned int handle) { m_handle = handle; };
    BOOL FindColum(const CString& cstrKey, int iColnum, int& iFind);
    void GetAttendes(std::vector<CString> &_member);
    void CloseDlg();
    void BindVideoWindow();
    std::string GetUserStatus(TSDK_E_CONF_PARTICIPANT_STATUS status);
    unsigned int GetConfID(void) { return m_confID; };
    void UpdateVideoConfButtonStatus();


public:
    afx_msg void OnClose();
    afx_msg void OnNMRClickMemberList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnClickListMemMenuItem(UINT nID);
    afx_msg LRESULT OnConfAddresserUpdate(WPARAM, LPARAM);
    afx_msg LRESULT OnConfInfoAndStatusUpdate(WPARAM, LPARAM);
    afx_msg void OnBnClickedAddMember();
    afx_msg void OnBnClickedButtonVideoConfCamera();
    afx_msg void OnBnClickedButtonVideoConfMicMute();
    afx_msg void OnBnClickedButtonVideoConfDtmf();
    afx_msg void OnBnClickedButtonVideoConfDataconf();
    afx_msg void OnBnClickedButtonVideoConfMute();
    afx_msg void OnBnClickedButtonVideoConfLock();
    afx_msg void OnBnClickedButtonVideoConfApply();
    afx_msg void OnBnClickedButtonVideoConfRelease();
    afx_msg void OnBnClickedButtonVideoConfHandup();
    afx_msg void OnBnClickedButtonVideoConfMode();
};
