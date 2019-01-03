//
//  DemoDocumentsShareDlg.h
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

enum DOCUMENT_COLUMNID
{
	COL_DOCUMENT_STATE,
	COL_DOCUMENT_NAME,
    COL_DOCUMENT_PAGE_COUNT
};

// CDemoDocumentsShareDlg Dialog

class CDemoDocumentsShareDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDemoDocumentsShareDlg)

public:
	CDemoDocumentsShareDlg(CWnd* pParent = NULL);
	virtual ~CDemoDocumentsShareDlg();

// Dialog Data
	enum { IDD = IDD_DATA_CONF_DOCUMENTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
private:
	unsigned int m_docId;
	int m_pageNum;
	unsigned int m_pageCount;
	bool m_isChairman;
	bool m_isPresenter;
	CShareStatic m_static_desktop;
	CButton m_bt_new;
	CButton m_bt_delete;
	CButton m_bt_prepage;
	CButton m_bt_nextpage;
	CButton m_bt_update;
	CComboBox m_com_selectedPage;
	CListCtrl m_document_list;

public:
	virtual BOOL OnInitDialog();
	void UpdateDocinfo(unsigned int docid);
	int GetDocumentIndex(unsigned int docid);   ////Retrieves the ID of the document in the list, and returns -1 if it does not exist ////
	void InitDocumentElenemt();
	void SetChairman(bool isChairman) { m_isChairman = isChairman; };
	void SetPresent(bool isPresent) { m_isPresenter = isPresent; };
	void updateShareDlg();

	afx_msg void OnBnClickedBtNew();
	afx_msg void OnBnClickedBtDel();
	afx_msg void OnBnClickedBtUpdate();
	afx_msg void OnBnClickedBtPrePage();
	afx_msg void OnBnClickedBtNextPage();
	afx_msg void OnCbnSelchangeComboSelect();

public:
	afx_msg LRESULT OnDataConfDSDrawData(WPARAM,LPARAM);
	afx_msg LRESULT OnDSCurrentPage(WPARAM,LPARAM);
	afx_msg LRESULT OnDSLoaded(WPARAM,LPARAM);
    afx_msg LRESULT OnDSOpenNew(WPARAM,LPARAM);
    afx_msg LRESULT OnDSDeleteDoc(WPARAM,LPARAM);
    afx_msg LRESULT OnDSPageLoad(WPARAM, LPARAM);
};
