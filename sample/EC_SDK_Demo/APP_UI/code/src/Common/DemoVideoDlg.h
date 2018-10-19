//
//  DemoVideoDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"

// CDemoPromptDlg dialog

class CDemoVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDemoVideoDlg)

public:
	CDemoVideoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDemoVideoDlg();
	virtual BOOL OnInitDialog();

	// Dialog Data
	enum { IDD = IDD_VIDEO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CStatic m_remoteVideo;
	CStatic m_localVideo;
	CStatic m_title_remote;
	CStatic m_title_local;
    unsigned int m_callID;
    CButton m_bt_video_control;

public:
    void BindVideoWindow();
    void SetCallID(unsigned int callid) { m_callID = callid; };

    afx_msg void OnClickedBtControlVideo();
};
