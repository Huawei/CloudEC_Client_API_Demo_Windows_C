//
//  DemoDataconfCtrlDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoDataconfCtrlDlg.h"



IMPLEMENT_DYNAMIC(CDemoDataconfCtrlDlg, CDialogEx)

CDemoDataconfCtrlDlg::CDemoDataconfCtrlDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoDataconfCtrlDlg::IDD, pParent)
    , m_handle(0)
    , m_callID(0)
    , m_desktopShareDlg(NULL)
    , m_documentsShareDlg(NULL)
    , m_whiteboardShareDlg(NULL)
    , m_isChairman(false)
    , m_isPresenter(false)
    , m_Tab_CurSel(0)
{
    for (int i = 0; i < DATACONF_DLG_NUM; i++)
    {
        pDlg[i] = NULL;
    }
}

CDemoDataconfCtrlDlg::~CDemoDataconfCtrlDlg()
{
    /*service_data_conf_release();
    m_handle = 0;*/
    SAFE_DELETE(m_desktopShareDlg);
    SAFE_DELETE(m_documentsShareDlg);
    SAFE_DELETE(m_whiteboardShareDlg);
}

void CDemoDataconfCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATA_TAB, m_dataconf_tab);
}


BEGIN_MESSAGE_MAP(CDemoDataconfCtrlDlg, CDialogEx)
    ON_WM_CLOSE()
    ON_NOTIFY(TCN_SELCHANGE, IDC_DATA_TAB, &CDemoDataconfCtrlDlg::OnTcnSelchangeDataTab)
    ON_MESSAGE(WM_DATACONF_MODULE_SHARING_SESSION, &CDemoDataconfCtrlDlg::OnShareSession)
    ON_MESSAGE(WM_DATACONF_MODULE_SHARING_STATE, &CDemoDataconfCtrlDlg::OnShareState)
    ON_MESSAGE(WM_DATACONF_MODULE_SCREEN_DATA, &CDemoDataconfCtrlDlg::OnDataConfASUpdateScreen)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_NEW, &CDemoDataconfCtrlDlg::OnDSOpenNew)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_PAGE_LOADED, &CDemoDataconfCtrlDlg::OnDSPageLoad)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_DOCLOADED, &CDemoDataconfCtrlDlg::OnDSLoaded)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_DRAW_DATA, &CDemoDataconfCtrlDlg::OnDataConfDSDrawData)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_PAGE_IND, &CDemoDataconfCtrlDlg::OnDSCurrentPage)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_DELETE, &CDemoDataconfCtrlDlg::OnDSDeleteDoc)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_DOC_NEW, &CDemoDataconfCtrlDlg::OnWBOpenNew)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_CURRENT_PAGE, &CDemoDataconfCtrlDlg::OnWBSetCurrentPage)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_CURRENT_PAGE_IND, &CDemoDataconfCtrlDlg::OnWBSetCurrentPageInd)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_PAG_NEW, &CDemoDataconfCtrlDlg::OnWBNewPage)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_DRAW_DATA, &CDemoDataconfCtrlDlg::OnWBDrawData)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_DOC_DEL, &CDemoDataconfCtrlDlg::OnWBDelete)
    ON_MESSAGE(WM_DATACONF_MODULE_AS_PRIVILEGE_CHANGE, &CDemoDataconfCtrlDlg::OnSharePrivilegeStateChange)

END_MESSAGE_MAP()


// tup_sdk_demo_dataconf_ctrlDlg 消息处理程序
BOOL CDemoDataconfCtrlDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    InitUI();
    return TRUE;  // return TRUE unless you set the focus to a control
}

