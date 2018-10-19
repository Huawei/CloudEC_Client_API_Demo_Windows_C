//
//  DemoShareStatic.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoApp.h"
#include "DemoShareStatic.h"
#include "service_os_adapt.h"
#include "service_conf_interface.h"

// CShareStatic

IMPLEMENT_DYNAMIC(CShareStatic, CStatic)

CShareStatic::CShareStatic()
{
    m_hASBitmap = NULL;
    service_memset_s(&borderRc, sizeof(RECT), 0, sizeof(RECT));

}

CShareStatic::~CShareStatic()
{
    if (m_hASBitmap)
    {
        ::DeleteObject(m_hASBitmap);
    }
    //	m_handle = 0;
}


BEGIN_MESSAGE_MAP(CShareStatic, CStatic)
    ON_WM_PAINT()
    ON_WM_CREATE()
END_MESSAGE_MAP()



// CShareStatic 消息处理程序
HPEN hPen = NULL;
void CShareStatic::OnDraw(CDC* pDC)
{
    CRect rect;
    HDC hdc = pDC->GetSafeHdc();
    //return;
    GetClientRect(&rect);
    if (m_hASBitmap == NULL)
    {
        CBrush bs;

        bs.CreateSolidBrush(RGB(255, 255, 255));

        pDC->FillRect(&rect, &bs);

		void *data = service_data_conf_ds_share_get_surfacebmp(FALSE);

		if (data == NULL)
		{
			data = service_data_conf_ds_share_get_surfacebmp(TRUE);
		}
		if(data)
		{
			::BitBlt(pDC->m_hDC, 0, 0, rect.Width(), rect.Height(), (HDC)data, 0, 0, SRCCOPY);
		}
    }
    else
    {
        HDC memDc = ::CreateCompatibleDC(pDC->GetSafeHdc());
        HBITMAP old = (HBITMAP)::SelectObject(memDc, (HGDIOBJ)m_hASBitmap);
        BITMAP m_bitmap;
        GetObject(m_hASBitmap, sizeof(m_bitmap), &m_bitmap);
        //半色调模式，解决画面拉伸失真问题
        ::SetStretchBltMode(hdc, HALFTONE);
        //拉伸画面，适合dialog界面输出
        ::StretchBlt(hdc, 0, 0, rect.Width(), rect.Height(), memDc, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
        {
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            if (NULL == hPen)
            {
                //hPen = CreatePen(PS_SOLID, 1, RGB(0,255,255));
                hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
            }
            SelectObject(hdc, hPen);
            //SelectObject(hdc, GetStockObject(WHITE_PEN));
            Rectangle(hdc, borderRc.left, borderRc.top, borderRc.right + 1, borderRc.bottom + 1);
        }
        ::SelectObject(memDc, old);
        ::DeleteDC(memDc);
    }
}


void CShareStatic::SetBitmap2(BITMAP *pBMP)
{
    //////////////////////////////////////////////////////////////////////////
    GetClientRect(&borderRc);
    if (!pBMP)
    {
        if (m_hASBitmap)
        {
            ::DeleteObject(m_hASBitmap);
            m_hASBitmap = NULL;
            Invalidate(TRUE);

        }
        return;
    }
    if (m_hASBitmap == NULL)
    {
        m_hASBitmap = CreateBitmap(pBMP->bmWidth, pBMP->bmHeight, pBMP->bmPlanes, pBMP->bmBitsPixel, pBMP->bmBits);
    }
    else
    {
        ::DeleteObject(m_hASBitmap);
        m_hASBitmap = CreateBitmap(pBMP->bmWidth, pBMP->bmHeight, pBMP->bmPlanes, pBMP->bmBitsPixel, pBMP->bmBits);

    }

    Invalidate(TRUE);
}

void CShareStatic::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CStatic::OnPaint()
    OnDraw(&dc);
}

int CShareStatic::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CStatic::OnCreate(lpCreateStruct) == -1)
        return -1;
    GetClientRect(&borderRc);
    //borderRc.left = 5;
    //borderRc.top = 5;
    //borderRc.right = 50;
    //borderRc.bottom = 50;

    return 0;
}
