//
//  service_call_interface.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef __SERVICE_CALL_H__
#define __SERVICE_CALL_H__

#include "tsdk.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef SERVICE_EXPORTS
#define SERVICE_CALL __declspec(dllexport)
#else
#define SERVICE_CALL __declspec(dllimport)
#endif

    SERVICE_CALL int service_call_audio_start(unsigned int callid, const char *call_number);
    SERVICE_CALL int service_call_video_start(const char *call_number, unsigned int local_video_wnd, unsigned int remote_video_wnd);
    SERVICE_CALL int service_set_video_window(unsigned int callid, unsigned int local_video_wnd, unsigned int remote_video_wnd);
    SERVICE_CALL int service_call_end(unsigned int callid);
    SERVICE_CALL int service_call_accept(unsigned int callid, unsigned int isVideo);
    SERVICE_CALL int service_call_media_startplay(unsigned int loops, const char *play_file_path, int *play_handle);
    SERVICE_CALL int service_call_media_stopplay(int play_handle);
    SERVICE_CALL int service_call_divert(unsigned int callid, const char* divert_number);
    SERVICE_CALL int service_call_transfer(unsigned int callid, const char* trans_number);
    SERVICE_CALL int service_call_send_DTMF(unsigned int callid, TSDK_E_DTMF_TONE tone);
    SERVICE_CALL int service_call_mic_mute(unsigned int callid, unsigned int isMute);
    SERVICE_CALL int service_call_hold(unsigned int callid);
    SERVICE_CALL int service_call_unhold(unsigned int callid);
    SERVICE_CALL int service_call_add_video(unsigned int callid);
    SERVICE_CALL int service_call_delete_video(unsigned int callid);
    SERVICE_CALL int service_call_reply_add_video(unsigned int callid, unsigned int isAccept);
    SERVICE_CALL int service_call_video_control(unsigned int callid, unsigned int isStop);
    SERVICE_CALL int service_get_devices(unsigned int *device_num, TSDK_S_DEVICE_INFO *device_info, TSDK_E_DEVICE_TYPE device_type);
    SERVICE_CALL int service_get_speak_volume(unsigned int *volume);
    SERVICE_CALL int service_set_speak_volume(unsigned int volume);
    SERVICE_CALL int service_device_get_index(unsigned int *index, const TSDK_E_DEVICE_TYPE device_type);
    SERVICE_CALL int service_device_set_index(unsigned int index, const TSDK_E_DEVICE_TYPE device_type);
    SERVICE_CALL int service_video_open_preview(unsigned int local_preview_wnd, unsigned int index);
    SERVICE_CALL int service_video_close_preview();
    SERVICE_CALL int service_p2p_transfer_to_conference(unsigned int callId, TSDK_S_BOOK_CONF_INFO *bookConfInfo);
    SERVICE_CALL unsigned int get_call_id();
    SERVICE_CALL void set_call_id(unsigned int callid);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SERVICE_CALL_H__ */
