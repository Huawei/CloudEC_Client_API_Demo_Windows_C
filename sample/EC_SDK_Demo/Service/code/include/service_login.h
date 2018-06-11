//
//  service_login.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


#ifdef SERVICE_EXPORTS
#define SERVICE_LOGIN __declspec(dllexport)
#else
#define SERVICE_LOGIN __declspec(dllimport)
#endif

    SERVICE_LOGIN int ServiceLogin(const char *userAccount, const char *userPassword, const char *serverAddress, const unsigned short serverPort);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
