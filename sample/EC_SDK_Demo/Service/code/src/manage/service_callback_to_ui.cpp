//
//  service_callback_to_ui.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "service_callback_to_ui.h"
#include "service_log.h"
#include "service_tools.h"
#include "tsdk_manager_def.h"
#include <string.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

    /*static SERVICE_FN_CALLBACK_PTR g_fn_ui_proc;	*/
    static SERVICE_FN_CALLBACK_PTR g_login_fn_ui_proc; //Global variables, authentication and login component call back function address
    static SERVICE_FN_CALLBACK_PTR g_call_fn_ui_proc;
    static SERVICE_FN_CALLBACK_PTR g_conf_fn_ui_proc;

    /**
     * @brief UI set authentication and login component callback functions.
     *
     * @param [in] SERVICE_FN_CALLBACK_PTR fn   callback functions for events.
     * @retval void
     *
     * @attention Developers can modify the adaptation according to the needs
     **/
    void service_register_login_callback(SERVICE_FN_CALLBACK_PTR fn)
    {

        CHECK_POINTER(fn);

        LOG_D_AUTH_LOGIN_DEBUG("Authentication and login component callback function address.[%#x]", fn);

        g_login_fn_ui_proc = fn;

        return;
    }

    void service_login_notify_to_ui(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data)
    {
        LOG_D_AUTH_LOGIN_DEBUG("Notify msg id:%u, param1:%u, param1:%u", msg_id, param1, param2);

        if (g_login_fn_ui_proc != NULL)
        {
            g_login_fn_ui_proc(msg_id, param1, param2, data);
        }

        return;
    }

    void service_register_call_callback(SERVICE_FN_CALLBACK_PTR fn)
    {

        CHECK_POINTER(fn);

        LOG_D_CALL_DEBUG("Call component callback function address.[%#x]", fn);

        g_call_fn_ui_proc = fn;

        return;
    }

    void service_call_notify_to_ui(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data)
    {
        LOG_D_CALL_DEBUG("Notify msg id:%u, param1:%u, param1:%u", msg_id, param1, param2);

        if (g_call_fn_ui_proc != NULL)
        {
            g_call_fn_ui_proc(msg_id, param1, param2, data);
        }

        return;
    }



    void service_register_conf_callback(SERVICE_FN_CALLBACK_PTR fn)
    {

        CHECK_POINTER(fn);

        LOG_D_VOICE_CONF_DEBUG("Conf component callback function address.[%#x]", fn);

        g_conf_fn_ui_proc = fn;

        return;
    }


    void service_conf_notify_to_ui(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data)
    {
        LOG_D_VOICE_CONF_DEBUG("Notify msg id:%u, param1:%u, param1:%u", msg_id, param1, param2);

        if (g_conf_fn_ui_proc != NULL)
        {
            g_conf_fn_ui_proc(msg_id, param1, param2, data);
        }

        return;
    }

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
    void service_notify_to_ui_proc(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data)
    {
        if ((unsigned int)TSDK_E_LOGIN_EVT_LOGIN_BEGIN < msg_id  && msg_id < (unsigned int)TSDK_E_LOGIN_EVT_LOGIN_BUTT)
        {
            service_login_notify_to_ui(msg_id, param1, param2, data);
        }

        if ((unsigned int)TSDK_E_CALL_EVT_CALL_BEGIN < msg_id && msg_id < (unsigned int)TSDK_E_CALL_EVT_CALL_BUTT)
        {
            service_call_notify_to_ui(msg_id, param1, param2, data);
        }

        if ((unsigned int)TSDK_E_CONF_EVT_CONF_BEGIN < msg_id && msg_id < (unsigned int)TSDK_E_CONF_EVT_CONF_BUTT)
        {
            service_conf_notify_to_ui(msg_id, param1, param2, data);
        }
    }


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
