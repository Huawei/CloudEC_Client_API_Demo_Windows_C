//
//  DemoCallDlgManager.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once

#include <string>
#include <vector>
#include "DemoCallCtrlDlg.h"

using namespace std;

class CDemoCallCtrlDlg;
class CallDlgManager
{
private:
    CallDlgManager(void);
    ~CallDlgManager(void);

    typedef std::vector<CDemoCallCtrlDlg*> VEC_CALLDLG;
    VEC_CALLDLG m_vecCallDlg;


public:
    static CallDlgManager& GetInstance()
    {
        static CallDlgManager instance;
        return instance;
    }
    CDemoCallCtrlDlg* CreateCallDlgBySIPnumber(const std::string& sipnumber);
    CDemoCallCtrlDlg* GetCallDlgBySIPnumber(const std::string& sipnumber);
    CDemoCallCtrlDlg* GetCallDlgByNumber(const std::string& sipnumber);
    CDemoCallCtrlDlg* GetCallDlgByCallID(const unsigned int& callid);

    void DeleteCallDlgByCallDlg(CDemoCallCtrlDlg* pDlg);
};
