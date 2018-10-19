//
//  service_logout.h
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


#ifdef SERVICE_EXPORTS
#define SERVICE_LOGOUT __declspec(dllexport)
#else
#define SERVICE_LOGOUT __declspec(dllimport)
#endif

	/**
	* @brief [en]This interface is used to log out of the current account.
	*        [cn]登出
	* 
	* @retval TSDK_RESULT                          [en]If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                              [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA 
	**/
    SERVICE_LOGOUT int ServiceLogout(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
