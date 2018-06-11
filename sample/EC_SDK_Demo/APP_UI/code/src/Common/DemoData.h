//
//  DemoData.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef DATA_H
#define DATA_H

#include <map>
#include "tsdk_conference_def.h"

using namespace std;

#define RESULT_SUCCESS 0

typedef enum
{
    TERMINAL_ECS,   ////SIP终端//////
    TERMINAL_SIP    ////ECS终端//////
}APPTYPE;

typedef enum
{
    UC_SIGNLE_CHAT,    /////单聊//////
    UC_MULTI_CHAT,     /////群聊//////
    UC_SIGNLE_CALL,    /////P2P语音///
    SIP_SIGNLE_CALL,   /////P2P语音///
    UC_SIGNLE_VIDEO,   /////P2P视频///
    SIP_SIGNLE_VIDEO,  /////P2P视频///
    UC_MULTI_CALL,     /////会议通话//
    SIP_MULTI_CALL     /////会议通话//
}DLG_TYPE;

typedef enum {
    NO_CALL,        ///无呼叫////
    CALLING,        ///呼叫中////
    CALL_CONNECTED,  ///接通//////
    CALL_HOLD
}CALLSTATUS;

typedef enum
{
    AUDIO_CALL,   ////音频呼叫//////
    VIDEO_CALL,    ////视频呼叫//////
    AUDIO_CONF_CALL,     ////会议呼叫//////
    VIDEO_CONF_CALL
}COMMINTCALL_TYPE;

typedef enum
{
    AUDIO_BUTTON,   ////音频按钮//////
    VIDEO_BUTTON    ////视频按钮//////
}BUTTON_TYPE;

typedef enum
{
    COL_MEM_COMPERE,
    COL_MEM_NAME,
    COL_MEM_ACCOUNT,
    COL_MEM_CALLNO,
    COL_MEM_CALLSTATE,
    COL_MEM_SPK,
    COL_MEM_MUTE,
    COL_MEM_HANDUP,
    COL_MEM_BROADCAST,
    COL_MEM_PRESENT
}GROUPLIST_COLUMNID;

typedef enum
{
    AUDIO_METTING = 0x01,
    VIDEO_METTING = 0x02,
    HDVIDEO_METTING = 0x04,
    DATA_METTING = 0x10,
    DESKTOPSHARING_METTING = 0x20
}MettingType;

typedef enum
{
    COL_DATACONFMEM_NUMBER,
    COL_DATACONFMEM_NAME,
    COL_DATACONFMEM_STATUS,
    COL_DATACONFMEM_MUTE
}DATACONFLIST_COLUMNID;

typedef enum
{
    COL_Status,
    COL_Name,
    COL_ACCOUNT,
    COL_DptName,
    COL_Email,
    COL_BINDNUMBER,
    COL_BINDNO1,
    COL_BINDNO2,
    COL_MOBILE,
    COL_OFFICENUM,
    COL_OFFICENUM2,
    COL_HOMENUM,
    COL_OTHERNUM,
    COL_OTHERNUM2,
    COL_FAX,
    COL_TITLE
}STAFFLIST_COLUMNID;

typedef enum
{
    DESKTOP = 0x0000, /*Full screen sharing */
    APP = 0x0001    /*Program sharing */

}ShareType;

/////定义UI部分
#define eSDK_OK 0
#define eSDK_Fail 1;

