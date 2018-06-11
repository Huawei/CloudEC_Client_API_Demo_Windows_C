//
//  DemoDataConfAppShareDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoDataConfAppShareDlg.h"
#include "DemoData.h"
#include "DemoCommonTools.h"
#include "service_data_conf_global_data.h"
#include "service_os_adapt.h"

extern CString g_sipNumber;

// CDemoDataConfAppShareDlg Dialog

IMPLEMENT_DYNAMIC(CDemoDataConfAppShareDlg, CDialogEx)

CDemoDataConfAppShareDlg::CDemoDataConfAppShareDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoDataConfAppShareDlg::IDD, pParent)
    , isShareDesktop(false)
{

}

CDemoDataConfAppShareDlg::~CDemoDataConfAppShareDlg()
{
}

void CDemoDataConfAppShareDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
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
    ON_BN_CLICKED(IDC_BT_GETAPP, &CDemoDataConfAppShareDlg::OnBnClickedBtGetapp)
    ON_LBN_DBLCLK(IDC_LIST_SELECTED, &CDemoDataConfAppShareDlg::OnLbnDblclkListSelected)
    ON_MESSAGE(WM_DATACONF_MODULE_SCREEN_DATA, &CDemoDataConfAppShareDlg::OnDataConfASUpdateScreen)
END_MESSAGE_MAP()


// CDemoDataConfAppShareDlg message handle
BOOL CDemoDataConfAppShareDlg::OnInitDialog()
{
    CheckRadioButton(IDC_RADIO_SCREEN, IDC_RADIO_SCREEN, IDC_RADIO_SCREEN);
    CDialogEx::OnInitDialog();
    return TRUE;
}


void CDemoDataConfAppShareDlg::OnBnClickedBtGetapp()
{
    /*TSDK_UINT32 confHandle = get_data_conf_handle();
    TSDK_S_AS_WINDOW_INFO as_window_info[100];
    memset(as_window_info,0,sizeof(TSDK_S_AS_WINDOW_INFO)*100);
    unsigned int app_count;
    if (0 != service_data_conf_app_share_get_app_list(confHandle,as_window_info,&app_count))
    {
        AfxMessageBox(L"Getapp Failed");
    }
    m_list_apps.ResetContent();
    for (unsigned int i = 0;i<app_count;i++)
    {
        int nIndex = m_list_apps.AddString((LPCTSTR)as_window_info[i].window_title);
        m_list_apps.SetItemData(nIndex,(DWORD)as_window_info[i].window_handle);
    }
    UpdateData(TRUE);*/
}

LRESULT CDemoDataConfAppShareDlg::OnDataConfASUpdateScreen(WPARAM, LPARAM)
{
    TSDK_UINT32 confHandle = get_data_conf_handle();
    TSDK_S_CONF_AS_SCREEN_DATA screendata;
    service_memset_s(&screendata, sizeof(screendata), 0, sizeof(screendata));

    if (0 != service_data_conf_app_share_get_screen_data(confHandle, &screendata) || NULL == screendata.data)
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
    else if (TSDK_E_CONF_SCREEN_DATA_DIB == screendata.data_format)
    {
    }

    return 0L;
}
void CDemoDataConfAppShareDlg::SetBitmapNULL(void)
{
    m_stcDeskTop.SetBitmap2(NULL);
}


void CDemoDataConfAppShareDlg::OnBnClickedBtSelect()
{
    int iSelect = m_list_apps.GetCurSel();
    if (iSelect != LB_ERR)
    {
        DWORD hwnd = (DWORD)m_list_apps.GetItemData(iSelect);
        /*service_data_conf_as_set_app_share((void*)hwnd,SERVICE_DATA_CONF_IID_AS_ACTION_ADD);*/
        TCHAR pText[256];
        service_memset_s(pText, 256, 0, 256);
        m_list_apps.GetText(iSelect, pText);
        int nIndex = m_list_selected.AddString(pText);
        m_list_selected.SetItemData(nIndex, hwnd);
    }
    UpdateData(TRUE);
}


void CDemoDataConfAppShareDlg::OnBnClickedBtRemove()
{
    int iSelect = m_list_selected.GetCurSel();
    if (iSelect != LB_ERR)
    {
        DWORD hwnd = (DWORD)m_list_selected.GetItemData(iSelect);
        //service_data_conf_as_set_app_share((void*)hwnd,SERVICE_DATA_CONF_IID_AS_ACTION_DELETE);
        m_list_selected.DeleteString((unsigned int)iSelect);
    }
    UpdateData(TRUE);
}


void CDemoDataConfAppShareDlg::OnLbnDblclkListApp()
{
    OnBnClickedBtSelect();
}


void CDemoDataConfAppShareDlg::OnLbnDblclkListSelected()
{
    OnBnClickedBtRemove();
}

void CDemoDataConfAppShareDlg::updateShareDlg(bool bIsPresent)
{
    if (bIsPresent)
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
    else
    {
        setShareType(false);
        m_bt_select.EnableWindow(TRUE);
        m_bt_remove.EnableWindow(TRUE);
        m_bt_getapps.EnableWindow(TRUE);
    }
}

void CDemoDataConfAppShareDlg::OnBnClickedBtShare()
{
    unsigned int handle = get_data_conf_handle();

    ////get self number
    CString selfNum = CTools::GetSipNumber(g_sipNumber);
    std::string strSelfNum = CTools::UNICODE2UTF(selfNum);

    CString cstr;
    m_bt_share.GetWindowText(cstr);

    if (cstr == _T("StartShare"))
    {
        (void)service_data_conf_app_share_set_owner(handle, const_cast<char*>(strSelfNum.c_str()), TSDK_E_CONF_AS_ACTION_ADD);
        m_bt_share.SetWindowText(_T("StopShare"));
    }
    else
    {
        (void)service_data_conf_app_share_stop(handle);
        (void)service_data_conf_app_share_set_owner(handle, const_cast<char*>(strSelfNum.c_str()), TSDK_E_CONF_AS_ACTION_DELETE);
        m_bt_share.SetWindowText(_T("StartShare"));
    }
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
