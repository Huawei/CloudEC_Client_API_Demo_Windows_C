//
//  DemoApp.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once

//#ifndef __AFXWIN_H__
//    #error "include 'stdafx.h' before including this file for PCH"
//#endif

#include "stdafx.h"
#include "resource.h"        // main symbols
#include "DemoRunInfoDlg.h"


// CDemoApp:
// See APP_UI.cpp for the implementation of this class
//

class CDemoApp : public CWinApp
{
public:
    CDemoApp();

    // Overrides
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

    CWnd* m_pMainDlgWnd;
    CWnd* m_pLoginDlgWnd;
    /*CDemoRunInfoDlg* m_pRunInfoDlg;*/

// Implementation

    DECLARE_MESSAGE_MAP()
};

extern CDemoApp theApp;
