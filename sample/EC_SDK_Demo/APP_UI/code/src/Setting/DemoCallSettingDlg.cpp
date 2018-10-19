//
//  DemoCallSettingDlg.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "DemoCallSettingDlg.h"

// CDemoCallSettingDlg dialog

IMPLEMENT_DYNAMIC(CDemoCallSettingDlg, CDialogEx)

CDemoCallSettingDlg::CDemoCallSettingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDemoCallSettingDlg::IDD, pParent)
{

}

CDemoCallSettingDlg::~CDemoCallSettingDlg()
{
}

void CDemoCallSettingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE1, m_callsetTree);
}


BEGIN_MESSAGE_MAP(CDemoCallSettingDlg, CDialogEx)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CDemoCallSettingDlg::OnTvnSelchangedTree1)
END_MESSAGE_MAP()

BOOL CDemoCallSettingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    DWORD dwStyles = (DWORD)GetWindowLong(m_callsetTree.m_hWnd, GWL_STYLE);//获取树控制原风格 
    dwStyles |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
    (void)SetWindowLong(m_callsetTree.m_hWnd, GWL_STYLE, (LONG)dwStyles);//设置风格 

    HTREEITEM hItem;
    HTREEITEM hSubItem;

    /*hItem = m_callsetTree.InsertItem(_T("呼叫业务"),TVI_ROOT);
    hSubItem = m_callsetTree.InsertItem(_T("呼叫前转"), hItem);
    m_callsetTree.SetItemData(hSubItem, 0);
    hSubItem = m_callsetTree.InsertItem(_T("联动"),hItem, hSubItem);
    m_callsetTree.SetItemData(hSubItem, 1);*/

    hItem = m_callsetTree.InsertItem(_T("Advanced"), TVI_ROOT);

    hSubItem = m_callsetTree.InsertItem(_T("Media"), hItem);
    m_callsetTree.SetItemData(hSubItem, 0);

    CRect rect;
    if (NULL != GetDlgItem(IDC_STATIC))
    {
        GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);

        ScreenToClient(&rect);

        (void)m_mediaDlg.Create(CDemoMediaSettingDlg::IDD, this);
        m_mediaDlg.MoveWindow(rect);
        (void)m_mediaDlg.ShowWindow(SW_SHOW);
    }

    return TRUE;
}


// CDemoCallSettingDlg 消息处理程序

void CDemoCallSettingDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
    if ((NULL == pNMHDR) || (NULL == pResult))
    {
        return;
    }
    /*lint -e826 */
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    /*lint +e826 */
    HTREEITEM hItem = m_callsetTree.GetSelectedItem();
    switch (m_callsetTree.GetItemData(hItem))
    {
    case 0:
        (void)m_mediaDlg.ShowWindow(SW_SHOW);
        break;
    case 1:
        (void)m_mediaDlg.ShowWindow(SW_HIDE);
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        (void)m_mediaDlg.ShowWindow(SW_SHOW);
        break;
    case 5:
        break;
    case 6:
        (void)m_mediaDlg.ShowWindow(SW_HIDE);
        break;
    default:
        break;
    }
    *pResult = 0;
}
