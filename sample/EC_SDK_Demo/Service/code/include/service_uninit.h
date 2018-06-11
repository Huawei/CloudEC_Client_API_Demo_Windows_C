//
//  service_uninit.h
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
#define SERVICE_UNINIT __declspec(dllexport)
#else
#define SERVICE_UNINIT __declspec(dllimport)
#endif

    SERVICE_UNINIT int UninitAllModule(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
