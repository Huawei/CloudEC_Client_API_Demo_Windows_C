//
//  DemoMediaSettingDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoMediaSettingDlg.h"
#include "DemoCommonTools.h"
#include "DemoData.h"
#include "tsdk_call_def.h"
#include "service_os_adapt.h"
#include "service_call_interface.h"

#define DEVICE_NUM 10

// CDemoMediaSettingDlg dialog

IMPLEMENT_DYNAMIC(CDemoMediaSettingDlg, CDialogEx)

CDemoMediaSettingDlg::CDemoMediaSettingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoMediaSettingDlg::IDD, pParent)
{
    preview_open = false;
}

CDemoMediaSettingDlg::~CDemoMediaSettingDlg()
{
}

void CDemoMediaSettingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_AUDIN_DEV, m_cbxAudioInputDev);
    DDX_Control(pDX, IDC_COMBO_AUDOUT_DEV, m_cbxAudioOutDev);
    DDX_Control(pDX, IDC_COMBO_VIDEO_DEV, m_cbxVideoDev);
    DDX_Control(pDX, IDC_SLIDER_AUD_OUT, m_sldSpeakLevel);
    DDX_Control(pDX, IDC_STATIC_PREVIEW, m_PreviewWnd);
}


BEGIN_MESSAGE_MAP(CDemoMediaSettingDlg, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO_AUDIN_DEV, &CDemoMediaSettingDlg::OnCbnSelchangeComboAudinDev)
    ON_CBN_SELCHANGE(IDC_COMBO_AUDOUT_DEV, &CDemoMediaSettingDlg::OnCbnSelchangeComboAudoutDev)
    ON_CBN_SELCHANGE(IDC_COMBO_VIDEO_DEV, &CDemoMediaSettingDlg::OnCbnSelchangeComboVideoDev)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AUD_OUT, &CDemoMediaSettingDlg::OnNMReleasedcaptureSliderAudOut)
    ON_BN_CLICKED(IDC_BUTTON_PREVIEW_OPEN, &CDemoMediaSettingDlg::OnBnClickedButtonPreviewOpen)
    ON_BN_CLICKED(IDC_BUTTON_PREVIEW_CLOSE, &CDemoMediaSettingDlg::OnBnClickedButtonPreviewClose)
END_MESSAGE_MAP()

// CDemoMediaSettingDlg 消息处理程序
BOOL CDemoMediaSettingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    InitDevice();
    RefreshControl();

    return TRUE;
}

void CDemoMediaSettingDlg::InitDevice()
{
    unsigned int uiDevideNUm(DEVICE_NUM);
    ///get mic devices
    TSDK_S_DEVICE_INFO* pMicdevices = new TSDK_S_DEVICE_INFO[DEVICE_NUM];
    service_memset_s(pMicdevices, sizeof(TSDK_S_DEVICE_INFO)*DEVICE_NUM, 0, sizeof(TSDK_S_DEVICE_INFO)*DEVICE_NUM);
    service_get_devices(&uiDevideNUm, pMicdevices, TSDK_E_DEVICE_MIC);
    for (unsigned int i = 0; i < uiDevideNUm; i++)
    {
        m_cbxAudioInputDev.InsertString((int)pMicdevices[i].index, CTools::UTF2UNICODE(pMicdevices[i].device_name));
    }
    delete (pMicdevices);

    ///get spk devices
    uiDevideNUm = DEVICE_NUM;
    TSDK_S_DEVICE_INFO* pSpkdevice = new TSDK_S_DEVICE_INFO[DEVICE_NUM];
    service_memset_s(pSpkdevice, sizeof(TSDK_S_DEVICE_INFO)*DEVICE_NUM, 0, sizeof(TSDK_S_DEVICE_INFO)*DEVICE_NUM);
    service_get_devices(&uiDevideNUm, pSpkdevice, TSDK_E_DEVICE_SPEAKER);
    for (unsigned int i = 0; i < uiDevideNUm; i++)
    {
        m_cbxAudioOutDev.InsertString((int)pSpkdevice[i].index, CTools::UTF2UNICODE(pSpkdevice[i].device_name));
    }
    delete (pSpkdevice);

    //GetVideo Device
    uiDevideNUm = DEVICE_NUM;
    TSDK_S_DEVICE_INFO* pVideo = new TSDK_S_DEVICE_INFO[DEVICE_NUM];
    service_memset_s(pVideo, sizeof(TSDK_S_DEVICE_INFO)*DEVICE_NUM, 0, sizeof(TSDK_S_DEVICE_INFO)*DEVICE_NUM);
    service_get_devices(&uiDevideNUm, pVideo, TSDK_E_DEVICE_CAMERA);
    for (unsigned int i = 0; i < uiDevideNUm; i++)
    {
        m_cbxVideoDev.InsertString((int)pVideo[i].index, CTools::UTF2UNICODE(pVideo[i].device_name));
    }
    delete(pVideo);

    //init spk volue
    m_sldSpeakLevel.SetRange(0, 100);
    unsigned int spkLevel;
    service_get_speak_volume(&spkLevel);
    m_sldSpeakLevel.SetPos((int)spkLevel);
}


void CDemoMediaSettingDlg::RefreshControl()
{
    unsigned int micIndex = 0;
    unsigned int spkIndex = 0;
    unsigned int videoIndex = 0;
    ///setMIC
    service_device_get_index(&micIndex, TSDK_E_DEVICE_MIC);
    m_cbxAudioInputDev.SetCurSel((int)micIndex);
    ////Set spk
    service_device_get_index(&spkIndex, TSDK_E_DEVICE_SPEAKER);
    m_cbxAudioOutDev.SetCurSel((int)spkIndex);
    ////set video
    service_device_get_index(&videoIndex, TSDK_E_DEVICE_CAMERA);
    m_cbxVideoDev.SetCurSel((int)videoIndex);
}



void CDemoMediaSettingDlg::OnCbnSelchangeComboAudinDev()
{
    int Index = m_cbxAudioInputDev.GetCurSel();
    service_device_set_index((unsigned int)Index, TSDK_E_DEVICE_MIC);
}


void CDemoMediaSettingDlg::OnCbnSelchangeComboAudoutDev()
{
    int Index = m_cbxAudioOutDev.GetCurSel();
    service_device_set_index((unsigned int)Index, TSDK_E_DEVICE_SPEAKER);
}


void CDemoMediaSettingDlg::OnCbnSelchangeComboVideoDev()
{
    int Index = m_cbxVideoDev.GetCurSel();
    service_device_set_index((unsigned int)Index, TSDK_E_DEVICE_CAMERA);
}


void CDemoMediaSettingDlg::OnNMReleasedcaptureSliderAudOut(NMHDR *pNMHDR, LRESULT *pResult)
{
    *pResult = 0;
    unsigned int spkLevel = (unsigned int)m_sldSpeakLevel.GetPos();
    service_set_speak_volume(spkLevel);
}


void CDemoMediaSettingDlg::OnBnClickedButtonPreviewOpen()
{
    unsigned int videoIndex = 0;
    HANDLE previewhand = m_PreviewWnd.GetSafeHwnd();
    service_device_get_index(&videoIndex, TSDK_E_DEVICE_CAMERA);
    service_video_open_preview((unsigned int)previewhand, videoIndex);
}


void CDemoMediaSettingDlg::OnBnClickedButtonPreviewClose()
{
    Invalidate(TRUE);
    service_video_close_preview();
}