#define ID_UI_BEGIN                               WM_USER
#define ID_MAIN_SETTING_MENU                     (ID_UI_BEGIN+1)            //系统设置////
#define ID_MAIN_LOGOUT_MENU                      (ID_UI_BEGIN+2)            //注销按钮////
#define ID_MAIN_EXIT_MENU                        (ID_UI_BEGIN+3)            //退出按钮////
#define ID_CONF_DEL_MEM_MENU                     (ID_UI_BEGIN+4)            //语音会议中删除成员////
#define ID_CONF_BROADCAST_MEM_MENU               (ID_UI_BEGIN+5)
#define ID_CONF_UNBROADCAST_MEM_MENU             (ID_UI_BEGIN+6)
#define ID_CONF_WATCH_MEM_MENU                   (ID_UI_BEGIN+7)
#define ID_CONF_RELEASE_CHAIRMAN                 (ID_UI_BEGIN+8)            //释放主席////
#define ID_CONF_RECALL_MEM_MENU                  (ID_UI_BEGIN+9)            //重新呼叫////
#define ID_CONF_HANGUP_MEM_MENU                  (ID_UI_BEGIN+10)            //挂断正在邀请或者在会议中的成员////
#define ID_CONF_MUTE_MEM_MENU                    (ID_UI_BEGIN+11)            //语音会议中静音成员////
#define ID_CONF_UNMUTE_MEM_MENU                  (ID_UI_BEGIN+12)        //语音会议中取消静音成员////
#define ID_DCONF_SETPRESENT_MEM_MENU             (ID_UI_BEGIN+13)    //数据会议中设置为主讲人////
#define ID_DCONF_SHARE_DESKTOP_MEM_MENU          (ID_UI_BEGIN+14)     //数据会议中邀请与会者共享////
#define ID_DCONF_STOP_SHARE_DESKTOP_MEM_MENU     (ID_UI_BEGIN+15)        //数据会议中停止与会者共享////
#define ID_DCONF_REINVITE_MEM_MENU               (ID_UI_BEGIN+16)    //数据会议中重新邀请与会者////
//Private Group
#define ID_PRIGROUP_MODIFY_MENU                  (ID_UI_BEGIN+17)    //群组中修改按钮////
#define ID_PRIGROUP_DEL_MENU                     (ID_UI_BEGIN+18)    //个人通讯录中删除按钮////
#define ID_PRIGROUP_ADD_MENU                     (ID_UI_BEGIN+19)    //个人通讯录中新增按钮////
#define ID_PRIGROUP_ADD_CONTACT_MENU             (ID_UI_BEGIN+20)    //个人通讯录中新增联系人按钮////
#define ID_PRIGROUP_ADD_UC_CONTACT_MENU          (ID_UI_BEGIN+21)    //个人通讯录中新增UC好友按钮////
//Private Contact
#define ID_PRIGROUP_DEL_CONTACT_MENU             (ID_UI_BEGIN+22)    //个人通讯录中删除联系人////
#define ID_PRIGROUP_MODIFY_CONTACT_MENU          (ID_UI_BEGIN+23)    //个人通讯录中修改联系人////
#define ID_PRIGROUP_CONTACT_DETAIL_MENU          (ID_UI_BEGIN+24)    //个人通讯录中查看详情////
#define ID_PRIGROUP_INSTANTMSG_MENU              (ID_UI_BEGIN+25)    //个人通讯录中发起及时消息////
#define ID_PRIGROUP_SETNICKNAME_MENU             (ID_UI_BEGIN+26)    //个人通讯录中修改好友昵称////

//Move Group List
#define ID_PRIGROUP_CONTACT_MOVE_MENU_START      (ID_UI_BEGIN+27)    //个人通讯录中移动好友分组开始////
#define ID_PRIGROUP_CONTACT_MOVE_MENU_END        (ID_UI_BEGIN+28)    //个人通讯录中移动好友分组结束//// 
//EntAddr Menu
#define ID_ENTADDR_ADD_CONTACT                   (ID_UI_BEGIN+29)    //企业通讯录中新增联系人////
#define ID_ENTADDR_GROUP_ADD_MENU_START          (ID_UI_BEGIN+30)    //企业通讯录中添加开始按钮////
#define ID_ENTADDR_GROUP_ADD_MENU_END            (ID_UI_BEGIN+31)    //企业通讯录中添加结束按钮////

#define ID_GROUP_RELEASE_MEM_MENU                (ID_UI_BEGIN +32)     //解散群组////    
#define ID_GROUP_ADD_MEMBER_MENU                 (ID_UI_BEGIN +33)     //新建群组成员////    
#define ID_GROUP_EXIT_MENU                       (ID_UI_BEGIN +34)     //退出群组////            
#define ID_GROUP_ADD_MENU                        (ID_UI_BEGIN +35)     //新增群组////    

#define ID_CONF_JOIN_MENU                        (ID_UI_BEGIN +36)     //加入会议////
#define ID_CONF_IVR_JOIN_MENU                    (ID_UI_BEGIN +37)
#define ID_CONF_DETAIL_MENU                      (ID_UI_BEGIN +38)     //查看群组详情////


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
#define WM_CALL_VIDEO_AUDIO                      (WM_CALL_MODULE_BEGIN + 15)
#define WM_CALL_AUDIO_VIDEO                      (WM_CALL_MODULE_BEGIN + 16)
#define WM_CALL_STARTCALL                        (WM_CALL_MODULE_BEGIN + 17)
#define WM_CALL_IPT_SUCESS                       (WM_CALL_MODULE_BEGIN + 18)
#define WM_CALL_IPT_FAILED                       (WM_CALL_MODULE_BEGIN + 19)
#define WM_CALL_BLTRANS_SUCESS                   (WM_CALL_MODULE_BEGIN + 20)
#define WM_CALL_BLTRANS_FAILED                   (WM_CALL_MODULE_BEGIN + 21)
#define WM_CALL_ADD_VIDEO                        (WM_CALL_MODULE_BEGIN + 22)
#define WM_CALL_START_CALL                       (WM_CALL_MODULE_BEGIN + 23)

#define WM_CALL_OPEN_VIDEO                       (WM_CALL_MODULE_BEGIN + 30)
#define WM_CALL_CLOSE_VIDEO                      (WM_CALL_MODULE_BEGIN + 31)
#define WM_CALL_REFUSE_OPEN_VIDEO                (WM_CALL_MODULE_BEGIN + 32)
#define WM_CALL_TRANS_TO_CONF_RESULT             (WM_CALL_MODULE_BEGIN + 33)

//AudioConf Defines
#define WM_CALL_CONF_CREAT                       (WM_CALL_MODULE_BEGIN + 50) 
#define WM_CALL_CONF_CONNECTED                   (WM_CALL_MODULE_BEGIN + 51)
#define WM_CALL_CONF_REFRESH                     (WM_CALL_MODULE_BEGIN + 52)
#define WM_CALL_CONF_COMMING                     (WM_CALL_MODULE_BEGIN + 53)
#define WM_CALL_CONF_END                         (WM_CALL_MODULE_BEGIN + 54)
#define WM_CALL_CONF_CLOSE_DLG                   (WM_CALL_MODULE_BEGIN + 55)

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
#define WM_DATACONF_MODULE_WB_PAGE_IND           (WM_DATACONF_MODULE_BEGIN + 19)
#define WM_DATACONF_MODULE_WB_DRAW_DATA          (WM_DATACONF_MODULE_BEGIN + 20)
#define WM_DATACONF_MODULE_WB_DOC_DEL            (WM_DATACONF_MODULE_BEGIN + 21)
#define WM_DATACONF_MODULE_DS_DRAW_DATA          (WM_DATACONF_MODULE_BEGIN + 22)
#define WM_DATACONF_MODULE_DS_PAGE_IND           (WM_DATACONF_MODULE_BEGIN + 23)
#define WM_DATACONF_MODULE_BIGDATA               (WM_DATACONF_MODULE_BEGIN + 24)
#define WM_DATACONF_MODULE_DS_DOCLOADED          (WM_DATACONF_MODULE_BEGIN + 25)


///Auth_login Defines
#define WM_AUTH_LOGIN_MODULE_BEGIN               (ID_UI_BEGIN + 300)
#define WM_AUTH_LOGIN_MODULE_LOGIN_RESULT        (WM_AUTH_LOGIN_MODULE_BEGIN + 1)
#define WM_AUTH_LOGIN_SAVE_SELF_INFO             (WM_AUTH_LOGIN_MODULE_BEGIN + 2)
#define WM_LOGIN_AUTH_RESULT                     (WM_AUTH_LOGIN_MODULE_BEGIN + 3)

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

