//
//  service_init.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
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

    int g_use_ui_plugin = 0;

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
        case TSDK_E_CONF_EVT_DS_DOC_NEW:
        {
            LOG_D_CALL_INFO("doc share new");
            break;
        }
		case TSDK_E_CONF_EVT_DS_DOC_PAGE_NEW:
		{
            LOG_D_CALL_INFO("doc share page new");
			break;
		}
		case TSDK_E_CONF_EVT_DS_DOC_CURRENT_PAGE:
		{
            LOG_D_CALL_INFO("doc share current page");
			break;
		}
        case TSDK_E_CONF_EVT_DS_DOC_PAGE_DATA_DOWNLOAD:
        {
            LOG_D_CALL_INFO("doc share page data download");
            break;
        }
        case TSDK_E_CONF_EVT_DS_DOC_PAGE_DEL:
        {
            LOG_D_CALL_INFO("doc share page delete");
            break;
        }
        default:
            //tsdk上报的消息，需要界面处理
            service_notify_to_ui_proc(msgid, param1, param2, data);
            break;
        }
    }

	/*****************************************************************************
	函 数 名  : ServiceInitAllModule
	功能描述  : 初始化所有模块功能
	输入参数  : 无      
	输出参数  : 无
	返 回 值  : int
	调用函数  : tsdk_init

	修改历史      :
	1.日    期   : 2018年6月1日
	作    者   : EC Open development Team
	修改内容   : 新生成函数 

	*****************************************************************************/
    int ServiceInitAllModule(void)
    {
        TSDK_RESULT ret;
        TSDK_S_APP_INFO_PARAM app_info;
        service_memset_s(&app_info, sizeof(app_info), 0, sizeof(app_info));

        app_info.client_type = TSDK_E_CLIENT_PC;
        strcpy_s(app_info.product_name, TSDK_D_MAX_PRODUCT_NAME_LEN + 1, "WeLink-desktop");
        app_info.support_audio_and_video_call = 1;
        app_info.support_audio_and_video_conf = 1;
        app_info.support_ctd = 1;
        app_info.support_data_conf = 1;
        app_info.support_rich_media_message = 0;
        app_info.support_enterprise_address_book = 1;
        app_info.support_im = 0;
        app_info.use_ui_plugin = g_use_ui_plugin;

        ret = tsdk_init(&app_info, COMPONENT_FN_CALLBACK_PTR);
        return ret;
    }

    /*****************************************************************************
    函 数 名  : service_set_config_param
    功能描述  : 设置是否使用IDO会控
    输入参数  : unsigned int isIdoConf
    输出参数  : 无
    返 回 值  : int
    调用函数  : tsdk_set_config_param

    修改历史      :
    1.日    期   : 2018年6月1日
    作    者   : EC Open development Team
    修改内容   : 新生成函数

    *****************************************************************************/
    int service_set_config_param(unsigned int isIdoConf)
    {
        TSDK_RESULT ret;
        TSDK_S_CONF_CTRL_PARAM confCtrlParam;
        service_memset_s(&confCtrlParam, sizeof(TSDK_S_CONF_CTRL_PARAM), 0, sizeof(TSDK_S_CONF_CTRL_PARAM));
        if (isIdoConf)
        {
            confCtrlParam.protocol = TSDK_E_CONF_CTRL_PROTOCOL_IDO;
        }
        else
        {
            confCtrlParam.protocol = TSDK_E_CONF_CTRL_PROTOCOL_REST;
        }

        ret = tsdk_set_config_param(TSDK_E_CONFIG_CONF_CTRL_PARAM, &confCtrlParam);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_AUTH_LOGIN_INFO("set conf ctrl param failed");
        }
        return ret;
    }


    int service_is_use_ui_plugin(void)
    {
        return g_use_ui_plugin;
    }


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
