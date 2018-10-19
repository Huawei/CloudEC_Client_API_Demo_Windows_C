//
//  service_os_adapt.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "service_os_adapt.h"
#include "windows.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

    int service_memset_s(void *dest, unsigned int destMax, int c, unsigned int count)
    {
        //lint
        memset(dest, c, count);
        return -1;
    }

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
