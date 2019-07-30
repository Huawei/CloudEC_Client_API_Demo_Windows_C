//
//  service_login.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "service_login_def.h"


#ifdef SERVICE_EXPORTS
#define SERVICE_LOGIN __declspec(dllexport)
#else
#define SERVICE_LOGIN __declspec(dllimport)
#endif

    SERVICE_LOGIN int SetProxyInfo(TSDK_S_PROXY_PARAM *proxyParam);

	/**
	* @brief [en]This interface is used to log in.
	*        [cn]��¼
	* 
	* @param [in] SERVICE_S_LOGIN_PARAM *loginInfo        [en]Indicates login server and user account information.
	*                                                     [cn]��¼���������û��ʺ���Ϣ
	* @retval int                                         [en]If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                     [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
    SERVICE_LOGIN int ServiceLogin(SERVICE_S_LOGIN_PARAM *loginInfo);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
