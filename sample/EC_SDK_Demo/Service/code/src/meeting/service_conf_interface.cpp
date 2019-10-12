//
//  service_conf_interface.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "malloc.h"
#include "service_conf_interface.h"
#include "service_log.h"
#include "service_conf_handle_global.h"
#include "service_os_adapt.h"
#include "service_tools.h"
#include "tsdk_error_def.h"
#include "tsdk_conference_interface.h"
#include <string.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


    int service_conf_book(SERVICE_S_BOOK_CONF_INFO *bookConfInfo)
    {
        TSDK_RESULT ret;
        TSDK_S_BOOK_CONF_INFO bookConf;
        service_memset_s(&bookConf,sizeof(bookConf),0,sizeof(bookConf));

        strncpy_s(bookConf.subject,TSDK_D_MAX_SUBJECT_LEN + 1,bookConfInfo->subject,_TRUNCATE);
        strncpy_s(bookConf.start_time,TSDK_D_MAX_TIME_FORMATE_LEN + 1,bookConfInfo->start_time,_TRUNCATE);
        bookConf.conf_type =  bookConfInfo->conf_type;
        bookConf.conf_media_type = bookConfInfo->conf_media_type;

        //默认使用高清会议
        bookConf.is_hd_conf = TSDK_TRUE;
        bookConf.is_multi_stream_conf = TSDK_TRUE;

        unsigned int attendeenumber = bookConfInfo->attendee_num;
        if (0 == attendeenumber)
        {
            LOG_D_CONF_ERROR("member count is 0");
            return -1;
        }
        
        bookConf.attendee_list = (TSDK_S_ATTENDEE_BASE_INFO*)malloc(attendeenumber*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
        if (NULL == bookConf.attendee_list)
        {
            LOG_D_CONF_ERROR("bookConf.attendee_list is NULL");
            return -1;
        }
        
        (void)service_memset_s(bookConf.attendee_list, attendeenumber*sizeof(TSDK_S_ATTENDEE_BASE_INFO), 0, attendeenumber*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
        TSDK_S_ATTENDEE_BASE_INFO* pTempAttendee = bookConf.attendee_list;
        for (unsigned int i = 0; i < attendeenumber; i++)
        {
            if (pTempAttendee)
            {
                (void)strncpy_s(pTempAttendee->number, TSDK_D_MAX_PARTICIPANTID_LEN + 1, bookConfInfo->attendee_list[i].number, _TRUNCATE);
                if (strlen(bookConfInfo->attendee_list[i].display_name) > 0)
                {
                    (void)strncpy_s(pTempAttendee->display_name, TSDK_D_MAX_DISPLAY_NAME_LEN + 1, bookConfInfo->attendee_list[i].display_name, _TRUNCATE);
                }
                else
                {
                    (void)strncpy_s(pTempAttendee->display_name, TSDK_D_MAX_DISPLAY_NAME_LEN + 1, bookConfInfo->attendee_list[i].number, _TRUNCATE);
                }

                (void)strncpy_s(pTempAttendee->account_id, TSDK_D_MAX_ACCOUNT_LEN + 1, bookConfInfo->attendee_list[i].account_id, _TRUNCATE);
                (void)strncpy_s(pTempAttendee->email, TSDK_D_MAX_EMAIL_LEN + 1, bookConfInfo->attendee_list[i].email, _TRUNCATE);
                (void)strncpy_s(pTempAttendee->sms, TSDK_D_MAX_NUMBER_LEN + 1, bookConfInfo->attendee_list[i].sms, _TRUNCATE);
                pTempAttendee->role = bookConfInfo->attendee_list[i].role;
            }
            else
            {
                break;
            }

            pTempAttendee++;
        }

        bookConf.size = attendeenumber;

        bookConf.attendee_num = attendeenumber;

        ret = tsdk_book_conference(&bookConf);
        free(bookConf.attendee_list);
        bookConf.attendee_list = NULL;
        
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("book conf failed. result=%#x", ret);
        }
        
        return ret;
    }


    int service_conf_get_list()
    {
        TSDK_RESULT ret;

        TSDK_S_QUERY_CONF_LIST_REQ argConfList;
        argConfList.conf_right = TSDK_E_CONF_RIGHT_CREATE_JOIN;
        argConfList.is_include_end = FALSE;
        argConfList.page_index = 1;
        argConfList.page_size = 200;

        ret = tsdk_query_conference_list(&argConfList);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("get conf list failed. result=%#x", ret);
        }
        
        return ret;
    }


    int service_conf_query_conference_detail(TSDK_CHAR *conf_id)
    {
        TSDK_RESULT ret;

        TSDK_S_QUERY_CONF_DETAIL_REQ argConfDetail;
        service_memset_s(&argConfDetail, sizeof(argConfDetail), 0, sizeof(argConfDetail));
        strncpy_s(argConfDetail.conf_id, TSDK_D_MAX_CONF_ID_LEN + 1, conf_id,_TRUNCATE);
        argConfDetail.page_index = 1;
        argConfDetail.page_size = 200;

        ret = tsdk_query_conference_detail(&argConfDetail);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("query conference detail failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_join(TSDK_S_CONF_JOIN_PARAM* confJoinParam, TSDK_CHAR* joinNumber, unsigned int isVideoJoin, TSDK_UINT32 *callId)
    {
        TSDK_RESULT ret;
        ret = tsdk_join_conference(confJoinParam, joinNumber, isVideoJoin, callId);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("join conf failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_mute(TSDK_UINT32 confHandle, unsigned int isMute)
    {
        TSDK_RESULT ret;
        ret = tsdk_mute_conference(confHandle, isMute);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("mute conference failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_add_attendee(TSDK_UINT32 confHandle, const TSDK_S_ADD_ATTENDEES_INFO* addAttendeeInfo)
    {
        TSDK_RESULT ret;
        ret = tsdk_add_attendee(confHandle, addAttendeeInfo);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("add conf member failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_lock(TSDK_UINT32 confHandle, unsigned int isLock)
    {
        TSDK_RESULT ret;
        ret = tsdk_lock_conference(confHandle, isLock);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("lock conf failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_leave(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_leave_conference(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("leave conf failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_end(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_end_conference(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("end conf failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_release(TSDK_UINT32 confHandle)
    {
        tsdk_release_conference(confHandle);

        return 0;
    }

    int service_conf_delete_attendee(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee)
    {
        TSDK_RESULT ret;
        ret = tsdk_remove_attendee(confHandle, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("remove mem failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_mute_attendee(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee, unsigned int isMute)
    {
        TSDK_RESULT ret;
        ret = tsdk_mute_attendee(confHandle, attendee, isMute);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("mute mem failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_hangup_attendee(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee)
    {
        TSDK_RESULT ret;
        ret = tsdk_hang_up_attendee(confHandle, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("hangup mem failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_accept(TSDK_UINT32 confHandle, unsigned int isJoinVideo)
    {
        TSDK_RESULT ret;
        ret = tsdk_accept_conference(confHandle, isJoinVideo);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("accept conf failed. result=%#x", ret);
        }
        return ret;
    }


    int service_conf_reject(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_reject_conference(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("reject conf failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_release_chairman(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_release_chairman(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("release chairman failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_request_chairman(TSDK_UINT32 confHandle,TSDK_CHAR* pwd)
    {
        TSDK_RESULT ret;
        ret = tsdk_request_chairman(confHandle, pwd);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("request chairman failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_handup(TSDK_UINT32 confHandle, unsigned int isHandup, TSDK_CHAR* attendee)
    {
        TSDK_RESULT ret;
        ret = tsdk_set_handup(confHandle, isHandup, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("hand up failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_set_video_mode(TSDK_UINT32 confHandle, TSDK_E_CONF_VIDEO_MODE confMode)
    {
        TSDK_RESULT ret;
        ret = tsdk_set_video_mode(confHandle, confMode);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("set video conf mode failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_broadcast_attendee(TSDK_UINT32 confHandle, TSDK_CHAR* attendee, unsigned int isRoadcast)
    {
        TSDK_RESULT ret;
        ret = tsdk_broadcast_attendee(confHandle, attendee, isRoadcast);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("broadcast attendee failed. result=%#x", ret);
        }
        return ret;
    }

    int service_conf_watch_attendee(TSDK_UINT32 confHandle, TSDK_S_WATCH_ATTENDEES_INFO* attendee)
    {
        TSDK_RESULT ret;
        ret = tsdk_watch_attendee(confHandle, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("watch attendee failed. result=%#x", ret);
        }
        return ret;
    }

    //***************Data Conf******************////
    int service_conf_upgrade_conf(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;

        TSDK_S_CONF_UPGRADE_PARAM upParam = { 0 };
        strcpy_s(upParam.group_uri, TSDK_D_MAX_GROUP_URI_LEN + 1, "");

        ret = tsdk_upgrade_conference(confHandle, &upParam);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("update data conf failed. result=%#x", ret);
        }
        
        return ret;
    }

    int service_conf_join_data_conference(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;
        ret = tsdk_join_data_conference(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("join data conf failed. result=%#x", ret);
        }
        return ret;
    }

    int service_data_conf_set_presenter(TSDK_UINT32 confHandle, TSDK_CHAR* attendee)
    {
        TSDK_RESULT ret;
        
        ret = tsdk_set_presenter(confHandle, attendee);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("set presenter failed. result=%#x", ret);
        }
        
        return ret;
    }

    int service_data_conf_app_share_set_owner(TSDK_CHAR* attendee, TSDK_E_CONF_AS_ACTION_TYPE action)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_app_share_set_owner(confHandle, attendee, action);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("share set owner failed. result=%#x", ret);
        }
        
        return ret;
    }


    int service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_TYPE shareType)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_app_share_start(confHandle, shareType);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("share start failed. result=%#x", ret);
        }
        
        return ret;
    }

    int service_data_conf_app_share_set_privilege(TSDK_CHAR* attendee, TSDK_E_CONF_SHARE_PRIVILEGE_TYPE privilege_type, TSDK_E_CONF_AS_ACTION_TYPE action)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_app_share_set_privilege(confHandle, attendee, privilege_type, action);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("share set privilege failed. result=%#x", ret);
        }

        return ret;
    }

    int service_data_conf_app_share_get_screen_data(TSDK_S_CONF_AS_SCREEN_DATA *screenData)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_app_share_get_screen_data(confHandle, screenData);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("share get screen data failed. result=%#x", ret);
        }
        
        return ret;
    }

    int service_data_conf_app_share_attach_window(TSDK_UPTR window_handle)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_app_share_attach_render(confHandle, window_handle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("app share attach window failed. result=%#x", ret);
        }

        return ret;
    }


    int service_data_conf_app_share_detach_window(TSDK_VOID)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_app_share_detach_render(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("app share detach window  failed. result=%#x", ret);
        }

        return ret;
    }


    int service_data_conf_app_share_set_render_view_size(TSDK_INT32 width, TSDK_INT32 high)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        TSDK_S_SIZE view_size;
        view_size.width = width;
        view_size.high = high;

        ret = tsdk_app_share_set_render_view_size(confHandle, &view_size);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("app share set render view size  failed. result=%#x", ret);
        }

        return ret;
    }


    int service_data_conf_app_share_stop()
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_app_share_stop(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("share stop failed. result=%#x", ret);
        }
        
        return ret;
    }

    int service_data_conf_ds_share_open_document(const char* file_path, unsigned int* doc_id)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_doc_share_open_document(confHandle, file_path, TSDK_E_DOC_SHARE_SIZE, doc_id);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("share open document failed. result=%#x", ret);
        }
        
        return ret;
    }

    int service_data_conf_ds_share_close_document(unsigned int docId)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_doc_share_close_document(confHandle, docId);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("close document failed. result=%#x", ret);
        }
        
        return ret;
    }

    int service_data_conf_ds_share_get_syn_document_info(TSDK_E_COMPONENT_ID componentId, TSDK_S_DOC_PAGE_DETAIL_INFO* sync_info)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_doc_share_get_syn_document_info(confHandle, componentId, sync_info);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("get syn document info failed. result=%#x", ret);
        }
        
        return ret;
    }
    

    int service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex, unsigned int isSyn)
    {
        TSDK_RESULT ret;
        TSDK_S_DOC_PAGE_BASE_INFO page_info;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        service_memset_s(&page_info, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        page_info.component_id = componentId;
        page_info.document_id = docId;
        page_info.page_index = pageIndex;
        ret = tsdk_doc_share_set_current_page(confHandle,&page_info,isSyn);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("set current page failed. result=%#x", ret);
        }
        return ret;
    }

    void* service_data_conf_ds_share_get_surfacebmp(TSDK_E_COMPONENT_ID componentId)
    {
        unsigned int bmpWidth = 0;
        unsigned int bmpHeight = 0;
        void* data = NULL;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, NULL);
        
        data = tsdk_doc_share_get_surface_bmp(confHandle, componentId,&bmpWidth,&bmpHeight);
        if (NULL == data)
        {
            LOG_D_CONF_ERROR("get surface bmp failed.");
        }

        return data;
    }

    int service_data_conf_ds_share_set_canvas_size(TSDK_E_COMPONENT_ID componentId, int width, int high)
    {
        unsigned int conf_handle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(conf_handle, NULL);

        TSDK_RESULT ret;

        TSDK_S_SIZE c_size;
        c_size.width = width;
        c_size.high = high;

        ret = tsdk_doc_share_set_canvas_size(conf_handle, componentId, &c_size, TSDK_TRUE);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("set canvas size failed. result=%#x", ret);
        }

        return ret;
    }

    int service_data_conf_ds_share_set_background_color(TSDK_E_COMPONENT_ID componentId)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_doc_share_set_background_color(confHandle, componentId, 0xFFFFFFFF);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("set background color failed. result=%#x", ret);
        }
        
        return ret;
    }

    int service_data_conf_ds_share_set_display_mode(TSDK_E_COMPONENT_ID componentId)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_doc_share_set_display_mode(confHandle, componentId, TSDK_E_DOC_SHARE_DISPLAY_MODE_CENTER);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("set display mode failed. result=%#x", ret);
        }
        
        return ret;
    }

    int service_data_conf_ds_share_set_zoom_mode(TSDK_E_COMPONENT_ID componentId, IN TSDK_UINT32 document_id,
        IN TSDK_E_DOC_SHARE_ZOOM_MODE zoom_mode, IN TSDK_UINT32 zoom_percent, IN TSDK_BOOL is_sync, IN TSDK_BOOL is_redraw)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_doc_share_set_zoom_mode(confHandle, componentId, document_id, zoom_mode, zoom_percent, is_sync, is_redraw);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("set zoom mode failed. result=%#x", ret);
        }

        return ret;
    }

    int service_data_conf_wb_share_open_whiteboard(unsigned int* docId)
    {
        TSDK_RESULT ret;
        
        TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_whiteboard_new_document(confHandle, docId);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("open new whiteboard failed. result=%#x", ret);
        }
        return ret;
    }

    int service_data_conf_wb_share_new_page(unsigned int docId, int page_width, int page_height, unsigned int* page_id)
    {
        TSDK_RESULT ret;
        
        TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_whiteboard_new_page(confHandle, docId, page_width, page_height, page_id);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("create new page failed. result=%#x", ret);
        }
        return ret;
    }

    int service_data_conf_wb_share_whiteboard_delete(unsigned int docId)
    {
        TSDK_RESULT ret;
        
        TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_whiteboard_delete_document(confHandle, docId);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("delete whiteboard failed. result=%#x", ret);
        }
        return ret;
    }

    int service_data_conf_wb_share_whiteboard_delete_page(unsigned int docId, unsigned int pageId)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_whiteboard_delete_page(confHandle, docId, pageId);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("delete whiteboard page failed. result=%#x", ret);
        }
        return ret;
    }
    
    int service_data_conf_annotation_create_start(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex,
        IN TSDK_E_ANNOTATION_MAIN_TYPE mainType, TSDK_E_ANNOTATION_DRAWING_SUB_TYPE subType, int x, int y)
    {
        TSDK_RESULT ret;
        TSDK_S_DOC_PAGE_BASE_INFO page_base_info;
        TSDK_S_POINT point;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        service_memset_s(&page_base_info, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        page_base_info.component_id = componentId;
        page_base_info.document_id = docId;
        page_base_info.page_index = pageIndex;

        service_memset_s(&point, sizeof(TSDK_S_POINT), 0, sizeof(TSDK_S_POINT));
        point.x = x;
        point.y = y;

        ret = tsdk_annotation_create_start(confHandle, componentId, &page_base_info, mainType, (TSDK_UINT32)subType, &point);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("annotation create start failed. result=%#x", ret);
        }

        return ret;
    }

    int service_data_conf_annotation_update(TSDK_E_COMPONENT_ID componentId, const TSDK_S_POINT* point)
    {
        TSDK_RESULT ret;
        TSDK_S_ANNOTATION_DRAWING_DATA update_point = { 0 };
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        update_point.point.x = point->x;
        update_point.point.y = point->y;

        /*Upodate annotation data*/
        ret = tsdk_annotation_create_update(confHandle, TSDK_E_COMPONENT_WB, TSDK_E_ANNOTATION_DRAWING, (TSDK_VOID*)&update_point);
        if (0 != ret)
        {
            LOG_D_CONF_ERROR("Upodate annotation data failed. result=%#x", ret);
        }

        return ret;
    }

    int service_data_conf_annotation_create_finish(TSDK_E_COMPONENT_ID componentId, unsigned int is_cancel)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        TSDK_UINT32 annotation_id = 0;

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        /*Finish creating annotation*/
        ret = tsdk_annotation_create_done(confHandle, componentId, is_cancel, &annotation_id);
        if (0 != ret)
        {
            LOG_D_CONF_ERROR("Finish annotation data failed. result=%#x", ret);
        }

        return ret;
    }

    int service_data_conf_annotation_delete(TSDK_E_COMPONENT_ID componentId, 
        unsigned int document_id, unsigned int page_index, unsigned int* annotation_id, int count)
    {
        TSDK_RESULT ret;
        TSDK_S_ANNOTATION_DELETE_INFO delete_info;
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        service_memset_s(&delete_info, sizeof(TSDK_S_ANNOTATION_DELETE_INFO), 0, sizeof(TSDK_S_ANNOTATION_DELETE_INFO));
        delete_info.annotation_id_list = annotation_id;
        delete_info.count = count;
        delete_info.component_id = componentId;
        delete_info.doc_page_info.component_id = componentId;
        delete_info.doc_page_info.document_id = document_id;
        delete_info.doc_page_info.page_index = page_index;
        
        ret = tsdk_annotation_delete_annotation(confHandle, &delete_info);
        if (0 != ret)
        {
            LOG_D_CONF_ERROR("Finish annotation data failed. result=%#x", ret);
        }

        return ret;
    }


    int service_data_conf_annotation_laser_pointer_start(TSDK_E_COMPONENT_ID componentId, 
        TSDK_S_ANNOTATION_LASER_POINTER_INFO *laser_pointer_info)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_annotation_laser_pointer_start(confHandle, componentId, laser_pointer_info);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("tsdk_annotation_laser_pointer_start return failed. result=%#x", ret);
        }

        return ret;
    }

    int service_data_conf_annotation_laser_pointer_moveto(TSDK_E_COMPONENT_ID componentId, int x, int y)
    {
        TSDK_RESULT ret;
        TSDK_S_POINT update_point = { 0 };
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        update_point.x = x;
        update_point.y = y;

        /*Upodate annotation data*/
        ret = tsdk_annotation_laser_pointer_moveto(confHandle, componentId, &update_point);
        if (0 != ret)
        {
            LOG_D_CONF_ERROR("tsdk_annotation_laser_pointer_moveto return failed. result=%#x", ret);
        }

        return ret;
    }
    

    int service_data_conf_annotation_laser_pointer_stop(TSDK_E_COMPONENT_ID componentId)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        /*Upodate annotation data*/
        ret = tsdk_annotation_laser_pointer_stop(confHandle, componentId);
        if (0 != ret)
        {
            LOG_D_CONF_ERROR("tsdk_annotation_laser_pointer_stop return failed. result=%#x", ret);
        }

        return ret;
    }


    int service_data_conf_annotation_set_select(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex, 
        TSDK_E_ANNOTATION_SELECT_MODE selectMode, unsigned int* annotation_id, int count, unsigned int isRedraw)
    {
        TSDK_RESULT ret;
        TSDK_S_ANNOTATION_SELECT_INFO annotationSelectInfo;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);
        
        service_memset_s(&annotationSelectInfo, sizeof(TSDK_S_ANNOTATION_SELECT_INFO), 0, sizeof(TSDK_S_ANNOTATION_SELECT_INFO));
        annotationSelectInfo.component_id = componentId;
        annotationSelectInfo.doc_page_info.component_id = componentId;
        annotationSelectInfo.doc_page_info.document_id = docId;
        annotationSelectInfo.doc_page_info.page_index = pageIndex;
        annotationSelectInfo.annotation_id_list = (TSDK_UINT32*)annotation_id;
        annotationSelectInfo.select_mode = selectMode;
        annotationSelectInfo.count = count;
       
        ret = tsdk_annotation_set_select(confHandle, &annotationSelectInfo,(TSDK_BOOL)isRedraw);

        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("annotation set select failed. result=%#x", ret);
        }

        return ret;
    }

    int service_data_conf_annotation_edit_start(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex, 
        unsigned int* annotationId, int count, unsigned int refAnnotationId, TSDK_E_ANNOTATION_HIT_TEST_CODE editType, TSDK_S_POINT* point)
    {
        TSDK_RESULT ret;
        TSDK_S_DOC_PAGE_BASE_INFO pageInfo;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);
        
        service_memset_s(&pageInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        pageInfo.component_id = componentId;
        pageInfo.document_id = docId;
        pageInfo.page_index = pageIndex;

        ret = tsdk_annotation_edit_start(confHandle, componentId, &pageInfo,(TSDK_UINT32*)annotationId, count,(TSDK_UINT32)refAnnotationId, editType, point);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("annotation edit start failed. result=%#x", ret);
        }

        return ret;
    }

    int service_data_conf_annotation_edit_update(TSDK_E_COMPONENT_ID componentId, TSDK_S_POINT* point)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);
        
        ret = tsdk_annotation_edit_update(confHandle, TSDK_E_COMPONENT_WB, point);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("annotation edit update failed. result=%#x", ret);

            (void)tsdk_annotation_edit_done(confHandle, componentId, TSDK_TRUE);
        }

        return ret;
    }

    int service_data_conf_annotation_edit_finish(TSDK_E_COMPONENT_ID componentId, unsigned int isCancel)
    {
        TSDK_RESULT ret;
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        ret = tsdk_annotation_edit_done(confHandle, componentId, isCancel);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("annotation edit done failed. result=%#x", ret);
        }

        return ret;
    }
    

    int service_data_conf_annotation_hit_test_point(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex, 
        TSDK_S_POINT* point, unsigned int* selectAnnotationId, TSDK_E_ANNOTATION_HIT_TEST_CODE* testResult, unsigned int* annotationType)
    {
        TSDK_RESULT ret;
        TSDK_S_ANNOTATION_HIT_TEST_POINT_INFO testPointInfo;        
        TSDK_UINT32 confHandle = get_data_conf_handle();
        
        CHECK_DATA_CONF_HANDLE(confHandle, -1);
        
        service_memset_s(&testPointInfo, sizeof(TSDK_S_ANNOTATION_HIT_TEST_POINT_INFO), 0, sizeof(TSDK_S_ANNOTATION_HIT_TEST_POINT_INFO));
        testPointInfo.component_id = componentId;
        testPointInfo.doc_page_info.component_id = componentId;
        testPointInfo.doc_page_info.document_id = docId;
        testPointInfo.doc_page_info.page_index = pageIndex;
        testPointInfo.hit_test_mode = TSDK_E_ANNOTATION_HIT_TEST_ALL;
        testPointInfo.point.x = point->x;
        testPointInfo.point.y = point->y;

        ret = tsdk_annotation_hit_test_point(confHandle, &testPointInfo, selectAnnotationId, testResult, annotationType);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("annotation hit test point failed. result=%#x", ret);
        }

        return ret;
    }
    
    int service_data_conf_annotation_set_pen(TSDK_E_COMPONENT_ID componentId, TSDK_E_ANNOTATION_PEN_TYPE penType, 
        TSDK_E_ANNOTATION_PEN_STYLE style, unsigned int color, unsigned int width)
    {
        TSDK_RESULT ret;
        TSDK_S_ANNOTATION_PEN_INFO old_pen_info;
        TSDK_S_ANNOTATION_PEN_INFO new_pen_info;
        TSDK_UINT32 confHandle = get_data_conf_handle();

        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        service_memset_s(&old_pen_info, sizeof(TSDK_S_ANNOTATION_PEN_INFO), 0, sizeof(TSDK_S_ANNOTATION_PEN_INFO));
        service_memset_s(&new_pen_info, sizeof(TSDK_S_ANNOTATION_PEN_INFO), 0, sizeof(TSDK_S_ANNOTATION_PEN_INFO));

        new_pen_info.style = style;
        new_pen_info.color = color;
        new_pen_info.width = width;

        ret = tsdk_annotation_set_pen(confHandle, componentId, penType, &new_pen_info, &old_pen_info);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("annotation set pen failed. result=%#x", ret);
        }

        return ret;
    }
        

    int service_join_conference_by_anonymous(TSDK_S_CONF_ANONYMOUS_JOIN_PARAM *confJoinParam)
    {
        TSDK_RESULT ret;

        ret = tsdk_join_conference_by_anonymous(confJoinParam);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CONF_ERROR("join conference by anonymous failed. result=%#x", ret);
        }
        
        return ret;
    }

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
