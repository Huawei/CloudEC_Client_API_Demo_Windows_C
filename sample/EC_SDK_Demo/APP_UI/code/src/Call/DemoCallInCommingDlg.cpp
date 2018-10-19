//
//  DemoCallInCommingDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoApp.h"
#include "DemoData.h"
#include "DemoCallInCommingDlg.h"
#include "service_call_interface.h"


// CDemoCallInCommingDlg dialog

IMPLEMENT_DYNAMIC(CDemoCallInCommingDlg, CDialogEx)

CDemoCallInCommingDlg::CDemoCallInCommingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoCallInCommingDlg::IDD, pParent)
    , istransfe(false)
    , play_handle(0)
    , m_buttonType(AUDIO_BUTTON)
    , m_commingcallType(AUDIO_CALL)
    , callid(0)
{

}

CDemoCallInCommingDlg::~CDemoCallInCommingDlg()
{
}

void CDemoCallInCommingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_CALLER_NUM, m_TelNum);
    DDX_Control(pDX, IDC_EDIT_CALL_TYPE, m_Type);
    DDX_Control(pDX, IDC_EDIT_CALLER_NUM2, m_edit_transferNnmber);
    DDX_Control(pDX, IDC_BUTTON_DIVERT, m_bt_transfer);
    DDX_Control(pDX, IDC_BUTTON_AUDIO_ACCEPT, m_bt_audioAccept);
    DDX_Control(pDX, IDC_BUTTON_VIDEO_ACCEPT, m_bt_videoAccept);
}


BEGIN_MESSAGE_MAP(CDemoCallInCommingDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_AUDIO_ACCEPT, &CDemoCallInCommingDlg::OnBnClickedAudioAccept)
    ON_BN_CLICKED(IDC_BUTTON_VIDEO_ACCEPT, &CDemoCallInCommingDlg::OnBnClickedVideoAccept)
    ON_BN_CLICKED(IDC_BUTTON_REJECT, &CDemoCallInCommingDlg::OnBnClickedReject)
    ON_BN_CLICKED(IDC_BUTTON_DIVERT, &CDemoCallInCommingDlg::OnBnClickedTransfer)
END_MESSAGE_MAP()

// CDemoCallInCommingDlg message handlers

BOOL CDemoCallInCommingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    CRect rect;
    (void)SystemParametersInfo(SPI_GETWORKAREA, 0, rect, 0);
    CRect rcDlg;
    GetWindowRect(&rcDlg);
    ScreenToClient(&rcDlg);
    SetWindowPos(NULL, rect.right - rcDlg.Width(), rect.bottom - rcDlg.Height(), rcDlg.Width(), rcDlg.Height(), SWP_NOSIZE);
    ShowWindow(SW_SHOW);

    /////²¥·ÅÀ´µçÁåÒô/////
    PlayPhoneRinging();

    m_TelNum.SetWindowText(m_tel_number.GetString());
    switch (m_commingcallType)
    {
    case AUDIO_CALL:
    {
        m_Type.SetWindowText(_T("Audio Call"));
        m_bt_videoAccept.EnableWindow(FALSE);
        m_bt_audioAccept.EnableWindow(TRUE);
        break;
    }
    case VIDEO_CALL:
    {
        m_Type.SetWindowText(_T("Video Call"));
        m_bt_videoAccept.EnableWindow(TRUE);
        m_bt_audioAccept.EnableWindow(TRUE);
        break;
    }
    case AUDIO_CONF_CALL:
    {
        m_Type.SetWindowText(_T("Audio Conf Call"));
        m_bt_videoAccept.EnableWindow(FALSE);
        m_bt_audioAccept.EnableWindow(TRUE);
        break;
    }
    case VIDEO_CONF_CALL:
    {
        m_Type.SetWindowText(_T("Video Conf Call"));
        m_bt_videoAccept.EnableWindow(TRUE);
        m_bt_audioAccept.EnableWindow(TRUE);
        break;
    }
    default:break;
    }

    return TRUE;
}

void CDemoCallInCommingDlg::OnBnClickedAudioAccept()
{
    m_buttonType = AUDIO_BUTTON;
    (void)service_call_media_stopplay(play_handle);
    OnOK();
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(), WM_CALL_INCOMMING_DLG_CLOSE, NULL, NULL);
}

void CDemoCallInCommingDlg::OnBnClickedVideoAccept()
{
    m_buttonType = VIDEO_BUTTON;
    (void)service_call_media_stopplay(play_handle);
    OnOK();
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(), WM_CALL_INCOMMING_DLG_CLOSE, NULL, NULL);
}

void CDemoCallInCommingDlg::OnBnClickedReject()
{
    (void)service_call_media_stopplay(play_handle);
    OnCancel();
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(), WM_CALL_INCOMMING_DLG_CLOSE, NULL, NULL);
}

void CDemoCallInCommingDlg::OnBnClickedTransfer()
{
    CString strnumber;
    m_edit_transferNnmber.GetWindowText(strnumber);
    if (!strnumber.GetLength())
    {
        AfxMessageBox(_T("Transfer Number is null"));
        return;
    }
    set_call_id(callid);
    istransfe = true;
    if (RESULT_SUCCESS != service_call_divert(callid, CTools::UNICODE2UTF(strnumber).c_str()))
    {
        AfxMessageBox(_T("service_call_divert failed"));
        return;
    }
    set_call_id(0);
    int result = service_call_media_stopplay(play_handle);
    if (result)
    {
        AfxMessageBox(_T("demo_call_media_stopplay failed"));
    }
    OnOK();
}

// CDemoCallInCommingDlg member handlers
void CDemoCallInCommingDlg::PlayPhoneRinging()
{
    std::string plafile = CTools::UNICODE2UTF(CTools::getCurrentPath());
    plafile = plafile + "\\audio\\In.wav";
    (void)service_call_media_startplay(0, plafile.c_str(), &play_handle);
};

void CDemoCallInCommingDlg::OnCloseDlg()
{
    OnCancel();
}

