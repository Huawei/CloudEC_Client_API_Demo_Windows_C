//
//  service_callback_to_ui.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef __SERVICE_AUTH_LOGIN_TO_UI_H__
#define __SERVICE_AUTH_LOGIN_TO_UI_H__


#include "service_def.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef SERVICE_EXPORTS
#define SERVICE_CALLBACK __declspec(dllexport)
#else
#define SERVICE_CALLBACK __declspec(dllimport)
#endif

	/**
	* @brief UI set authentication and login component callback functions.
	*
	* @param [in] SERVICE_FN_CALLBACK_PTR fn   callback functions for events.
	* @retval void
	*
	* @attention Developers can modify the adaptation according to the needs
	**/
	SERVICE_CALLBACK void service_register_login_callback(SERVICE_FN_CALLBACK_PTR fn);
	SERVICE_CALLBACK void service_register_call_callback(SERVICE_FN_CALLBACK_PTR fn);
	SERVICE_CALLBACK void service_register_conf_callback(SERVICE_FN_CALLBACK_PTR fn);

	/**
	* @brief Authentication and login component Message Notify to UI.
	*
	* @param [in] unsigned int msg_id      Msg id.
	* @param [in] unsigned int param1      Param1.
	* @param [in] unsigned int param2      Param2.
	* @param [in] void*  data				Data.
	* @retval void
	*
	* @attention Developers can modify the adaptation according to the needs
	**/
	SERVICE_CALLBACK void service_notify_to_ui_proc(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data);
	SERVICE_CALLBACK void service_login_notify_to_ui(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data);
	SERVICE_CALLBACK void service_call_notify_to_ui(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data);
	SERVICE_CALLBACK void service_conf_notify_to_ui(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif
