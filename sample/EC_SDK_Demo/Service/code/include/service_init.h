//
//  service_init.h
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
#define SERVICE_INIT __declspec(dllexport)
#else
#define SERVICE_INIT __declspec(dllimport)
#endif

	/**
	* @brief [en]This interface is used to init all function
	*        [cn] ��ʼ������ģ�鹦��
	* 
	* @param [in] NA
	*
	* @retval int                                  [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                              [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention [en] NA.
	*            [cn] ����
	**/
    SERVICE_INIT int ServiceInitAllModule(void);

    /**
    * @brief [en]This interface is used to set config param
    *        [cn]����ҵ�����
    *
    * @param [in] unsigned int isIdoConf                   [en] Indicates if use ido conf control.
    *                                                      [cn] ��ʾ�Ƿ�ʹ��IDO���
    *
    * @retval int                                  [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
    *                                              [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
    *
    * @attention [en] NA.
    *            [cn] ����
    **/
    SERVICE_INIT int service_set_config_param(unsigned int isIdoConf);

    SERVICE_INIT int service_is_use_ui_plugin(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
