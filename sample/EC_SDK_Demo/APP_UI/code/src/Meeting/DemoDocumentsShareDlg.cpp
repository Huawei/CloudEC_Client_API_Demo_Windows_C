//
//  DemoDocumentsShareDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "resource.h"
#include <stdlib.h>
#include "afxdialogex.h"
#include "DemoDocumentsShareDlg.h"
#include "service_os_adapt.h"
#include "service_conf_handle_global.h"
#include "service_conf_interface.h"
#include "service_conf_def.h"


// CDemoDocumentsShareDlg Dialog

IMPLEMENT_DYNAMIC(CDemoDocumentsShareDlg, CDialogEx)

CDemoDocumentsShareDlg::CDemoDocumentsShareDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoDocumentsShareDlg::IDD, pParent)
    , m_isChairman(false)
    , m_isPresenter(false)
    , m_docId(0)
    , m_pageNum(0)
    , m_pageCount(0)
{

}

CDemoDocumentsShareDlg::~CDemoDocumentsShareDlg()
{
}

void CDemoDocumentsShareDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DOCUMENT, m_document_list);
    DDX_Control(pDX, IDC_ST_DOC_DESKTOP, m_static_desktop);
    DDX_Control(pDX, IDC_COMBO_SELECT_DOC, m_com_selectedPage);
    DDX_Control(pDX, IDC_BT_DOC_NEW, m_bt_new);
    DDX_Control(pDX, IDC_BT_DOC_DEL, m_bt_delete);
    DDX_Control(pDX, IDC_BT_DOC_UPDATE,m_bt_update);
    DDX_Control(pDX, IDC_BT_DOC_PRE_PAGE,m_bt_prepage);
    DDX_Control(pDX, IDC_BT_DOC_NEXT_PAGE,m_bt_nextpage);
}


BEGIN_MESSAGE_MAP(CDemoDocumentsShareDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_BN_CLICKED(IDC_BT_DOC_NEW, &CDemoDocumentsShareDlg::OnBnClickedBtNew)
    ON_BN_CLICKED(IDC_BT_DOC_DEL, &CDemoDocumentsShareDlg::OnBnClickedBtDel)
    ON_BN_CLICKED(IDC_BT_DOC_UPDATE, &CDemoDocumentsShareDlg::OnBnClickedBtUpdate)
    ON_BN_CLICKED(IDC_BT_DOC_PRE_PAGE, &CDemoDocumentsShareDlg::OnBnClickedBtPrePage)
    ON_BN_CLICKED(IDC_BT_DOC_NEXT_PAGE, &CDemoDocumentsShareDlg::OnBnClickedBtNextPage)
    ON_CBN_SELCHANGE(IDC_COMBO_SELECT_DOC, &CDemoDocumentsShareDlg::OnCbnSelchangeComboSelect)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_DRAW_DATA,&CDemoDocumentsShareDlg::OnDataConfDSDrawData)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_PAGE_IND,&CDemoDocumentsShareDlg::OnDSCurrentPage)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_DOCLOADED,&CDemoDocumentsShareDlg::OnDSLoaded)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_NEW,&CDemoDocumentsShareDlg::OnDSOpenNew)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_DELETE,&CDemoDocumentsShareDlg::OnDSDeleteDoc)
    ON_MESSAGE(WM_DATACONF_MODULE_DS_PAGE_LOADED, &CDemoDocumentsShareDlg::OnDSPageLoad)
END_MESSAGE_MAP()


// CDemoDocumentsShareDlg message handle

BOOL CDemoDocumentsShareDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    //Init documentlist///
    m_document_list.DeleteAllItems();
    m_document_list.ModifyStyle(0,LVS_SINGLESEL);
    m_document_list.InsertColumn(COL_DOCUMENT_STATE,_T("STATE"),LVCFMT_LEFT,65);
    m_document_list.InsertColumn(COL_DOCUMENT_NAME,_T("NAME"),LVCFMT_LEFT,65);
    m_document_list.InsertColumn(COL_DOCUMENT_PAGE_COUNT, _T("PAGE_COUNT"), LVCFMT_LEFT, 65);
    DWORD dwStyle = m_document_list.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;
    m_document_list.SetExtendedStyle(dwStyle);

    InitDocumentElenemt();

    updateShareDlg();

    return TRUE;  
}