//IM Defines for EC6.0
#define WM_IM_BEGIN                              (ID_UI_BEGIN + 500)
#define WM_MENU_SEND_IM                          (WM_IM_BEGIN +1)            //发送即时消息
#define WM_SHOW_DETAIL                           (WM_IM_BEGIN +2)    
#define WM_CLOSE_IM_WND                          (WM_IM_BEGIN +3)            //关闭即时消息dialog
#define WM_RECV_IM                               (WM_IM_BEGIN +4)            //关闭即时消息dialog
#define WM_RECV_INPUTING                         (WM_IM_BEGIN +5)            //关闭即时消息dialog
#define WM_UPDATE_CONTACT                        (WM_IM_BEGIN +6)            
#define WM_MENU_GROUP_CHAT                       (WM_IM_BEGIN +7) 
#define WM_GROUP_NOTIFY                          (WM_IM_BEGIN +8)            //群组通知
#define WM_GROUP_MEM_ADD                         (WM_IM_BEGIN +9)            //新增群组成员///
#define WM_GROUP_MEM_DEL                         (WM_IM_BEGIN +10)           //删除群组成员///
#define WM_CONFIRM_JOINFIXEDGROUP_NOTIFY         (WM_IM_BEGIN +11)           //审批加入固定群申请///
#define WM_DISMISS_FIXEDGROUP_NOTIFY             (WM_IM_BEGIN +12)           //固定群组解散通知
#define WM_FIXGROUP_IDENTIFY_NOTIFY              (WM_IM_BEGIN +13)           //固定群组认证通知
#define WM_FIXGROUP_DELETE_NOTIFY                (WM_IM_BEGIN +14)           //删除群组成员通知
#define WM_GROUP_INVITEDLG_CLOSE                 (WM_IM_BEGIN +15)           //关闭群组通知dialog
#define WM_UPDATE_STATUS                         (WM_IM_BEGIN +16)           //状态变更////
#define WM_FIXGROUP_RECEIVEJOIN_FIEDGROUP        (WM_IM_BEGIN +17)           //管理员收到申请者入群申请/

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

typedef struct tagCall_Member
{
    char name[SERVICE_IM_D_MAX_NAME_LENGTH];                /**< 用户名 */
    char account[SERVICE_IM_D_MAX_ACCOUNT_LENGTH];          /**< 成员账号 */
    char CallNo[SERVICE_IM_D_MAX_PHONE_LENGTH];             /**< 呼叫的号码 */
}CALL_MEMBER;
typedef std::map<std::string, CALL_MEMBER> MAP_SELECT_USER;

/**
*  Sex type
*/
typedef enum tagSERVICE_IM_E_GENDER_TYPE
{
    SERVICE_IM_E_GENDER_MALE = 0,        /**< male */
    SERVICE_IM_E_GENDER_FEMAIL = 1,      /**< female*/
    SERVICE_IM_E_GENDER_UNKNOWN = 2      /**< unknow */
}SERVICE_IM_E_GENDER_TYPE;

/**
*  user info struct
*/
typedef struct tagSERVICE_IM_S_USERINFO
{
    long long   staff_ID;                                            /**< staffID */
    char    account[SERVICE_IM_D_MAX_ACCOUNT_LENGTH];                /**< account */
    char    staff_NO[SERVICE_IM_D_MAX_ACCOUNT_LENGTH];               /**< member number */
    char    name[SERVICE_IM_D_MAX_NAME_LENGTH];                      /**< username */
    char    native_name[SERVICE_IM_D_MAX_NAME_LENGTH];               /**< native name */
    char    qPinYin[SERVICE_IM_D_MAX_NAME_LENGTH];                   /**< [en]Full spelling. [cn]全拼    */
    SERVICE_IM_E_GENDER_TYPE    gender;                              /**< gender */
    char    birthday[SERVICE_IM_D_MAX_BIRTHDAY_LENGTH];              /**< [en]Birthday. [cn]生日 */
    char    age[SERVICE_IM_D_AGE_LENGTH];                            /**< [en]Age. [cn]年龄 */
    char    bind_NO[SERVICE_IM_D_MAX_PHONE_LENGTH];                  /**< bind number */
    char    mobile[SERVICE_IM_D_MAX_PHONE_LENGTH];                   /**< phone number */
    char    home_phone[SERVICE_IM_D_MAX_PHONE_LENGTH];               /**< home phone number */
    char    office_phone[SERVICE_IM_D_MAX_PHONE_LENGTH];             /**< office phone number */
    char    short_phone[SERVICE_IM_D_MAX_PHONE_LENGTH];              /**< short phone number */
    char    other_phone[SERVICE_IM_D_MAX_PHONE_LENGTH];              /**< other phone number */
    char    voip[SERVICE_IM_D_MAX_PHONE_LENGTH];                     /**< VOIP phone number */
    char    ip_phone[SERVICE_IM_D_MAX_PHONE_LENGTH];                 /**< bind IPPhone number */
    char    fax[SERVICE_IM_D_MAX_PHONE_LENGTH];                      /**< [en]Fax. [cn]传真 */
    char    email[SERVICE_IM_D_MAX_DESC_LENGTH];                     /**< email adress */
    char    web_site[SERVICE_IM_D_MAX_DESC_LENGTH];                  /**< [en]Personal website. [cn]个人网站 */
    char    signature[SERVICE_IM_D_MAX_DESC_LENGTH];                 /**< signature */
    char    desc[SERVICE_IM_D_MAX_DESC_LENGTH];                      /**< describition */
    char    address[SERVICE_IM_D_MAX_DESC_LENGTH];                   /**< address */
    char    image_ID[SERVICE_IM_D_MAX_DESC_LENGTH];                  /**< head image ID */
    char    postalcode[SERVICE_IM_D_MAX_DESC_LENGTH];                /**< postalcode */
    unsigned int    is_secrecy;                                      /**< is Secrecy*/
    char    title[SERVICE_IM_D_MAX_DESC_LENGTH];                     /**< title */
    char    dept_ID[SERVICE_IM_D_MAX_DEPTNAME_LENGTH];               /**< department ID */
    char    dept_name_en[SERVICE_IM_D_MAX_NAME_LENGTH];              /**< department english name */
    char    dept_name_cn[SERVICE_IM_D_MAX_NAME_LENGTH];              /**< departmeng chinese name */
    char    image_sync_time[SERVICE_IM_D_MAX_TIMESTAMP_LENGTH];      /**< head image sync time stamp */
    char    old_account[SERVICE_IM_D_MAX_ACCOUNT_LENGTH];            /**< old account */
    char    state[SERVICE_IM_D_MAX_DESC_LENGTH];                     /**< in service state 0：in/1：leave */
    char    modify_time[SERVICE_IM_D_MAX_TIMESTAMP_LENGTH];          /**< last update time */
}SERVICE_IM_S_USERINFO;


