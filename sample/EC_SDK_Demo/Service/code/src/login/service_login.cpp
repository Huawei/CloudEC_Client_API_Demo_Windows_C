//
//  service_login.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
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

    int SetProxyInfo(TSDK_S_PROXY_PARAM *proxyParam)
    {
        return tsdk_set_config_param(TSDK_E_CONFIG_PROXY_PARAM, (TSDK_VOID*)proxyParam);
    }

	/*****************************************************************************
	函 数 名  : ServiceLogin
	功能描述  : 帐号登录
	输入参数  : SERVICE_S_LOGIN_PARAM *loginInfo
	输出参数  : 无
	返 回 值  : int
	调用函数  : tsdk_login
	被调函数  : 

	修改历史      :
	1.日    期   : 2018年6月1日
	作    者   : EC Open development Team
	修改内容   : 新生成函数 

	*****************************************************************************/
    int ServiceLogin(SERVICE_S_LOGIN_PARAM *loginInfo)
    {
        int ret;

        TSDK_S_DISPLAY_LOCAL_INFO display_info;
        service_memset_s(&display_info, sizeof(display_info), 0, sizeof(display_info));
        strcpy_s(display_info.display_name, TSDK_D_MAX_DISPLAY_NAME_LEN + 1, loginInfo->display_name);
        ret = tsdk_set_config_param(TSDK_E_CONFIG_DISPLAY_LOCAL_INFO, (TSDK_VOID*)&display_info);

        
        TSDK_S_LOGIN_PARAM login_param;
        service_memset_s(&login_param, sizeof(login_param), 0, sizeof(login_param));

        login_param.user_id = 1;
        login_param.auth_type = TSDK_E_AUTH_NORMAL;
        strcpy_s(login_param.user_name, TSDK_D_MAX_ACCOUNT_LEN + 1, loginInfo->user_name);
        strcpy_s(login_param.password, TSDK_D_MAX_PASSWORD_LENGTH + 1, loginInfo->password);

        login_param.server_type = TSDK_E_SERVER_TYPE_PORTAL;
        strcpy_s(login_param.server_addr, TSDK_D_MAX_URL_LENGTH + 1, loginInfo->server_addr);
        login_param.server_port = loginInfo->server_port;

        ret = tsdk_login(&login_param);
        return ret;
    }


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
