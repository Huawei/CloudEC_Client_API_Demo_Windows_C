//
//  DemoWhiteboardShareDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "resource.h"
#include <stdlib.h>
#include "afxdialogex.h"
#include "DemoWhiteboardShareDlg.h"
#include "service_os_adapt.h"
#include "service_conf_handle_global.h"
#include "service_conf_interface.h"
#include "service_conf_def.h"



// CDemoWhiteboardShareDlg Dialog

IMPLEMENT_DYNAMIC(CDemoWhiteboardShareDlg, CDialogEx)

CDemoWhiteboardShareDlg::CDemoWhiteboardShareDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoWhiteboardShareDlg::IDD, pParent)
    , m_isChairman(false)
    , m_isPresenter(false)
    , m_cur_wb_id(0)
    , m_cur_page_index(0)
    , m_laserBegin(false)
    , m_annotationCreating(false)
    , m_annotationEditing(false)
    //, m_pageCount(0)
{
    service_memset_s(&m_laser_pointer_info, sizeof(m_laser_pointer_info), 0, sizeof(m_laser_pointer_info));
    service_memset_s(&m_penInfo, sizeof(m_penInfo), 0, sizeof(m_penInfo));
    service_memset_s(&m_ptOrg, sizeof(m_ptOrg), 0, sizeof(m_ptOrg));
}

CDemoWhiteboardShareDlg::~CDemoWhiteboardShareDlg()
{
    if (m_laser_pointer_info.data != NULL)
    {
        delete (char*)m_laser_pointer_info.data;
        m_laser_pointer_info.data = NULL ;
    }
    service_memset_s(&m_laser_pointer_info, sizeof(m_laser_pointer_info), 0, sizeof(m_laser_pointer_info));
}

void CDemoWhiteboardShareDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_WHITEBOARD, m_whiteboard_list);
    DDX_Control(pDX, IDC_ST_WB_DESKTOP, m_static_desktop);
    DDX_Control(pDX, IDC_COMBO_SELECT_WB, m_com_selectedPage);
    DDX_Control(pDX, IDC_BT_WB_NEW, m_bt_wb_new);
    DDX_Control(pDX, IDC_BT_WB_DEL, m_bt_wb_close);
    DDX_Control(pDX, IDC_BT_WB_UPDATE,m_bt_wb_update);
    DDX_Control(pDX, IDC_BT_WB_PRE_PAGE,m_bt_wb_prepage);
    DDX_Control(pDX, IDC_BT_WB_NEXT_PAGE,m_bt_wb_nextpage);
    DDX_Control(pDX, IDC_COMBO_ACTION_TYPE_WB, m_com_pentype);
    DDX_Control(pDX, IDC_COMBO_LINE_WB, m_com_linewidth);
}


BEGIN_MESSAGE_MAP(CDemoWhiteboardShareDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_BN_CLICKED(IDC_BT_WB_NEW, &CDemoWhiteboardShareDlg::OnBnClickedBtNew)
    ON_BN_CLICKED(IDC_BT_WB_DEL, &CDemoWhiteboardShareDlg::OnBnClickedBtDel)
    ON_BN_CLICKED(IDC_BT_WB_NEW_PAGE, &CDemoWhiteboardShareDlg::OnBnClickedPageNew)
    ON_BN_CLICKED(IDC_BT_WB_DEL_PAGE, &CDemoWhiteboardShareDlg::OnBnClickedPageDelete)
    ON_BN_CLICKED(IDC_BT_WB_UPDATE, &CDemoWhiteboardShareDlg::OnBnClickedBtUpdate)
    ON_BN_CLICKED(IDC_BT_WB_PRE_PAGE, &CDemoWhiteboardShareDlg::OnBnClickedBtPrePage)
    ON_BN_CLICKED(IDC_BT_WB_NEXT_PAGE, &CDemoWhiteboardShareDlg::OnBnClickedBtNextPage)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_DOC_NEW, &CDemoWhiteboardShareDlg::OnWBOpenNew)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_CURRENT_PAGE, &CDemoWhiteboardShareDlg::OnWBSetCurrentPage)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_CURRENT_PAGE_IND, &CDemoWhiteboardShareDlg::OnWBSetCurrentPageInd)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_PAG_NEW, &CDemoWhiteboardShareDlg::OnWBNewPage)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_DRAW_DATA, &CDemoWhiteboardShareDlg::OnWBDrawData)
    ON_MESSAGE(WM_DATACONF_MODULE_WB_DOC_DEL, &CDemoWhiteboardShareDlg::OnWBDelete)
    ON_BN_CLICKED(IDC_BT_COLOUR_WB, &CDemoWhiteboardShareDlg::OnBnClickedBtColourWb)
    ON_CBN_SELCHANGE(IDC_COMBO_ACTION_TYPE_WB, &CDemoWhiteboardShareDlg::OnCbnSelchangeComboActionType)    
    ON_BN_CLICKED(IDC_BT_WB_CANCEL, &CDemoWhiteboardShareDlg::OnBnClickedBtWbCancel)
    ON_BN_CLICKED(IDC_BT_WB_DEL_SELECTED, &CDemoWhiteboardShareDlg::OnBnClickedBtWbDelSelected)
    ON_CBN_SELCHANGE(IDC_COMBO_SELECT_WB, &CDemoWhiteboardShareDlg::OnCbnSelchangeComboSelectWb)
END_MESSAGE_MAP()


// CDemoDocumentsShareDlg message handle

void CDemoWhiteboardShareDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (NULL == GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB))
    {
        return;
    }
    
    CDC *pDC = GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB)->GetDC();
    if (pDC != NULL)
    {
        CRect m_rct;
        GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB)->GetClientRect(m_rct);
        CBrush m_brs;
        m_brs.CreateSolidBrush(m_penInfo.m_clr);
        pDC->FillRect(&m_rct, &m_brs);
    }
}

BOOL CDemoWhiteboardShareDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    
    /* Init laser pointer info*/
    service_memset_s(&m_laser_pointer_info, sizeof(TSDK_S_ANNOTATION_LASER_POINTER_INFO), 0, sizeof(TSDK_S_ANNOTATION_LASER_POINTER_INFO));
    InitLaserPointerData();

    /*Init Pen info*/
    m_penInfo.m_clr = 0x00FF00FF;
    m_penInfo.line_width = 1;
    m_penInfo.pen_style = TSDK_E_ANNOTATION_PEN_NORMAL;

    //Init documentlist///
    m_whiteboard_list.DeleteAllItems();
    m_whiteboard_list.ModifyStyle(0,LVS_SINGLESEL);
    m_whiteboard_list.InsertColumn(COL_WHITEBOARD_STATE,_T("STATE"),LVCFMT_LEFT,65);
    m_whiteboard_list.InsertColumn(COL_WHITEBOARD_ID,_T("WB_ID"),LVCFMT_LEFT,65);
    m_whiteboard_list.InsertColumn(COL_WHITEBOARD_PAGE_COUNT, _T("PAGE_COUNT"), LVCFMT_LEFT, 65);
    DWORD dwStyle = m_whiteboard_list.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;
    m_whiteboard_list.SetExtendedStyle(dwStyle);

    /*Init pen*/
    m_com_pentype.ResetContent();
    m_com_pentype.AddString(_T("None"));
    
    m_com_pentype.AddString(_T("Normal Brush"));
    m_com_pentype.AddString(_T("Hightlight Brush"));
    m_com_pentype.AddString(_T("Rectangle"));
    m_com_pentype.AddString(_T("Round Rectangle"));
    m_com_pentype.AddString(_T("Ellipse"));
    m_com_pentype.AddString(_T("Line"));
    m_com_pentype.AddString(_T("Line Arrow "));
    m_com_pentype.AddString(_T("Line Double Arrow "));
    
    m_com_pentype.AddString(_T("Laser Pointer"));
    
    m_com_pentype.SetCurSel(0);

    /*Init line*/
    m_com_linewidth.ResetContent();
    m_com_linewidth.AddString(_T("1 px"));
    m_com_linewidth.AddString(_T("2 px"));
    m_com_linewidth.AddString(_T("3 px"));
    m_com_linewidth.AddString(_T("4 px"));
    m_com_linewidth.AddString(_T("5 px"));
    m_com_linewidth.AddString(_T("6 px"));
    m_com_linewidth.SetCurSel(0);

    /*Init Color*/
    if (NULL != GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB))
    {
        CDC *pDC = GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB)->GetDC();    
        if (pDC != NULL)
        {
            CRect m_rect;
            GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB)->GetClientRect(m_rect);
            CBrush m_brs;
            m_brs.CreateSolidBrush(m_penInfo.m_clr);
            pDC->FillRect(&m_rect, &m_brs);
        }
    }
    
    /*init button*/
    GetDlgItem(IDC_BT_WB_NEW_PAGE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BT_WB_DEL_PAGE)->EnableWindow(TRUE);

    InitWhiteboardElenemt();

    updateShareDlg();

    return TRUE;  
}


void CDemoWhiteboardShareDlg::InitUI(void)
{
    ////Init documentlist///
    //m_whiteboard_list.DeleteAllItems();
    //while (m_whiteboard_list.DeleteColumn(0));
    //m_whiteboard_list.ModifyStyle(0, LVS_SINGLESEL);
    //m_whiteboard_list.InsertColumn(COL_WHITEBOARD_STATE, _T("STATE"), LVCFMT_LEFT, 70);
    //m_whiteboard_list.InsertColumn(COL_WHITEBOARD_NAME, _T("STATE"), LVCFMT_LEFT, 70);
    //DWORD dwStyle = m_whiteboard_list.GetExtendedStyle();
    //dwStyle |= LVS_EX_FULLROWSELECT;
    //dwStyle |= LVS_EX_GRIDLINES;
    //m_whiteboard_list.SetExtendedStyle(dwStyle);

    ///*Init pen*/
    //m_com_pentype.ResetContent();
    //m_com_pentype.AddString(_T("None"));
    //m_com_pentype.AddString(_T("Normal Brush"));
    //m_com_pentype.AddString(_T("Hightlight Brush"));
    //m_com_pentype.AddString(_T("Laser Pointer"));
    //m_com_pentype.SetCurSel(0);

    ///*Init line*/
    //m_com_linewidth.ResetContent();
    //m_com_linewidth.AddString(_T("1 px"));
    //m_com_linewidth.AddString(_T("2 px"));
    //m_com_linewidth.AddString(_T("3 px"));
    //m_com_linewidth.AddString(_T("4 px"));
    //m_com_linewidth.AddString(_T("5 px"));
    //m_com_linewidth.AddString(_T("6 px"));
    //m_com_linewidth.SetCurSel(0);

    ///*Init Color*/
    //CDC *pDC = GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB)->GetDC();
    //CRect m_rect;
    //GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB)->GetClientRect(m_rect);
    //CBrush m_brs;
    //m_brs.CreateSolidBrush(m_penInfo.m_clr);
    //pDC->FillRect(&m_rect, &m_brs);

    ///*init button*/
    //GetDlgItem(IDC_BT_WB_NEW_PAGE)->EnableWindow(TRUE);
    //GetDlgItem(IDC_BT_WB_DEL_PAGE)->EnableWindow(TRUE);
}

