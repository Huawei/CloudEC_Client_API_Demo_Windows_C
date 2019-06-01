//
//  DemoData.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef DATA_H
#define DATA_H

#include <map>
#include "tsdk_conference_def.h"

using namespace std;

#define RESULT_SUCCESS 0

typedef enum
{
    AUDIO_DLG,   /////��Ƶ///
    VIDEO_DLG    /////��Ƶ///
}CALL_DLG_TYPE;

typedef enum {
    NO_CALL,           ///�޺���////
    CALLING,           ///������////
    CALL_CONNECTED,    ///��ͨ//////
    CALL_HOLD
}CALLSTATUS;

typedef enum
{
    AUDIO_CALL,        ////��Ƶ����//////
    VIDEO_CALL,        ////��Ƶ����//////
    AUDIO_CONF_CALL,   ////�������//////
    VIDEO_CONF_CALL
}COMMINTCALL_TYPE;

typedef enum
{
    AUDIO_BUTTON,   ////��Ƶ��ť//////
    VIDEO_BUTTON    ////��Ƶ��ť//////
}BUTTON_TYPE;

typedef enum
{
    COL_MEM_COMPERE,
    COL_MEM_PRESENT,
    COL_MEM_NAME,
    COL_MEM_ACCOUNT,
    COL_MEM_CALLNO,
    COL_MEM_CALLSTATE,
    COL_MEM_SPK,
    COL_MEM_MUTE,
    COL_MEM_HANDUP,
    COL_MEM_BROADCAST
}GROUPLIST_COLUMNID;

typedef enum
{
    AUDIO_CONF,
    VIDEO_CONF,
    AUDIO_DATA_CONF,
    VIDEO_DATA_CONF
}CONF_TYPE;

typedef enum
{
    DESKTOP = 0x0000, /*Full screen sharing */
    APP = 0x0001    /*Program sharing */
}ShareType;

/////����UI����
#define eSDK_OK 0
#define eSDK_Fail 1;

