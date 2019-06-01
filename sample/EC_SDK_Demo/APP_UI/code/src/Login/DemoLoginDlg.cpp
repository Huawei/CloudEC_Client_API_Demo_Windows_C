//
//  DemoLoginDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoLoginDlg.h"
#include "DemoData.h"
#include "tsdk_login_interface.h"
#include "service_login.h"
#include "service_tools.h"
#include "service_os_adapt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString g_loginAccount;
CString g_sipNumber;
CString g_shortNumber;

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDemoLoginDlg dialog
CDemoLoginDlg::CDemoLoginDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoLoginDlg::IDD, pParent)
    , m_Account(_T(""))
    , m_Password(_T(""))
    , m_ServerPort(0)
    , m_bLoginFlag(false)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pLoginSetting = NULL;
    m_pLoginJoinConf = NULL;
}

void CDemoLoginDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_EditAccount);
    DDX_Control(pDX, IDC_EDIT_PASSWORD, m_EditPwd);
}

BEGIN_MESSAGE_MAP(CDemoLoginDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CDemoLoginDlg::OnBnClickedButtonLogin)
    ON_BN_CLICKED(IDC_BUTTON_LOGIN_SETTING, &CDemoLoginDlg::OnBnClickedButtonLoginSetting)
    ON_BN_CLICKED(IDC_BUTTON_LOGIN_JOIN_CONF, &CDemoLoginDlg::OnBnClickedButtonLoginJoinConf)
    ON_MESSAGE(WM_LOGIN_AUTH_RESULT, &CDemoLoginDlg::OnLoginAuthResult)
    ON_MESSAGE(WM_LOGIN_RESULT, &CDemoLoginDlg::OnLoginResult)
    ON_MESSAGE(WM_LOGIN_TOKEN_REFRESH_FAILED, &CDemoLoginDlg::OnLoginTokenRefreshFailed)
    ON_MESSAGE(WM_AUTH_LOGIN_SAVE_SELF_INFO, &CDemoLoginDlg::OnSaveSelfInfo)
    ON_MESSAGE(WM_LOGIN_GET_TEMP_USER_RESULT, &CDemoLoginDlg::OnLoginGetTempUserResult)
END_MESSAGE_MAP()


// CDemoLoginDlg message handlers

BOOL CDemoLoginDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // TODO: Add extra initialization here

    if (NULL == m_pLoginSetting)
    {
        m_pLoginSetting = new CDemoLoginSettingDlg(this);
        if (!::IsWindow(m_pLoginSetting->GetSafeHwnd()))
        {
            (void)m_pLoginSetting->Create(IDD_LOGIN_SETTING);
        }
    }

    if (NULL == m_pLoginJoinConf)
    {
        m_pLoginJoinConf = new CDemoLoginJoinConfDlg(this);
        if (!::IsWindow(m_pLoginJoinConf->GetSafeHwnd()))
        {
            (void)m_pLoginJoinConf->Create(IDD_LOGIN_JOIN_CONF);
        }
    }

    ////// 获取上一次登录成功的账号信息
    CTools::GetIniConfigParam(_T("LoginConfig"), _T("account"), m_Account);
    m_EditAccount.SetWindowText(m_Account);
    m_EditPwd.SetWindowText(_T(""));
    /*CTools::GetIniConfigParam(_T("LoginConfig"), _T("pwd"), m_Password);
    m_EditPwd.SetWindowText(m_Password);*/
    g_loginAccount = m_Account;

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        (void)dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

void CDemoLoginDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoLoginDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CDemoLoginDlg::OnBnClickedButtonLogin()
{
    int result = 0;
    result = Login();
    if (RESULT_SUCCESS != result)
    {
        AfxMessageBox(_T("login failed"));
    }
    else
    {
        m_bLoginFlag = true;
        CTools::WriteIniConfigParam(_T("LoginConfig"), _T("account"), m_Account);
        /*CTools::WriteIniConfigParam(_T("LoginConfig"), _T("pwd"), m_Password);*/
    }
}

