//
//  DemoDataConfAppShareDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoDataConfAppShareDlg.h"
#include "DemoData.h"
#include "DemoCommonTools.h"
#include "DemoPromptDlg.h"
#include "service_conf_handle_global.h"
#include "service_os_adapt.h"
#include "service_tools.h"

extern CString g_sipNumber;

// CDemoDataConfAppShareDlg Dialog

IMPLEMENT_DYNAMIC(CDemoDataConfAppShareDlg, CDialogEx)

CDemoDataConfAppShareDlg::CDemoDataConfAppShareDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoDataConfAppShareDlg::IDD, pParent)
    , ispresenter(false)
    , ischairman(false)
    , isShareDesktop(false)
    , m_handle(0)
    , m_callID(0)
{

}

CDemoDataConfAppShareDlg::~CDemoDataConfAppShareDlg()
{
}

void CDemoDataConfAppShareDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ST_STATUS, m_st_status);
    DDX_Control(pDX, IDC_BT_SHARE, m_bt_share);
    DDX_Control(pDX, IDC_STATIC_DESKTOP, m_stcDeskTop);
    DDX_Control(pDX, IDC_LIST_APP, m_list_apps);
    DDX_Control(pDX, IDC_BT_SELECT, m_bt_select);
    DDX_Control(pDX, IDC_BT_REMOVE, m_bt_remove);
    DDX_Control(pDX, IDC_LIST_SELECTED, m_list_selected);
    DDX_Control(pDX, IDC_BT_GETAPP, m_bt_getapps);
}

BEGIN_MESSAGE_MAP(CDemoDataConfAppShareDlg, CDialogEx)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_SCREEN, IDC_RADIO_SCREEN, &CDemoDataConfAppShareDlg::OnBnClickedRadio)
    ON_BN_CLICKED(IDC_BT_SHARE, &CDemoDataConfAppShareDlg::OnBnClickedBtShare)
    ON_MESSAGE(WM_DATACONF_MODULE_SCREEN_DATA, &CDemoDataConfAppShareDlg::OnDataConfASUpdateScreen)
    ON_MESSAGE(WM_DATACONF_MODULE_SHARING_SESSION, &CDemoDataConfAppShareDlg::OnShareSession)
    ON_MESSAGE(WM_DATACONF_MODULE_SHARING_STATE, &CDemoDataConfAppShareDlg::OnShareState)
    ON_MESSAGE(WM_DATACONF_MODULE_AS_PRIVILEGE_CHANGE, &CDemoDataConfAppShareDlg::OnSharePrivilegeStateChange)
END_MESSAGE_MAP()


// CDemoDataConfAppShareDlg message handle
BOOL CDemoDataConfAppShareDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    CheckRadioButton(IDC_RADIO_SCREEN, IDC_RADIO_SCREEN, IDC_RADIO_SCREEN);
    return TRUE;
}

LRESULT CDemoDataConfAppShareDlg::OnDataConfASUpdateScreen(WPARAM, LPARAM)
{
    TSDK_S_CONF_AS_SCREEN_DATA screendata;
    service_memset_s(&screendata, sizeof(screendata), 0, sizeof(screendata));

    if (0 != service_data_conf_app_share_get_screen_data(&screendata) || NULL == screendata.data)
    {
        AfxMessageBox(_T("UpdateScreen failed"));
        return 0L;
    }
    /*Show data*/
    if (TSDK_E_CONF_SCREEN_DATA_DDB == screendata.data_format)
    {
        m_stcDeskTop.SetBitmap2((BITMAP*)screendata.data);
    }
    else if (TSDK_E_CONF_SCREEN_DATA_DC == screendata.data_format)
    {
        HDC hAnnotDataDC = (HDC)screendata.data;
        BITMAP bm;
        HBITMAP hBmp = (HBITMAP)::GetCurrentObject(hAnnotDataDC, OBJ_BITMAP);
        if (NULL == hBmp)
        {
            DWORD nRet = GetLastError();
            TRACE("NULL == hBmp, GetLastError:%d", nRet);
        }
        (VOID)::GetObject(hBmp, sizeof(bm), &bm);
        m_stcDeskTop.SetBitmap(hBmp);
    }
    else
    {
    }
    return 0L;
}
void CDemoDataConfAppShareDlg::SetBitmapNULL(void)
{
    m_stcDeskTop.SetBitmap2(NULL);
}

void CDemoDataConfAppShareDlg::updateShareDlg()
{
    if (ispresenter || ischairman)
    {
        m_bt_share.EnableWindow(TRUE);
    }
    else
    {
        m_bt_share.EnableWindow(FALSE);
    }
}

void CDemoDataConfAppShareDlg::OnBnClickedRadio(UINT idCtl)
{
    if (IDC_RADIO_SCREEN == idCtl)
    {
        setShareType(true);
        m_bt_select.EnableWindow(FALSE);
        m_bt_remove.EnableWindow(FALSE);
        m_bt_getapps.EnableWindow(FALSE);
    }
    /*else
    {
        setShareType(false);
        m_bt_select.EnableWindow(TRUE);
        m_bt_remove.EnableWindow(TRUE);
        m_bt_getapps.EnableWindow(TRUE);
    }*/
}

