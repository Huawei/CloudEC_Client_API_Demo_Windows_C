//
//  DemoApp.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoApp.h"
#include "DemoLoginDlg.h"
#include "DemoEventProc.h"
#include "DemoData.h"
#include "service_init.h"
#include "service_callback_to_ui.h"
#include "service_uninit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDemoApp

BEGIN_MESSAGE_MAP(CDemoApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDemoApp construction

CDemoApp::CDemoApp()
{
    // support Restart Manager
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
    m_pMainDlgWnd = NULL;
    m_pLoginDlgWnd = NULL;
    /*m_pRunInfoDlg = NULL;*/
}


// The one and only CDemoApp object
CDemoApp theApp;


// CDemoApp initialization
BOOL CDemoApp::InitInstance()
{
    // InitCommonControlsEx() is required on Windows XP if an application
    // manifest specifies use of ComCtl32.dll version 6 or later to enable
    // visual styles.  Otherwise, any window creation will fail.
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // Set this to include all the common control classes you want to use
    // in your application.
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    (void)CWinApp::InitInstance();

    if (!AfxSocketInit())
    {
        AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
        return FALSE;
    }


    // Initialize OLE libraries
    if (!AfxOleInit())
    {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }

    // Init gdi+
    GdiplusStartupInput m_gdiplusStartupInput;
    ULONG_PTR m_pGdiToken;
    GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);

    AfxEnableControlContainer();

    // Create the shell manager, in case the dialog contains
    // any shell tree view or shell list view controls.
    CShellManager *pShellManager = new CShellManager;

    // Activate "Windows Native" visual manager for enabling themes in MFC controls
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    // of your final executable, you should remove from the following
    // the specific initialization routines you do not need
    // Change the registry key under which our settings are stored
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    // Set Config Param
    CString cstrIsIdoConfControl;
    CTools::GetIniConfigParam(_T("IDOConfig"), _T("IdoConfControl"), cstrIsIdoConfControl);
    if (_T("") == cstrIsIdoConfControl)
    {
        CTools::WriteIniConfigParam(_T("IDOConfig"), _T("IdoConfControl"), _T("1"));
    }

    CTools::GetIniConfigParam(_T("IDOConfig"), _T("IdoConfControl"), cstrIsIdoConfControl);
    if (_T("1") == cstrIsIdoConfControl)
    {
        service_set_config_param(TRUE);
    }
    else
    {
        service_set_config_param(FALSE);
    }
    
    // Init All Module
    if (RESULT_SUCCESS != ServiceInitAllModule())
    {
        AfxMessageBox(_T("Init All Module failed"));
    }

    //// Get history config info
 //   if (m_pRunInfoDlg == NULL)
 //   {
 //       m_pRunInfoDlg = new CDemoRunInfoDlg();
 //       m_pRunInfoDlg->Create(CDemoRunInfoDlg::IDD);
 //   }
 //   m_pRunInfoDlg->ShowWindow(SW_SHOW);

    ///设置回调函数//////
    service_register_login_callback(NotifyCallBack::loginMsgNotify);
    service_register_call_callback(NotifyCallBack::callMsgNotify);
    service_register_conf_callback(NotifyCallBack::confMsgNotify);

    if (1 == service_is_use_ui_plugin())
    {
        //创建视频窗口
        service_register_ui_plugin_callback(NotifyCallBack::uiPluginMsgNotify);
    }
 
    for (;;)
    {
        CDemoLoginDlg  LoginDlg;
        m_pLoginDlgWnd = &LoginDlg;
        INT_PTR mRet = LoginDlg.DoModal();
        if (mRet == IDCANCEL)
        {
            break;
        }
        bool bRet = LoginDlg.GetLoginFlag();

        CDemoMainDlg mainDlg;
        if (bRet)
        {
            m_pMainDlgWnd = &mainDlg;
            INT_PTR nResponse = mainDlg.DoModal();
            if (nResponse == IDOK)
            {
                continue;
            }
            else if (nResponse == IDCANCEL)
            {
                exit(0);
            }
            else if (nResponse == -1)
            {
                TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
                TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
            }
        }
    }

    //// Get history config info
    //if (m_pRunInfoDlg == NULL)
    //{
    //    m_pRunInfoDlg = new CDemoRunInfoDlg();
    //    m_pRunInfoDlg->Create(CDemoRunInfoDlg::IDD);
    //}
    //m_pRunInfoDlg->ShowWindow(SW_SHOW);

    // Delete the shell manager created above.
    if (pShellManager != NULL)
    {
        delete pShellManager;
    }

    //卸载gdi+
    GdiplusShutdown(m_pGdiToken);

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}

int CDemoApp::ExitInstance()
{
    AfxOleTerm(FALSE);

    //去初始化
    int ret;
    ret = ServiceUninitAllModule();
    if (RESULT_SUCCESS != ret)
    {
        AfxMessageBox(_T("uninit failed"));
    }

    ////析构RunInfoDlg
    //if (m_pRunInfoDlg)
    //{
    //    m_pRunInfoDlg->OnClose();
    //    SAFE_DELETE(m_pRunInfoDlg);
    //}

    return CWinApp::ExitInstance();
}
