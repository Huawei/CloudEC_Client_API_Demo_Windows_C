//
//  DemoCustomMessage.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef __DEMO_CUSTOM_MESSAGE_H__
#define __DEMO_CUSTOM_MESSAGE_H__

using namespace std;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define DEMO_CUSTOM_BEGIN               WM_USER

#define CUSTOM_IDC_BEGIN                (DEMO_CUSTOM_BEGIN + 100)
#define CUSTOM_WM_BEGIN                 (DEMO_CUSTOM_BEGIN + 300)


//login message
#define WM_LOGIN_RESULT                 (CUSTOM_WM_BEGIN + 1)
#define WM_LOGOUT_RESULT                (CUSTOM_WM_BEGIN + 2)
#define WM_LOGIN_TOKEN_REFRESH_FAILED   (CUSTOM_WM_BEGIN + 3)
#define WM_FORCE_LOGOUT                 (CUSTOM_WM_BEGIN + 4)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
