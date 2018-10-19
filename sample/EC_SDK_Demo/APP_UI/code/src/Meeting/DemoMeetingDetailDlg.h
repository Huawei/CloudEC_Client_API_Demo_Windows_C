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
	CDemoMeetingDetailDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDemoMeetingDetailDlg();

// dialog����
	enum { IDD = IDD_CONF_DETAIL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	/*afx_msg LRESULT OnShowMeetingDetail(WPARAM,LPARAM);*/
	DECLARE_MESSAGE_MAP()

public:	
	//CStatic�ؼ�
	CStatic m_stcConfTopic;     //��������
	CStatic m_stcConfStatus;    //����״̬
	CStatic m_stcStartTime;     //���鿪ʼʱ��
	CStatic m_stcEndTime;       //�������ʱ��
	CStatic m_stcHostPwd;       //����������
	CStatic m_stcAttendPwd;     //���������
	CStatic m_stcConfHostName;  //������
	CStatic m_stcMeetingType;   //��������
	CStatic m_stcAccessNum;     //���������
	CStatic m_stcConfID;        //�������
	CStatic m_stcSelfNum;       //�Լ��ĺ��룬Ĭ����ʾsip���룬���ʱ��Ҫ�̺���

	//Edit�ؼ�
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