void CDemoDocumentsShareDlg::InitDocumentElenemt()
{
    /*Set the properties of the whiteboard */
    /*Set background white, that is, 0xFFFFFFFF */
    service_data_conf_ds_share_set_background_color(TSDK_E_COMPONENT_DS);

    /*The default mode is TSDK_E_CONF_DS_DISPLAY_MODE_CENTER */
    service_data_conf_ds_share_set_display_mode(TSDK_E_COMPONENT_DS);

    CRect rct;
    m_static_desktop.GetClientRect(rct);
    CDC *pDC = m_static_desktop.GetDC();
    int ppiX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX);
    int ppiY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY);

    if (0 == service_data_conf_ds_share_set_canvas_size(TSDK_E_COMPONENT_DS, rct.Width()*ppiX, rct.Height()*ppiY))
    {
        /*Set success */
        SendMessage(WM_DATACONF_MODULE_DS_DRAW_DATA,NULL,NULL);
    }
}

void CDemoDocumentsShareDlg::OnBnClickedBtNew()
{
    CString docmentPath;
    CFileDialog filedlg(TRUE);
    if (filedlg.DoModal())
    {
        docmentPath = filedlg.GetPathName();
    }

    unsigned int newdocid = 0;
    if (0 != service_data_conf_ds_share_open_document(CTools::UNICODE2UTF(docmentPath).c_str(),&newdocid))
    {
        CTools::ShowMessageTimeout(_T("Load Doc failed"),2000);
    }
    m_docId = newdocid;
    m_pageNum = 1;        
}


void CDemoDocumentsShareDlg::OnBnClickedBtDel()
{
    int iSelIndex = m_document_list.GetNextItem(-1,LVNI_FOCUSED);
    if (-1 == iSelIndex)
    {
        CTools::ShowMessageTimeout(_T("No selected"),2000);
        return;
    }
    int docCur = iSelIndex + 1;
    if (m_document_list.GetItemCount() == 1)
    {
        docCur = -1;
    }
    else if (iSelIndex == m_document_list.GetItemCount() - 1)
    {
        docCur = 0;
    }

    unsigned int selectDocId = m_document_list.GetItemData(iSelIndex);
    if (selectDocId == 0)
    {
        return ;
    }
    /*Document*/
    if (0 == service_data_conf_ds_share_close_document(selectDocId))
    {
        /*Del Document Sucess*/
        if (docCur != -1)
        {
            m_document_list.SetItemState(docCur,LVIS_SELECTED | LVIS_FOCUSED,LVIS_SELECTED | LVIS_FOCUSED);
        }
        if (selectDocId == m_docId)
        {
            /*the (del) Document is the current sharing Document*/
            if (docCur != -1)
            {
                unsigned int documentId = m_document_list.GetItemData(docCur);
                service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_DS, documentId ,m_pageNum, TRUE);
            }
            else
            {
                /*the (del)Document is not the sharing Document*/
                m_com_selectedPage.ResetContent();
                m_com_selectedPage.AddString(_T("0P"));
                m_com_selectedPage.SetCurSel(0);
                m_static_desktop.SetBitmap2(NULL);
                Invalidate(TRUE);
                m_docId = 0;
                m_pageNum = 0;
            }
        }
    }
    else
    {
        /*resent the current sharing whiteboard*/
        service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_DS, m_docId ,m_pageNum, TRUE);
    }
}

void CDemoDocumentsShareDlg::OnCbnSelchangeComboSelect()
{
    if (m_docId == 0)
    {
        CTools::ShowMessageTimeout(_T("document or page is not exist"),2000);
        return;
    }

    int selectIndex = m_com_selectedPage.GetCurSel();
    /*if (!selectIndex)
    {
        return ;
    }*/
    
    /*Set current page*/
    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_DS, m_docId, selectIndex, TRUE);
    m_com_selectedPage.SetCurSel(selectIndex);
}

