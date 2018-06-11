//
//  DemoShareStatic.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once

class CShareStatic : public CStatic
{
    DECLARE_DYNAMIC(CShareStatic)

public:
    CShareStatic();
    virtual ~CShareStatic();
    virtual void OnDraw(CDC* pDC);

protected:
    DECLARE_MESSAGE_MAP()

protected:
    HBITMAP m_hASBitmap;
    RECT borderRc;
public:

    void SetBitmap2(BITMAP *pBMP);
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //	CONF_HANDLE m_handle;

};
