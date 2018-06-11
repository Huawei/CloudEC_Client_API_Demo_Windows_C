//
//  DemoCallDtmfDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoCallDtmfDlg.h"
#include "service_call_interface.h"
#include "DemoCommonTools.h"


// CDemoCallDtmfDlg dialog

IMPLEMENT_DYNAMIC(CDemoCallDtmfDlg, CDialogEx)

CDemoCallDtmfDlg::CDemoCallDtmfDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoCallDtmfDlg::IDD, pParent)
    , callId(0)
{
    m_apppath = CTools::getCurrentPath();
}

CDemoCallDtmfDlg::~CDemoCallDtmfDlg()
{
}

void CDemoCallDtmfDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_DTMF_NUM, m_edit_number);
}


BEGIN_MESSAGE_MAP(CDemoCallDtmfDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_1, &CDemoCallDtmfDlg::OnBnClickedDtmfButton1)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_2, &CDemoCallDtmfDlg::OnBnClickedDtmfButton2)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_3, &CDemoCallDtmfDlg::OnBnClickedDtmfButton3)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_4, &CDemoCallDtmfDlg::OnBnClickedDtmfButton4)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_5, &CDemoCallDtmfDlg::OnBnClickedDtmfButton5)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_6, &CDemoCallDtmfDlg::OnBnClickedDtmfButton6)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_7, &CDemoCallDtmfDlg::OnBnClickedDtmfButton7)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_8, &CDemoCallDtmfDlg::OnBnClickedDtmfButton8)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_9, &CDemoCallDtmfDlg::OnBnClickedDtmfButton9)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_0, &CDemoCallDtmfDlg::OnBnClickedDtmfButton0)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_STAR, &CDemoCallDtmfDlg::OnBnClickedDtmfButtonStar)
    ON_BN_CLICKED(IDC_BUTTON_DTMF_POUND, &CDemoCallDtmfDlg::OnBnClickedDtmfButtonPound)
END_MESSAGE_MAP()

//CDemoCallDtmfDlg member function

void CDemoCallDtmfDlg::SendDTMF(TSDK_E_DTMF_TONE Tone, CString tonepath)
{
    int tupHandle = 0;
    (void)service_call_send_DTMF(callId, Tone);
    (void)service_call_media_startplay(0, (CTools::UNICODE2UTF(tonepath)).c_str(), &tupHandle);
    Sleep(200);
    (void)service_call_media_stopplay(tupHandle);
}

void CDemoCallDtmfDlg::ProcessInputNumber(CString number)
{
    CString phobenumber;
    m_edit_number.GetWindowText(phobenumber);
    phobenumber.Append(number);
    m_edit_number.SetWindowText(phobenumber.GetString());
    UpdateData(FALSE);
}

// CDemoCallDtmfDlg message handlers
void CDemoCallDtmfDlg::OnBnClickedDtmfButton1()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_1;
    CString audiopath = m_apppath + _T("\\audio\\Key\\1.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("1"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButton2()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_2;
    CString audiopath = m_apppath + _T("\\audio\\Key\\2.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("2"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButton3()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_3;
    CString audiopath = m_apppath + _T("\\audio\\Key\\3.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("3"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButton4()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_4;
    CString audiopath = m_apppath + _T("\\audio\\Key\\4.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("4"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButton5()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_5;
    CString audiopath = m_apppath + _T("\\audio\\Key\\5.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("5"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButton6()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_6;
    CString audiopath = m_apppath + _T("\\audio\\Key\\6.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("6"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButton7()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_7;
    CString audiopath = m_apppath + _T("\\audio\\Key\\7.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("7"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButton8()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_8;
    CString audiopath = m_apppath + _T("\\audio\\Key\\8.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("8"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButton9()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_9;
    CString audiopath = m_apppath + _T("\\audio\\Key\\9.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("9"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButton0()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_0;
    CString audiopath = m_apppath + _T("\\audio\\Key\\0.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("0"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButtonStar()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_STAR;
    CString audiopath = m_apppath + _T("\\audio\\Key\\Xin.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("*"));
}

void CDemoCallDtmfDlg::OnBnClickedDtmfButtonPound()
{
    TSDK_E_DTMF_TONE key = TSDK_E_DTMF_POUND;
    CString audiopath = m_apppath + _T("\\audio\\Key\\Jin.wav");
    SendDTMF(key, audiopath);
    ProcessInputNumber(_T("#"));
}
