//
//  service_init.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdio.h"
#include "windows.h"
#include "tsdk.h"
#include "service_init.h"
#include "service_callback_to_ui.h"
#include "service_log.h"
#include "service_os_adapt.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

    /**
    * tsdk_init的接口参数回调COMPONENT_FN_CALLBACK_PTR
    */
    TSDK_VOID COMPONENT_FN_CALLBACK_PTR(TSDK_UINT32 msgid, TSDK_UINT32 param1, TSDK_UINT32 param2, TSDK_VOID *data)
    {
        //tsdk上报的消息，不需要界面层处理的，在service层处理掉
        switch (msgid)
        {
        case TSDK_E_LOGIN_EVT_AUTH_SUCCESS:
        {
            LOG_D_AUTH_LOGIN_INFO("login auth success !");
            break;
        }
        case TSDK_E_CALL_EVT_CALL_START_RESULT:
        {
            LOG_D_AUTH_LOGIN_INFO("start call result");
            break;
        }
        case TSDK_E_CALL_EVT_CALL_RTP_CREATED:
        {
            LOG_D_CALL_INFO("start call Event");
            break;
        }
        case TSDK_E_CALL_EVT_CALL_RINGBACK:
        {
            LOG_D_CALL_INFO("call ringback");
            break;
        }
        case TSDK_E_CALL_EVT_HOLD_FAILED:
        {
            LOG_D_CALL_INFO("hold failed");
            break;
        }
        case TSDK_E_CALL_EVT_UNHOLD_FAILED:
        {
            LOG_D_CALL_INFO("unhold failed");
            break;
        }
        case TSDK_E_CONF_EVT_BOOK_CONF_RESULT:
        {
            LOG_D_CALL_INFO("book conf result");
            break;
        }
        default:
            //tsdk上报的消息，需要界面处理
            service_notify_to_ui_proc(msgid, param1, param2, data);
            break;
        }
    }

    /**
    *This method is used to init all tsdk service
    *初始化各个tsdk模块业务
    *@param logPath log path
    */
    int InitAllModule(void)
    {
        int ret;
        TSDK_S_APP_INFO_PARAM app_info;
        service_memset_s(&app_info, sizeof(app_info), 0, sizeof(app_info));

        app_info.client_type = TSDK_E_CLIENT_PC;
        strcpy_s(app_info.product_name, TSDK_D_MAX_PRODUCT_NAME_LEN + 1, "SoftClient on Desktop");
        app_info.support_audio_and_video_call = 1;
        app_info.support_audio_and_video_conf = 1;
        app_info.support_ctd = 1;
        app_info.support_data_conf = 1;
        app_info.support_rich_media_message = 1;
        app_info.support_enterprise_address_book = 1;
        app_info.support_im = 1;

        ret = tsdk_init(&app_info, COMPONENT_FN_CALLBACK_PTR);
        return ret;
    }


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
