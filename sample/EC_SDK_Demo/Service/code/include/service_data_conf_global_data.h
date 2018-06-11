//
//  service_data_conf_global_data.h
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
     * @param[in]unsigned int handle	unique data conference handle
     * @retval void
     *
     * @attention: NA
     **/
    SERVICE_GLOBAL void set_data_conf_handle(unsigned int handle);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
