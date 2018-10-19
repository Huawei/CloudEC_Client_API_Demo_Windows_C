//
//  DemoRunInfoDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoRunInfoDlg.h"
#include "afxdialogex.h"


// CDemoRunInfoDlg dialog

IMPLEMENT_DYNAMIC(CDemoRunInfoDlg, CDialogEx)

CDemoRunInfoDlg::CDemoRunInfoDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoRunInfoDlg::IDD, pParent)
{

}

CDemoRunInfoDlg::~CDemoRunInfoDlg()
{
}

void CDemoRunInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_NotifyListCtrl);
}


BEGIN_MESSAGE_MAP(CDemoRunInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CDemoRunInfoDlg message handlers
void CDemoRunInfoDlg::OnClose()
{
    m_NotifyListCtrl.DeleteAllItems();

    CDialogEx::OnClose();
}
