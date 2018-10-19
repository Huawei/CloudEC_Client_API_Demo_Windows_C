//
//  service_login_def.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef __SERVICE_LOGIN_DEF_H__
#define __SERVICE_LOGIN_DEF_H__

#include "tsdk_def.h"
#include "tsdk_manager_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/**
* [en]This structure is used to describe login parameters.
* [cn]登录信息参数
*/
typedef struct tagSERVICE_S_LOGIN_PARAM
{ 
	TSDK_CHAR user_name[TSDK_D_MAX_ACCOUNT_LEN + 1];                    /**< [en]Indicates the account username. 
																			 [cn]账户用户名，鉴权类型为TSDK_E_AUTH_NORMAL时填写 */
	TSDK_CHAR password[TSDK_D_MAX_PASSWORD_LENGTH + 1];                 /**< [en]Indicates the account password. 
																			 [cn]账户密码，鉴权类型为TSDK_E_AUTH_NORMAL时填写 */
	TSDK_CHAR server_addr[TSDK_D_MAX_URL_LENGTH + 1];                   /**< [en]Indicates the server address. 
																			 [cn]服务器地址 */
	TSDK_UINT16 server_port;                                            /**< [en]Indicates the server port. 
																		 	 [cn]服务器端口号 */
} SERVICE_S_LOGIN_PARAM;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SERVICE_LOGIN_DEF_H__ */
