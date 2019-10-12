
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
    *        [cn]预约会议(立即或延时召开)
    *
    * @param [in] SERVICE_S_BOOK_CONF_INFO *bookConfInfo       [en]Indicates info of book conference.
    *                                                          [cn]预约会议信息
    *
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code, value of TSDK_E_CONF_ERR_ID.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码，取值参考TSDK_E_CONF_ERR_ID
    *
    * @attention [en]If you create an instant meeting, the SDK automatically joins the meeting after the meeting is successfully created
    *            [cn]如果创建的是立即会议，会议创建成功后，SDK会自动加入会议
    * @see TSDK_E_CONF_EVT_BOOK_CONF_RESULT
    **/
    SERVICE_CONF int service_conf_book(SERVICE_S_BOOK_CONF_INFO *bookConfInfo);

    /**
    * @ingroup ConfMng
    * @brief [en]This interface is used to get conference list.
    *        [cn]获取会议列表
    *
    * @param [in]NA
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en] corresponding callback event is TSDK_E_CONF_EVT_QUERY_CONF_LIST_RESULT.
    *            [cn] 对应的回调事件为TSDK_E_CONF_EVT_QUERY_CONF_LIST_RESULT
    * @see TSDK_E_CONF_EVT_QUERY_CONF_LIST_RESULT
    **/
    SERVICE_CONF int service_conf_get_list();

    /**
    * @ingroup ConfMng
    * @brief [en]This interface is used to get detail info of conference.
    *        [cn]获取会议详细信息
    *
    * @param [in] TSDK_CHAR *conf_id                           [en]Indicates get detail info of conference id.
    *                                                          [cn]获取获取会议详细信息的会议id
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en] corresponding callback event is TSDK_E_CONF_EVT_QUERY_CONF_DETAIL_RESULT.
    *            [cn] 对应的回调事件为TSDK_E_CONF_EVT_QUERY_CONF_DETAIL_RESULT
    * @see TSDK_E_CONF_EVT_QUERY_CONF_DETAIL_RESULT
    **/
    SERVICE_CONF int service_conf_query_conference_detail(TSDK_CHAR *conf_id);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to proactively join a conference.
    *        [cn]主动加入会议
    *
    * @param [in] TSDK_S_CONF_JOIN_PARAM* confJoinParam        [en]Indicates conf join param.
    *                                                          [cn]入会参数
    * @param [in] TSDK_CHAR* joinNumber                        [en]Indicates join number.
    *                                                          [cn]入会号码
    * @param [in] unsigned int isVideoJoi                      [en]Indicates whether video join conference.
    *                                                          [cn]是否视频接入会议
    * @param [out] TSDK_UINT32 *callId                         [en]Indicates the call ID corresponding to the meeting is valid when the SIP terminal number is used.
    *                                                          [cn]会议对应的呼叫ID，在使用SIP终端号码入会时有效。
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see TSDK_E_CONF_EVT_JOIN_CONF_RESULT
    **/
    SERVICE_CONF int service_conf_join(TSDK_S_CONF_JOIN_PARAM* confJoinParam, TSDK_CHAR* joinNumber, unsigned int isVideoJoin, TSDK_UINT32 *callId);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to mute or unmute a conference.
    *        [cn]设置或取消闭音会场
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] unsigned int isMute                          [en]Indicates whether mute.
    *                                                          [cn]是否闭音
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]corresponding result event notification is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
    *            [cn]对应的结果事件通知为TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT；
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_mute(TSDK_UINT32 confHandle, unsigned int isMute);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to lock or unlock a conference.
    *        [cn]设置或取消锁定会议
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] unsigned int isLock                          [en]Indicates whether lock conference.
    *                                                          [cn]是否锁定会议
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]Under chairman conference control, when conference is locked attendees can not join conference by any way except invited by chairman.
    *            [en]corresponding result event notify is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    *            [cn]主席会控，会议锁定后，除主席邀请外，其他人不能通过任何途径加入会议;
    *            [cn]对应的结果事件通知为TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_lock(TSDK_UINT32 confHandle, unsigned int isLock);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is invoked by a participant to proactively leave a conference.
    *        [cn]离开会议
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see NA.
    **/
    SERVICE_CONF int service_conf_leave(TSDK_UINT32 confHandle);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is invoked by the chairman to end an ongoing conference.
    *        [cn]结束会议
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see TSDK_E_CONF_EVT_CONF_END_IND.
    **/
    SERVICE_CONF int service_conf_end(TSDK_UINT32 confHandle);

    SERVICE_CONF int service_conf_release(TSDK_UINT32 confHandle);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is invoked by the chairman to add a new participant to a conference.
    *        [cn]添加与会者
    *
    * @param [in] TSDK_UINT32 confHandle                            [en]Indicates conference control handle.
    *                                                               [cn]会控句柄
    * @param [in] const TSDK_S_ADD_ATTENDEES_INFO* addAttendeeInfo  [en]Indicates add attendee info.
    *                                                               [cn]添加与会者信息
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA
    *            [cn]NA
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_add_attendee(TSDK_UINT32 confHandle, const TSDK_S_ADD_ATTENDEES_INFO* addAttendeeInfo);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to remove attendee.
    *        [cn]删除与会者
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] const TSDK_CHAR* attendee                    [en]Indicates attendee number.
    *                                                          [cn]与会者号码
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_delete_attendee(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to mute attendee.
    *        [cn]闭音与会者
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] const TSDK_CHAR* attendee                    [en]Indicates attendee number.
    *                                                          [cn]与会者号码
    * @param [in] unsigned int isMute                          [en]Indicates whether mute.
    *                                                          [cn]是否闭音
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]Chairman can mute all attendee, normal attendee can only mute themselves, attendee can only listen not speak when they are muted.
    *            [en]corresponding result event notification is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
    *            [cn]主席可对所有与会者设置或取消闭音，普通与会者只可对自己设置或取消闭音，被设置闭音时，与会者可听不可说；
    *            [cn]对应的结果事件通知为TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT；
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_mute_attendee(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee, unsigned int isMute);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to hang up attendee.
    *        [cn]挂断与会者
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] const TSDK_CHAR* attendee                    [en]Indicates attendee number.
    *                                                          [cn]与会者号码
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_hangup_attendee(TSDK_UINT32 confHandle, const TSDK_CHAR* attendee);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to accept a conference call.
    *        [cn]接听会议来电
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] unsigned int isJoinVideo                     [en]Indicates whether join video conference.
                                                               [cn]是否接入视频会议
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                             [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @attention [en]NA.
    *            [cn]NA.
    * @see NA.
    **/
    SERVICE_CONF int service_conf_accept(TSDK_UINT32 confHandle, unsigned int isJoinVideo);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to reject a conference call.
    *        [cn]拒接会议来电
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conf handle.
    *                                                          [cn]会控句柄
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see NA.
    **/
    SERVICE_CONF int service_conf_reject(TSDK_UINT32 confHandle);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to release chair rights.
    *        [cn]释放主席权限
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]Corresponding result event notify is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
    *            [cn]对应的结果事件通知为TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_release_chairman(TSDK_UINT32 confHandle);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to apply for chair rights.
    *        [cn]申请主席权限
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] TSDK_CHAR* pwd                               [en]Indicates chairman password.
    *                                                          [cn]主席密码
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]corresponding result event notify is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
    *            [cn]对应的结果事件通知为TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT；
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_request_chairman(TSDK_UINT32 confHandle,TSDK_CHAR* pwd);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is invoked by a common participant in a conference to set their hands-up or cancel the setting or is invoked by the moderator to cancel hands-up of the other participants.
    *        [cn]设置或取消举手
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] unsigned int isHandup                        [en]Indicates whether hand up.
    *                                                          [cn]是否举手
    * @param [in] TSDK_CHAR* attendee                          [en]Indicates attendee number(It's no need if it's config oneself).
    *                                                          [cn]与会者号码(若设置自己，则无需填写)
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]Corresponding result event notify is TSDK_E_CONF_SET_HANDUP or TSDK_E_CONF_CANCEL_HANDUP.
    *            [cn]对应的结果事件通知为TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_handup(TSDK_UINT32 confHandle, unsigned int isHandup, TSDK_CHAR* attendee);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to set conference video mode.
    *        [cn]设置会议视频模式
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] TSDK_E_CONF_VIDEO_MODE confMode              [en]Indicates conference video mode.
    *                                                          [cn]会议视频模式
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention NA.
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
    **/
    SERVICE_CONF int service_conf_set_video_mode(TSDK_UINT32 confHandle, TSDK_E_CONF_VIDEO_MODE confMode);

    /**
    * @ingroup ConfCtrl.
    * @brief [en]This interface is used to broadcast or cancel broadcasting a specified participant.
    *        [cn]广播或取消广播指定与会者（会场）
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] TSDK_CHAR* attendee                          [en]Indicates attendee number.
    *                                                          [cn]与会者号码
    * @param [in] unsigned int isRoadcast                      [en]Indicates broadcast or cancel broadcast.
    *                                                          [cn]广播或是取消广播
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_broadcast_attendee(TSDK_UINT32 confHandle, TSDK_CHAR* attendee, unsigned int isRoadcast);

    /**
    * @ingroup ConfCtrl.
    * @brief [en]This interface is invoked by the chairman to select the participant to view among the participants who are being broadcast. 
    *        [cn]请求观看指定与会者画面
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @param [in] TSDK_S_WATCH_ATTENDEES_INFO* attendee        [en]Indicates watch attendee param info.
    *                                                          [cn]选看与会者画面参数信息
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_watch_attendee(TSDK_UINT32 confHandle, TSDK_S_WATCH_ATTENDEES_INFO* attendee);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to upgrade conference.
    *        [cn]升级会议
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]Corresponding result event notify is TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT.
    *            [cn]对应的结果事件通知为TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_conf_upgrade_conf(TSDK_UINT32 confHandle);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to join data conference.
    *        [cn]加入数据会议
    *
    * @param [in] TSDK_UINT32 confHandle                       [en]Indicates conference handle.
    *                                                          [cn]会控句柄
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see TSDK_E_CONF_EVT_JOIN_CONF_RESULT.
    **/
    SERVICE_CONF int service_conf_join_data_conference(TSDK_UINT32 confHandle);

    /**
    * @ingroup ConfCtrl
    * @brief [en]This interface is used to set conference presenter
    *        [cn]设置主讲人
    *
    * @param [in] TSDK_UINT32 confHandle                 [en]Indicates conference handle conference handle
    *                                                    [cn]会议句柄
    * @param [in] TSDK_CHAR* attendee                    [en]Indicates attendee number
    *                                                    [cn]与会者号码
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    *
    * @attention [en]NA.
    *            [cn]NA.
    * @see TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT
    **/
    SERVICE_CONF int service_data_conf_set_presenter(TSDK_UINT32 confHandle, TSDK_CHAR* attendee);

    /**
    * @ingroup AppShare
    * @brief [en]This interface is used to configure the owner of screen sharing.
    *        [cn]设置屏幕共享的拥有者
    *
    * @param [in] TSDK_CHAR* attendee                    [en]Indicates attendee number
    *                                                    [cn]与会者号码
    * @param [in] TSDK_E_CONF_AS_ACTION_TYPE action      [en]Indicates set action, refer to TSDK_E_CONF_AS_ACTION_TYPE.
    *                                                    [cn]设置动作, 参考TSDK_E_CONF_AS_ACTION_TYPE.
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @attention [en]NA
    *            [cn]NA
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_app_share_set_owner(TSDK_CHAR* attendee, TSDK_E_CONF_AS_ACTION_TYPE action);

    /**
    * @ingroup AppShare
    * @brief [en]This interface is used to starts desktop sharing or application sharing.
    *        [cn]开始桌面共享或应用程序共享
    *
    * @param [in] TSDK_E_CONF_APP_SHARE_TYPE shareType         [en]Indicates app share type.
    *                                                          [cn]应用共享类型
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @attention [en]For PC, the mobile device does not support this function 
    *            [cn]用于PC，移动设备不支持此功能
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_app_share_start(TSDK_E_CONF_APP_SHARE_TYPE shareType);

    SERVICE_CONF int service_data_conf_app_share_set_privilege(TSDK_CHAR* attendee, TSDK_E_CONF_SHARE_PRIVILEGE_TYPE privilege_type, TSDK_E_CONF_AS_ACTION_TYPE action);


    //SERVICE_CONF int service_data_conf_request_present();

    /**
    * @ingroup AppShare
    * @brief [en]This interface is used to get screen data.
    *        [cn]获取屏幕数据
    *
    * @param [in] TSDK_UINT32 confHandle                           [en]Indicates conference handle.
    *                                                              [cn]会议句柄
    * @param [out] TSDK_S_CONF_AS_SCREEN_DATA *screenData          [en]Indicates screen data.
    *                                                              [cn]屏幕数据
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @attention [en]NA
    *            [cn]NA
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_app_share_get_screen_data(TSDK_S_CONF_AS_SCREEN_DATA *screenData);


    SERVICE_CONF int service_data_conf_app_share_attach_window(TSDK_UPTR window_handle);


    SERVICE_CONF int service_data_conf_app_share_detach_window(TSDK_VOID);


    SERVICE_CONF int service_data_conf_app_share_set_render_view_size(TSDK_INT32 width, TSDK_INT32 high);

    /**
    * @ingroup AppShare
    * @brief [en]This interface is used to stop desktop sharing or application sharing.
    *        [cn]停止桌面共享或应用程序共享
    *
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_app_share_stop();

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to open a document.
    *        [cn]打开一个共享文档
    *
    * @param [in] const char* file_path               [en]Indicates file path.
    *                                                 [cn]打开的文件路径
    * @param [in] unsigned int* doc_id                [en]Indicates document id.
    *                                                 [cn]文档id
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_ds_share_open_document(const char* file_path,unsigned int* doc_id);

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to close a document.
    *        [cn]关闭共享文档
    *
    * @param [in] unsigned int* doc_id                [en]Indicates document id.
    *                                                 [cn]文档id
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_ds_share_close_document(unsigned int docId);

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to get syn document_info.
    *        [cn]获取服务器上的当前文档信息
    *
    * @param [out] TSDK_S_DOC_PAGE_DETAIL_INFO* sync_info    [en]Indicates document information.
    *                                                        [cn]文档页面信息
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_ds_share_get_syn_document_info(TSDK_E_COMPONENT_ID componentId, TSDK_S_DOC_PAGE_DETAIL_INFO* sync_info);  

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to set current page to show.
    *        [cn]设置当前显示的页面
    *
    * @param [in] unsigned int* doc_id                [en]Indicates document id.
    *                                                 [cn]文档id
    * @param [in] int pageIndex                       [en]Indicates page id.
    *                                                 [cn]页面id
    * @param [in] unsigned int isDocShare             [en]Indicates whether share document.
    *                                                 [cn]是否为文档共享
    * @param [in] unsigned int isSyn                  [en]Indicates whether synchronization settings.
    *                                                 [cn]是否同步设置
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_ds_share_set_current_page(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex, unsigned int isSyn);

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to get the rendered current page image.
    *        [cn]获取渲染好的当前页面图像
    *
    * @param [in] unsigned int isDocShare                     [en]Indicates whether share document.
    *                                                         [cn]是否为文档共享
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF void* service_data_conf_ds_share_get_surfacebmp(TSDK_E_COMPONENT_ID componentId);

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to set canvas background colour of document sharing module 
    *        [cn]设置文档共享模块画布的背景色
    *
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_ds_share_set_canvas_size(TSDK_E_COMPONENT_ID componentId, int width, int high);

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to set display mode of document sharing module
    *        [cn]设置文档共享模块的显示模式
    *
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_ds_share_set_background_color(TSDK_E_COMPONENT_ID componentId);

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to set the size of the display area.
    *        [cn]设置显示区域的大小
    *
    * @param [in] TSDK_S_SIZE size                    [en]Indicates display area width and height.
    *                                                 [cn]显示区域的宽高，以TWIPS为单位
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_ds_share_set_display_mode(TSDK_E_COMPONENT_ID componentId);

    SERVICE_CONF int service_data_conf_ds_share_set_zoom_mode(TSDK_E_COMPONENT_ID componentId, IN TSDK_UINT32 document_id,
        IN TSDK_E_DOC_SHARE_ZOOM_MODE zoom_mode, IN TSDK_UINT32 zoom_percent, IN TSDK_BOOL is_sync, IN TSDK_BOOL is_redraw);


    /**
    * @ingroup WhiteboardShare
    * @brief [en]This interface is used to open a whiteboard.
    *        [cn]打开一个新的共享白板
    *
    * @param [out] unsigned int* doc_id                    [en]Indicates document id.
    *                                                      [cn]文档id
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_data_conf_wb_share_open_whiteboard(unsigned int* docId);

    SERVICE_CONF int service_data_conf_wb_share_new_page(unsigned int docId, int page_width, int page_height, unsigned int* page_id);

    SERVICE_CONF int service_data_conf_wb_share_whiteboard_delete(unsigned int docId);

    SERVICE_CONF int service_data_conf_wb_share_whiteboard_delete_page(unsigned int docId, unsigned int pageId);

    SERVICE_CONF int service_data_conf_annotation_create_start(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex,
        IN TSDK_E_ANNOTATION_MAIN_TYPE mainType, TSDK_E_ANNOTATION_DRAWING_SUB_TYPE subType, int x, int y);
    
    SERVICE_CONF int service_data_conf_annotation_update(TSDK_E_COMPONENT_ID componentId, const TSDK_S_POINT* point);
    
    SERVICE_CONF int service_data_conf_annotation_create_finish(TSDK_E_COMPONENT_ID componentId, unsigned int is_cancel);
    
    SERVICE_CONF int service_data_conf_annotation_delete(TSDK_E_COMPONENT_ID componentId, 
        unsigned int document_id, unsigned int page_index, unsigned int* annotation_id, int count);
    
    SERVICE_CONF int service_data_conf_annotation_laser_pointer_start(TSDK_E_COMPONENT_ID componentId, 
        TSDK_S_ANNOTATION_LASER_POINTER_INFO *laser_pointer_info);
    
    SERVICE_CONF int service_data_conf_annotation_laser_pointer_moveto(TSDK_E_COMPONENT_ID componentId, int x, int y);   

    SERVICE_CONF int service_data_conf_annotation_laser_pointer_stop(TSDK_E_COMPONENT_ID componentId);
    
    SERVICE_CONF int service_data_conf_annotation_set_select(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex, 
        TSDK_E_ANNOTATION_SELECT_MODE selectMode, unsigned int* annotation_id, int count, unsigned int isRedraw);
   
    SERVICE_CONF int service_data_conf_annotation_edit_start(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex, 
        unsigned int* annotationId, int count, unsigned int refAnnotationId, TSDK_E_ANNOTATION_HIT_TEST_CODE editType, TSDK_S_POINT* point);
    
    SERVICE_CONF int service_data_conf_annotation_edit_update(TSDK_E_COMPONENT_ID componentId, TSDK_S_POINT* point);

    SERVICE_CONF int service_data_conf_annotation_edit_finish(TSDK_E_COMPONENT_ID componentId, unsigned int isCancel);

    SERVICE_CONF int service_data_conf_annotation_hit_test_point(TSDK_E_COMPONENT_ID componentId, unsigned int docId, int pageIndex, 
        TSDK_S_POINT* point, unsigned int* selectAnnotationId, TSDK_E_ANNOTATION_HIT_TEST_CODE* testResult, unsigned int* annotationType);
        
    SERVICE_CONF int service_data_conf_annotation_set_pen(TSDK_E_COMPONENT_ID componentId, TSDK_E_ANNOTATION_PEN_TYPE penType, 
        TSDK_E_ANNOTATION_PEN_STYLE style, unsigned int color, unsigned int width);       

    /**
    * @ingroup DocShare
    * @brief [en]This interface is used to join conference by anonymous.
    *        [cn]加入匿名会议
    *
    * @param [in] TSDK_S_CONF_ANONYMOUS_JOIN_PARAM *confJoinParam       [en]Indicates param of anonymous join conference.
    *                                                                   [cn]匿名入会参数
    * @retval int                [en]If success return TSDK_SUCCESS, otherwise return corresponding error code.
    *                            [cn]成功返回TSDK_SUCCESS，失败返回相应错误码
    * @see NA
    **/
    SERVICE_CONF int service_join_conference_by_anonymous(TSDK_S_CONF_ANONYMOUS_JOIN_PARAM *confJoinParam);

    
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
