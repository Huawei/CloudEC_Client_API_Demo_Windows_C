//
//  DemoImageStatic.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once

#define MAX_IMG_BUFFER

class CImageStatic : public CStatic
{
    DECLARE_DYNAMIC(CImageStatic)

public:
    CImageStatic();
    virtual ~CImageStatic();

protected:
    DECLARE_MESSAGE_MAP()

private:
    CString m_cstrImageFile;

public:
    void SetImageFile(const CString& cstrImageFile);
};