///**
//* contacts info
//*  @brief contacter：1.user has owned account;2.no account user
//*  @attention contacts staffID为0，own account user staffID
//*/
typedef struct tagSERVICE_IM_S_CONTACTNFO
{
    long long    id;                                                     /**<friend ID */
    long long    staff_ID;                                               /**< staffID */
    char    name[SERVICE_IM_D_MAX_NAME_LENGTH];                          /**< name */
    char   nick_name[SERVICE_IM_D_MAX_NAME_LENGTH];                      /**< nickname */
    char    foreign_name[SERVICE_IM_D_MAX_NAME_LENGTH];                  /**< Foreign name. */
    char    birthday[SERVICE_IM_D_MAX_BIRTHDAY_LENGTH];                  /**< Birthday.  */
    SERVICE_IM_E_GENDER_TYPE gender;                                     /**< gender */
    char    corp_name[SERVICE_IM_D_MAX_NAME_LENGTH];                     /**< company name */
    char    dept_name[SERVICE_IM_D_MAX_NAME_LENGTH];                     /**< departname */
    char    title[SERVICE_IM_D_MAX_DESC_LENGTH];                         /**< Title. */
    char    mobile[SERVICE_IM_D_MAX_PHONE_LENGTH];                       /**< mobile phone */
    char    office_phone[SERVICE_IM_D_MAX_PHONE_LENGTH];                 /**< office phone */
    char    home_phone[SERVICE_IM_D_MAX_PHONE_LENGTH];                   /**< home phone */
    char    other_phone[SERVICE_IM_D_MAX_PHONE_LENGTH];                  /**< other phone */
    char    fax[SERVICE_IM_D_MAX_PHONE_LENGTH];                          /**< Fax. */
    char    email[SERVICE_IM_D_MAX_DESC_LENGTH];                         /**< email */
    char    webSite[SERVICE_IM_D_MAX_DESC_LENGTH];                       /**< Home page.*/
    char    im_NO[SERVICE_IM_D_MAX_DESC_LENGTH];                         /**< chat tools number */
    char    address[SERVICE_IM_D_MAX_DESC_LENGTH];                       /**< address */
    char    desc[SERVICE_IM_D_MAX_DESC_LENGTH];                          /**< Description. */
    char    postalcode[SERVICE_IM_D_MAX_DESC_LENGTH];                    /**< Postal code. */
    char    state;                                                       /**<Synchronize state(use when incremental synchronize ) */
}SERVICE_IM_S_CONTACTNFO;


//address list
typedef std::multimap<long long, long long> MAP_USER_GROUP;
extern MAP_USER_GROUP g_mapUserGroup;
//typedef std::map<long long, SERVICE_IM_S_CONTACTNFO> MAP_CONTACT;
//extern MAP_CONTACT g_mapContact;
typedef std::map<long long, SERVICE_IM_S_USERINFO> MAP_USER;

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
