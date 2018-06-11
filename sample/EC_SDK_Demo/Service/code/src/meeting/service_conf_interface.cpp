//
//  service_conf_interface.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "service_conf_interface.h"
#include "service_log.h"
#include "service_data_conf_global_data.h"
#include "tsdk_error_def.h"
#include "tsdk_conference_interface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


    int service_conf_book(TSDK_S_BOOK_CONF_INFO *bookConfInfo)
    {
        TSDK_RESULT ret;
        ret = tsdk_book_conference(bookConfInfo);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("book conf failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }


    int service_conf_get_list(TSDK_S_QUERY_CONF_LIST_REQ *arg)
    {
        TSDK_RESULT ret;
        ret = tsdk_query_conference_list(arg);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("get conf list failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_join(TSDK_S_CONF_JOIN_PARAM* confJoinParam, TSDK_CHAR* joinNumber, unsigned int isVideoJoin, TSDK_UINT32 *callId)
    {
        TSDK_RESULT ret;
        ret = tsdk_join_conference(confJoinParam, joinNumber, isVideoJoin, callId);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("join conf failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_query_conference_detail(TSDK_S_QUERY_CONF_DETAIL_REQ *arg)
    {
        TSDK_RESULT ret;
        ret = tsdk_query_conference_detail(arg);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("query conference detail failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_mute(TSDK_UINT32 confHandle, unsigned int isMute)
    {
        TSDK_RESULT ret;
        ret = tsdk_mute_conference(confHandle, isMute);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("mute conference failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_mem_add(TSDK_UINT32 confHandle, const TSDK_S_ADD_ATTENDEES_INFO* addAttendeeInfo)
    {
        TSDK_RESULT ret;
        ret = tsdk_add_attendee(confHandle, addAttendeeInfo);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("add conf member failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_lock(TSDK_UINT32 confHandle, unsigned int isLock)
    {
        TSDK_RESULT ret;
        ret = tsdk_lock_conference(confHandle, isLock);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("lock conf failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_leave(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_leave_conference(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("leave conf failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_end(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_end_conference(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("end conf failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_mem_delete(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee)
    {
        TSDK_RESULT ret;
        ret = tsdk_remove_attendee(confHandle, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("remove mem failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_mem_mute(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee, unsigned int isMute)
    {
        TSDK_RESULT ret;
        ret = tsdk_mute_attendee(confHandle, attendee, isMute);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("mute mem failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_mem_hangup(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee)
    {
        TSDK_RESULT ret;
        ret = tsdk_hang_up_attendee(confHandle, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("hangup mem failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_mem_accept(TSDK_UINT32 confHandle, unsigned int isJoinVideo)
    {
        TSDK_RESULT ret;
        ret = tsdk_accept_conference(confHandle, isJoinVideo);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("accept conf failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }


    int service_conf_mem_reject(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_reject_conference(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("reject conf failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_release_chairman(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_release_chairman(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("release chairman failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_request_chairman(TSDK_UINT32 confHandle, TSDK_CHAR* pwd)
    {
        TSDK_RESULT ret;
        ret = tsdk_request_chairman(confHandle, pwd);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("request chairman failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_handup(TSDK_UINT32 confHandle, unsigned int isHandup, TSDK_CHAR* attendee)
    {
        TSDK_RESULT ret;
        ret = tsdk_set_handup(confHandle, isHandup, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("hand up failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_set_video_mode(TSDK_UINT32 confHandle, TSDK_E_CONF_VIDEO_MODE confMode)
    {
        TSDK_RESULT ret;
        ret = tsdk_set_video_mode(confHandle, confMode);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("set video conf mode failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_broadcast_attendee(TSDK_UINT32 confHandle, TSDK_CHAR* attendee, unsigned int isRoadcast)
    {
        TSDK_RESULT ret;
        ret = tsdk_broadcast_attendee(confHandle, attendee, isRoadcast);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("broadcast attendee failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_conf_watch_attendee(TSDK_UINT32 confHandle, TSDK_S_WATCH_ATTENDEES_INFO* attendee)
    {
        TSDK_RESULT ret;
        ret = tsdk_watch_attendee(confHandle, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("watch attendee failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    //***************Data Conf******************////
    int service_conf_update_deta_conf(TSDK_UINT32 confHandle, TSDK_S_CONF_UPGRADE_PARAM* upgradeParam)
    {
        TSDK_RESULT ret;
        ret = tsdk_upgrade_conference(confHandle, upgradeParam);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("update data conf failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_data_conf_join(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_join_data_conference(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("join data conf failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_data_conf_set_presenter(TSDK_UINT32 confHandle, TSDK_CHAR* attendee)
    {
        TSDK_RESULT ret;
        ret = tsdk_set_presenter(confHandle, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("set presenter failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_data_conf_app_share_set_owner(TSDK_UINT32 confHandle, TSDK_CHAR* attendee, TSDK_E_CONF_AS_ACTION_TYPE action)
    {
        TSDK_RESULT ret;
        ret = tsdk_app_share_set_owner(confHandle, attendee, action);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("share set owner failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_TYPE shareType)
    {
        TSDK_UINT32 confHandle = get_data_conf_handle();
        TSDK_RESULT ret;
        ret = tsdk_app_share_start(confHandle, shareType);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("share start failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    //int service_data_conf_request_present()
    //{
    //    TSDK_UINT32 confHandle = get_data_conf_handle();
    //    TSDK_RESULT ret;
    //    ret = tsdk_set_request_presenter(confHandle);
    //    if (TSDK_SUCCESS != ret)
    //    {
    //        LOG_D_CALL_ERROR("share start failed. result=%#x", ret);
    //        return -1;
    //    }
    //    return TSDK_SUCCESS;
    //}

    int service_data_conf_app_share_get_screen_data(TSDK_UINT32 confHandle, TSDK_S_CONF_AS_SCREEN_DATA *screenData)
    {
        TSDK_RESULT ret;
        ret = tsdk_app_share_get_screen_data(confHandle, screenData);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("share get screen data failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_data_conf_app_share_stop(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_app_share_stop(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("share stop failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    //int service_data_conf_app_share_get_app_list(TSDK_UINT32 confHandle, TSDK_S_AS_WINDOW_INFO* app_list, TSDK_UINT32* app_count)
    //{
    //	TSDK_RESULT ret;
    //	ret = tsdk_app_share_get_app_list(confHandle, app_list, app_count);
    //	if (TSDK_SUCCESS != ret)
    //	{
    //		LOG_D_CALL_ERROR("get app list failed. result=%#x", ret);
    //		return -1;
    //	}
    //	return TSDK_SUCCESS;
    //}

    //int service_data_conf_app_share_set_app(TSDK_UINT32 confHandle, TSDK_VOID* appWindow, TSDK_E_CONF_AS_ACTION_TYPE action)
    //{
    //	TSDK_RESULT ret;
    //	ret = tsdk_app_share_set_app(confHandle, appWindow, action);
    //	if (TSDK_SUCCESS != ret)
    //	{
    //		LOG_D_CALL_ERROR("share app set app failed. result=%#x", ret);
    //		return -1;
    //	}
    //	return TSDK_SUCCESS;
    //}





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
