//
//  DemoWhiteboardShareDlg.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "DemoData.h"
#include "DemoCommonTools.h"
#include "DemoShareStatic.h"
#include "service_conf_def.h"

enum WHITEBOARD_COLUMNID
{
    COL_WHITEBOARD_STATE,
    COL_WHITEBOARD_ID,
    COL_WHITEBOARD_PAGE_COUNT
};

enum LOCALRES_TYPE  /*Index for defining picture Tags */
{         
    LOCALRES_CHECK,
    LOCALRES_XCHECK,
    LOCALRES_LEFTPOINTER,
    LOCALRES_RIGHTPOINTER,
    LOCALRES_UPPOINTER,
    LOCALRES_DOWNPOINTER,
    LOCALRES_LASERPOINTER,
    LOCALRES_COUNT
};

typedef struct
{
    TSDK_E_ANNOTATION_PEN_TYPE pen_style;
    unsigned int line_width;
    COLORREF m_clr;
}PenInfo;

// CDemoDocumentsShareDlg Dialog

class CDemoWhiteboardShareDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CDemoWhiteboardShareDlg)

public:
    CDemoWhiteboardShareDlg(CWnd* pParent = NULL);
    virtual ~CDemoWhiteboardShareDlg();

// Dialog Data
    enum { IDD = IDD_DATA_CONF_WHITEBOARD };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
private:
    TSDK_S_ANNOTATION_LASER_POINTER_INFO m_laser_pointer_info;
    PenInfo m_penInfo;
    unsigned int m_cur_wb_id;
    int m_cur_page_index;
    bool m_annotationCreating;
    bool m_annotationEditing;
    bool m_laserBegin;
    //unsigned int m_pageCount;
    bool m_isChairman;
    bool m_isPresenter;
    CShareStatic m_static_desktop;
    CButton m_bt_wb_new;
    CButton m_bt_wb_close;
    CButton m_bt_wb_page_new;
    CButton m_bt_wb_page_delete;
    CButton m_bt_wb_prepage;
    CButton m_bt_wb_nextpage;
    CButton m_bt_wb_update;
    CComboBox m_com_selectedPage;
    CComboBox m_com_pentype;
    CComboBox m_com_linewidth;
    CListCtrl m_whiteboard_list;
    TSDK_S_POINT m_ptOrg;
    std::vector<unsigned int> m_selectAnnots;
    int m_cur_page_real_width;
    int m_cur_page_real_height;

public:
    virtual BOOL OnInitDialog();
    void UpdateWBinfo(unsigned int docid, unsigned int page_count);
    void UnSelectAnnots(bool bRedraw);
    void SelectAnnot(unsigned int* ids, int count);
    int GetDocumentIndex(unsigned int docid);   ////Retrieves the ID of the document in the list, and returns -1 if it does not exist ////
    int GetDocumentPageCount(unsigned int docid);
    void InitWhiteboardElenemt();
    void InitLaserPointerData();
    void SetChairman(bool isChairman) { m_isChairman = isChairman; };
    void SetPresent(bool isPresent) { m_isPresenter = isPresent; };
    void updateShareDlg();
    void SetPenInfo(TSDK_E_ANNOTATION_PEN_TYPE penType);
    void InitUI(void);
    bool IsAnnotSelected(unsigned int docId, unsigned int pageId, unsigned int id);

    afx_msg void OnPaint();
    afx_msg void OnBnClickedBtNew();
    afx_msg void OnBnClickedBtDel();
    afx_msg void OnBnClickedPageNew();
    afx_msg void OnBnClickedPageDelete();
    afx_msg void OnBnClickedBtUpdate();
    afx_msg void OnBnClickedBtPrePage();
    afx_msg void OnBnClickedBtNextPage();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
    afx_msg LRESULT OnWBOpenNew(WPARAM,LPARAM);
    afx_msg LRESULT OnWBSetCurrentPage(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnWBSetCurrentPageInd(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnWBNewPage(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnWBDrawData(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnWBDelete(WPARAM wparam, LPARAM lparam);
    afx_msg void OnBnClickedBtColourWb();
    afx_msg void OnCbnSelchangeComboActionType();
    afx_msg void OnBnClickedBtWbCancel();
    afx_msg void OnBnClickedBtWbDelSelected();
    afx_msg void OnCbnSelchangeComboSelectWb();
};
