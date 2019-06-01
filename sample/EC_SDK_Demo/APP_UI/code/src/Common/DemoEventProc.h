//
//  DemoEventProc.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#pragma once

class NotifyCallBack
{
private:
    NotifyCallBack(void);
    ~NotifyCallBack(void);
public:
    static void loginMsgNotify(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data);
    static void callMsgNotify(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data);
    static void confMsgNotify(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data);
    static void uiPluginMsgNotify(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data);
};
