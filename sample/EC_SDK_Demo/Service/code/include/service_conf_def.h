//
//  service_conf_def.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef __SERVICE_CONF_DEF_H__
#define __SERVICE_CONF_DEF_H__

#include "tsdk_conference_def.h"
#include "tsdk_manager_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

	/**
	* [en]This struct is used to describe book conf info.
	* [cn]ԤԼ������Ϣ
	*/
	typedef struct tagSERVICE_S_BOOK_CONF_INFO
	{
		TSDK_CHAR subject[TSDK_D_MAX_SUBJECT_LEN + 1];                   /**< [en]Indicates conference subject  ,this param is optional.
																		      [cn]�������� */
		TSDK_CHAR start_time[TSDK_D_MAX_TIME_FORMATE_LEN + 1];           /**< [en]Indicates conference start time, format:YYYY-MM-DD HH:MM  ,this param is optional.
																		      [cn]��ѡ�����鿪ʼʱ�䣬��ʽ��YYYY-MM-DD HH:MM����������ʱ������д */
		TSDK_E_CONF_TYPE conf_type;                                      /**< [en]Indicates conference type.
																		      [cn]�������� */
		TSDK_E_CONF_MEDIA_TYPE conf_media_type;                          /**< [en]Indicates conference media type.
																		      [cn]ý������ */
		TSDK_UINT32 attendee_num;                                        /**< [en]Indicates attendee number. 
                                                                              [cn]��������� */
		TSDK_S_ATTENDEE_BASE_INFO* attendee_list;                        /**< [en]Indicates attendee list. 
																		      [cn]������б� */
	}SERVICE_S_BOOK_CONF_INFO;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SERVICE_CONF_DEF_H__ */
