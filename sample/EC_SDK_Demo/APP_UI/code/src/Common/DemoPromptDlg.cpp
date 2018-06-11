//
//  DemoPromptDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoPromptDlg.h"


// CDemoPromptDlg dialog

IMPLEMENT_DYNAMIC(CDemoPromptDlg, CDialogEx)

CDemoPromptDlg::CDemoPromptDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoPromptDlg::IDD, pParent)
{

}

CDemoPromptDlg::~CDemoPromptDlg()
{
}

void CDemoPromptDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_CONTENT, m_content);
}


BEGIN_MESSAGE_MAP(CDemoPromptDlg, CDialogEx)
END_MESSAGE_MAP()


// CDemoRunInfoDlg message handlers
BOOL CDemoPromptDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    font.CreatePointFont(160, _T("ËÎÌו"));
    m_content.SetFont(&font);
    m_content.SetWindowText(strContentText);
    return TRUE;
}

void CDemoPromptDlg::SetTextOfContent(CString strText)
{
    strContentText = strText;
}
