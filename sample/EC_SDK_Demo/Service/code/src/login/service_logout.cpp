//
//  service_logout.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdio.h"
#include "windows.h"
#include "tsdk.h"
#include "service_logout.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


	/*****************************************************************************
	函 数 名  : ServiceLogout
	功能描述  : 帐号登出
	输入参数  : 无
	输出参数  : 无
	返 回 值  : int
	调用函数  : tsdk_logout
	被调函数  : 

	修改历史      :
	1.日    期   : 2018年6月1日
	作    者   : EC Open development Team
	修改内容   : 新生成函数 

	*****************************************************************************/
    int ServiceLogout(void)
    {
        int ret = tsdk_logout();
        return ret;
    }


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