void CDemoWhiteboardShareDlg::InitWhiteboardElenemt()
{
    /*Set the properties of the whiteboard */
    /*Set background white, that is, 0xFFFFFFFF */
    service_data_conf_ds_share_set_background_color(TSDK_E_COMPONENT_WB);

    /*The default mode is TSDK_E_CONF_DS_DISPLAY_MODE_CENTER */
    service_data_conf_ds_share_set_display_mode(TSDK_E_COMPONENT_WB);

    CRect rct;
    m_static_desktop.GetClientRect(rct);
    CDC *pDC = m_static_desktop.GetDC();
    if (NULL == pDC)
    {
        return;
    }
    
    int ppiX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX);
    int ppiY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY);

    if (0 == service_data_conf_ds_share_set_canvas_size(TSDK_E_COMPONENT_WB, rct.Width()*ppiX, rct.Height()*ppiY))
    {
        /*Set success */
        SendMessage(WM_DATACONF_MODULE_DS_DRAW_DATA,NULL,NULL);
    }
}


void CDemoWhiteboardShareDlg::InitLaserPointerData()
{
    if (NULL == m_laser_pointer_info.data)
    {
        FILE* fp = NULL;
        errno_t err;
        std::string laserPointerPath = CTools::UNICODE2UTF(CTools::getCurrentPath()) + "\\image\\AnnotImage\\lp.png";
        err = fopen_s(&fp, laserPointerPath.c_str(), "rb");
        if((err == 0) && (fp != NULL))
        {
            (void)fseek(fp, 0, SEEK_END);
            unsigned int dataLen = (unsigned int)ftell(fp);
            (void)fseek(fp, 0, SEEK_SET);

            void* pData = new char[dataLen];
            if (NULL != pData)
            {
                (void)fread(pData, 1, dataLen, fp);
            }

            (void)fclose(fp);
            fp = NULL;

            m_laser_pointer_info.data = pData;
            m_laser_pointer_info.data_len = dataLen;
            m_laser_pointer_info.pic_format = TSDK_E_PICTURE_FORMAT_PNG;
            m_laser_pointer_info.pic_width = 28 * 15;
            m_laser_pointer_info.pic_high = 28 * 15;            
            m_laser_pointer_info.display_size.width = 28 * 15;
            m_laser_pointer_info.display_size.high = 28 * 15;
            m_laser_pointer_info.offset.x = 14 * 15;
            m_laser_pointer_info.offset.y = 14 * 15;

            m_laser_pointer_info.is_local = TSDK_FALSE;
            
        }  
    }
}


void CDemoWhiteboardShareDlg::OnBnClickedBtNew()
{
    unsigned int newdocid = 0;
    if (0 != service_data_conf_wb_share_open_whiteboard(&newdocid))
    {
        CTools::ShowMessageTimeout(_T("New Whiteboard failed"), 2000);
        return;
    }

    m_cur_wb_id = newdocid;
    m_cur_page_index = 0;

    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index, TRUE);
}


void CDemoWhiteboardShareDlg::OnBnClickedBtDel()
{
    int iSelIndex = m_whiteboard_list.GetNextItem(-1, LVNI_FOCUSED);
    if (-1 == iSelIndex)
    {
        CTools::ShowMessageTimeout(_T("No selected"), 2000);
        return;
    }

    int m_NewCur = iSelIndex + 1;
    if (m_whiteboard_list.GetItemCount() == 1)
    {
        m_NewCur = -1;
    }
    else if (iSelIndex == m_whiteboard_list.GetItemCount() - 1)
    {
        m_NewCur = 0;
    }

    unsigned int selectDocId = m_whiteboard_list.GetItemData(iSelIndex);
    if (selectDocId == 0)
    {
        return;
    }

    /*WhiteBoard*/
    if (0 == service_data_conf_wb_share_whiteboard_delete(selectDocId))
    {
        /*Del WhiteBoard Sucess*/
        if (m_NewCur != -1)
        {
            m_whiteboard_list.SetItemState(m_NewCur, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
        }
        if (selectDocId == m_cur_wb_id)
        {
            /*the (del) whiteboard is the current sharing whiteboard*/
            if (m_NewCur != -1)
            {
                unsigned int m_docid = m_whiteboard_list.GetItemData(m_NewCur);
                service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index, TRUE);
            }
            else
            {
                /*the (del)whiteboard is not the sharing whiteboard*/
                m_com_selectedPage.ResetContent();
                m_com_selectedPage.AddString(_T("0P"));
                m_com_selectedPage.SetCurSel(0);
                m_static_desktop.SetBitmap2(NULL);
                Invalidate(TRUE);
                m_cur_wb_id = 0;
                m_cur_page_index = 0;
            }
        }
    }
    else
    {
        /*resent the current sharing whiteboard*/
        service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index, TRUE);
    }
}


