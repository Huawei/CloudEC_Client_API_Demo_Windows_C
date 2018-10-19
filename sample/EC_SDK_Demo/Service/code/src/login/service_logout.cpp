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
	�� �� ��  : ServiceLogout
	��������  : �ʺŵǳ�
	�������  : ��
	�������  : ��
	�� �� ֵ  : int
	���ú���  : tsdk_logout
	��������  : 

	�޸���ʷ      :
	1.��    ��   : 2018��6��1��
	��    ��   : EC Open development Team
	�޸�����   : �����ɺ��� 

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
