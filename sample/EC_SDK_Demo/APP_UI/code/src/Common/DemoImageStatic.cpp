//
//  DemoImageStatic.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include "DemoImageStatic.h"


// CImageStatic
IMPLEMENT_DYNAMIC(CImageStatic, CStatic)

CImageStatic::CImageStatic()
: m_cstrImageFile(_T(""))
{

}

CImageStatic::~CImageStatic()
{
}

BEGIN_MESSAGE_MAP(CImageStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CImageStatic::SetImageFile(const CString& cstrImageFile)
{
	m_cstrImageFile = cstrImageFile;
}