void CDemoWhiteboardShareDlg::OnBnClickedPageNew()
{
    if (m_cur_wb_id == 0)
    {
        CTools::ShowMessageTimeout(_T("No Document"), 200);
        return;
    }

    CRect Rect;
    m_static_desktop.GetClientRect(Rect);
    CDC *pDC = m_static_desktop.GetDC();
    int ppiX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX);
    int ppiY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY);
    
    unsigned int pageid = 0;
    if (0 != service_data_conf_wb_share_new_page(m_cur_wb_id, Rect.Width()*ppiX, Rect.Height()*ppiY, &pageid))
    {
        CTools::ShowMessageTimeout(_T("NewPage failed"), 200);
        return;
    }

    m_cur_page_index = (int)pageid;
    //m_pageCount++;
}

void CDemoWhiteboardShareDlg::OnBnClickedPageDelete()
{
    if (m_cur_wb_id == 0)
    {
        CTools::ShowMessageTimeout(_T("No document to del"), 3000);
        return;
    }

    unsigned int page_count = (unsigned int)GetDocumentPageCount(m_cur_wb_id);
    if (page_count == 0)
    {
        CTools::ShowMessageTimeout(_T("Cannot be deleted as a cover page, please specify when other shared pages"), 2000);
        return;
    }

    int selectIndex = m_com_selectedPage.GetCurSel();

    if (0 != service_data_conf_wb_share_whiteboard_delete_page(m_cur_wb_id, (unsigned int)selectIndex))
    {
        CTools::ShowMessageTimeout(_T("delete page return failed"), 2000);
        return;
    }

    page_count--;
    if (page_count > 0)
    {
        /*Set current page*/
        int curIndex = selectIndex;
        if (selectIndex == page_count)
        {
            curIndex--;
        }

        service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id, curIndex, TRUE);
        m_com_selectedPage.SetCurSel(curIndex);
    }

    UpdateWBinfo(m_cur_wb_id, page_count);
}

void CDemoWhiteboardShareDlg::OnCbnSelchangeComboSelectWb()
{
    if (m_cur_wb_id == 0)
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
    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id, selectIndex, TRUE);
    m_com_selectedPage.SetCurSel(selectIndex);
}

void CDemoWhiteboardShareDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    int ret;
    
    /*1.Judge available points */
    ClientToScreen(&point);
    CRect m_rect;
    m_static_desktop.GetWindowRect(m_rect);
    if (point.x < m_rect.left || point.x > m_rect.right || point.y < m_rect.top || point.y > m_rect.bottom)
    {
        return;
    }

    CDC *pDC = m_static_desktop.GetDC();
    if (NULL == pDC)
    {
        return;
    }
    
    int ppiX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX);
    int ppiY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY);
    ScreenToClient(&point);
    //m_ptOrg.x = (point.x - 340) * ppiX;
    //m_ptOrg.y = (point.y - 280) * ppiY;

    m_ptOrg.x = (point.x) * ppiX;
    m_ptOrg.y = (point.y) * ppiY;
    

    int m_Index = m_com_pentype.GetCurSel();
    switch (m_Index)
    {
        case 0:
        {
            /*Select is not marked, you can choose to mark */
            unsigned int id = 0xffffffff;
            TSDK_E_ANNOTATION_HIT_TEST_CODE rst;
            unsigned int annotType = 0;
            service_data_conf_annotation_hit_test_point(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index, &m_ptOrg, &id, &rst, &annotType);
            if ((id != 0xffffffff) && (rst != 0))    /*Select a label to enter the edit state */
            {
                /*The label is not selected before, clear the original selected, and select the current */
                if (!IsAnnotSelected(m_cur_wb_id, (unsigned int)m_cur_page_index, id))                    
                {
                    UnSelectAnnots(false);
                    unsigned int ids[1] = { id };
                    SelectAnnot(ids, 1);
                }
                /*Into the edit state, text tagging part of the temporary support */
                /*
                do with text

                */
                unsigned int* ids = new unsigned int[m_selectAnnots.size()];
                for (size_t i = 0; i < m_selectAnnots.size(); i++)
                {
                    ids[i] = m_selectAnnots[i];
                }

                ret = service_data_conf_annotation_edit_start(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index, ids,(int)m_selectAnnots.size(),id, rst,&m_ptOrg);
                if (ret == 0)
                {
                    m_annotationEditing = true;
                }
                
                delete[]ids;
                ids = NULL;

            }
            else  /*There is no point in any label, clear the original selected */
            {
                UnSelectAnnots(true);
            }
            
            break;
        }

        /* Normal Brus */
        case 1:
        {
            SetPenInfo(TSDK_E_ANNOTATION_PEN_NORMAL);
            ret = service_data_conf_annotation_create_start(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index,
                TSDK_E_ANNOTATION_DRAWING, TSDK_E_ANNOTATION_DRAWING_FREEHAND, m_ptOrg.x, m_ptOrg.y);
            if (0 == ret)
            {
                m_annotationCreating = true;
            }
            else
            {
                m_annotationCreating = false;
            }
            
            break;
        }
        

        /* Hightlight Brush */
        case 2:
        {
            SetPenInfo(TSDK_E_ANNOTATION_PEN_HILIGHT);
            ret = service_data_conf_annotation_create_start(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index,
                TSDK_E_ANNOTATION_DRAWING, TSDK_E_ANNOTATION_DRAWING_HILIGHT, m_ptOrg.x, m_ptOrg.y);
            if (0 == ret)
            {
                m_annotationCreating = true;
            }
            else
            {
                m_annotationCreating = false;
            }            
            break;
        }

        /* rectangle */
        case 3:
        {
            SetPenInfo(TSDK_E_ANNOTATION_PEN_NORMAL);
            ret = service_data_conf_annotation_create_start(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index,
                TSDK_E_ANNOTATION_DRAWING, TSDK_E_ANNOTATION_DRAWING_RECTANGLE, m_ptOrg.x, m_ptOrg.y);
            if (0 == ret)
            {
                m_annotationCreating = true;
            }       
            else
            {
                m_annotationCreating = false;
            }            
            break;
        }

        /* round rectangle */
        case 4:
        {
            SetPenInfo(TSDK_E_ANNOTATION_PEN_NORMAL);
            ret = service_data_conf_annotation_create_start(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index,
                TSDK_E_ANNOTATION_DRAWING, TSDK_E_ANNOTATION_DRAWING_ROUNDRECTANGLE, m_ptOrg.x, m_ptOrg.y);
            if (0 == ret)
            {
                m_annotationCreating = true;
            }  
            else
            {
                m_annotationCreating = false;
            }            
            break;
        }
        
        /* ellipse */
        case 5:
        {
            SetPenInfo(TSDK_E_ANNOTATION_PEN_NORMAL);
            ret = service_data_conf_annotation_create_start(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index,
                TSDK_E_ANNOTATION_DRAWING, TSDK_E_ANNOTATION_DRAWING_ELLIPSE, m_ptOrg.x, m_ptOrg.y);
            if (0 == ret)
            {
                m_annotationCreating = true;
            } 
            else
            {
                m_annotationCreating = false;
            }            
            break;
        }

        /* line */
        case 6:
        {
            SetPenInfo(TSDK_E_ANNOTATION_PEN_NORMAL);
            ret = service_data_conf_annotation_create_start(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index,
                TSDK_E_ANNOTATION_DRAWING, TSDK_E_ANNOTATION_DRAWING_LINE, m_ptOrg.x, m_ptOrg.y);
            if (0 == ret)
            {
                m_annotationCreating = true;
            }
            else
            {
                m_annotationCreating = false;
            }            
            break;
        }

        /* line arrow  */
        case 7:
        {
            SetPenInfo(TSDK_E_ANNOTATION_PEN_NORMAL);
            ret = service_data_conf_annotation_create_start(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index,
                TSDK_E_ANNOTATION_DRAWING, TSDK_E_ANNOTATION_DRAWING_LINEARROW, m_ptOrg.x, m_ptOrg.y);
            if (0 == ret)
            {
                m_annotationCreating = true;
            }
            else
            {
                m_annotationCreating = false;
            }            
            break;
        }

        /* line double arrow  */
        case 8:
        {
            SetPenInfo(TSDK_E_ANNOTATION_PEN_NORMAL);
            ret = service_data_conf_annotation_create_start(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index,
                TSDK_E_ANNOTATION_DRAWING, TSDK_E_ANNOTATION_DRAWING_LINEDOUBLEARROW, m_ptOrg.x, m_ptOrg.y);
            if (0 == ret)
            {
                m_annotationCreating = true;
            }
            else
            {
                m_annotationCreating = false;
            }            
            break;
        }
        
        default:
            break;
    }
    CDialog::OnLButtonDown(nFlags, point);
}

void CDemoWhiteboardShareDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
    /*1.Judge available points */
    ClientToScreen(&point);
    CRect m_rect;
    m_static_desktop.GetWindowRect(m_rect);
    if (point.x < m_rect.left || point.x > m_rect.right || point.y < m_rect.top || point.y > m_rect.bottom)
    {
        return;
    }
    ScreenToClient(&point);
    int m_Index = m_com_pentype.GetCurSel();
    switch (m_Index)
    {
        case 0:
        {
            /*Select is not marked, you can choose to mark */
            if (m_selectAnnots.size() == 0)
            {
                return;
            }

            if (m_annotationEditing)
            {
                service_data_conf_annotation_edit_finish(TSDK_E_COMPONENT_WB, TSDK_FALSE);
                m_annotationEditing = false;
            }

        }break;
        
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        {
            /*Select the ordinary brush, the brush is used to highlight the operation */
            service_data_conf_annotation_create_finish(TSDK_E_COMPONENT_WB, TSDK_FALSE);
            m_annotationCreating = false;
            break;
        }
        
        default:
            break;
    }

    CDialog::OnLButtonUp(nFlags, point);
}


void CDemoWhiteboardShareDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    int ret;
    
    /*1.Judge available points */
    ClientToScreen(&point);
    CRect m_rect;
    m_static_desktop.GetWindowRect(m_rect);
    if (point.x < m_rect.left || point.x > m_rect.right || point.y < m_rect.top || point.y > m_rect.bottom)
    {
        return;
    }

    ScreenToClient(&point);

    CDC *pDC = m_static_desktop.GetDC();
    if (NULL == pDC)
    {
        return;
    }

    int ppiX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX);
    int ppiY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY);

    TSDK_S_POINT tsdk_point = { 0 };
    //tsdk_point.x = (point.x - 340) * ppiX;
    //tsdk_point.y = (point.y - 280) * ppiY;

    tsdk_point.x = (point.x) * ppiX;
    tsdk_point.y = (point.y) * ppiY;    

    int m_Index = m_com_pentype.GetCurSel();
    switch (m_Index)
    {
        case 0:
        {
            /*Select is not marked, you can choose to mark */
            if (m_selectAnnots.size() == 0)
                return;

            if (m_annotationEditing)
            {
                /*Processing selected annotations */
                ret = service_data_conf_annotation_edit_update(TSDK_E_COMPONENT_WB, &tsdk_point);
                if (ret != 0)
                {
                    service_data_conf_annotation_edit_finish(TSDK_E_COMPONENT_WB, TSDK_TRUE);
                    m_annotationEditing = false;
                    UnSelectAnnots(false);
                }
            }
            break;
        }
        
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        {
            if (m_annotationCreating)
            {
                /*Select the ordinary brush, the brush is used to highlight the operation */
                service_data_conf_annotation_update(TSDK_E_COMPONENT_WB, &tsdk_point);
            }
            break;
        }
        
        case 9:
        {
            /*Laser pointer */
            service_data_conf_annotation_laser_pointer_moveto(TSDK_E_COMPONENT_WB, tsdk_point.x, tsdk_point.y);
            break;
        }
            
        default:
            break;
    }

    CDialog::OnMouseMove(nFlags, point);
}


