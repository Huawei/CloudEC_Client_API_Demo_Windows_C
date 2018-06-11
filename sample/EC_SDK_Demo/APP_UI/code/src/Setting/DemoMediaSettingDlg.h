//
//  DemoMediaSettingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <map>

// CDemoMediaSettingDlg dialog

class CDemoMediaSettingDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoMediaSettingDlg)

public:
    CDemoMediaSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDemoMediaSettingDlg();
    virtual BOOL OnInitDialog();


    // dialog Data
    enum { IDD = IDD_MEDIA_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
private:
    void InitDevice();
    void RefreshControl();
public:
    CComboBox m_cbxAudioInputDev;
    CComboBox m_cbxAudioOutDev;
    CComboBox m_cbxVideoDev;
    CSliderCtrl m_sldSpeakLevel;

    //媒体设置
    bool preview_open;
    CStatic m_PreviewWnd;
    afx_msg void OnCbnSelchangeComboAudinDev();
    afx_msg void OnCbnSelchangeComboAudoutDev();
    afx_msg void OnCbnSelchangeComboVideoDev();
    afx_msg void OnNMReleasedcaptureSliderAudOut(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedButtonPreviewOpen();
    afx_msg void OnBnClickedButtonPreviewClose();
};
