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
* [cn]��¼��Ϣ����
*/
typedef struct tagSERVICE_S_LOGIN_PARAM
{ 
	TSDK_CHAR user_name[TSDK_D_MAX_ACCOUNT_LEN + 1];                    /**< [en]Indicates the account username. 
																			 [cn]�˻��û�������Ȩ����ΪTSDK_E_AUTH_NORMALʱ��д */
	TSDK_CHAR password[TSDK_D_MAX_PASSWORD_LENGTH + 1];                 /**< [en]Indicates the account password. 
																			 [cn]�˻����룬��Ȩ����ΪTSDK_E_AUTH_NORMALʱ��д */
	TSDK_CHAR server_addr[TSDK_D_MAX_URL_LENGTH + 1];                   /**< [en]Indicates the server address. 
																			 [cn]��������ַ */
	TSDK_UINT16 server_port;                                            /**< [en]Indicates the server port. 
																		 	 [cn]�������˿ں� */
} SERVICE_S_LOGIN_PARAM;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SERVICE_LOGIN_DEF_H__ */
