//
//  DemoCallOutGoingDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "stdafx.h"
#include "resource.h"

// CDemoCallOutGoingDlg dialog

class CDemoCallOutGoingDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoCallOutGoingDlg)

public:
    CDemoCallOutGoingDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDemoCallOutGoingDlg();

    // Dialog Data
    enum { IDD = IDD_CALL_OUTGOING_DLG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
};
