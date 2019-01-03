//
//  service_call_interface.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdio.h"
#include "windows.h"
#include "service_log.h"
#include "service_call_interface.h"

#define SERVICE_CALL_D_VIDEO_WINDOW_NUM  (2)
static unsigned int g_call_id;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


    int service_call_start(unsigned int* callid, const char* call_number, unsigned int isVideo)
    {
        TSDK_RESULT ret;
        ret = tsdk_start_call(callid, call_number, isVideo);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("start call failed. result=%#x", ret);
        }
        return ret;
    }

    int service_set_video_window(unsigned int callid, unsigned int local_video_wnd, unsigned int remote_video_wnd)
    {
        TSDK_RESULT ret;
        TSDK_S_VIDEO_WND_INFO video_window_info[SERVICE_CALL_D_VIDEO_WINDOW_NUM] = { TSDK_E_VIDEO_WND_REMOTE };

        video_window_info[TSDK_E_VIDEO_WND_LOCAL].render = (TSDK_UINT32)local_video_wnd;
        video_window_info[TSDK_E_VIDEO_WND_LOCAL].video_wnd_type = TSDK_E_VIDEO_WND_LOCAL;
        video_window_info[TSDK_E_VIDEO_WND_LOCAL].index = 1;
        video_window_info[TSDK_E_VIDEO_WND_LOCAL].display_mode = TSDK_E_VIDEO_WND_DISPLAY_FULL;

        video_window_info[TSDK_E_VIDEO_WND_REMOTE].render = (TSDK_UINT32)remote_video_wnd;
        video_window_info[TSDK_E_VIDEO_WND_REMOTE].video_wnd_type = TSDK_E_VIDEO_WND_REMOTE;
        video_window_info[TSDK_E_VIDEO_WND_REMOTE].index = 0;
        video_window_info[TSDK_E_VIDEO_WND_REMOTE].display_mode = TSDK_E_VIDEO_WND_DISPLAY_FULL;

        ret = tsdk_set_video_window(callid, SERVICE_CALL_D_VIDEO_WINDOW_NUM, video_window_info);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("set video window info failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_end(unsigned int callid)
    {
        TSDK_RESULT ret;
        ret = tsdk_end_call(callid);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("end call failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_accept(unsigned int callid, unsigned int isVideo)
    {
        TSDK_RESULT ret;
        ret = tsdk_accept_call(callid, isVideo ? 1 : 0);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("accept call failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_media_startplay(unsigned int loops, const char *play_file_path, int *play_handle)
    {
        TSDK_RESULT ret;
        ret = tsdk_start_play_media(loops, play_file_path, play_handle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("call media start play failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_media_stopplay(int play_handle)
    {
        TSDK_RESULT ret;
        ret = tsdk_stop_play_media(play_handle);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("call media stop play failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_divert(unsigned int callid, const char* divert_number)
    {
        TSDK_RESULT ret;
        ret = tsdk_divert_call(callid, divert_number);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("divert call failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_transfer(unsigned int callid, const char* trans_number)
    {
        TSDK_RESULT ret;
        ret = tsdk_blind_transfer(callid, trans_number);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("blind transfer failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_send_DTMF(unsigned int callid, TSDK_E_DTMF_TONE tone)
    {
        TSDK_RESULT ret;
        ret = tsdk_send_dtmf(callid, tone);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("send dtmf failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_mic_mute(unsigned int callid, unsigned int isMute)
    {
        TSDK_RESULT ret;
        ret = tsdk_mute_mic(callid, isMute ? 1 : 0);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("mute mic failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_hold(unsigned int callid)
    {
        TSDK_RESULT ret;
        ret = tsdk_hold_call(callid);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("hold failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_unhold(unsigned int callid)
    {
        TSDK_RESULT ret;
        ret = tsdk_unhold_call(callid);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("unhold failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_add_video(unsigned int callid)
    {
        TSDK_RESULT ret;
        ret = tsdk_add_video(callid);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("add video failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_reply_add_video(unsigned int callid, unsigned int isAccept)
    {
        TSDK_RESULT ret;
        ret = tsdk_reply_add_video(callid, isAccept ? 1 : 0);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("reply add video failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_delete_video(unsigned int callid)
    {
        TSDK_RESULT ret;
        ret = tsdk_del_video(callid);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("delete video failed. result=%#x", ret);
        }
        return ret;
    }

    int service_call_video_control(unsigned int callid, unsigned int isStop)
    {
        TSDK_RESULT ret;

        TSDK_S_VIDEO_CTRL_INFO videoControl;
        videoControl.is_sync = TRUE;
        videoControl.object = TSDK_E_VIDEO_CTRL_CAMERA | TSDK_E_VIDEO_CTRL_LOCAL_WND;

        if (isStop)
        {
            videoControl.operation = TSDK_E_VIDEO_CTRL_STOP;
        }
        else
        {
            videoControl.operation = TSDK_E_VIDEO_CTRL_START;
        }

        ret = tsdk_video_control(callid, &videoControl);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("control video failed. result=%#x", ret);
        }
        return ret;
    }

    int service_get_devices(unsigned int *device_num, TSDK_S_DEVICE_INFO *device_info, TSDK_E_DEVICE_TYPE device_type)
    {
        TSDK_RESULT ret;
        ret = tsdk_get_devices(device_type, device_num, device_info);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("get devices failed. result=%#x", ret);
        }
        return ret;
    }

    int service_get_speak_volume(unsigned int *volume)
    {
        TSDK_RESULT ret;
        ret = tsdk_get_speak_volume(volume);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("get speak volume failed. result=%#x", ret);
        }
        return ret;
    }

    int service_set_speak_volume(unsigned int volume)
    {
        TSDK_RESULT ret;
        ret = tsdk_set_speak_volume(volume);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("set speak volume failed. result=%#x", ret);
        }
        return ret;
    }

    int service_device_get_index(unsigned int *index, const TSDK_E_DEVICE_TYPE device_type)
    {
        TSDK_RESULT ret;
        switch (device_type)
        {
        case TSDK_E_DEVICE_MIC:
            {
                /*mic device*/
                ret = tsdk_get_mic_index(index);
                if (TSDK_SUCCESS != ret)
                {
                    LOG_D_CALL_ERROR("get mic index failed. result=%#x", ret);
                    return ret;
                }
                break;
            }
        case TSDK_E_DEVICE_SPEAKER:
            {
                /*speak device*/
                ret = tsdk_get_speak_index(index);
                if (TSDK_SUCCESS != ret)
                {
                    LOG_D_CALL_ERROR("get speak index failed. result=%#x", ret);
                    return ret;
                }
                break;
            }
        case TSDK_E_DEVICE_CAMERA:
            {
                /*video device*/
                ret = tsdk_get_video_index(index);
                if (TSDK_SUCCESS != ret)
                {
                    LOG_D_CALL_ERROR("get video index failed. result=%#x", ret);
                    return ret  ;
                }
                break;
            }
        default:
            {
                /*invalid device*/
                LOG_D_CALL_ERROR("invaid device type.");
                return -1;
            }
        }
        return TSDK_SUCCESS;
    }

    int service_device_set_index(unsigned int index, const TSDK_E_DEVICE_TYPE device_type)
    {
        TSDK_RESULT ret;
        switch (device_type)
        {
        case TSDK_E_DEVICE_MIC:
            {
                /*mic device*/
                ret = tsdk_set_mic_index(index);
                if (TSDK_SUCCESS != ret)
                {
                    LOG_D_CALL_ERROR("set mic index failed. result=%#x", ret);
                    return ret;
                }
                break;
            }
        case TSDK_E_DEVICE_SPEAKER:
            {
                /*speak device*/
                ret = tsdk_set_speak_index(index);
                if (TSDK_SUCCESS != ret)
                {
                    LOG_D_CALL_ERROR("set speak index failed. result=%#x", ret);
                    return ret;
                }
                break;
            }
        case TSDK_E_DEVICE_CAMERA:
            {
                /*video device*/
                ret = tsdk_set_video_index(index);
                if (TSDK_SUCCESS != ret)
                {
                    LOG_D_CALL_ERROR("set video index failed. result=%#x", ret);
                    return ret;
                }
                break;
            }
        default:
            {
                /*invalid device*/
                LOG_D_CALL_ERROR("invaid device type.");
                return -1;
            }
        }
        return TSDK_SUCCESS;
    }

    int service_video_open_preview(unsigned int local_preview_wnd, unsigned int index)
    {
        TSDK_RESULT ret;
        ret = tsdk_open_video_preview(local_preview_wnd, index);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("open video preview failed. result=%#x", ret);
        }
        return ret;
    }

    int service_video_close_preview()
    {
        TSDK_RESULT ret;
        ret = tsdk_close_video_preview();
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("close video preview failed. result=%#x", ret);
        }
        return ret;
    }

    int service_p2p_transfer_to_conference(unsigned int callId, TSDK_S_BOOK_CONF_INFO *bookConfInfo)
    {
        TSDK_RESULT ret;
        ret = tsdk_p2p_transfer_to_conference(callId, bookConfInfo);
        if (TSDK_SUCCESS != ret)
        {
            LOG_D_CALL_ERROR("p2p transfer to conference failed. result=%#x", ret);
        }
        return ret;
    }

    unsigned int get_call_id()
    {
        return g_call_id;
    }

    void set_call_id(unsigned int callid)
    {
        g_call_id = callid;
    }

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