#define ID_UI_BEGIN                               WM_USER
#define ID_MAIN_SETTING_MENU                     (ID_UI_BEGIN+1)          //ϵͳ����////
#define ID_MAIN_LOGOUT_MENU                      (ID_UI_BEGIN+2)          //ע����ť////
#define ID_MAIN_EXIT_MENU                        (ID_UI_BEGIN+3)          //�˳���ť////
#define ID_CONF_DEL_MEM_MENU                     (ID_UI_BEGIN+4)          //����������ɾ����Ա////
#define ID_CONF_BROADCAST_MEM_MENU               (ID_UI_BEGIN+5)
#define ID_CONF_UNBROADCAST_MEM_MENU             (ID_UI_BEGIN+6)
#define ID_CONF_WATCH_MEM_MENU                   (ID_UI_BEGIN+7)
#define ID_CONF_RELEASE_CHAIRMAN                 (ID_UI_BEGIN+8)          //�ͷ���ϯ////
#define ID_CONF_RECALL_MEM_MENU                  (ID_UI_BEGIN+9)          //���º���////
#define ID_CONF_HANGUP_MEM_MENU                  (ID_UI_BEGIN+10)         //�Ҷ�������������ڻ����еĳ�Ա////
#define ID_CONF_MUTE_MEM_MENU                    (ID_UI_BEGIN+11)         //�����о�����Ա////
#define ID_CONF_UNMUTE_MEM_MENU                  (ID_UI_BEGIN+12)         //������ȡ��������Ա////
#define ID_CONF_UNHANDUP_MEM_MENU                (ID_UI_BEGIN+13)         //������ȡ������߾���////
#define ID_DCONF_SETPRESENT_MEM_MENU             (ID_UI_BEGIN+14)         //���ݻ���������Ϊ������////
#define ID_DCONF_SHARE_DESKTOP_MEM_MENU          (ID_UI_BEGIN+15)         //���ݻ�������������߹���////
#define ID_DCONF_STOP_SHARE_DESKTOP_MEM_MENU     (ID_UI_BEGIN+16)         //���ݻ�����ֹͣ����߹���////
#define ID_DCONF_REINVITE_MEM_MENU               (ID_UI_BEGIN+17)         //���ݻ������������������////
#define ID_DCONF_WATCH_MENU                      (ID_UI_BEGIN+18)         //ѡ�������////
#define ID_DCONF_BROADCAST_MENU                  (ID_UI_BEGIN+19)         //�㲥�����////
#define ID_DCONF_APPLY_AS_PRESENT_MENU           (ID_UI_BEGIN+20)         //����Ϊ������////
#define ID_DCONF_REQ_REMOTE_CONTROL_MENU         (ID_UI_BEGIN+21)         //����Զ�˿��Ʊ�����Ļ////
#define ID_DCONF_CANCEL_REMOTE_CONTROL_MENU      (ID_UI_BEGIN+22)         //ȡ��Զ�˿��Ʊ�����Ļ////
////Private Group
//#define ID_PRIGROUP_MODIFY_MENU                  (ID_UI_BEGIN+17)    //Ⱥ�����޸İ�ť////
//#define ID_PRIGROUP_DEL_MENU                     (ID_UI_BEGIN+18)    //����ͨѶ¼��ɾ����ť////
//#define ID_PRIGROUP_ADD_MENU                     (ID_UI_BEGIN+19)    //����ͨѶ¼��������ť////
//#define ID_PRIGROUP_ADD_CONTACT_MENU             (ID_UI_BEGIN+20)    //����ͨѶ¼��������ϵ�˰�ť////
//#define ID_PRIGROUP_ADD_UC_CONTACT_MENU          (ID_UI_BEGIN+21)    //����ͨѶ¼������UC���Ѱ�ť////
////Private Contact
//#define ID_PRIGROUP_DEL_CONTACT_MENU             (ID_UI_BEGIN+22)    //����ͨѶ¼��ɾ����ϵ��////
//#define ID_PRIGROUP_MODIFY_CONTACT_MENU          (ID_UI_BEGIN+23)    //����ͨѶ¼���޸���ϵ��////
//#define ID_PRIGROUP_CONTACT_DETAIL_MENU          (ID_UI_BEGIN+24)    //����ͨѶ¼�в鿴����////
//#define ID_PRIGROUP_INSTANTMSG_MENU              (ID_UI_BEGIN+25)    //����ͨѶ¼�з���ʱ��Ϣ////
//#define ID_PRIGROUP_SETNICKNAME_MENU             (ID_UI_BEGIN+26)    //����ͨѶ¼���޸ĺ����ǳ�////
//
////Move Group List
//#define ID_PRIGROUP_CONTACT_MOVE_MENU_START      (ID_UI_BEGIN+27)    //����ͨѶ¼���ƶ����ѷ��鿪ʼ////
//#define ID_PRIGROUP_CONTACT_MOVE_MENU_END        (ID_UI_BEGIN+28)    //����ͨѶ¼���ƶ����ѷ������//// 
////EntAddr Menu
//#define ID_ENTADDR_ADD_CONTACT                   (ID_UI_BEGIN+29)    //��ҵͨѶ¼��������ϵ��////
//#define ID_ENTADDR_GROUP_ADD_MENU_START          (ID_UI_BEGIN+30)    //��ҵͨѶ¼����ӿ�ʼ��ť////
//#define ID_ENTADDR_GROUP_ADD_MENU_END            (ID_UI_BEGIN+31)    //��ҵͨѶ¼����ӽ�����ť////
//
//#define ID_GROUP_RELEASE_MEM_MENU                (ID_UI_BEGIN +32)     //��ɢȺ��////    
//#define ID_GROUP_ADD_MEMBER_MENU                 (ID_UI_BEGIN +33)     //�½�Ⱥ���Ա////    
//#define ID_GROUP_EXIT_MENU                       (ID_UI_BEGIN +34)     //�˳�Ⱥ��////            
//#define ID_GROUP_ADD_MENU                        (ID_UI_BEGIN +35)     //����Ⱥ��////    

