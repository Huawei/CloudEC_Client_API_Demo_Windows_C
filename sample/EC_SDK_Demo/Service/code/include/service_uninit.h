//
//  service_uninit.h
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
#define SERVICE_UNINIT __declspec(dllexport)
#else
#define SERVICE_UNINIT __declspec(dllimport)
#endif

	/**
	* @brief [en]This interface is used to uninit all function
	*        [cn] 去初始化所有功能
	* 
	* @param [in] void
	*
	* @retval int                                  [en] If it's success return TSDK_SUCCESS, otherwise, return the corresponding error code.
	*                                              [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention [en] This interface is invoked before program exit, stop related service before it's invoked
	*            [cn] 程序退出前调用，调用前停止相关业务
	**/
    SERVICE_UNINIT int ServiceUninitAllModule(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
