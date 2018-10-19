//
//  DemoMeetingAddMemDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoCommonTools.h"
#include "DemoMeetingAddMemDlg.h"


// CDetailDlg dialog
IMPLEMENT_DYNAMIC(CDemoMeetingAddMemDlg, CDialogEx)

CDemoMeetingAddMemDlg::CDemoMeetingAddMemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemoMeetingAddMemDlg::IDD, pParent)
    , addMemSipNum(_T(""))
{

}

CDemoMeetingAddMemDlg::~CDemoMeetingAddMemDlg()
{
}

void CDemoMeetingAddMemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_METTING_ADD_MEMBER_EDIT1, m_edtAddMember);
}

BEGIN_MESSAGE_MAP(CDemoMeetingAddMemDlg, CDialogEx)
	ON_WM_CLOSE()
    ON_BN_CLICKED(IDOK, &CDemoMeetingAddMemDlg::OnBnClickedAdd)
END_MESSAGE_MAP()


// CDetailDlg 消息处理程序

BOOL CDemoMeetingAddMemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_edtAddMember.SetWindowText(_T(""));

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDemoMeetingAddMemDlg::OnClose()
{
	CDialog::OnClose();
}

void CDemoMeetingAddMemDlg::OnBnClickedAdd()
{
    m_edtAddMember.GetWindowText(addMemSipNum);
    CDialogEx::OnOK();
}
