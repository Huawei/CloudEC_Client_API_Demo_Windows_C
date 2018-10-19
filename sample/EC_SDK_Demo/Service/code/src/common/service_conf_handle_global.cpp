//
//  service_data_conf_global_data.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "service_conf_handle_global.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


    static unsigned int g_data_conf_handle;							//Global variables, unique data conference handle


    /**
     * @brief UI get unique data conference handle
     *
     * @param NA
     * @retval unsigned int
     *
     * @attention: NA
     **/
    unsigned int get_data_conf_handle()
    {
        return g_data_conf_handle;
    }


    /**
     * @brief UI set unique data conference handle
     *
     * @param[in]unsigned int handle	unique data conference handle
     * @retval void
     *
     * @attention: NA
     **/
    void set_data_conf_handle(unsigned int handle)
    {
        g_data_conf_handle = handle;
    }


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
