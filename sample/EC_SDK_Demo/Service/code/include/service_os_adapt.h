//
//  service_os_adapt.h
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
#define SERVICE_OS_ADAPT __declspec(dllexport)
#else
#define SERVICE_OS_ADAPT __declspec(dllimport)
#endif

    SERVICE_OS_ADAPT int service_memset_s(void *dest, unsigned int destMax, int c, unsigned int count);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