bool CDemoWhiteboardShareDlg::IsAnnotSelected(unsigned int docId, unsigned int pageIndex, unsigned int id)
{
    if (docId != m_cur_wb_id || pageIndex != m_cur_page_index)
    {
        return false;
    }

    size_t len = m_selectAnnots.size();
    for (size_t i = 0; i < len; i++)
    {
        if (m_selectAnnots[i] == id)
        {
            return true;
        }
    }

    return false;
}

void CDemoWhiteboardShareDlg::UnSelectAnnots(bool bRedraw)
{
    if (m_selectAnnots.size() == 0)
    {
        return;
    }
    
    unsigned int* ids = new unsigned int[m_selectAnnots.size()];
    if (NULL == ids)
    {
        return;
    }

    for (size_t i = 0; i < m_selectAnnots.size(); i++)
    {
        ids[i] = m_selectAnnots[i];
    }

    service_data_conf_annotation_set_select(TSDK_E_COMPONENT_WB, m_cur_wb_id,m_cur_page_index,
        TSDK_E_ANNOTATION_SELECT_UN_SELECT,ids, (int)m_selectAnnots.size(), (bRedraw ? TSDK_TRUE : TSDK_FALSE));
    m_selectAnnots.clear();

    delete[] ids;
    ids = NULL;
}

void CDemoWhiteboardShareDlg::SelectAnnot(unsigned int* ids, int count)
{
    for (int i = 0; i < count; i++)
    {
        m_selectAnnots.push_back(ids[i]);
    }

    if (m_selectAnnots.size() == 0)
    {
        return;
    }

    unsigned int* newids = new unsigned int[m_selectAnnots.size()];
    if (NULL == newids)
    {
        return;
    }
    
    for (size_t i = 0; i < m_selectAnnots.size(); i++)
    {
        newids[i] = m_selectAnnots[i];
    }

    service_data_conf_annotation_set_select(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index, TSDK_E_ANNOTATION_SELECT_ALL, ids, (int)m_selectAnnots.size(), FALSE);
    delete[] newids;
    newids = NULL;

}

void CDemoWhiteboardShareDlg::UpdateWBinfo(unsigned int docid, unsigned int page_count)
{
    /*Update Doc information */
    if (!docid)
    {
        return;
    }
    
    /*Delete all documents*/
    for (int i = 0; i < m_whiteboard_list.GetItemCount(); i++)
    {
        m_whiteboard_list.SetItemText(i, COL_WHITEBOARD_STATE, _T(""));
    }

    int m_DocIndex = GetDocumentIndex(docid);
    if (-1 != m_DocIndex)
    {
        /*Document exists */
        /*Modify current document information */
        m_whiteboard_list.SetItemText(m_DocIndex, COL_WHITEBOARD_STATE, _T("Sharing"));

        CString id_str;
        id_str.Format(_T("%d"), docid);
        m_whiteboard_list.SetItemText(m_DocIndex, COL_WHITEBOARD_ID, id_str);

        CString count_str;
        count_str.Format(_T("%d"), page_count);
        m_whiteboard_list.SetItemText(m_DocIndex, COL_WHITEBOARD_PAGE_COUNT, count_str);
    }
    else
    {
        /*Document does not exist */
        /*Document does not exist at this time need to re create new documents in the document*/
        m_DocIndex = m_whiteboard_list.GetItemCount();
        m_whiteboard_list.InsertItem(m_DocIndex, _T(""));
        m_whiteboard_list.SetItemData(m_DocIndex, (DWORD_PTR)docid);

        CString id_str;
        id_str.Format(_T("%d"), docid);
        m_whiteboard_list.SetItemText(m_DocIndex, COL_WHITEBOARD_ID, id_str);

        CString count_str;
        count_str.Format(_T("%d"), page_count);
        m_whiteboard_list.SetItemText(m_DocIndex, COL_WHITEBOARD_PAGE_COUNT, count_str);
    }

    /*Set page control */
    m_com_selectedPage.ResetContent();
    if (0 == page_count)
    {
        /*Page number is 0 */
        m_com_selectedPage.AddString(_T("0P"));
        m_com_selectedPage.SetCurSel(0);
    }
    else
    {
        /*Page number >=1 */
        for (int i = 1; i <= (int)page_count; i++)
        {
            CString str;
            str.Format(_T("%dP"), i);
            m_com_selectedPage.AddString(str);
        }

        /*Get the current page(Ò³Âë) */
        m_com_selectedPage.SetCurSel(m_cur_page_index);
        /*service_data_conf_ds_share_set_current_page(m_docId, 0, FALSE, FALSE);*/
    }
}