void CDemoDocumentsShareDlg::UpdateDocinfo(unsigned int docid)
{
    if(!docid)
    {
        return ;
    }
    
    for (int i = 0;i < m_document_list.GetItemCount();i++)
    {
        m_document_list.SetItemText(i,COL_DOCUMENT_STATE, _T(""));
    }

    int docIndex = GetDocumentIndex(docid);
    if (-1 != docIndex)
    {
        /*Document exists */
        /*Modify current document information */
        CString strDocId;
        strDocId.Format(_T("%d"), docid);
        m_document_list.SetItemText(docIndex,COL_DOCUMENT_NAME, strDocId);
        m_document_list.SetItemText(docIndex,COL_DOCUMENT_STATE, _T("Sharing"));

        CString strPageCount;
        strPageCount.Format(_T("%dP"), m_pageCount);
        m_document_list.SetItemText(docIndex, COL_DOCUMENT_PAGE_COUNT, strPageCount);
    }
    else
    {
        /*Document does not exist */
        /*Document does not exist at this time need to re create new documents in the document*/
        docIndex = m_document_list.GetItemCount();
        m_document_list.InsertItem(docIndex, _T(""));
        m_document_list.SetItemData(docIndex,(DWORD_PTR)docid);
        CString strDocId;
        strDocId.Format(_T("%d"), docid);
        m_document_list.SetItemText(docIndex, COL_DOCUMENT_NAME, strDocId);
        m_document_list.SetItemText(docIndex, COL_DOCUMENT_STATE, _T("Sharing"));

        CString strPageCount;
        strPageCount.Format(_T("%dP"), m_pageCount);
        m_document_list.SetItemText(docIndex, COL_DOCUMENT_PAGE_COUNT, strPageCount);
    }

    /*Set page control */
    m_com_selectedPage.ResetContent();
    if (!m_pageCount)
    {
        /*Page number is 0 */
        m_com_selectedPage.AddString(_T("0P"));
        m_com_selectedPage.SetCurSel(0);
    }
    else
    {
        /*Page number >=1 */
        for (int i = 1;i <= (int)m_pageCount;i++)
        {
            CString str;
            str.Format(_T("%dP"),i);
            m_com_selectedPage.AddString(str);
        }

        m_com_selectedPage.SetCurSel(0);
        service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_DS, m_docId, 0, FALSE);
    }
}

void CDemoDocumentsShareDlg::OnBnClickedBtUpdate()
{
    TSDK_S_DOC_PAGE_DETAIL_INFO info;
    service_memset_s(&info, sizeof(TSDK_S_DOC_PAGE_DETAIL_INFO), 0, sizeof(TSDK_S_DOC_PAGE_DETAIL_INFO));
    service_data_conf_ds_share_get_syn_document_info(TSDK_E_COMPONENT_DS, &info);
    
    m_docId = info.doc_page_info.document_id;
    m_pageNum = info.doc_page_info.page_index;

    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_DS, m_docId,m_pageNum, FALSE);
}

void CDemoDocumentsShareDlg::OnBnClickedBtPrePage()
{
    if (m_docId == 0 || m_pageNum == 0)
    {
        CTools::ShowMessageTimeout(_T("document or page is not exist"),2000);
        return;
    }

    int selectIndex = m_com_selectedPage.GetCurSel();
    if (!selectIndex)
    {
        return ;
    }

    /*Set current page*/
    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_DS, m_docId, selectIndex - 1, TRUE);
    m_com_selectedPage.SetCurSel(selectIndex - 1);
}

void CDemoDocumentsShareDlg::OnBnClickedBtNextPage()
{
    if (m_docId == 0)
    {
        CTools::ShowMessageTimeout(_T("document or page is not exist"), 2000);
        return;
    }

    int selectIndex = m_com_selectedPage.GetCurSel();

    if (selectIndex == m_pageCount -1)
    {
        /////最后一页，直接return；
        return ;
    }

    /*Set current page*/
    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_DS, m_docId, selectIndex + 1, TRUE);
    m_com_selectedPage.SetCurSel(selectIndex + 1);
}

int CDemoDocumentsShareDlg::GetDocumentIndex(unsigned int docid)
{
    int doc_number = m_document_list.GetItemCount();
    int iIndex = -1;
    for (int i = 0; i < doc_number; i++)
    {
        unsigned int document_id = (unsigned int)m_document_list.GetItemData(i);
        if (document_id == docid)
        {
            iIndex = i;
            break;
        }
    }
    return iIndex;
}