#define ID_CONF_JOIN_MENU                          (ID_UI_BEGIN +36)     //�������////
#define ID_CONF_DETAIL_MENU                        (ID_UI_BEGIN +38)     //�鿴Ⱥ������////

//Call Defines
#define WM_CALL_MODULE_BEGIN                     (ID_UI_BEGIN + 100)
#define WM_CALL_HANGUP                           (WM_CALL_MODULE_BEGIN + 1)
#define WM_CALL_HOLD                             (WM_CALL_MODULE_BEGIN + 2)
#define WM_CALL_UNHOLD                           (WM_CALL_MODULE_BEGIN + 3)
#define WM_CALL_HOLD_SUCESS                      (WM_CALL_MODULE_BEGIN + 4)
#define WM_CALL_UNHOLD_SUCESS                    (WM_CALL_MODULE_BEGIN + 5)
#define WM_CALL_START_RECORD                     (WM_CALL_MODULE_BEGIN + 6)
#define WM_CALL_STOP_RECORD                      (WM_CALL_MODULE_BEGIN + 7)
#define WM_CALL_BLIND_TRANSFER                   (WM_CALL_MODULE_BEGIN + 8)
#define WM_CALL_INCOMMING                        (WM_CALL_MODULE_BEGIN + 9)
#define WM_CALL_CONNECTED                        (WM_CALL_MODULE_BEGIN + 10)
#define WM_CALL_ANSWER_AUDIO                     (WM_CALL_MODULE_BEGIN + 11)
#define WM_CALL_ANSWER_VIDEO                     (WM_CALL_MODULE_BEGIN + 12)
#define WM_CALL_END                              (WM_CALL_MODULE_BEGIN + 13)
#define WM_CALL_MODIFY_VIDEO                     (WM_CALL_MODULE_BEGIN + 14)
#define WM_CALL_STARTCALL                        (WM_CALL_MODULE_BEGIN + 17)
#define WM_CALL_IPT_SUCESS                       (WM_CALL_MODULE_BEGIN + 18)
#define WM_CALL_IPT_FAILED                       (WM_CALL_MODULE_BEGIN + 19)
#define WM_CALL_BLTRANS_SUCESS                   (WM_CALL_MODULE_BEGIN + 20)
#define WM_CALL_BLTRANS_FAILED                   (WM_CALL_MODULE_BEGIN + 21)
#define WM_CALL_ADD_VIDEO                        (WM_CALL_MODULE_BEGIN + 22)
#define WM_CALL_START_CALL                       (WM_CALL_MODULE_BEGIN + 23)
#define WM_CALL_DTMF                             (WM_CALL_MODULE_BEGIN + 24)
#define WM_CALL_VIDEO_CREATE                     (WM_CALL_MODULE_BEGIN + 25)
#define WM_CALL_VIDEO_CLOSE                      (WM_CALL_MODULE_BEGIN + 26)
#define WM_CALL_DLG_CREATE                       (WM_CALL_MODULE_BEGIN + 27)
#define WM_CALL_DLG_CLOSE                        (WM_CALL_MODULE_BEGIN + 28)


#define WM_CALL_OPEN_VIDEO                       (WM_CALL_MODULE_BEGIN + 30)
#define WM_CALL_CLOSE_VIDEO                      (WM_CALL_MODULE_BEGIN + 31)
#define WM_CALL_REFUSE_OPEN_VIDEO                (WM_CALL_MODULE_BEGIN + 32)
#define WM_CALL_TRANS_TO_CONF_RESULT             (WM_CALL_MODULE_BEGIN + 33)

//AudioConf Defines
#define WM_CALL_CONF_REFRESH                     (WM_CALL_MODULE_BEGIN + 50)
#define WM_CALL_CONF_CLOSE_DLG                   (WM_CALL_MODULE_BEGIN + 51)
#define WM_CALL_INCOMMING_DLG_CLOSE              (WM_CALL_MODULE_BEGIN + 52)

