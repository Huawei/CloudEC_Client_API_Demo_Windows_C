//
//  service_login.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdio.h"
#include "windows.h"
#include "tsdk.h"
#include "service_login.h"
#include "service_os_adapt.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

    int ServiceLogin(const char *userAccount, const char *userPassword, const char *serverAddress, const unsigned short serverPort)
    {
        int ret;
        TSDK_S_LOGIN_PARAM login_param;
        service_memset_s(&login_param, sizeof(login_param), 0, sizeof(login_param));

        login_param.user_id = 1;
        login_param.auth_type = TSDK_E_AUTH_NORMAL;
        strcpy_s(login_param.user_name, TSDK_D_MAX_ACCOUNT_LEN + 1, userAccount);
        strcpy_s(login_param.password, TSDK_D_MAX_PASSWORD_LENGTH + 1, userPassword);

        login_param.server_type = TSDK_E_SERVER_TYPE_PORTAL;
        strcpy_s(login_param.server_addr, TSDK_D_MAX_URL_LENGTH + 1, serverAddress);
        login_param.server_port = serverPort;

        ret = tsdk_login(&login_param);
        return ret;
    }


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