LRESULT CDemoDocumentsShareDlg::OnDataConfDSDrawData(WPARAM, LPARAM)
{
    CRect rect;
    m_static_desktop.GetClientRect(&rect);
    HDC* pData = (HDC*)service_data_conf_ds_share_get_surfacebmp(TSDK_E_COMPONENT_DS);
    if (pData)
    {
        HDC dc = ::GetDC(m_static_desktop.GetSafeHwnd());
        BOOL ret = ::BitBlt(dc, 0, 0, rect.Width(), rect.Height(), (HDC)pData, 0, 0, SRCCOPY);
        ::ReleaseDC(m_static_desktop.GetSafeHwnd(), dc);
    }

    return 0L;
}

LRESULT CDemoDocumentsShareDlg::OnDSCurrentPage(WPARAM wparam,LPARAM lparam)
{
    TSDK_S_DOC_PAGE_BASE_INFO* pageBaseInfo = (TSDK_S_DOC_PAGE_BASE_INFO*)wparam;
    m_pageNum = pageBaseInfo->page_index;
    m_docId = pageBaseInfo->document_id;

    UpdateDocinfo(m_docId);
    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_DS, m_docId,m_pageNum, FALSE);
    InitDocumentElenemt();
    delete(pageBaseInfo);
    return 0L;
}

LRESULT CDemoDocumentsShareDlg::OnDSLoaded(WPARAM wparam, LPARAM lparam)
{         
    TSDK_S_DOC_BASE_INFO* docBaseInfo = (TSDK_S_DOC_BASE_INFO*)wparam;
    unsigned int result = (unsigned int)lparam;

    m_docId = docBaseInfo->document_id;

    UpdateDocinfo(m_docId);
    
    return 0L;
}

LRESULT CDemoDocumentsShareDlg::OnDSOpenNew(WPARAM wparam,LPARAM lparam)
{
    TSDK_S_DOC_BASE_INFO* docBaseInfo = (TSDK_S_DOC_BASE_INFO*)wparam;

    m_pageCount = docBaseInfo->page_count;
    m_docId = docBaseInfo->document_id;

    delete (docBaseInfo);
    return 0L;
}

LRESULT CDemoDocumentsShareDlg::OnDSDeleteDoc(WPARAM wparam,LPARAM lparam)
{
    TSDK_S_DOC_SHARE_DEL_DOC_INFO* documentInfo = (TSDK_S_DOC_SHARE_DEL_DOC_INFO*)wparam;
    if (NULL == documentInfo)
    {
        return -1L;
    }

    int docIndex = GetDocumentIndex(documentInfo->doc_base_info.document_id);
    if ( -1 == docIndex)
    {
        return -1L;
    }
    
    m_document_list.DeleteItem(docIndex);

    delete (documentInfo);
    return 0L;
}

LRESULT CDemoDocumentsShareDlg::OnDSPageLoad(WPARAM wparam, LPARAM lparam)
{
    TSDK_S_DOC_PAGE_BASE_INFO* pageBaseInfo = (TSDK_S_DOC_PAGE_BASE_INFO*)wparam;
    m_docId = pageBaseInfo->document_id;
    m_pageNum = pageBaseInfo->page_index;

    delete (pageBaseInfo);
    return 0L;
}

void CDemoDocumentsShareDlg::updateShareDlg()
{
    if (m_isPresenter || m_isChairman)
    {
        m_bt_new.EnableWindow(TRUE);
        m_bt_delete.EnableWindow(TRUE);
        m_com_selectedPage.EnableWindow(TRUE);
        m_bt_prepage.EnableWindow(TRUE);
        m_bt_nextpage.EnableWindow(TRUE);
        m_bt_update.EnableWindow(TRUE);
    }
    else
    {
        m_bt_new.EnableWindow(FALSE);
        m_bt_delete.EnableWindow(FALSE);
        m_com_selectedPage.EnableWindow(FALSE);
        m_bt_prepage.EnableWindow(FALSE);
        m_bt_nextpage.EnableWindow(FALSE);
        m_bt_update.EnableWindow(FALSE);
    }
}
