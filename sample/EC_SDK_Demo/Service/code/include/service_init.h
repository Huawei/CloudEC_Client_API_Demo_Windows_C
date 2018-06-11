//
//  service_init.h
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
#define SERVICE_INIT __declspec(dllexport)
#else
#define SERVICE_INIT __declspec(dllimport)
#endif

    SERVICE_INIT int InitAllModule(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