void CDemoWhiteboardShareDlg::OnBnClickedBtUpdate()
{
    TSDK_S_DOC_PAGE_DETAIL_INFO info;
    service_data_conf_ds_share_get_syn_document_info(TSDK_E_COMPONENT_WB, &info);
    
    m_cur_wb_id = info.doc_page_info.document_id;
    m_cur_page_index = info.doc_page_info.page_index;

    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id,m_cur_page_index, FALSE);
}

void CDemoWhiteboardShareDlg::OnBnClickedBtPrePage()
{
    if (m_cur_wb_id == 0)
    {
        CTools::ShowMessageTimeout(_T("document or page is not exist"),2000);
        return;
    }

    int selectIndex = m_com_selectedPage.GetCurSel();
    if (0 == selectIndex)
    {
        return ;
    }

    /*Set current page*/
    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id, selectIndex - 1, TRUE);
    m_com_selectedPage.SetCurSel(selectIndex - 1);
}

void CDemoWhiteboardShareDlg::OnBnClickedBtNextPage()
{
    if (m_cur_wb_id == 0)
    {
        CTools::ShowMessageTimeout(_T("whiteboard or page is not exist"), 2000);
        return;
    }

    int selectIndex = m_com_selectedPage.GetCurSel();
    int pageCount = GetDocumentPageCount(m_cur_wb_id);
    if (selectIndex == pageCount -1)
    {
        return ;
    }

    /*Set current page*/
    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id, selectIndex + 1, TRUE);
    m_com_selectedPage.SetCurSel(selectIndex + 1);
}

int CDemoWhiteboardShareDlg::GetDocumentIndex(unsigned int docid)
{
    int doc_number = m_whiteboard_list.GetItemCount();
    int iIndex = -1;
    for (int i = 0; i < doc_number; i++)
    {
        unsigned int document_id = (unsigned int)m_whiteboard_list.GetItemData(i);
        if (document_id == docid)
        {
            iIndex = i;
            break;
        }
    }
    return iIndex;
}


int CDemoWhiteboardShareDlg::GetDocumentPageCount(unsigned int docid)
{
    int doc_number = m_whiteboard_list.GetItemCount();
    int page_count = 0;
    for (int i = 0; i < doc_number; i++)
    {
        unsigned int document_id = (unsigned int)m_whiteboard_list.GetItemData(i);
        if (document_id == docid)
        {
            CString page_count_str = m_whiteboard_list.GetItemText(i, COL_WHITEBOARD_PAGE_COUNT);
            page_count = _ttoi(page_count_str);
            break;
        }
    }
    return page_count;
}

LRESULT CDemoWhiteboardShareDlg::OnWBOpenNew(WPARAM wparam,LPARAM lparam)
{
    TSDK_S_DOC_BASE_INFO* docBaseInfo = (TSDK_S_DOC_BASE_INFO*)wparam;

    //m_pageCount = docBaseInfo->page_count;
    m_cur_wb_id = docBaseInfo->document_id;

    UpdateWBinfo(m_cur_wb_id, docBaseInfo->page_count);

    delete (docBaseInfo);
    return 0L;
}

void CDemoWhiteboardShareDlg::updateShareDlg()
{
    if (m_isPresenter || m_isChairman)
    {
        m_bt_wb_new.EnableWindow(TRUE);
        m_bt_wb_close.EnableWindow(TRUE);
        m_com_selectedPage.EnableWindow(TRUE);
        m_bt_wb_prepage.EnableWindow(TRUE);
        m_bt_wb_nextpage.EnableWindow(TRUE);
        m_bt_wb_update.EnableWindow(TRUE);
    }
    else
    {
        m_bt_wb_new.EnableWindow(FALSE);
        m_bt_wb_close.EnableWindow(FALSE);
        m_com_selectedPage.EnableWindow(FALSE);
        m_bt_wb_prepage.EnableWindow(FALSE);
        m_bt_wb_nextpage.EnableWindow(FALSE);
        m_bt_wb_update.EnableWindow(FALSE);
    }
}


void CDemoWhiteboardShareDlg::SetPenInfo(TSDK_E_ANNOTATION_PEN_TYPE penType)
{
    /*Color conversion from COLORREF format to COLORRGBA format */    
    TSDK_E_ANNOTATION_PEN_STYLE style = TSDK_E_ANNOTATION_PEN_STYLE_SOLID;
    unsigned int color = (unsigned int)(GetRValue(m_penInfo.m_clr) * 256 * 256 * 256 + GetGValue(m_penInfo.m_clr) * 256 * 256 + GetBValue(m_penInfo.m_clr) * 256 + 0xFF);
    unsigned int width = (m_com_linewidth.GetCurSel() + 1) * 15;

    if (TSDK_E_ANNOTATION_PEN_HILIGHT == penType)
    {
        width = width * 3;
    }

    if (0 != service_data_conf_annotation_set_pen(TSDK_E_COMPONENT_WB, penType, style, color, width))
    {
        CTools::ShowMessageTimeout(_T("UpdatePenInfo failed"), 3000);
    }
}


LRESULT CDemoWhiteboardShareDlg::OnWBSetCurrentPage(WPARAM wparam, LPARAM lparam)
{
    TSDK_S_DOC_PAGE_BASE_INFO* pageInfo = (TSDK_S_DOC_PAGE_BASE_INFO*)wparam;
    m_cur_wb_id = pageInfo->document_id;
    m_cur_page_index= pageInfo->page_index;
    UpdateWBinfo(m_cur_wb_id, pageInfo->page_count);
    //UpdatePenInfo(m_penInfo);
    /*service_data_conf_ds_share_set_current_page(m_docId, m_pageNum, FALSE, FALSE);*/
    InitWhiteboardElenemt();
    delete (pageInfo);
    return 0L;
}