#define WM_CALL_UI_PLUGIN_CLICK_HANGUP_CALL      (WM_CALL_MODULE_BEGIN + 55)

////DataConf Defines
#define WM_DATACONF_MODULE_BEGIN                 (ID_UI_BEGIN + 200)
#define WM_DATACONF_MODULE_PARAM                 (WM_DATACONF_MODULE_BEGIN + 1)
#define WM_DATACONF_MODULE_CLOSE                 (WM_DATACONF_MODULE_BEGIN + 2)
#define WM_DATACONF_MODULE_JOIN                  (WM_DATACONF_MODULE_BEGIN + 3)
#define WM_DATACONF_MODULE_CONPONENT             (WM_DATACONF_MODULE_BEGIN + 4)
#define WM_DATACONF_MODULE_ADD                   (WM_DATACONF_MODULE_BEGIN + 5)
#define WM_DATACONF_MODULE_USERLEAVE             (WM_DATACONF_MODULE_BEGIN + 6)
#define WM_DATACONF_MODULE_END                   (WM_DATACONF_MODULE_BEGIN + 7)
#define WM_DATACONF_MODULE_PRESENTERCHG          (WM_DATACONF_MODULE_BEGIN + 8)
#define WM_DATACONF_MODULE_HOST_CHG              (WM_DATACONF_MODULE_BEGIN + 9)
#define WM_DATACONF_MODULE_MUTE                  (WM_DATACONF_MODULE_BEGIN + 10)
#define WM_DATACONF_MODULE_VIDEO_ON              (WM_DATACONF_MODULE_BEGIN + 11)
#define WM_DATACONF_MODULE_VIDEO_OFF             (WM_DATACONF_MODULE_BEGIN + 12)
#define WM_DATACONF_MODULE_SHARING_SESSION       (WM_DATACONF_MODULE_BEGIN + 13)
#define WM_DATACONF_MODULE_SHARING_STATE         (WM_DATACONF_MODULE_BEGIN + 14)
#define WM_DATACONF_MODULE_SCREEN_DATA           (WM_DATACONF_MODULE_BEGIN + 15)
#define WM_DATACONF_MODULE_WB_DOC_NEW            (WM_DATACONF_MODULE_BEGIN + 16)
#define WM_DATACONF_MODULE_WB_PAG_NEW            (WM_DATACONF_MODULE_BEGIN + 17)
#define WM_DATACONF_MODULE_WB_CURRENT_PAGE       (WM_DATACONF_MODULE_BEGIN + 18)
#define WM_DATACONF_MODULE_WB_CURRENT_PAGE_IND   (WM_DATACONF_MODULE_BEGIN + 19)
#define WM_DATACONF_MODULE_WB_DRAW_DATA          (WM_DATACONF_MODULE_BEGIN + 20)
#define WM_DATACONF_MODULE_WB_DOC_DEL            (WM_DATACONF_MODULE_BEGIN + 21)
#define WM_DATACONF_MODULE_DS_DRAW_DATA          (WM_DATACONF_MODULE_BEGIN + 22)
#define WM_DATACONF_MODULE_DS_PAGE_IND           (WM_DATACONF_MODULE_BEGIN + 23)
#define WM_DATACONF_MODULE_DS_DOCLOADED          (WM_DATACONF_MODULE_BEGIN + 24)
#define WM_DATACONF_MODULE_DS_NEW                (WM_DATACONF_MODULE_BEGIN + 25)
#define WM_DATACONF_MODULE_DS_DELETE             (WM_DATACONF_MODULE_BEGIN + 26)
#define WM_DATACONF_MODULE_DS_PAGE_LOADED        (WM_DATACONF_MODULE_BEGIN + 27)
#define WM_DATACONF_MODULE_AS_PRIVILEGE_CHANGE   (WM_DATACONF_MODULE_BEGIN + 28)

