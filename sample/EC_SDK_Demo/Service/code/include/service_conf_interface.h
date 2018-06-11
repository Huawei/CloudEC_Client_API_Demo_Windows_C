//
//  service_conf_interface.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "tsdk_conference_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef SERVICE_EXPORTS
#define SERVICE_CONF __declspec(dllexport)
#else
#define SERVICE_CONF __declspec(dllimport)
#endif

    SERVICE_CONF int service_conf_book(TSDK_S_BOOK_CONF_INFO *bookConfInfo);
    SERVICE_CONF int service_conf_get_list(TSDK_S_QUERY_CONF_LIST_REQ *arg);
    SERVICE_CONF int service_conf_query_conference_detail(TSDK_S_QUERY_CONF_DETAIL_REQ *arg);
    SERVICE_CONF int service_conf_join(TSDK_S_CONF_JOIN_PARAM* confJoinParam, TSDK_CHAR* joinNumber, unsigned int isVideoJoin, TSDK_UINT32 *callId);
    SERVICE_CONF int service_conf_mute(TSDK_UINT32 confHandle, unsigned int isMute);
    SERVICE_CONF int service_conf_lock(TSDK_UINT32 confHandle, unsigned int isLock);
    SERVICE_CONF int service_conf_leave(TSDK_UINT32 confHandle);
    SERVICE_CONF int service_conf_end(TSDK_UINT32 confHandle);
    SERVICE_CONF int service_conf_mem_add(TSDK_UINT32 confHandle, const TSDK_S_ADD_ATTENDEES_INFO* addAttendeeInfo);
    SERVICE_CONF int service_conf_mem_delete(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee);
    SERVICE_CONF int service_conf_mem_mute(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee, unsigned int isMute);
    SERVICE_CONF int service_conf_mem_hangup(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee);
    SERVICE_CONF int service_conf_mem_accept(TSDK_UINT32 confHandle, unsigned int isJoinVideo);
    SERVICE_CONF int service_conf_mem_reject(TSDK_UINT32 confHandle);
    SERVICE_CONF int service_conf_release_chairman(TSDK_UINT32 confHandle);
    SERVICE_CONF int service_conf_request_chairman(TSDK_UINT32 confHandle, TSDK_CHAR* pwd);
    SERVICE_CONF int service_conf_handup(TSDK_UINT32 confHandle, unsigned int isHandup, TSDK_CHAR* attendee);
    SERVICE_CONF int service_conf_set_video_mode(TSDK_UINT32 confHandle, TSDK_E_CONF_VIDEO_MODE confMode);
    SERVICE_CONF int service_conf_broadcast_attendee(TSDK_UINT32 confHandle, TSDK_CHAR* attendee, unsigned int isRoadcast);
    SERVICE_CONF int service_conf_watch_attendee(TSDK_UINT32 confHandle, TSDK_S_WATCH_ATTENDEES_INFO* attendee);
    SERVICE_CONF int service_conf_update_deta_conf(TSDK_UINT32 confHandle, TSDK_S_CONF_UPGRADE_PARAM* upgradeParam);
    SERVICE_CONF int service_data_conf_join(TSDK_UINT32 confHandle);
    SERVICE_CONF int service_data_conf_set_presenter(TSDK_UINT32 confHandle, TSDK_CHAR* attendee);
    SERVICE_CONF int service_data_conf_app_share_set_owner(TSDK_UINT32 confHandle, TSDK_CHAR* attendee, TSDK_E_CONF_AS_ACTION_TYPE action);
    SERVICE_CONF int service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_TYPE shareType);
    //SERVICE_CONF int service_data_conf_request_present();
    SERVICE_CONF int service_data_conf_app_share_get_screen_data(TSDK_UINT32 confHandle, TSDK_S_CONF_AS_SCREEN_DATA *screenData);
    SERVICE_CONF int service_data_conf_app_share_stop(TSDK_UINT32 confHandle);
    SERVICE_CONF int service_data_conf_app_share_get_app_list(TSDK_UINT32 confHandle, TSDK_S_AS_WINDOW_INFO* app_list, TSDK_UINT32* app_count);
    SERVICE_CONF int service_data_conf_app_share_set_app(TSDK_UINT32 confHandle, TSDK_VOID* appWindow, TSDK_E_CONF_AS_ACTION_TYPE action);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
