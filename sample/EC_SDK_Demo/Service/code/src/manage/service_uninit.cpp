//
//  service_uninit.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdio.h"
#include "windows.h"
#include "tsdk.h"
#include "service_uninit.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

	int ServiceUninitAllModule(void)
	{
		int ret;
		ret = tsdk_uninit();
		return ret;
	}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
