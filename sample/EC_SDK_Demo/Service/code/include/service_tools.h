//
//  service_tools.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef __SERVICE_TOOLS_H__
#define __SERVICE_TOOLS_H__


#include <string.h>


#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


#define CHECK_POINTER_RETURN(point, ret) if(NULL == point)\
{\
	return ret;\
}


#define CHECK_POINTER(point) if(NULL == point)\
{\
	return;\
}


#define SAFE_FREE_ARRAY(point) if(NULL != point)\
{\
	free(point);\
	point = NULL;\
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif	/* __SERVICE_TOOLS_H__ */