LRESULT CDemoWhiteboardShareDlg::OnWBSetCurrentPageInd(WPARAM wparam, LPARAM lparam)
{
    TSDK_S_DOC_PAGE_BASE_INFO* pageInfo = (TSDK_S_DOC_PAGE_BASE_INFO*)wparam;
    m_cur_wb_id = pageInfo->document_id;
    m_cur_page_index = pageInfo->page_index;
    UpdateWBinfo(m_cur_wb_id, pageInfo->page_count);
    service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index, FALSE);
    delete (pageInfo);
    return 0L;
}

LRESULT CDemoWhiteboardShareDlg::OnWBNewPage(WPARAM wparam, LPARAM lparam)
{
    TSDK_S_DOC_PAGE_BASE_INFO* pageInfo = (TSDK_S_DOC_PAGE_BASE_INFO*)wparam;
    m_cur_wb_id = pageInfo->document_id;
    m_cur_page_index = pageInfo->page_index;
    UpdateWBinfo(m_cur_wb_id, pageInfo->page_count);
    (void)service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_WB, m_cur_wb_id, m_cur_page_index, TRUE);
    
    delete (pageInfo);
    return 0L;
}

LRESULT CDemoWhiteboardShareDlg::OnWBDrawData(WPARAM wparam, LPARAM lparam)
{
    TSDK_S_DOC_PAGE_BASE_INFO* pageInfo = (TSDK_S_DOC_PAGE_BASE_INFO*)wparam;
    m_cur_wb_id = pageInfo->document_id;
    m_cur_page_index = pageInfo->page_index;

    CRect rect;
    m_static_desktop.GetClientRect(rect);
    CDC *pDC = m_static_desktop.GetDC();
    void *data = service_data_conf_ds_share_get_surfacebmp(TSDK_E_COMPONENT_WB);
    if (data)
    {
        ::BitBlt(pDC->m_hDC, 0, 0, rect.Width(), rect.Height(), (HDC)data, 0, 0, SRCCOPY);
    }
    
    ::ReleaseDC(GetSafeHwnd(), pDC->GetSafeHdc());
    delete (pageInfo);
    return 0L;
}

LRESULT CDemoWhiteboardShareDlg::OnWBDelete(WPARAM wparam, LPARAM lparam)
{
    TSDK_S_WB_DEL_DOC_INFO* deleteDocInfo = (TSDK_S_WB_DEL_DOC_INFO*)wparam;
    m_cur_wb_id = deleteDocInfo->wb_base_info.document_id;
    
    int Index = GetDocumentIndex(m_cur_wb_id);
    if (-1 == Index)
    {
        return -1L;
    }

    /*remove document*/
    m_whiteboard_list.DeleteItem(Index);
    return 0L;
}


void CDemoWhiteboardShareDlg::OnBnClickedBtColourWb()
{
    // TODO: Add your control notification handler code here
    CColorDialog m_setColDlg;
    m_setColDlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;  /*CC_RGBINIT can display the last selected color */
    m_setColDlg.m_cc.rgbResult = m_penInfo.m_clr - 0xFF;      /*Record last selected color */
    if (IDOK == m_setColDlg.DoModal())
    {
        m_penInfo.m_clr = m_setColDlg.m_cc.rgbResult;
    }
    /*Draw colors on the control */
    if (NULL != GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB))
    {
        CDC *pDC = GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB)->GetDC();    
        if (pDC != NULL)
        {
            CRect m_rct;
            GetDlgItem(IDC_STATIC_CONTROL_COLOR_WB)->GetClientRect(m_rct);
            CBrush m_brs;
            m_brs.CreateSolidBrush(m_penInfo.m_clr);
            pDC->FillRect(&m_rct, &m_brs);
        }
    }    
    /*Update brush info */
    //UpdatePenInfo(m_penInfo);
}

void CDemoWhiteboardShareDlg::OnCbnSelchangeComboActionType()
{
    int penIndex = m_com_pentype.GetCurSel();
    switch (penIndex)
    {
        /*Laser pointer */
        case 9:
        {
            if (!m_laserBegin)
            {
                service_data_conf_annotation_laser_pointer_start(TSDK_E_COMPONENT_WB, &m_laser_pointer_info);
                m_laserBegin = true;
            }            

            break;
        }
        
        default:
        {
            if (m_laserBegin)
            {
                service_data_conf_annotation_laser_pointer_stop(TSDK_E_COMPONENT_WB);
                m_laserBegin = false;
            }

            break;
        }
    }
}


void CDemoWhiteboardShareDlg::OnBnClickedBtWbCancel()
{
    // TODO: Add your control notification handler code here
    UnSelectAnnots(true);
}




void CDemoWhiteboardShareDlg::OnBnClickedBtWbDelSelected()
{
    // TODO: Add your control notification handler code here
    if (m_selectAnnots.size() == 0)
    {
        return;
    }
    
    unsigned int* newids = new unsigned int[m_selectAnnots.size()];
    for (size_t i = 0; i < m_selectAnnots.size(); i++)
    {
        newids[i] = m_selectAnnots[i];
    }

    service_data_conf_annotation_delete(TSDK_E_COMPONENT_WB, m_cur_wb_id,(unsigned int)m_cur_page_index, newids, (int)m_selectAnnots.size());

    delete[] newids;
    newids = NULL;
}
