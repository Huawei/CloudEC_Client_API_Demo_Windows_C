//
//  service_data_conf_global_data.h
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
#define SERVICE_GLOBAL __declspec(dllexport)
#else
#define SERVICE_GLOBAL __declspec(dllimport)
#endif

    /**
     * @brief UI get unique data conference handle
     *
     * @param NA
     * @retval unsigned int
     *
     * @attention: NA
     **/
    SERVICE_GLOBAL unsigned int get_data_conf_handle();


    /**
     * @brief UI set unique data conference handle
     *
     * @param[in]unsigned int handle	[en]unique data conference handle
	                                    [cn]数据会议句柄
     * @retval void
     *
     * @attention: NA
     **/
    SERVICE_GLOBAL void set_data_conf_handle(unsigned int handle);

#define  CHECK_DATA_CONF_HANDLE(handle, ret) \
    if((0 == handle) || (0xFFFFFFFF == handle))\
    {\
    LOG_D_DATA_CONF_ERROR("Invalid handle.");\
    return ret;\
    }

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