void CDemoDataconfCtrlDlg::InitUI()
{
    /*Init Dlg*/
    m_dataconf_tab.InsertItem(0, _T("Screen Share"));
    m_dataconf_tab.InsertItem(1, _T("Documents Share"));
    m_dataconf_tab.InsertItem(2, _T("Whiteboard Share"));

    CRect rect;
    m_dataconf_tab.GetClientRect(&rect);
    if (NULL == m_desktopShareDlg)
    {
        m_desktopShareDlg = new CDemoDataConfAppShareDlg;
    }
    if (!::IsWindow(m_desktopShareDlg->GetSafeHwnd()))
    {
        (void)m_desktopShareDlg->Create(IDD_DATA_CONF_SCREEN_APP, &m_dataconf_tab);
    }

    if (m_documentsShareDlg == NULL)
    {
        m_documentsShareDlg = new CDemoDocumentsShareDlg;
    }
    if (!::IsWindow(m_documentsShareDlg->GetSafeHwnd()))
    {
        (void)m_documentsShareDlg->Create(IDD_DATA_CONF_DOCUMENTS, &m_dataconf_tab);
    }

    if (m_whiteboardShareDlg == NULL)
    {
        m_whiteboardShareDlg = new CDemoWhiteboardShareDlg;
    }
    if (!::IsWindow(m_whiteboardShareDlg->GetSafeHwnd()))
    {
        (void)m_whiteboardShareDlg->Create(IDD_DATA_CONF_WHITEBOARD, &m_dataconf_tab);
    }

    pDlg[0] = m_desktopShareDlg;
    pDlg[1] = m_documentsShareDlg;
    pDlg[2] = m_whiteboardShareDlg;

    for (int i = 0; i < DATACONF_DLG_NUM; i++)
    {
        SetSubDlgPosion(rect, i);
    }
    m_Tab_CurSel = 0;
    pDlg[m_Tab_CurSel]->ShowWindow(SW_SHOW);
}

void CDemoDataconfCtrlDlg::SetSubDlgPosion(CRect rect, int index)
{
    rect.top += 24;
    pDlg[index]->MoveWindow(&rect);
    pDlg[index]->ShowWindow(SW_HIDE);
}

void CDemoDataconfCtrlDlg::OnTcnSelchangeDataTab(NMHDR *pNMHDR, LRESULT *pResult)
{
    CRect rect;
    m_dataconf_tab.GetClientRect(&rect);

    pDlg[m_Tab_CurSel]->ShowWindow(SW_HIDE);
    m_Tab_CurSel = m_dataconf_tab.GetCurSel();
    pDlg[m_Tab_CurSel]->ShowWindow(SW_SHOW);

    switch (m_Tab_CurSel)
    {
    case 0:
        if (m_desktopShareDlg)
        {
            m_desktopShareDlg->updateShareDlg();
        }
        break;
    case 1:
        if (m_documentsShareDlg)
        {
            /*m_documentsShareDlg->InitUI();*/
            m_documentsShareDlg->InitDocumentElenemt();
        }
        break;
    case 2:
        if (m_whiteboardShareDlg)
        {
            //m_whiteboardShareDlg->InitUI();
            //m_whiteboardShareDlg->InitWhiteboardElenemt();
        }
        break;
    default:
        break;
    }

    *pResult = 0;
}

void CDemoDataconfCtrlDlg::updateShareDlg()
{
    //update all UI buttons
    m_desktopShareDlg->SetChairman(m_isChairman);
    m_desktopShareDlg->SetPresent(m_isPresenter);
    m_desktopShareDlg->updateShareDlg();

    m_documentsShareDlg->SetChairman(m_isChairman);
    m_documentsShareDlg->SetPresent(m_isPresenter);
    m_documentsShareDlg->updateShareDlg();

    m_whiteboardShareDlg->SetChairman(m_isChairman);
    m_whiteboardShareDlg->SetPresent(m_isPresenter);
    m_whiteboardShareDlg->updateShareDlg();

    //switch (m_Tab_CurSel)
    //{
    //    case 0:
    //    {
    //        m_desktopShareDlg->SetChairman(m_isChairman);
    //        m_desktopShareDlg->SetPresent(m_isPresenter);
    //        m_desktopShareDlg->updateShareDlg();
    //        
    //        break;
    //    }
    //    
    //    case 1:
    //    {
    //        m_documentsShareDlg->SetChairman(m_isChairman);
    //        m_documentsShareDlg->SetPresent(m_isPresenter);
    //        m_documentsShareDlg->updateShareDlg();
    //        
    //        break;
    //    }
    //    
    //    case 2:
    //    {
    //        m_whiteboardShareDlg->SetChairman(m_isChairman);
    //        m_whiteboardShareDlg->SetPresent(m_isPresenter);
    //        m_whiteboardShareDlg->updateShareDlg();
    //        
    //        break;
    //        
    //    }
    //    
    //    default:
    //        break;
    //}
}


