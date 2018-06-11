//
//  DemoCallDialPadDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoCallDialPadDlg.h"
#include "DemoCommonTools.h"
#include "DemoCallCtrlDlg.h"
#include "DemoCallDlgManager.h"
#include "service_call_interface.h"
#include "service_os_adapt.h"

// CDemoCallDialPadDlg dialog

IMPLEMENT_DYNAMIC(CDemoCallDialPadDlg, CDialogEx)

CDemoCallDialPadDlg::CDemoCallDialPadDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoCallDialPadDlg::IDD, pParent)
    , m_callid(0)
{

}

CDemoCallDialPadDlg::~CDemoCallDialPadDlg()
{
}

void CDemoCallDialPadDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_CALLEE, m_PhoneNumber);
}


BEGIN_MESSAGE_MAP(CDemoCallDialPadDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CDemoCallDialPadDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CDemoCallDialPadDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CDemoCallDialPadDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON4, &CDemoCallDialPadDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CDemoCallDialPadDlg::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON6, &CDemoCallDialPadDlg::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON7, &CDemoCallDialPadDlg::OnBnClickedButton7)
    ON_BN_CLICKED(IDC_BUTTON8, &CDemoCallDialPadDlg::OnBnClickedButton8)
    ON_BN_CLICKED(IDC_BUTTON9, &CDemoCallDialPadDlg::OnBnClickedButton9)
    ON_BN_CLICKED(IDC_BUTTON0, &CDemoCallDialPadDlg::OnBnClickedButton0)
    ON_BN_CLICKED(IDC_BUTTON_STAR, &CDemoCallDialPadDlg::OnBnClickedButtonStar)
    ON_BN_CLICKED(IDC_BUTTON_POUND, &CDemoCallDialPadDlg::OnBnClickedButtonPound)
    ON_BN_CLICKED(IDC_BUTTON_AUDIO, &CDemoCallDialPadDlg::OnBnClickedButtonAudio)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO, &CDemoCallDialPadDlg::OnBnClickedButtonVideo)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDemoCallDialPadDlg::OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CDemoCallDialPadDlg message handlers
BOOL CDemoCallDialPadDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    font.CreatePointFont(300, _T("ËÎÌו"));
    m_PhoneNumber.SetFont(&font);

    return TRUE;
}

void CDemoCallDialPadDlg::OnBnClickedButton1()
{
    m_PhoneString.Append(_T("1"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButton2()
{
    m_PhoneString.Append(_T("2"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButton3()
{
    m_PhoneString.Append(_T("3"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButton4()
{
    m_PhoneString.Append(_T("4"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButton5()
{
    m_PhoneString.Append(_T("5"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButton6()
{
    m_PhoneString.Append(_T("6"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButton7()
{
    m_PhoneString.Append(_T("7"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButton8()
{
    m_PhoneString.Append(_T("8"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButton9()
{
    m_PhoneString.Append(_T("9"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButton0()
{
    m_PhoneString.Append(_T("0"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButtonStar()
{
    m_PhoneString.Append(_T("*"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButtonPound()
{
    m_PhoneString.Append(_T("#"));
    m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
}

void CDemoCallDialPadDlg::OnBnClickedButtonDel()
{
    if (m_PhoneString.GetLength() > 0)
    {
        m_PhoneString = m_PhoneString.Left(m_PhoneString.GetLength() - 1);
        m_PhoneNumber.SetWindowText(m_PhoneString.GetString());
    }
    else
    {
        AfxMessageBox(_T("Number is empty!"));
        return;
    }
}

void CDemoCallDialPadDlg::OnBnClickedButtonAudio()
{
    if (m_PhoneString.IsEmpty())
    {
        return;
    }
    StartCall(CTools::UNICODE2UTF(m_PhoneString), FALSE);
}

void CDemoCallDialPadDlg::OnBnClickedButtonVideo()
{
    if (m_PhoneString.IsEmpty())
    {
        return;
    }
    StartCall(CTools::UNICODE2UTF(m_PhoneString), TRUE);
}

void CDemoCallDialPadDlg::StartCall(std::string sipnumber, BOOL isVideo)
{
    CDemoCallCtrlDlg* pCallCtrlDlg = CallDlgManager::GetInstance().CreateCallDlgBySIPnumber(sipnumber);
    if (NULL == pCallCtrlDlg)
    {
        return;
    }

    if (isVideo)
    {
        pCallCtrlDlg->SetCallDlgtype(SIP_SIGNLE_VIDEO);
    }
    else
    {
        pCallCtrlDlg->SetCallDlgtype(SIP_SIGNLE_CALL);
    }

    unsigned int nlen = sipnumber.length();
    char* psznumber = new char[nlen + 1];
    service_memset_s(psznumber, nlen + 1, 0, nlen + 1);
    strncpy_s(psznumber, nlen + 1, sipnumber.c_str(), _TRUNCATE);

    pCallCtrlDlg->SendMessage(WM_CALL_START_CALL, (WPARAM)(psznumber), (LPARAM)isVideo);
    pCallCtrlDlg->ShowWindow(SW_SHOW);

}

