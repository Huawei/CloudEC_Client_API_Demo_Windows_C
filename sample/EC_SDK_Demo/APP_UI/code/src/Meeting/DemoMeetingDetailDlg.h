//
//  DemoMeetingDetailDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <vector>
#include "DemoMeetingJoinDlg.h"

// MeetingDetailDlg dialog

class CDemoMeetingDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDemoMeetingDetailDlg)

public:
	CDemoMeetingDetailDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDemoMeetingDetailDlg();

// dialog数据
	enum { IDD = IDD_CONF_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	/*afx_msg LRESULT OnShowMeetingDetail(WPARAM,LPARAM);*/
	DECLARE_MESSAGE_MAP()

public:	
	//CStatic控件
	CStatic m_stcConfTopic;     //会议主题
	CStatic m_stcConfStatus;    //会议状态
	CStatic m_stcStartTime;     //会议开始时间
	CStatic m_stcEndTime;       //会议结束时间
	CStatic m_stcHostPwd;       //主持人密码
	CStatic m_stcAttendPwd;     //与会者密码
	CStatic m_stcConfHostName;  //主持人
	CStatic m_stcMeetingType;   //会议类型
	CStatic m_stcAccessNum;     //会议接入码
	CStatic m_stcConfID;        //会议号码
	CStatic m_stcSelfNum;       //自己的号码，默认显示sip号码，入会时需要短号码

	//Edit控件
	CEdit m_edtConfTopic;    
	CEdit m_edtConfStatus;
	CEdit m_edtStartTime;
	CEdit m_edtEndTime;
	CEdit m_edtHostPwd; 
	CEdit m_edtAttendPwd; 
	CEdit m_edtConfHostName; 
	CEdit m_edtMeetingType; 
	CEdit m_edtAccessNum;   
	CEdit m_edtConfID;   
	CEdit m_edtSelfNum;

	afx_msg void OnClose();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonJoinConf();
};