LRESULT CDemoDataconfCtrlDlg::OnShareSession(WPARAM wparam, LPARAM lparam)
{
    if (m_desktopShareDlg)
    {
        ::PostMessage(m_desktopShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_SHARING_SESSION, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnShareState(WPARAM wparam, LPARAM lparam)
{
    if (m_desktopShareDlg)
    {
        ::PostMessage(m_desktopShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_SHARING_STATE, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnDataConfASUpdateScreen(WPARAM wparam, LPARAM lparam)
{
    if (m_desktopShareDlg)
    {
        ::PostMessage(m_desktopShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_SCREEN_DATA, wparam, lparam);
    }
    return 0L;
}


LRESULT CDemoDataconfCtrlDlg::OnSharePrivilegeStateChange(WPARAM wparam, LPARAM lparam)
{
    if (m_desktopShareDlg)
    {
        ::PostMessage(m_desktopShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_AS_PRIVILEGE_CHANGE, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnDSOpenNew(WPARAM wparam, LPARAM lparam)
{
    if (m_documentsShareDlg)
    {
        ::PostMessage(m_documentsShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_NEW, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnDSPageLoad(WPARAM wparam, LPARAM lparam)
{
    if (m_documentsShareDlg)
    {
        ::PostMessage(m_documentsShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_PAGE_LOADED, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnDSLoaded(WPARAM wparam, LPARAM lparam)
{
    if (m_documentsShareDlg)
    {
        ::PostMessage(m_documentsShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_DOCLOADED, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnDataConfDSDrawData(WPARAM wparam, LPARAM lparam)
{
    if (m_documentsShareDlg)
    {
        ::PostMessage(m_documentsShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_DRAW_DATA, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnDSCurrentPage(WPARAM wparam, LPARAM lparam)
{
    if (m_documentsShareDlg)
    {
        ::PostMessage(m_documentsShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_PAGE_IND, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnDSDeleteDoc(WPARAM wparam, LPARAM lparam)
{
    if (m_documentsShareDlg)
    {
        ::PostMessage(m_documentsShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_DELETE, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnWBOpenNew(WPARAM wparam, LPARAM lparam)
{
    if (m_whiteboardShareDlg)
    {
        ::PostMessage(m_whiteboardShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_DOC_NEW, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnWBSetCurrentPage(WPARAM wparam, LPARAM lparam)
{
    if (m_whiteboardShareDlg)
    {
        ::PostMessage(m_whiteboardShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_CURRENT_PAGE, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnWBSetCurrentPageInd(WPARAM wparam, LPARAM lparam)
{
    if (m_whiteboardShareDlg)
    {
        ::PostMessage(m_whiteboardShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_CURRENT_PAGE_IND, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnWBNewPage(WPARAM wparam, LPARAM lparam)
{
    if (m_whiteboardShareDlg)
    {
        ::PostMessage(m_whiteboardShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_PAG_NEW, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnWBDrawData(WPARAM wparam, LPARAM lparam)
{
    if (m_whiteboardShareDlg)
    {
        ::PostMessage(m_whiteboardShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_DRAW_DATA, wparam, lparam);
    }
    return 0L;
}

LRESULT CDemoDataconfCtrlDlg::OnWBDelete(WPARAM wparam, LPARAM lparam)
{
    if (m_whiteboardShareDlg)
    {
        ::PostMessage(m_whiteboardShareDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_DOC_DEL, wparam, lparam);
    }
    return 0L;
}