void CDemoDataConfAppShareDlg::OnBnClickedBtShare()
{
    ////get self number
    CString selfNum = CTools::GetSipNumber(g_sipNumber);
    std::string strSelfNum = CTools::UNICODE2UTF(selfNum);

    CString cstr;
    m_bt_share.GetWindowText(cstr);

    if (cstr == _T("StartShare"))
    {
        (void)service_data_conf_app_share_set_owner(const_cast<char*>(strSelfNum.c_str()), TSDK_E_CONF_AS_ACTION_ADD);
        m_bt_share.SetWindowText(_T("StopShare"));
    }
    else
    {
        (void)service_data_conf_app_share_stop();
        (void)service_data_conf_app_share_set_owner(const_cast<char*>(strSelfNum.c_str()), TSDK_E_CONF_AS_ACTION_DELETE);
        m_bt_share.SetWindowText(_T("StartShare"));
    }
    updateShareDlg();
}

void CDemoDataConfAppShareDlg::setShareType(bool isDesktop)
{
    if (isDesktop)
    {
        isShareDesktop = true;
    }
    else
    {
        isShareDesktop = false;
    }
}

LRESULT CDemoDataConfAppShareDlg::OnShareSession(WPARAM wparam, LPARAM lparam)
{
    TSDK_E_CONF_AS_ACTION_TYPE actionType = (TSDK_E_CONF_AS_ACTION_TYPE)wparam;
    std::string shareOwnerNum = (TSDK_CHAR *)lparam;

    CString cstxt = CTools::UTF2UNICODE(shareOwnerNum);
    cstxt += _T("has the right to share");
    m_st_status.SetWindowText(cstxt);

    CString selfNumber = CTools::GetSipNumber(g_sipNumber);
    TSDK_CHAR strSelfNumber[TSDK_D_MAX_NUMBER_LEN + 1];
    CTools::CString2Char(selfNumber, strSelfNumber, TSDK_D_MAX_NUMBER_LEN);

    if (TSDK_E_CONF_AS_ACTION_ADD == actionType)
    {
        if (shareOwnerNum == strSelfNumber)
        {
            if (ischairman || ispresenter)
            {
                (void)service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_DESKTOP);
            }
            else
            {
                CDemoPromptDlg promptDlg;
                promptDlg.SetTextOfContent(_T("The Chairman invite share desktop,do you agree?"));
                INT_PTR nResponse = promptDlg.DoModal();
                if (IDOK == nResponse)
                {
                    (void)service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_DESKTOP);
                    m_bt_share.EnableWindow(TRUE);
                    m_bt_share.SetWindowText(_T("StopShare"));
                }
                else
                {
                    return 0L;
                }
            }
        }
    }
    else if (TSDK_E_CONF_AS_ACTION_DELETE == actionType)
    {
        if (shareOwnerNum == strSelfNumber)
        {
            if (!ispresenter)
            {
                (void)service_data_conf_app_share_stop();
            }
        }
    }
    return 0L;
}


LRESULT CDemoDataConfAppShareDlg::OnSharePrivilegeStateChange(WPARAM wparam, LPARAM lparam)
{
    TSDK_E_CONF_AS_PRIVILEGE_INFO* privilegeInfo = (TSDK_E_CONF_AS_PRIVILEGE_INFO*)wparam;
    CHECK_POINTER_RETURN(privilegeInfo, -1L);

    if (TSDK_E_CONF_SHARE_PRIVILEGE_CONTROL == privilegeInfo->privilege_type)
    {
        switch (privilegeInfo->action)
        {
        case TSDK_E_CONF_AS_ACTION_DELETE:
        {
            //建议弹出提示窗口，控制权限收回或被收回
            break;
        }

        case TSDK_E_CONF_AS_ACTION_ADD:
        {
            //UI Plugin已处理，无需应用层处理
            break;
        }

        case TSDK_E_CONF_AS_ACTION_MODIFY:
        {
            break;
        }

        case TSDK_E_CONF_AS_ACTION_REQUEST:
        {
            //其他用户请求进行控制，应用程序根据需要弹出提示窗口，根据用户选择是否授予远程控制权限
            //当前直接同意请求，授予远程控制权限
            service_data_conf_app_share_set_privilege(privilegeInfo->attendee.base_info.number, TSDK_E_CONF_SHARE_PRIVILEGE_CONTROL, TSDK_E_CONF_AS_ACTION_ADD);            
            break;
        }

        case TSDK_E_CONF_AS_ACTION_REJECT:
        {
            break;
        }

        default:
            break;
        }
    }

    return 0L;
}

LRESULT CDemoDataConfAppShareDlg::OnShareState(WPARAM wparam, LPARAM lparam)
{
    TSDK_S_CONF_AS_STATE_INFO* shareState = (TSDK_S_CONF_AS_STATE_INFO*)wparam;
    CHECK_POINTER_RETURN(shareState, -1L);

    TSDK_UINT32 sharetype = (unsigned int)lparam;

    CString cstxt;
    if (sharetype == DESKTOP)
    {
        cstxt = _T("DeskTop Share");
    }
    else if (sharetype == APP)
    {
        cstxt = _T("APP Share");
    }

    switch (shareState->state)
    {
    case TSDK_E_CONF_AS_STATE_NULL:
    {
        cstxt += _T("Status is NULL");
        SetBitmapNULL();
        break;
    }
    case TSDK_E_CONF_AS_STATE_VIEW:
    {
        cstxt += _T("Status is Viewing");
        break;
    }
    case TSDK_E_CONF_AS_STATE_START:
    {
        cstxt += _T("Status is Start");
        break;;
    }
    case TSDK_E_CONF_AS_STATE_PAUSE:
    {
        cstxt += _T("Status is Pause");
        SetBitmapNULL();
        break;
    }
    case TSDK_E_CONF_AS_STATE_PAUSEVIEW:
    {
        cstxt += _T("Status is View Pause");
        SetBitmapNULL();
        break;
    }
    }
    m_st_status.SetWindowText(cstxt);
    delete (shareState);
    return 0L;
}

