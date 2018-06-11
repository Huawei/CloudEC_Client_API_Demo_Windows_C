//
//  DemoCallTransferDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoCallTransferDlg.h"
#include "DemoCommonTools.h"


// CDemoCallTransferDlg dialog

IMPLEMENT_DYNAMIC(CDemoCallTransferDlg, CDialogEx)

CDemoCallTransferDlg::CDemoCallTransferDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoCallTransferDlg::IDD, pParent)
{

}

CDemoCallTransferDlg::~CDemoCallTransferDlg()
{
}

void CDemoCallTransferDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_TRANSFER_NUM, m_edit_number);
}


BEGIN_MESSAGE_MAP(CDemoCallTransferDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDemoCallTransferDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDemoCallTransferDlg message handlers
void CDemoCallTransferDlg::OnBnClickedOk()
{
    CString strnumber;
    m_edit_number.GetWindowText(strnumber);
    m_number = CTools::UNICODE2UTF(strnumber);
    CDialogEx::OnOK();
}
