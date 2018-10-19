//
//  service_uninit.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
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

	/**
	* @brief [en]This interface is used to uninit all function
	*        [cn] ȥ��ʼ�����й���
	* 
	* @param [in] void
	*
	* @retval int                                  [en] If it's success return TSDK_SUCCESS, otherwise, return the corresponding error code.
	*                                              [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention [en] This interface is invoked before program exit, stop related service before it's invoked
	*            [cn] �����˳�ǰ���ã�����ǰֹͣ���ҵ��
	**/
    SERVICE_UNINIT int ServiceUninitAllModule(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
