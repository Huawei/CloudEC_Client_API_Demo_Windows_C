//
//  service_conf_interface.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "tsdk_conference_def.h"
#include "tsdk_conference_interface.h"
#include "service_conf_def.h"

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

	/**
	* @ingroup conference
	* @brief [en]This interface is used to schedule a conference (scheduled or instant conference).
	*        [cn]ԤԼ����(��������ʱ�ٿ�)
	*
	* @param [in] SERVICE_S_BOOK_CONF_INFO *bookConfInfo       [en]Indicates info of book conference.
	*                                                          [cn]ԤԼ������Ϣ
	*
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code, value of TSDK_E_CONF_ERR_ID.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ�����룬ȡֵ�ο�TSDK_E_CONF_ERR_ID
	*
	* @attention [en]If you create an instant meeting, the SDK automatically joins the meeting after the meeting is successfully created
	*            [cn]������������������飬���鴴���ɹ���SDK���Զ��������
	* @see TSDK_E_CONF_EVT_BOOK_CONF_RESULT
	**/
    SERVICE_CONF int service_conf_book(SERVICE_S_BOOK_CONF_INFO *bookConfInfo);

	/**
	* @ingroup ConfMng
	* @brief [en]This interface is used to get conference list.
	*        [cn]��ȡ�����б�
	*
	* @param [in]NA
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en] corresponding callback event is TSDK_E_CONF_EVT_QUERY_CONF_LIST_RESULT.
	*            [cn] ��Ӧ�Ļص��¼�ΪTSDK_E_CONF_EVT_QUERY_CONF_LIST_RESULT
	* @see TSDK_E_CONF_EVT_QUERY_CONF_LIST_RESULT
	**/
    SERVICE_CONF int service_conf_get_list();

	/**
	* @ingroup ConfMng
	* @brief [en]This interface is used to get detail info of conference.
	*        [cn]��ȡ������ϸ��Ϣ
	*
	* @param [in] TSDK_CHAR *conf_id                           [en]Indicates get detail info of conference id.
	*                                                          [cn]��ȡ��ȡ������ϸ��Ϣ�Ļ���id
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en] corresponding callback event is TSDK_E_CONF_EVT_QUERY_CONF_DETAIL_RESULT.
	*            [cn] ��Ӧ�Ļص��¼�ΪTSDK_E_CONF_EVT_QUERY_CONF_DETAIL_RESULT
	* @see TSDK_E_CONF_EVT_QUERY_CONF_DETAIL_RESULT
	**/
    SERVICE_CONF int service_conf_query_conference_detail(TSDK_CHAR *conf_id);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to proactively join a conference.
	*        [cn]�����������
	*
	* @param [in] TSDK_S_CONF_JOIN_PARAM* confJoinParam        [en]Indicates conf join param.
	*                                                          [cn]������
	* @param [in] TSDK_CHAR* joinNumber                        [en]Indicates join number.
	*                                                          [cn]������
	* @param [in] unsigned int isVideoJoi                      [en]Indicates whether video join conference.
	*                                                          [cn]�Ƿ���Ƶ�������
	* @param [out] TSDK_UINT32 *callId                         [en]Indicates the call ID corresponding to the meeting is valid when the SIP terminal number is used.
	*                                                          [cn]�����Ӧ�ĺ���ID����ʹ��SIP�ն˺������ʱ��Ч��
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see TSDK_E_CONF_EVT_JOIN_CONF_RESULT
	**/
    SERVICE_CONF int service_conf_join(TSDK_S_CONF_JOIN_PARAM* confJoinParam, TSDK_CHAR* joinNumber, unsigned int isVideoJoin, TSDK_UINT32 *callId);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to mute or unmute a conference.
	*        [cn]���û�ȡ�������᳡
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] unsigned int isMute                          [en]Indicates whether mute.
	*                                                          [cn]�Ƿ����
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]corresponding result event notification is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
	*            [cn]��Ӧ�Ľ���¼�֪ͨΪTSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT��
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_mute(TSDK_UINT32 confHandle, unsigned int isMute);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to lock or unlock a conference.
	*        [cn]���û�ȡ����������
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] unsigned int isLock                          [en]Indicates whether lock conference.
	*                                                          [cn]�Ƿ���������
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]Under chairman conference control, when conference is locked attendees can not join conference by any way except invited by chairman.
	*            [en]corresponding result event notify is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	*            [cn]��ϯ��أ����������󣬳���ϯ�����⣬�����˲���ͨ���κ�;���������;
	*            [cn]��Ӧ�Ľ���¼�֪ͨΪTSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_lock(TSDK_UINT32 confHandle, unsigned int isLock);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is invoked by a participant to proactively leave a conference.
	*        [cn]�뿪����
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see NA.
	**/
    SERVICE_CONF int service_conf_leave(TSDK_UINT32 confHandle);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is invoked by the chairman to end an ongoing conference.
	*        [cn]��������
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see TSDK_E_CONF_EVT_CONF_END_IND.
	**/
    SERVICE_CONF int service_conf_end(TSDK_UINT32 confHandle);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is invoked by the chairman to add a new participant to a conference.
	*        [cn]��������
	*
	* @param [in] TSDK_UINT32 confHandle                            [en]Indicates conference control handle.
	*                                                               [cn]��ؾ��
	* @param [in] const TSDK_S_ADD_ATTENDEES_INFO* addAttendeeInfo  [en]Indicates add attendee info.
	*                                                               [cn]����������Ϣ
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA
	*            [cn]NA
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_mem_add(TSDK_UINT32 confHandle, const TSDK_S_ADD_ATTENDEES_INFO* addAttendeeInfo);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to remove attendee.
	*        [cn]ɾ�������
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] const TSDK_CHAR* attendee                    [en]Indicates attendee number.
	*                                                          [cn]����ߺ���
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_mem_delete(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to mute attendee.
	*        [cn]���������
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] const TSDK_CHAR* attendee                    [en]Indicates attendee number.
	*                                                          [cn]����ߺ���
	* @param [in] unsigned int isMute                          [en]Indicates whether mute.
	*                                                          [cn]�Ƿ����
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]Chairman can mute all attendee, normal attendee can only mute themselves, attendee can only listen not speak when they are muted.
	*            [en]corresponding result event notification is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
	*            [cn]��ϯ�ɶ�������������û�ȡ����������ͨ�����ֻ�ɶ��Լ����û�ȡ�������������ñ���ʱ������߿�������˵��
	*            [cn]��Ӧ�Ľ���¼�֪ͨΪTSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT��
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_mem_mute(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee, unsigned int isMute);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to hang up attendee.
	*        [cn]�Ҷ������
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] const TSDK_CHAR* attendee                    [en]Indicates attendee number.
	*                                                          [cn]����ߺ���
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_mem_hangup(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to accept a conference call.
	*        [cn]������������
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] unsigned int isJoinVideo                     [en]Indicates whether join video conference.
	                                                           [cn]�Ƿ������Ƶ����
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*							 [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @attention [en]NA.
	*            [cn]NA.
	* @see NA.
	**/
    SERVICE_CONF int service_conf_mem_accept(TSDK_UINT32 confHandle, unsigned int isJoinVideo);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to reject a conference call.
	*        [cn]�ܽӻ�������
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conf handle.
	*                                                          [cn]��ؾ��
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see NA.
	**/
	SERVICE_CONF int service_conf_mem_reject(TSDK_UINT32 confHandle);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to release chair rights.
	*        [cn]�ͷ���ϯȨ��
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]Corresponding result event notify is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
	*            [cn]��Ӧ�Ľ���¼�֪ͨΪTSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_release_chairman(TSDK_UINT32 confHandle);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to apply for chair rights.
	*        [cn]������ϯȨ��
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
    * @param [in] TSDK_CHAR* pwd                               [en]Indicates chairman password.
    *                                                          [cn]��ϯ����
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]corresponding result event notify is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
	*            [cn]��Ӧ�Ľ���¼�֪ͨΪTSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT��
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_request_chairman(TSDK_UINT32 confHandle,TSDK_CHAR* pwd);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is invoked by a common participant in a conference to set their hands-up or cancel the setting or is invoked by the moderator to cancel hands-up of the other participants.
	*        [cn]���û�ȡ������
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] unsigned int isHandup                        [en]Indicates whether hand up.
	*                                                          [cn]�Ƿ����
	* @param [in] TSDK_CHAR* attendee                          [en]Indicates attendee number(It's no need if it's config oneself).
	*                                                          [cn]����ߺ���(�������Լ�����������д)
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]Corresponding result event notify is TSDK_E_CONF_SET_HANDUP or TSDK_E_CONF_CANCLE_HANDUP.
	*            [cn]��Ӧ�Ľ���¼�֪ͨΪTSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_handup(TSDK_UINT32 confHandle, unsigned int isHandup, TSDK_CHAR* attendee);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to set conference video mode.
	*        [cn]���û�����Ƶģʽ
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] TSDK_E_CONF_VIDEO_MODE confMode              [en]Indicates conference video mode.
	*                                                          [cn]������Ƶģʽ
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention NA.
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
	**/
    SERVICE_CONF int service_conf_set_video_mode(TSDK_UINT32 confHandle, TSDK_E_CONF_VIDEO_MODE confMode);

	/**
	* @ingroup ConfCtrl.
	* @brief [en]This interface is used to broadcast or cancel broadcasting a specified participant.
	*        [cn]�㲥��ȡ���㲥ָ������ߣ��᳡��
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] TSDK_CHAR* attendee                          [en]Indicates attendee number.
	*                                                          [cn]����ߺ���
	* @param [in] unsigned int isRoadcast                      [en]Indicates broadcast or cancel broadcast.
	*                                                          [cn]�㲥����ȡ���㲥
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_broadcast_attendee(TSDK_UINT32 confHandle, TSDK_CHAR* attendee, unsigned int isRoadcast);

	/**
	* @ingroup ConfCtrl.
	* @brief [en]This interface is invoked by the chairman to select the participant to view among the participants who are being broadcast. 
	*        [cn]����ۿ�ָ������߻���
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @param [in] TSDK_S_WATCH_ATTENDEES_INFO* attendee        [en]Indicates watch attendee param info.
	*                                                          [cn]ѡ������߻��������Ϣ
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
	SERVICE_CONF int service_conf_watch_attendee(TSDK_UINT32 confHandle, TSDK_S_WATCH_ATTENDEES_INFO* attendee);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to upgrade conference.
	*        [cn]��������
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]Corresponding result event notify is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
	*            [cn]��Ӧ�Ľ���¼�֪ͨΪTSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_conf_update_deta_conf(TSDK_UINT32 confHandle);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to join data conference.
	*        [cn]�������ݻ���
	*
	* @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
	*                                                          [cn]��ؾ��
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see TSDK_E_CONF_EVT_JOIN_CONF_RESULT.
	**/
    SERVICE_CONF int service_data_conf_join(TSDK_UINT32 confHandle);

	/**
	* @ingroup ConfCtrl
	* @brief [en]This interface is used to set conference presenter
	*        [cn]����������
	*
	* @param [in] TSDK_UINT32 confHandle                 [en]Indicates conference handle conference handle
	*                                                    [cn]������
	* @param [in] TSDK_CHAR* attendee                    [en]Indicates attendee number
	*                                                    [cn]����ߺ���
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	*
	* @attention [en]NA.
	*            [cn]NA.
	* @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
	**/
    SERVICE_CONF int service_data_conf_set_presenter(TSDK_UINT32 confHandle, TSDK_CHAR* attendee);

	/**
	* @ingroup AppShare
	* @brief [en]This interface is used to configure the owner of screen sharing.
	*        [cn]������Ļ�����ӵ����
	*
	* @param [in] TSDK_CHAR* attendee                    [en]Indicates attendee number
	*                                                    [cn]����ߺ���
	* @param [in] TSDK_E_CONF_AS_ACTION_TYPE action      [en]Indicates set action, refer to TSDK_E_CONF_AS_ACTION_TYPE.
	*                                                    [cn]���ö���, �ο�TSDK_E_CONF_AS_ACTION_TYPE.
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @attention [en]NA
	*            [cn]NA
	* @see NA
	**/
	SERVICE_CONF int service_data_conf_app_share_set_owner(TSDK_CHAR* attendee, TSDK_E_CONF_AS_ACTION_TYPE action);

	/**
	* @ingroup AppShare
	* @brief [en]This interface is used to starts desktop sharing or application sharing.
	*        [cn]��ʼ���湲���Ӧ�ó�����
	*
	* @param [in] TSDK_E_CONF_APP_SHARE_TYPE shareType         [en]Indicates app share type.
	*                                                          [cn]Ӧ�ù�������
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @attention [en]For PC, the mobile device does not support this function 
	*            [cn]����PC���ƶ��豸��֧�ִ˹���
	* @see NA
	**/
    SERVICE_CONF int service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_TYPE shareType);


    //SERVICE_CONF int service_data_conf_request_present();

	/**
	* @ingroup AppShare
	* @brief [en]This interface is used to get screen data.
	*        [cn]��ȡ��Ļ����
	*
	* @param [in] TSDK_UINT32 confHandle                           [en]Indicates conference handle.
	*                                                              [cn]������
	* @param [out] TSDK_S_CONF_AS_SCREEN_DATA *screenData          [en]Indicates screen data.
	*                                                              [cn]��Ļ����
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @attention [en]NA
	*            [cn]NA
	* @see NA
	**/
    SERVICE_CONF int service_data_conf_app_share_get_screen_data(TSDK_S_CONF_AS_SCREEN_DATA *screenData);

	/**
	* @ingroup AppShare
	* @brief [en]This interface is used to stop desktop sharing or application sharing.
	*        [cn]ֹͣ���湲���Ӧ�ó�����
	*
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @see NA
	**/
    SERVICE_CONF int service_data_conf_app_share_stop();

	/**
	* @ingroup DocShare
	* @brief [en]This interface is used to open a document.
	*        [cn]��һ�������ĵ�
	*
	* @param [in] const char* file_path               [en]Indicates file path.
	*                                                 [cn]�򿪵��ļ�·��
	* @param [in] unsigned int* doc_id                [en]Indicates document id.
	*                                                 [cn]�ĵ�id
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @see NA
	**/
	SERVICE_CONF int service_data_conf_ds_share_open_document(const char* file_path,unsigned int* doc_id);

	/**
	* @ingroup DocShare
	* @brief [en]This interface is used to close a document.
	*        [cn]�رչ����ĵ�
	*
	* @param [in] unsigned int* doc_id                [en]Indicates document id.
	*                                                 [cn]�ĵ�id
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @see NA
	**/
	SERVICE_CONF int service_data_conf_ds_share_close_document(unsigned int docId);

	/**
	* @ingroup DocShare
	* @brief [en]This interface is used to get syn document_info.
	*        [cn]��ȡ�������ϵĵ�ǰ�ĵ���Ϣ
	*
	* @param [out] TSDK_S_DOC_PAGE_DETAIL_INFO* sync_info    [en]Indicates document information.
	*                                                        [cn]�ĵ�ҳ����Ϣ
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @see NA
	**/
	SERVICE_CONF int service_data_conf_ds_share_get_syn_document_info(TSDK_S_DOC_PAGE_DETAIL_INFO* sync_info);

	/**
	* @ingroup DocShare
	* @brief [en]This interface is used to set current page to show.
	*        [cn]���õ�ǰ��ʾ��ҳ��
	*
	* @param [in] unsigned int* doc_id                [en]Indicates document id.
	*                                                 [cn]�ĵ�id
	* @param [in] int pageIndex                       [en]Indicates page id.
	*                                                 [cn]ҳ��id
	* @param [in] unsigned int isDocShare             [en]Indicates whether share document.
	*                                                 [cn]�Ƿ�Ϊ�ĵ�����
	* @param [in] unsigned int isSyn                  [en]Indicates whether synchronization settings.
	*                                                 [cn]�Ƿ�ͬ������
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @see NA
	**/
	SERVICE_CONF int service_data_conf_ds_share_set_current_page(unsigned int docId, int pageIndex, unsigned int isDocShare, unsigned int isSyn);

	/**
	* @ingroup DocShare
	* @brief [en]This interface is used to get the rendered current page image.
	*        [cn]��ȡ��Ⱦ�õĵ�ǰҳ��ͼ��
	*
	* @param [in] unsigned int isDocShare                     [en]Indicates whether share document.
	*                                                         [cn]�Ƿ�Ϊ�ĵ�����
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @see NA
	**/
	SERVICE_CONF void* service_data_conf_ds_share_get_surfacebmp(unsigned int isDocShare);

	/**
	* @ingroup DocShare
	* @brief [en]This interface is used to set canvas background colour of document sharing module 
	*        [cn]�����ĵ�����ģ�黭���ı���ɫ
	*
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @see NA
	**/
	SERVICE_CONF int service_data_conf_ds_share_set_background_color();

	/**
	* @ingroup DocShare
	* @brief [en]This interface is used to set display mode of document sharing module
	*        [cn]�����ĵ�����ģ�����ʾģʽ
	*
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @see NA
	**/
	SERVICE_CONF int service_data_conf_ds_share_set_display_mode();

	/**
	* @ingroup DocShare
	* @brief [en]This interface is used to set the size of the display area.
	*        [cn]������ʾ����Ĵ�С
	*
	* @param [in] TSDK_S_SIZE size                    [en]Indicates display area width and height.
	*                                                 [cn]��ʾ����Ŀ�ߣ���TWIPSΪ��λ
	* @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
	*                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
	* @see NA
	**/
	SERVICE_CONF int service_data_conf_ds_share_set_canvas_size(TSDK_S_SIZE size);

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to join conference by anonymous.
    *        [cn]������������
    *
    * @param [in] TSDK_S_CONF_ANONYMOUS_JOIN_PARAM *confJoinParam       [en]Indicates param of anonymous join conference.
    *                                                                   [cn]����������
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]�ɹ�����TSDK_SUCCESS��ʧ�ܷ�����Ӧ������
    * @see NA
    **/
    SERVICE_CONF int service_join_conference_by_anonymous(TSDK_S_CONF_ANONYMOUS_JOIN_PARAM *confJoinParam);

	
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
