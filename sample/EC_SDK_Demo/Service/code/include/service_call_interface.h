//
//  service_call_interface.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
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

	/**
	* @ingroup Call
	* @brief [en] This interface is used to start a normal audio call.
	*        [cn] 发起一路普通呼叫
	* 
	* @param [out] unsigned int callid              [en] Indicates call ID, uniquely identifying a call.
	*                                               [cn] 呼叫的id，标识唯一的呼叫
	* @param [in] const char *call_number           [en] Indicates called number, maximum valid length of 255 characters
	*                                               [cn] 被叫号码，最大有效长度255
    * @param [in] unsigned int isVideo              [en] Indicates whether video call
    *                                               [cn] 标识是否为视频呼叫
	* @retval int                                   [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                               [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA
	**/
	SERVICE_CALL int service_call_start(unsigned int* callid, const char* call_number, unsigned int isVideo);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to set video window info(window handle)
	*        [cn] 设置视频窗口信息(窗口句柄)
	* 
	* @param [in] unsigned int callid                  [en] Indicates call ID
	*                                                  [cn] 呼叫ID
	* @param [in] unsigned int local_video_wnd         [en] Indicates local window handle.
	*                                                  [cn] 本端视频窗口句柄
	* @param [in] unsigned int remote_video_wnd        [en] Indicates remote window handle.
	*                                                  [cn] 对端视频窗口句柄
	* @retval int                                      [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                  [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention [en] When call is exist, fill in the corresponding effective value of call id； when call does not exist (not established, calling out breath), fill in illegal value 
	*            [cn] 呼叫存在时，call_id填写对应的有效值，呼叫不存在(未建立，主叫呼出时)，call_id填写非法值
	**/
    SERVICE_CALL int service_set_video_window(unsigned int callid, unsigned int local_video_wnd, unsigned int remote_video_wnd);
    SERVICE_CALL int service_set_svc_video_window(unsigned int callid, unsigned int ssrc_lable, unsigned int local_video_wnd, unsigned int remote_video_wnd);


	/**
	* @ingroup Call
	* @brief [en] This interface is used to end a placed or received call.
	*        [cn] 结束和其他用户的通话或者来电
	* 
	* @param [in] unsigned int callid               [en] Indicates call ID
	*                                               [cn] 呼叫ID
	* @retval int                                   [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                               [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_end(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to answer a call when receiving a call request.
	*        [cn] 接听呼叫
	* 
	* @param [in] unsigned int callid               [en] Indicates call ID
	*                                               [cn] 呼叫ID
	* @param [in] unsigned int isVide               [en] Indicates whether to answer video call.
	*                                               [cn] 是否接听视频呼叫
	* @retval int                                   [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                               [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	*  
	* @attention NA
	**/
    SERVICE_CALL int service_call_accept(unsigned int callid, unsigned int isVideo);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to play local audio file(ringing tone,ring back tone,dial tone,DTMF tone,busy tone and keypad tone)
	*        [cn] 播放本地音频文件(振铃音、回铃音、拨号(提示)音、DTMF音、忙碌提示音和本地按健音等) 
	* 
	* @param [in] unsigned int loops                       [en] Indicates number of cycles("0" indicates loop play )
	*                                                      [cn] 循环次数（0表示循环播放）
	* @param [in] const char *play_file_path               [en] Indicates audio file to be played(Only support wav format)
	*                                                      [cn] 待播放的音频文件（目前支持wav格式）
	* @param [out] int *play_handle                        [en] Indicates play handle
	*                                                      [cn] 播放句柄(用于停止播放时的参数)
	* @retval TSDK_RESULT                                  [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                      [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention [en] Only support wav format, support PCMA, PCMU, G.729 or PCM(sampling rate: 8~48 kHz; precision: 8~16-bit),support double channel 
	*            [cn] WAV文件，目前支持PCMA、PCMU、G.729格式或采样精度为8或16位、采样率8k～48K的PCM数据，支持双声道
	**/
    SERVICE_CALL int service_call_media_startplay(unsigned int loops, const char *play_file_path, int *play_handle);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to stop playing tone
	*        [cn] 停止铃音播放
	* 
	* @param [in] int play_handle                          [en] Indicates play handle
	*                                                      [cn] 播放句柄
	* @retval int                                          [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                      [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_media_stopplay(int play_handle);

	/**
	* @ingroup IPTService
	* @brief [en] This interface is used to initiate a call divert request.
	*        [cn] 发起呼叫偏转请求
	* 
	* @param [in] unsigned int callid                 [en] Indicates call ID
	*                                                 [cn] 呼叫ID
	* @param [in] const char* divert_number           [en] Indicates target number for divert, the maximum length is 32.
	*                                                 [cn] 偏转目的号码，最大长度32
	* @retval int                                     [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                 [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_divert(unsigned int callid, const char* divert_number);

	/**
	* @ingroup IPTService
	* @brief [en] This interface is used to initiate a blind call transfer request.
	*        [cn] 发起呼叫盲转请求
	* 
	* @param [in] unsigned int callid                 [en] Indicates call ID
	*                                                 [cn] 呼叫ID
	* @param [in] const char* trans_number            [en] Indicates target number for blind transfer, the maximum length is 32.
	*                                                 [cn] 盲转目的号码，最大长度32
	* @retval int                                     [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                 [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_transfer(unsigned int callid, const char* trans_number);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to send two-stage dialing information during a call. 
	*        [cn] 在通话中发送二次拨号信息
	* 
	* @param [in] unsigned int callid               [en] Indicates call ID
	*                                               [cn] 呼叫ID
	* @param [in] TSDK_E_DTMF_TONE tone             [en] Indicates DTMF tone
	*                                               [cn] DTMF键值
	* @retval TSDK_RESULT                           [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                               [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention [en] This interface must be send during a call
	*            [cn] 通话中才可以发送
	**/
    SERVICE_CALL int service_call_send_DTMF(unsigned int callid, TSDK_E_DTMF_TONE tone);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to set whether mute the microphone
	*        [cn] 设置(或取消)麦克风静音
	* 
	* @param [in] unsigned int callid                    [en] Indicates call ID.
	*                                                    [cn] 呼叫ID
	* @param [in] unsigned int isMute                    [en] Indicates whether to mute the microphone.
	*                                                    [cn] 是否静音
	* @retval int                                        [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                    [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_mic_mute(unsigned int callid, unsigned int isMute);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to place a connected call on hold.
	*        [cn] 保持通话
	* 
	* @param [in] unsigned int callid                 [en] Indicates call ID
	*                                                 [cn] 呼叫ID
	* @retval int                                     [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                 [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention [en] This interface must be invoked during a call[D]
	*            [cn] 处于通话状态才可以调用
	**/
    SERVICE_CALL int service_call_hold(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to cancel a held call (resume a call).
	*        [cn] 取消保持通话(恢复通话)
	* 
	* @param [in] unsigned int callid                 [en] Indicates call ID
	*                                                 [cn] 呼叫ID
	* @retval int                                     [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                 [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention [en] This interface must be invoked during a call[D]
	*            [cn] 处于通话保持状态才可以调用
	**/
    SERVICE_CALL int service_call_unhold(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to initiate a request for adding a video (converting an audio call into a video call).
	*        [cn] 发起音频转视频呼叫请求
	* 
	* @param [in] unsigned int callid                   [en] Indicates call ID
	*                                                   [cn] 呼叫ID
	* @retval int                                       [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                   [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_add_video(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to initiate a request for deleting a video (converting a video call into an audio call).
	*        [cn] 发起视频转音频呼叫请求
	* 
	* @param [in] unsigned int callid                    [en] Indicates call ID
	*                                                    [cn] 呼叫ID
	* @retval int                                        [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                    [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_delete_video(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to when the peer party sends a request to convert an audio call into a video call, the local party invokes this interface to accept or reject the request.
	*        [cn] 对方请求音频转视频呼叫时，本方选择同意或者拒绝
	* 
	* @param [in] unsigned int callid                    [en] Indicates call ID
	*                                                    [cn] 呼叫ID
	* @param [in] unsigned int isAccept                  [en] Indicates whether to accept the request.
	*                                                    [cn] 是否同意
	* @retval int                                        [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                    [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	*                                                    
	* @attention NA
	**/
    SERVICE_CALL int service_call_reply_add_video(unsigned int callid, unsigned int isAccept);

	/**
	* @brief [en] This interface is used to control video
	*        [cn] 视频控制
	*
	* @param [in] unsigned int callid                    [en] Indicates Call ID.
	*                                                    [cn] 呼叫ID
	* @param [in] unsigned int isStop                    [en] Indicates whether to stop the video. 
	*                                                    [cn] 是否暂停视频画面
	* @retval int                                        [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                    [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* @attention NA
	**/
    SERVICE_CALL int service_call_video_control(unsigned int callid, unsigned int isStop);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to get the audio and video device list
	*        [cn] 获取音频视频设备列表
	* 
	* @param [in/out] unsigned int *device_num             [en] Indicates when it is the input parameter, it indicates the number of devices that the upper layer allocates. When it is the output parameter, it indicates the number of devices obtained.
	*                                                      [cn] 输入时表示上层分配的设备个数，输出时表示获取到得设备的个数
	* @param [out] TSDK_S_DEVICE_INFO *device_info         [en] Indicates which is the pointer of the device information array.
	*                                                      [cn] 设备信息数组指针
	* @param [in] TSDK_E_DEVICE_TYPE device_type           [en] Indicates device type.
	*                                                      [cn] 设备类型 
	* @retval int                                          [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                      [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* @attention NA
	**/
    SERVICE_CALL int service_get_devices(unsigned int *device_num, TSDK_S_DEVICE_INFO *device_info, TSDK_E_DEVICE_TYPE device_type);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to get output volume 
	*        [cn] 获取输出音量大小
	* 
	* @param [out] unsigned int *volum                  [en] Indicates volume range from 0 to 100
	*                                                   [cn] 音量大小，取值范围[0, 100]
	* @retval int                                       [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                   [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* @attention NA
	**/
    SERVICE_CALL int service_get_speak_volume(unsigned int *volume);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to set output volume 
	*        [cn] 设置当前输出设备音量大小
	* 
	* @param [in] unsigned int volum                   [en] Indicates volume range from 0 to 100
	*                                                  [cn] 音量大小，取值范围[0, 100]
	*             
	* @retval int                                      [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                  [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* @attention NA
	**/
    SERVICE_CALL int service_set_speak_volume(unsigned int volume);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to get microphone device index.
	*        [cn] 获取使用的麦克风设备序号
	* 
	* @param [out] unsigned int *index                    [en] Indicates device index.
	*                                                     [cn] 设备序号
	* @param [in] const TSDK_E_DEVICE_TYPE device_type    [en] Indicates device type.
	*                                                     [cn] 设备类型
	* @retval int                                         [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                     [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention [en] Only for interface test or device test
	*            [cn] 用于接口测试或产品调试，实际产品业务场景中无需调用
	**/
    SERVICE_CALL int service_device_get_index(unsigned int *index, const TSDK_E_DEVICE_TYPE device_type);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to set microphone device index 
	*        [cn] 设置使用的麦克风设备序号
	* 
	* @param [in] unsigned int inde                       [en] Indicates device index.
	*                                                     [cn] 设备序号
	* @param [in] const TSDK_E_DEVICE_TYPE device_type    [en] Indicates device type.
	*                                                     [cn] 设备类型
	* @retval int                                         [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                     [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention [en] Device index is generally obtained after the system initialization by tsdk_get_devices, used for PC
	*            [cn] 设备序号一般在系统初始化后通过tsdk_get_devices获取，用于PC
	**/
    SERVICE_CALL int service_device_set_index(unsigned int index, const TSDK_E_DEVICE_TYPE device_type);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to open local preview window, checking whether the local video can be normally displayed
	*        [cn] 打开本地预览窗口
	* 
	* @param [in] unsigned int local_preview_wnd          [en] Indicates window handle.
	*                                                     [cn] 窗口句柄
	* @param [in] unsigned int index                      [en] Indicates camera index
	*                                                     [cn] 摄相头索引
	* @retval int                                         [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                     [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* @attention NA
	**/
    SERVICE_CALL int service_video_open_preview(unsigned int local_preview_wnd, unsigned int index);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to close and delete local preview window 
	*        [cn] 关闭并删除本地预览窗口
	* 
	* @param [in] NA
	* @retval int                                         [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                     [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_video_close_preview();

	/**
	* @ingroup conference
	* @brief [en]This interface is used to two-party call to multi-party conference.
	*        [cn]两方通话转多方会议
	*
	* @param [in] unsigned int callId                          [en]Indicates p2p call id.
	*                                                          [cn]点对点通话呼叫id
	* @param [in] TSDK_S_BOOK_CONF_INFO *bookConfInfo          [en]Indicates info of book conference.
	*                                                          [cn]预约会议信息
	*
	* @retval int                                              [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                          [cn] 成功返回TSDK_SUCCESS，失败返回相应错误码TSDK_E_CONF_ERR_ID
	*
	* @attention NA
	**/
    SERVICE_CALL int service_p2p_transfer_to_conference(unsigned int callId, TSDK_S_BOOK_CONF_INFO *bookConfInfo);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to get call id 
	*        [cn] 获取call_id
	* 
	* @param [in] NA
	* @retval unsigned int                                [en] return call id.
	*                                                     [cn] 返回call id的值
	* 
	* @attention NA
	**/
    SERVICE_CALL unsigned int get_call_id();

	/**
	* @ingroup Call
	* @brief [en] This interface is used to set call id 
	*        [cn] 设置call_id
	* 
	* @param [in] unsigned int callid                     [en]Indicates call id.
                                                          [cn]表示call id
	* @retval NA                                
	*                                                  
	* 
	* @attention NA
	**/
    SERVICE_CALL void set_call_id(unsigned int callid);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SERVICE_CALL_H__ */
