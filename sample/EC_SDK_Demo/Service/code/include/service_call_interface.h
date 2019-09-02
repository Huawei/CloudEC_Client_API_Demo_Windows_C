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
	*        [cn] ����һ·��ͨ����
	* 
	* @param [out] unsigned int callid              [en] Indicates call ID, uniquely identifying a call.
	*                                               [cn] ���е�id����ʶΨһ�ĺ���
	* @param [in] const char *call_number           [en] Indicates called number, maximum valid length of 255 characters
	*                                               [cn] ���к��룬�����Ч����255
    * @param [in] unsigned int isVideo              [en] Indicates whether video call
    *                                               [cn] ��ʶ�Ƿ�Ϊ��Ƶ����
	* @retval int                                   [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                               [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
	SERVICE_CALL int service_call_start(unsigned int* callid, const char* call_number, unsigned int isVideo);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to set video window info(window handle)
	*        [cn] ������Ƶ������Ϣ(���ھ��)
	* 
	* @param [in] unsigned int callid                  [en] Indicates call ID
	*                                                  [cn] ����ID
	* @param [in] unsigned int local_video_wnd         [en] Indicates local window handle.
	*                                                  [cn] ������Ƶ���ھ��
	* @param [in] unsigned int remote_video_wnd        [en] Indicates remote window handle.
	*                                                  [cn] �Զ���Ƶ���ھ��
	* @retval int                                      [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                  [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention [en] When call is exist, fill in the corresponding effective value of call id�� when call does not exist (not established, calling out breath), fill in illegal value 
	*            [cn] ���д���ʱ��call_id��д��Ӧ����Чֵ�����в�����(δ���������к���ʱ)��call_id��д�Ƿ�ֵ
	**/
    SERVICE_CALL int service_set_video_window(unsigned int callid, unsigned int local_video_wnd, unsigned int remote_video_wnd);
    SERVICE_CALL int service_set_svc_video_window(unsigned int callid, unsigned int ssrc_lable, unsigned int local_video_wnd, unsigned int remote_video_wnd);


	/**
	* @ingroup Call
	* @brief [en] This interface is used to end a placed or received call.
	*        [cn] �����������û���ͨ����������
	* 
	* @param [in] unsigned int callid               [en] Indicates call ID
	*                                               [cn] ����ID
	* @retval int                                   [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                               [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_end(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to answer a call when receiving a call request.
	*        [cn] ��������
	* 
	* @param [in] unsigned int callid               [en] Indicates call ID
	*                                               [cn] ����ID
	* @param [in] unsigned int isVide               [en] Indicates whether to answer video call.
	*                                               [cn] �Ƿ������Ƶ����
	* @retval int                                   [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                               [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*  
	* @attention NA
	**/
    SERVICE_CALL int service_call_accept(unsigned int callid, unsigned int isVideo);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to play local audio file(ringing tone,ring back tone,dial tone,DTMF tone,busy tone and keypad tone)
	*        [cn] ���ű�����Ƶ�ļ�(��������������������(��ʾ)����DTMF����æµ��ʾ���ͱ��ذ�������) 
	* 
	* @param [in] unsigned int loops                       [en] Indicates number of cycles("0" indicates loop play )
	*                                                      [cn] ѭ��������0��ʾѭ�����ţ�
	* @param [in] const char *play_file_path               [en] Indicates audio file to be played(Only support wav format)
	*                                                      [cn] �����ŵ���Ƶ�ļ���Ŀǰ֧��wav��ʽ��
	* @param [out] int *play_handle                        [en] Indicates play handle
	*                                                      [cn] ���ž��(����ֹͣ����ʱ�Ĳ���)
	* @retval TSDK_RESULT                                  [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                      [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention [en] Only support wav format, support PCMA, PCMU, G.729 or PCM(sampling rate: 8~48 kHz; precision: 8~16-bit),support double channel 
	*            [cn] WAV�ļ���Ŀǰ֧��PCMA��PCMU��G.729��ʽ���������Ϊ8��16λ��������8k��48K��PCM���ݣ�֧��˫����
	**/
    SERVICE_CALL int service_call_media_startplay(unsigned int loops, const char *play_file_path, int *play_handle);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to stop playing tone
	*        [cn] ֹͣ��������
	* 
	* @param [in] int play_handle                          [en] Indicates play handle
	*                                                      [cn] ���ž��
	* @retval int                                          [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                      [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_media_stopplay(int play_handle);

	/**
	* @ingroup IPTService
	* @brief [en] This interface is used to initiate a call divert request.
	*        [cn] �������ƫת����
	* 
	* @param [in] unsigned int callid                 [en] Indicates call ID
	*                                                 [cn] ����ID
	* @param [in] const char* divert_number           [en] Indicates target number for divert, the maximum length is 32.
	*                                                 [cn] ƫתĿ�ĺ��룬��󳤶�32
	* @retval int                                     [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                 [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_divert(unsigned int callid, const char* divert_number);

	/**
	* @ingroup IPTService
	* @brief [en] This interface is used to initiate a blind call transfer request.
	*        [cn] �������äת����
	* 
	* @param [in] unsigned int callid                 [en] Indicates call ID
	*                                                 [cn] ����ID
	* @param [in] const char* trans_number            [en] Indicates target number for blind transfer, the maximum length is 32.
	*                                                 [cn] äתĿ�ĺ��룬��󳤶�32
	* @retval int                                     [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                 [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_transfer(unsigned int callid, const char* trans_number);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to send two-stage dialing information during a call. 
	*        [cn] ��ͨ���з��Ͷ��β�����Ϣ
	* 
	* @param [in] unsigned int callid               [en] Indicates call ID
	*                                               [cn] ����ID
	* @param [in] TSDK_E_DTMF_TONE tone             [en] Indicates DTMF tone
	*                                               [cn] DTMF��ֵ
	* @retval TSDK_RESULT                           [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                               [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention [en] This interface must be send during a call
	*            [cn] ͨ���вſ��Է���
	**/
    SERVICE_CALL int service_call_send_DTMF(unsigned int callid, TSDK_E_DTMF_TONE tone);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to set whether mute the microphone
	*        [cn] ����(��ȡ��)��˷羲��
	* 
	* @param [in] unsigned int callid                    [en] Indicates call ID.
	*                                                    [cn] ����ID
	* @param [in] unsigned int isMute                    [en] Indicates whether to mute the microphone.
	*                                                    [cn] �Ƿ���
	* @retval int                                        [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                    [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_mic_mute(unsigned int callid, unsigned int isMute);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to place a connected call on hold.
	*        [cn] ����ͨ��
	* 
	* @param [in] unsigned int callid                 [en] Indicates call ID
	*                                                 [cn] ����ID
	* @retval int                                     [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                 [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention [en] This interface must be invoked during a call[D]
	*            [cn] ����ͨ��״̬�ſ��Ե���
	**/
    SERVICE_CALL int service_call_hold(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to cancel a held call (resume a call).
	*        [cn] ȡ������ͨ��(�ָ�ͨ��)
	* 
	* @param [in] unsigned int callid                 [en] Indicates call ID
	*                                                 [cn] ����ID
	* @retval int                                     [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                 [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention [en] This interface must be invoked during a call[D]
	*            [cn] ����ͨ������״̬�ſ��Ե���
	**/
    SERVICE_CALL int service_call_unhold(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to initiate a request for adding a video (converting an audio call into a video call).
	*        [cn] ������Ƶת��Ƶ��������
	* 
	* @param [in] unsigned int callid                   [en] Indicates call ID
	*                                                   [cn] ����ID
	* @retval int                                       [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                   [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_add_video(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to initiate a request for deleting a video (converting a video call into an audio call).
	*        [cn] ������Ƶת��Ƶ��������
	* 
	* @param [in] unsigned int callid                    [en] Indicates call ID
	*                                                    [cn] ����ID
	* @retval int                                        [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                    [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_call_delete_video(unsigned int callid);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to when the peer party sends a request to convert an audio call into a video call, the local party invokes this interface to accept or reject the request.
	*        [cn] �Է�������Ƶת��Ƶ����ʱ������ѡ��ͬ����߾ܾ�
	* 
	* @param [in] unsigned int callid                    [en] Indicates call ID
	*                                                    [cn] ����ID
	* @param [in] unsigned int isAccept                  [en] Indicates whether to accept the request.
	*                                                    [cn] �Ƿ�ͬ��
	* @retval int                                        [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                    [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*                                                    
	* @attention NA
	**/
    SERVICE_CALL int service_call_reply_add_video(unsigned int callid, unsigned int isAccept);

	/**
	* @brief [en] This interface is used to control video
	*        [cn] ��Ƶ����
	*
	* @param [in] unsigned int callid                    [en] Indicates Call ID.
	*                                                    [cn] ����ID
	* @param [in] unsigned int isStop                    [en] Indicates whether to stop the video. 
	*                                                    [cn] �Ƿ���ͣ��Ƶ����
	* @retval int                                        [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                    [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @attention NA
	**/
    SERVICE_CALL int service_call_video_control(unsigned int callid, unsigned int isStop);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to get the audio and video device list
	*        [cn] ��ȡ��Ƶ��Ƶ�豸�б�
	* 
	* @param [in/out] unsigned int *device_num             [en] Indicates when it is the input parameter, it indicates the number of devices that the upper layer allocates. When it is the output parameter, it indicates the number of devices obtained.
	*                                                      [cn] ����ʱ��ʾ�ϲ������豸���������ʱ��ʾ��ȡ�����豸�ĸ���
	* @param [out] TSDK_S_DEVICE_INFO *device_info         [en] Indicates which is the pointer of the device information array.
	*                                                      [cn] �豸��Ϣ����ָ��
	* @param [in] TSDK_E_DEVICE_TYPE device_type           [en] Indicates device type.
	*                                                      [cn] �豸���� 
	* @retval int                                          [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                      [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @attention NA
	**/
    SERVICE_CALL int service_get_devices(unsigned int *device_num, TSDK_S_DEVICE_INFO *device_info, TSDK_E_DEVICE_TYPE device_type);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to get output volume 
	*        [cn] ��ȡ���������С
	* 
	* @param [out] unsigned int *volum                  [en] Indicates volume range from 0 to 100
	*                                                   [cn] ������С��ȡֵ��Χ[0, 100]
	* @retval int                                       [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                   [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @attention NA
	**/
    SERVICE_CALL int service_get_speak_volume(unsigned int *volume);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to set output volume 
	*        [cn] ���õ�ǰ����豸������С
	* 
	* @param [in] unsigned int volum                   [en] Indicates volume range from 0 to 100
	*                                                  [cn] ������С��ȡֵ��Χ[0, 100]
	*             
	* @retval int                                      [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                  [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @attention NA
	**/
    SERVICE_CALL int service_set_speak_volume(unsigned int volume);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to get microphone device index.
	*        [cn] ��ȡʹ�õ���˷��豸���
	* 
	* @param [out] unsigned int *index                    [en] Indicates device index.
	*                                                     [cn] �豸���
	* @param [in] const TSDK_E_DEVICE_TYPE device_type    [en] Indicates device type.
	*                                                     [cn] �豸����
	* @retval int                                         [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                     [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention [en] Only for interface test or device test
	*            [cn] ���ڽӿڲ��Ի��Ʒ���ԣ�ʵ�ʲ�Ʒҵ�񳡾����������
	**/
    SERVICE_CALL int service_device_get_index(unsigned int *index, const TSDK_E_DEVICE_TYPE device_type);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to set microphone device index 
	*        [cn] ����ʹ�õ���˷��豸���
	* 
	* @param [in] unsigned int inde                       [en] Indicates device index.
	*                                                     [cn] �豸���
	* @param [in] const TSDK_E_DEVICE_TYPE device_type    [en] Indicates device type.
	*                                                     [cn] �豸����
	* @retval int                                         [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                     [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention [en] Device index is generally obtained after the system initialization by tsdk_get_devices, used for PC
	*            [cn] �豸���һ����ϵͳ��ʼ����ͨ��tsdk_get_devices��ȡ������PC
	**/
    SERVICE_CALL int service_device_set_index(unsigned int index, const TSDK_E_DEVICE_TYPE device_type);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to open local preview window, checking whether the local video can be normally displayed
	*        [cn] �򿪱���Ԥ������
	* 
	* @param [in] unsigned int local_preview_wnd          [en] Indicates window handle.
	*                                                     [cn] ���ھ��
	* @param [in] unsigned int index                      [en] Indicates camera index
	*                                                     [cn] ����ͷ����
	* @retval int                                         [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                     [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @attention NA
	**/
    SERVICE_CALL int service_video_open_preview(unsigned int local_preview_wnd, unsigned int index);

	/**
	* @ingroup MediaAndDevices
	* @brief [en] This interface is used to close and delete local preview window 
	*        [cn] �رղ�ɾ������Ԥ������
	* 
	* @param [in] NA
	* @retval int                                         [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                     [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* 
	* @attention NA
	**/
    SERVICE_CALL int service_video_close_preview();

	/**
	* @ingroup conference
	* @brief [en]This interface is used to two-party call to multi-party conference.
	*        [cn]����ͨ��ת�෽����
	*
	* @param [in] unsigned int callId                          [en]Indicates p2p call id.
	*                                                          [cn]��Ե�ͨ������id
	* @param [in] TSDK_S_BOOK_CONF_INFO *bookConfInfo          [en]Indicates info of book conference.
	*                                                          [cn]ԤԼ������Ϣ
	*
	* @retval int                                              [en] If it's success return TSDK_SUCCESS, otherwise return the corresponding error code.
	*                                                          [cn] �ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������TSDK_E_CONF_ERR_ID
	*
	* @attention NA
	**/
    SERVICE_CALL int service_p2p_transfer_to_conference(unsigned int callId, TSDK_S_BOOK_CONF_INFO *bookConfInfo);

	/**
	* @ingroup Call
	* @brief [en] This interface is used to get call id 
	*        [cn] ��ȡcall_id
	* 
	* @param [in] NA
	* @retval unsigned int                                [en] return call id.
	*                                                     [cn] ����call id��ֵ
	* 
	* @attention NA
	**/
    SERVICE_CALL unsigned int get_call_id();

	/**
	* @ingroup Call
	* @brief [en] This interface is used to set call id 
	*        [cn] ����call_id
	* 
	* @param [in] unsigned int callid                     [en]Indicates call id.
                                                          [cn]��ʾcall id
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