///Auth_login Defines
#define WM_AUTH_LOGIN_MODULE_BEGIN               (ID_UI_BEGIN + 300)
#define WM_AUTH_LOGIN_MODULE_LOGIN_RESULT        (WM_AUTH_LOGIN_MODULE_BEGIN + 1)
#define WM_AUTH_LOGIN_SAVE_SELF_INFO             (WM_AUTH_LOGIN_MODULE_BEGIN + 2)
#define WM_LOGIN_AUTH_RESULT                     (WM_AUTH_LOGIN_MODULE_BEGIN + 3)
#define WM_LOGIN_GET_TEMP_USER_RESULT            (WM_AUTH_LOGIN_MODULE_BEGIN + 4)

//AudioConf Defines for EC6.0
#define WM_CONF_CTRL_MODULE_BEGIN                (ID_UI_BEGIN + 400)
#define WM_CONF_CTRL_BOOK_CONF_RESULT            (WM_CONF_CTRL_MODULE_BEGIN + 1)
#define WM_CONF_CTRL_CREATE_CONF_RESULT          (WM_CONF_CTRL_MODULE_BEGIN + 2)
#define WM_CONF_CTRL_CONF_CONNECTED_IND          (WM_CONF_CTRL_MODULE_BEGIN + 3)
#define WM_CONF_CTRL_GET_CONF_LIST_RESULT        (WM_CONF_CTRL_MODULE_BEGIN + 4)
#define WM_CONF_CTRL_GET_CONF_INFO_RESULT        (WM_CONF_CTRL_MODULE_BEGIN + 5)
#define WM_CONF_CTRL_BE_TRANS_TO_CONF_IND        (WM_CONF_CTRL_MODULE_BEGIN + 6)
#define WM_CONF_CTRL_CONF_INFO_IND               (WM_CONF_CTRL_MODULE_BEGIN + 7)
#define WM_CONF_CTRL_INFO_AND_STATUS_UPDATE      (WM_CONF_CTRL_MODULE_BEGIN + 8)
#define WM_CONF_CTRL_ADD_ATTENDEE_RESULT         (WM_CONF_CTRL_MODULE_BEGIN + 9)
#define WM_CONF_CTRL_CONF_INCOMING_IND           (WM_CONF_CTRL_MODULE_BEGIN + 10)
#define WM_CONF_CTRL_ADDRESSER_UPDATE_IND        (WM_CONF_CTRL_MODULE_BEGIN + 13)
#define WM_CONF_CTRL_CONF_COMMING                (WM_CONF_CTRL_MODULE_BEGIN + 14)
#define WM_CONF_CTRL_CALL_TRANS_CONF             (WM_CONF_CTRL_MODULE_BEGIN + 15)
#define WM_CONF_CTRL_ADD_DATA_CONF_IND           (WM_CONF_CTRL_MODULE_BEGIN + 16)
#define WM_CONF_CTRL_GET_DATA_CONF_PARAM         (WM_CONF_CTRL_MODULE_BEGIN + 17)
#define WM_CONF_CTRL_JOIN_RESULT                 (WM_CONF_CTRL_MODULE_BEGIN + 18)
#define WM_CONF_CTRL_JOIN_DATACONF_RESULT        (WM_CONF_CTRL_MODULE_BEGIN + 19)
#define WM_CONF_CTRL_OPERATION_RESULT            (WM_CONF_CTRL_MODULE_BEGIN + 20)
#define WM_CONF_CTRL_UI_PLUGIN_CLICK_END_CONF    (WM_CONF_CTRL_MODULE_BEGIN + 21)
#define WM_CONF_CTRL_UI_PLUGIN_CLICK_LEAVE_CONF  (WM_CONF_CTRL_MODULE_BEGIN + 22)
#define WM_CONF_CTRL_UI_PLUGIN_CLICK_START_SHARE (WM_CONF_CTRL_MODULE_BEGIN + 23)

