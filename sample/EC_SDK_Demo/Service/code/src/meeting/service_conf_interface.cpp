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

		//会议主题
		strncpy_s(bookConf.subject,TSDK_D_MAX_SUBJECT_LEN + 1,bookConfInfo->subject,_TRUNCATE);

        //会议开始时间
		strncpy_s(bookConf.start_time,TSDK_D_MAX_TIME_FORMATE_LEN + 1,bookConfInfo->start_time,_TRUNCATE);

		//会议类型
		bookConf.conf_type =  bookConfInfo->conf_type;

		//媒体类型
		bookConf.conf_media_type = bookConfInfo->conf_media_type;

		//与会者列表
		unsigned int attendeenumber = bookConfInfo->attendee_num;
		if (0 == attendeenumber)
		{
			LOG_D_CALL_ERROR("member count is 0");
			return -1;
		}
		bookConf.attendee_list = (TSDK_S_ATTENDEE_BASE_INFO*)malloc(attendeenumber*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
		
		if (NULL == bookConf.attendee_list)
		{
			LOG_D_CALL_ERROR("bookConf.attendee_list is NULL");
			return -1;
		}
		(void)service_memset_s(bookConf.attendee_list, attendeenumber*sizeof(TSDK_S_ATTENDEE_BASE_INFO), 0, attendeenumber*sizeof(TSDK_S_ATTENDEE_BASE_INFO));
		TSDK_S_ATTENDEE_BASE_INFO* pTempAttendee = bookConf.attendee_list;
		for (unsigned int i = 0; i < attendeenumber; i++)
		{
			if (pTempAttendee)
			{
				(void)strncpy_s(pTempAttendee->number, TSDK_D_MAX_PARTICIPANTID_LEN + 1, bookConfInfo->attendee_list[i].number, _TRUNCATE);
				(void)strncpy_s(pTempAttendee->display_name, TSDK_D_MAX_DISPLAY_NAME_LEN + 1, bookConfInfo->attendee_list[i].display_name, _TRUNCATE);
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

		//会议方数
		bookConf.size = attendeenumber;

		//与会者个数
		bookConf.attendee_num = attendeenumber;

        ret = tsdk_book_conference(&bookConf);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("book conf failed. result=%#x", ret);
            return -1;
        }
        free(bookConf.attendee_list);
        bookConf.attendee_list = NULL;
        return TSDK_SUCCESS;
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

    int service_conf_request_chairman(TSDK_UINT32 confHandle,TSDK_CHAR* pwd)
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
    int service_conf_update_deta_conf(TSDK_UINT32 confHandle)
    {
        TSDK_RESULT ret;

        TSDK_S_CONF_UPGRADE_PARAM upParam = { 0 };
        strcpy_s(upParam.group_uri, TSDK_D_MAX_GROUP_URI_LEN + 1, "");

        ret = tsdk_upgrade_conference(confHandle, &upParam);
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

    int service_data_conf_app_share_set_owner(TSDK_CHAR* attendee, TSDK_E_CONF_AS_ACTION_TYPE action)
    {
        TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

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
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        TSDK_RESULT ret;
        ret = tsdk_app_share_start(confHandle, shareType);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("share start failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_data_conf_app_share_get_screen_data(TSDK_S_CONF_AS_SCREEN_DATA *screenData)
    {
        TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        TSDK_RESULT ret;
        ret = tsdk_app_share_get_screen_data(confHandle, screenData);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("share get screen data failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

    int service_data_conf_app_share_stop()
    {
        TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        TSDK_RESULT ret;
        ret = tsdk_app_share_stop(confHandle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("share stop failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }

	int service_data_conf_ds_share_open_document(const char* file_path,unsigned int* doc_id)
	{
		TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

		TSDK_RESULT ret;
		ret = tsdk_doc_share_open_document(confHandle,file_path,TSDK_E_DOC_SHARE_SIZE,doc_id);
		if (TSDK_SUCCESS != ret)
		{
			LOG_D_CALL_ERROR("share open document failed. result=%#x", ret);
			return -1;
		}
		return TSDK_SUCCESS;
	}

	int service_data_conf_ds_share_close_document(unsigned int docId)
	{
		TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

		TSDK_RESULT ret;
		ret = tsdk_doc_share_close_document(confHandle,docId);
		if (TSDK_SUCCESS != ret)
		{
			LOG_D_CALL_ERROR("close document failed. result=%#x", ret);
			return -1;
		}
		return TSDK_SUCCESS;
	}

	int service_data_conf_ds_share_get_syn_document_info(TSDK_S_DOC_PAGE_DETAIL_INFO* sync_info)
	{
		TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

		TSDK_RESULT ret;

		ret = tsdk_doc_share_get_syn_document_info(confHandle,TSDK_E_COMPONENT_DS,sync_info);
		if (TSDK_SUCCESS != ret)
		{
			LOG_D_CALL_ERROR("get syn document info failed. result=%#x", ret);
			return -1;
		}
		return TSDK_SUCCESS;
	}
	

	int service_data_conf_ds_share_set_current_page(unsigned int docId,int pageIndex, unsigned int isDocShare, unsigned int isSyn)
	{
		TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

		TSDK_RESULT ret;
		TSDK_S_DOC_PAGE_BASE_INFO page_info;
		if (isDocShare)
		{
			page_info.component_id = TSDK_E_COMPONENT_DS;
		}
		else
		{
			page_info.component_id = TSDK_E_COMPONENT_WB;
		}
		page_info.document_id = docId;
		page_info.page_index = pageIndex;
		ret = tsdk_doc_share_set_current_page(confHandle,&page_info,isSyn);
		if (TSDK_SUCCESS != ret)
		{
			LOG_D_CALL_ERROR("set current page failed. result=%#x", ret);
			return -1;
		}
		return TSDK_SUCCESS;
	}

	void* service_data_conf_ds_share_get_surfacebmp(unsigned int isDocShare)
	{
		TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, NULL);

        unsigned int bmpWidth;
        unsigned int bmpHeight;

		void* data = NULL;
		if (isDocShare)
		{
			data = tsdk_doc_share_get_surface_bmp(confHandle,TSDK_E_COMPONENT_DS,&bmpWidth,&bmpHeight);
		}
		else
		{
			data = tsdk_doc_share_get_surface_bmp(confHandle,TSDK_E_COMPONENT_WB,&bmpWidth,&bmpHeight);
		}

		if (NULL == data)
		{
			LOG_D_CALL_ERROR("get surface bmp failed.");
			return NULL;
		}

		return data;
	}

	int service_data_conf_ds_share_set_canvas_size(TSDK_S_SIZE size)
	{
		unsigned int conf_handle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(conf_handle, NULL);

		TSDK_S_SIZE c_size;
		c_size.width = size.width;
		c_size.high = size.high;

		(void)tsdk_doc_share_set_canvas_size(conf_handle, TSDK_E_COMPONENT_DS, &c_size,TSDK_TRUE);

		return 0;
	}

	int service_data_conf_ds_share_set_background_color()
	{
		TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

        TSDK_RESULT ret;

		ret = tsdk_doc_share_set_background_color(confHandle,TSDK_E_COMPONENT_DS,0xFFFFFFFF);
		if (TSDK_SUCCESS != ret)
		{
			LOG_D_CALL_ERROR("set background color failed. result=%#x", ret);
			return -1;
		}
		return TSDK_SUCCESS;
	}

	int service_data_conf_ds_share_set_display_mode()
	{
		TSDK_UINT32 confHandle = get_data_conf_handle();
        CHECK_DATA_CONF_HANDLE(confHandle, -1);

		TSDK_RESULT ret;

		ret = tsdk_doc_share_set_display_mode(confHandle,TSDK_E_COMPONENT_DS,TSDK_E_DOC_SHARE_DISPLAY_MODE_CENTER);
		if (TSDK_SUCCESS != ret)
		{
			LOG_D_CALL_ERROR("set display mode failed. result=%#x", ret);
			return -1;
		}
		return TSDK_SUCCESS;
	}

    int service_join_conference_by_anonymous(TSDK_S_CONF_ANONYMOUS_JOIN_PARAM *confJoinParam)
    {
        TSDK_RESULT ret;

        ret = tsdk_join_conference_by_anonymous(confJoinParam);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("join conference by anonymous failed. result=%#x", ret);
            return -1;
        }
        return TSDK_SUCCESS;
    }
	
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