void CDemoLoginDlg::OnBnClickedButtonLoginJoinConf()
{
    INT_PTR nRes;
    CDemoLoginJoinConfDlg  loginJoinConf;
    nRes = loginJoinConf.DoModal();
}

void CDemoLoginDlg::OnBnClickedButtonLoginSetting()
{
    INT_PTR nRes;
    CDemoLoginSettingDlg  loginSetting;
    nRes = loginSetting.DoModal();
}

afx_msg LRESULT CDemoLoginDlg::OnLoginAuthResult(WPARAM wParam, LPARAM lParam)
{
    AfxMessageBox(_T("Login Auth Failed!"));
    return 0L;
}

afx_msg LRESULT CDemoLoginDlg::OnLoginResult(WPARAM wParam, LPARAM lParam)
{
    TSDK_E_SERVICE_ACCOUNT_TYPE service_account_type = (TSDK_E_SERVICE_ACCOUNT_TYPE)lParam;
    BOOL bSuccess = (BOOL)wParam;
    if (bSuccess)
    {
        if (service_account_type == TSDK_E_VOIP_SERVICE_ACCOUNT)
        {
            m_bLoginFlag = true;
            OnOK();
        }
        else
        {
            AfxMessageBox(_T("Login IM Success!"));
        }
    }
    else
    {
        AfxMessageBox(_T("Login Failed!"));
    }

    return 0L;
}

afx_msg LRESULT CDemoLoginDlg::OnLoginTokenRefreshFailed(WPARAM wParam, LPARAM lParam)
{
    AfxMessageBox(_T(" Please login again !"));
    return 0;
}

afx_msg LRESULT CDemoLoginDlg::OnSaveSelfInfo(WPARAM wParam, LPARAM lParam)
{
    TSDK_S_VOIP_ACCOUNT_INFO* selfInfo = (TSDK_S_VOIP_ACCOUNT_INFO*)wParam;
    CHECK_POINTER_RETURN(selfInfo, -1L);
    g_loginAccount = selfInfo->account;
    g_shortNumber = selfInfo->terminal;
    g_sipNumber = selfInfo->number;
    delete (selfInfo);
    return 0L;
}

afx_msg LRESULT CDemoLoginDlg::OnLoginGetTempUserResult(WPARAM wParam, LPARAM lParam)
{
    TSDK_CHAR* result = (TSDK_CHAR*)wParam;
    if (strcmp(result, "Success") == 0)
    {
        m_bLoginFlag = true;
    }
    OnOK();
    return 0L;
}

int CDemoLoginDlg::Login()
{
	int ret;
    // Get account and password info
    m_EditAccount.GetWindowText(m_Account);
    m_EditPwd.GetWindowText(m_Password);

    CString serverPort;
    CString serverParamPath = CTools::getCurrentPath() + _T("\\server.ini");
    (void)GetPrivateProfileString(_T("ServerConfig"), _T("serverIP"), _T(""), m_ServerAdress.GetBuffer(MAX_PATH), MAX_PATH, serverParamPath);
    (void)GetPrivateProfileString(_T("ServerConfig"), _T("serverPort"), _T(""), serverPort.GetBuffer(MAX_PATH), MAX_PATH, serverParamPath);

    string strPort = CTools::UNICODE2UTF(serverPort);
    m_ServerPort = (unsigned short)CTools::str2num(strPort);

	//界面填入的登录信息
    SERVICE_S_LOGIN_PARAM loginParam;
	service_memset_s(&loginParam,sizeof(loginParam),0,sizeof(loginParam));
	strncpy_s(loginParam.user_name,TSDK_D_MAX_ACCOUNT_LEN + 1,CTools::UNICODE2UTF(m_Account).c_str(), _TRUNCATE);
	strncpy_s(loginParam.password,TSDK_D_MAX_PASSWORD_LENGTH + 1,CTools::UNICODE2UTF(m_Password).c_str(), _TRUNCATE);
	strncpy_s(loginParam.server_addr,TSDK_D_MAX_URL_LENGTH + 1,CTools::UNICODE2UTF(m_ServerAdress).c_str(), _TRUNCATE);
	loginParam.server_port = m_ServerPort;

    ret = ServiceLogin(&loginParam);
    return ret;
}