//IM Defines for EC6.0
#define WM_IM_BEGIN                              (ID_UI_BEGIN + 500)
#define WM_MENU_SEND_IM                          (WM_IM_BEGIN +1)            //���ͼ�ʱ��Ϣ
#define WM_SHOW_DETAIL                           (WM_IM_BEGIN +2)    
#define WM_CLOSE_IM_WND                          (WM_IM_BEGIN +3)            //�رռ�ʱ��Ϣdialog
#define WM_RECV_IM                               (WM_IM_BEGIN +4)            //�رռ�ʱ��Ϣdialog
#define WM_RECV_INPUTING                         (WM_IM_BEGIN +5)            //�رռ�ʱ��Ϣdialog
#define WM_UPDATE_CONTACT                        (WM_IM_BEGIN +6)            
#define WM_MENU_GROUP_CHAT                       (WM_IM_BEGIN +7) 
#define WM_GROUP_NOTIFY                          (WM_IM_BEGIN +8)            //Ⱥ��֪ͨ
#define WM_GROUP_MEM_ADD                         (WM_IM_BEGIN +9)            //����Ⱥ���Ա///
#define WM_GROUP_MEM_DEL                         (WM_IM_BEGIN +10)           //ɾ��Ⱥ���Ա///
#define WM_CONFIRM_JOINFIXEDGROUP_NOTIFY         (WM_IM_BEGIN +11)           //��������̶�Ⱥ����///
#define WM_DISMISS_FIXEDGROUP_NOTIFY             (WM_IM_BEGIN +12)           //�̶�Ⱥ���ɢ֪ͨ
#define WM_FIXGROUP_IDENTIFY_NOTIFY              (WM_IM_BEGIN +13)           //�̶�Ⱥ����֤֪ͨ
#define WM_FIXGROUP_DELETE_NOTIFY                (WM_IM_BEGIN +14)           //ɾ��Ⱥ���Ա֪ͨ
#define WM_GROUP_INVITEDLG_CLOSE                 (WM_IM_BEGIN +15)           //�ر�Ⱥ��֪ͨdialog
#define WM_UPDATE_STATUS                         (WM_IM_BEGIN +16)           //״̬���////
#define WM_FIXGROUP_RECEIVEJOIN_FIEDGROUP        (WM_IM_BEGIN +17)           //����Ա�յ���������Ⱥ����/

#define SERVICE_IM_D_MAX_ACCOUNT_LENGTH           (32)                       /**< Account length*/
#define SERVICE_IM_D_MAX_NAME_LENGTH              (512)                      /**< Name length */
#define SERVICE_IM_D_MAX_BIRTHDAY_LENGTH          (64)                       /**< Birthday length */
#define SERVICE_IM_D_AGE_LENGTH                   (8)                        /**< Age length */
#define SERVICE_IM_D_MAX_PHONE_LENGTH             (256)                      /**< Phone length */
#define SERVICE_IM_D_MAX_DESC_LENGTH              (1024)                     /**< Describition length */
#define SERVICE_IM_D_MAX_DEPTNAME_LENGTH          (1024)                     /**< Deptname length */
#define SERVICE_IM_D_MAX_TIMESTAMP_LENGTH         (15)                       /**< Timestamp length */
#define SERVICE_IM_D_MAX_STATUS_LENGTN            (50)                       /**< Stauts   length */
#define SERVICE_IM_D_GROUPID_LENGTH               (64)                       /**<Group ID length*/
#define SERVICE_IM_D_GENEAL_LENGTH                (32)                       /**<Geneal length*/

//address list
typedef std::multimap<long long, long long> MAP_USER_GROUP;
extern MAP_USER_GROUP g_mapUserGroup;

//book conf list
typedef std::map<long long, TSDK_S_CONF_BASE_INFO> MAP_CONFINFO;
extern MAP_CONFINFO g_mapConfInfo;

#define SAFE_DELETE(pPoint) \
{/*lint -e774 */\
    if(NULL != pPoint)\
    {\
        delete pPoint;\
        pPoint = NULL;\
    }/*lint +e774 */\
}

#define SAFE_DELETE_ARRAY(pPoint) \
{/* lint -e774 */\
    if(NULL != pPoint)\
    {\
        delete[] pPoint;\
        pPoint = NULL;\
    }/* lint +e774 */\
}

#endif/*DATA_H*/
