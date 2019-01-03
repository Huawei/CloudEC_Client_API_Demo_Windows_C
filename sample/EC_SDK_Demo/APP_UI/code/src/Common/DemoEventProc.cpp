//
//  DemoEventProc.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include "stdafx.h"
#include <string>
#include "DemoEventProc.h"
#include "DemoApp.h"
#include "DemoMainDlg.h"
#include "DemoLoginDlg.h"
#include "DemoCallCtrlDlg.h"
#include "DemoCallInCommingDlg.h"
#include "DemoShare.h"
#include "DemoData.h"
#include "DemoCallDlgManager.h"
#include "service_tools.h"
#include "service_os_adapt.h"

NotifyCallBack::NotifyCallBack(void)
{
}

NotifyCallBack::~NotifyCallBack(void)
{
}

void NotifyCallBack::loginMsgNotify(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data)
{
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return;
    }
    CDemoLoginDlg* logindlg = (CDemoLoginDlg*)(app->m_pLoginDlgWnd);
    CHECK_POINTER(logindlg);

    switch (msg_id)
    {
    case TSDK_E_LOGIN_EVT_AUTH_FAILED:
    {
        ::PostMessage(logindlg->GetSafeHwnd(), WM_LOGIN_AUTH_RESULT, NULL, NULL);
        break;
    }
    case TSDK_E_LOGIN_EVT_LOGIN_SUCCESS:
    {
        ::PostMessage(logindlg->GetSafeHwnd(), WM_LOGIN_RESULT, (WPARAM)TRUE, NULL);
        break;
    }
    case TSDK_E_LOGIN_EVT_LOGIN_FAILED:
    {
        ::PostMessage(logindlg->GetSafeHwnd(), WM_LOGIN_RESULT, (WPARAM)FALSE, NULL);
        break;
    }
    case TSDK_E_LOGIN_EVT_AUTH_REFRESH_FAILED:
    {
        ::PostMessage(logindlg->GetSafeHwnd(), WM_LOGIN_TOKEN_REFRESH_FAILED, NULL, NULL);
        break;
    }
    case TSDK_E_LOGIN_EVT_LOGOUT_SUCCESS:
    {
        CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
        CHECK_POINTER(maindlg);
        ::PostMessage(maindlg->GetSafeHwnd(), WM_LOGOUT_RESULT, NULL, NULL);
        break;
    }
    case TSDK_E_LOGIN_EVT_FORCE_LOGOUT:
    {
        CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
        CHECK_POINTER(maindlg);
        ::PostMessage(maindlg->GetSafeHwnd(), WM_FORCE_LOGOUT, NULL, NULL);
        break;
    }
    case TSDK_E_LOGIN_EVT_VOIP_ACCOUNT_STATUS:
    {
        CHECK_POINTER(data);
        TSDK_S_VOIP_ACCOUNT_INFO* selfInfo = (TSDK_S_VOIP_ACCOUNT_INFO*)data;
        TSDK_S_VOIP_ACCOUNT_INFO* notifyInfo = new TSDK_S_VOIP_ACCOUNT_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_VOIP_ACCOUNT_INFO), 0, sizeof(TSDK_S_VOIP_ACCOUNT_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_VOIP_ACCOUNT_INFO), selfInfo, sizeof(TSDK_S_VOIP_ACCOUNT_INFO));
        ::PostMessage(logindlg->GetSafeHwnd(), WM_AUTH_LOGIN_SAVE_SELF_INFO, (WPARAM)notifyInfo, NULL);
        break;
    }
    case TSDK_E_LOGIN_EVT_GET_TEMP_USER_RESULT:
    {
        CHECK_POINTER(data);
        TSDK_CHAR* notifyInfo = (TSDK_CHAR*)data;
        ::PostMessage(logindlg->GetSafeHwnd(), WM_LOGIN_GET_TEMP_USER_RESULT, (WPARAM)notifyInfo, NULL);
        break;
    }
    default:
        break;
    }
}


void NotifyCallBack::callMsgNotify(unsigned int msg_id, unsigned int param1, unsigned int param2, void* data)
{
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return;
    }

    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER(maindlg);

    switch (msg_id)
    {
    case TSDK_E_CALL_EVT_CALL_INCOMING:
    {
        CHECK_POINTER(data);
        TSDK_S_CALL_INFO* callInfo = (TSDK_S_CALL_INFO*)data;
        TSDK_S_CALL_INFO* notifyInfo = new TSDK_S_CALL_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), 0, sizeof(TSDK_S_CALL_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), callInfo, sizeof(TSDK_S_CALL_INFO));

        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_INCOMMING, (WPARAM)notifyInfo, NULL);
        break;
    }
    case TSDK_E_CALL_EVT_CALL_OUTGOING:
    {
        CHECK_POINTER(data);
        TSDK_S_CALL_INFO* callInfo = (TSDK_S_CALL_INFO*)data;
        TSDK_S_CALL_INFO* notifyInfo = new TSDK_S_CALL_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), 0, sizeof(TSDK_S_CALL_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), callInfo, sizeof(TSDK_S_CALL_INFO));

        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_STARTCALL, WPARAM(notifyInfo), NULL);
        break;
    }
    case TSDK_E_CALL_EVT_CALL_CONNECTED:
    {
        CHECK_POINTER(data);
        TSDK_S_CALL_INFO* callInfo = (TSDK_S_CALL_INFO*)data;
        TSDK_S_CALL_INFO* notifyInfo = new TSDK_S_CALL_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), 0, sizeof(TSDK_S_CALL_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), callInfo, sizeof(TSDK_S_CALL_INFO));

        CDemoCallCtrlDlg* pCallDlg;
        pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(notifyInfo->call_id);
        CHECK_POINTER(pCallDlg);
        ::PostMessage(pCallDlg->GetSafeHwnd(), WM_CALL_CONNECTED, (WPARAM)notifyInfo, NULL);
        break;
    }
    case TSDK_E_CALL_EVT_CALL_ENDED:
    /*case TSDK_E_CALL_EVT_CALL_DESTROY:*/
    {
        CHECK_POINTER(data);
        TSDK_S_CALL_INFO* callInfo = (TSDK_S_CALL_INFO*)data;
        TSDK_S_CALL_INFO* notifyInfo = new TSDK_S_CALL_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), 0, sizeof(TSDK_S_CALL_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), callInfo, sizeof(TSDK_S_CALL_INFO));

        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_END, (WPARAM)notifyInfo, NULL);
        break;
    }
    case TSDK_E_CALL_EVT_OPEN_VIDEO_REQ:
    {
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_ADD_VIDEO, (WPARAM)param1, NULL);
        break;
    }
    case TSDK_E_CALL_EVT_OPEN_VIDEO_IND:
    {
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_OPEN_VIDEO, (WPARAM)param1, NULL);
        break;
    }
    case TSDK_E_CALL_EVT_CLOSE_VIDEO_IND:
    {
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_CLOSE_VIDEO, (WPARAM)param1, NULL);
        break;
    }
    case TSDK_E_CALL_EVT_REFUSE_OPEN_VIDEO_IND:
    {
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_REFUSE_OPEN_VIDEO, (WPARAM)param1, NULL);
        break;
    }
    case TSDK_E_CALL_EVT_HOLD_SUCCESS:
    {
        CHECK_POINTER(data);
        TSDK_S_CALL_INFO* callInfo = (TSDK_S_CALL_INFO*)data;
        TSDK_S_CALL_INFO* notifyInfo = new TSDK_S_CALL_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), 0, sizeof(TSDK_S_CALL_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), callInfo, sizeof(TSDK_S_CALL_INFO));

        CDemoCallCtrlDlg* pCallDlg;
        pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(notifyInfo->call_id);
        CHECK_POINTER(pCallDlg);
        ::PostMessage(pCallDlg->GetSafeHwnd(), WM_CALL_HOLD_SUCESS, NULL, NULL);
        break;
    }
    case TSDK_E_CALL_EVT_UNHOLD_SUCCESS:
    {
        CHECK_POINTER(data);
        TSDK_S_CALL_INFO* callInfo = (TSDK_S_CALL_INFO*)data;
        TSDK_S_CALL_INFO* notifyInfo = new TSDK_S_CALL_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), 0, sizeof(TSDK_S_CALL_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CALL_INFO), callInfo, sizeof(TSDK_S_CALL_INFO));

        CDemoCallCtrlDlg* pCallDlg;
        pCallDlg = CallDlgManager::GetInstance().GetCallDlgByCallID(notifyInfo->call_id);
        CHECK_POINTER(pCallDlg);
        ::PostMessage(pCallDlg->GetSafeHwnd(), WM_CALL_UNHOLD_SUCESS, NULL, NULL);
        break;
    }
    default:
        break;
    }
}


void NotifyCallBack::confMsgNotify(unsigned int msg_id, unsigned int param1, unsigned int param2, void* data)
{
    CDemoApp* app = (CDemoApp*)AfxGetApp();
    if (!app)
    {
        //窗口已经关闭
        return;
    }

    CDemoMainDlg* maindlg = (CDemoMainDlg*)(app->m_pMainDlgWnd);
    CHECK_POINTER(maindlg);

    switch (msg_id)
    {
    case TSDK_E_CONF_EVT_BOOK_CONF_RESULT:
    {
        if (TSDK_SUCCESS == param1)
        {
            CTools::ShowMessageTimeout(_T("Book conference success."),2000);
        }
        else
        {
            CTools::ShowMessageTimeout(_T("Book conference failed."), 2000);
        }
        break;
    }
    case TSDK_E_CONF_EVT_QUERY_CONF_LIST_RESULT:
    {
        if (TSDK_SUCCESS == param1)
        {
            CHECK_POINTER(data);
            TSDK_S_CONF_LIST_INFO* pResult = (TSDK_S_CONF_LIST_INFO*)data;
            TSDK_UINT32 currentConfNum = pResult->current_count;
            if (currentConfNum > 0)
            {
                TSDK_S_CONF_BASE_INFO* notifyInfo = new TSDK_S_CONF_BASE_INFO[currentConfNum];
                service_memset_s(notifyInfo, sizeof(TSDK_S_CONF_BASE_INFO)*currentConfNum, 0, sizeof(TSDK_S_CONF_BASE_INFO)*currentConfNum);
                for (unsigned int i = 0; i < currentConfNum; i++)
                {
                    notifyInfo[i].size = pResult->conf_info_list[i].size;
                    strncpy_s(notifyInfo[i].conf_id, TSDK_D_MAX_CONF_ID_LEN + 1, pResult->conf_info_list[i].conf_id, _TRUNCATE);
                    strncpy_s(notifyInfo[i].subject, TSDK_D_MAX_SUBJECT_LEN + 1, pResult->conf_info_list[i].subject, _TRUNCATE);
                    strncpy_s(notifyInfo[i].access_number, TSDK_D_MAX_CONF_ACCESS_LEN + 1, pResult->conf_info_list[i].access_number, _TRUNCATE);
                    strncpy_s(notifyInfo[i].chairman_pwd, TSDK_D_MAX_CONF_PASSWORD_LEN + 1, pResult->conf_info_list[i].chairman_pwd, _TRUNCATE);
                    strncpy_s(notifyInfo[i].guest_pwd, TSDK_D_MAX_CONF_PASSWORD_LEN + 1, pResult->conf_info_list[i].guest_pwd, _TRUNCATE);
                    strncpy_s(notifyInfo[i].start_time, TSDK_D_MAX_TIME_FORMATE_LEN + 1, pResult->conf_info_list[i].start_time, _TRUNCATE);
                    strncpy_s(notifyInfo[i].end_time, TSDK_D_MAX_TIME_FORMATE_LEN + 1, pResult->conf_info_list[i].end_time, _TRUNCATE);
                    notifyInfo[i].conf_media_type = pResult->conf_info_list[i].conf_media_type;
                    notifyInfo[i].conf_state = (TSDK_E_CONF_STATE)pResult->conf_info_list[i].conf_state;
                    strncpy_s(notifyInfo[i].scheduser_account, TSDK_D_MAX_ACCOUNT_LEN + 1, pResult->conf_info_list[i].scheduser_account, _TRUNCATE);
                    strncpy_s(notifyInfo[i].scheduser_name, TSDK_D_MAX_DISPLAY_NAME_LEN + 1, pResult->conf_info_list[i].scheduser_name, _TRUNCATE);
                }

                CDemoMeetingDlg* mettingDlg = maindlg->GetDemoMeetingDlg();
                CHECK_POINTER(mettingDlg);
                ::PostMessage(mettingDlg->GetSafeHwnd(), WM_CONF_CTRL_GET_CONF_LIST_RESULT, (WPARAM)notifyInfo, (LPARAM)currentConfNum);
            }
        }
        else
        {
            maindlg->MessageBox(_T("get conf list failed!"));
        }

        break;
    }
    case TSDK_E_CONF_EVT_JOIN_CONF_RESULT:
    {
        if (TSDK_SUCCESS == param2)
        {
            CHECK_POINTER(data);
            TSDK_S_JOIN_CONF_IND_INFO* pResult = (TSDK_S_JOIN_CONF_IND_INFO*)data;
            TSDK_S_JOIN_CONF_IND_INFO* notifyInfo = new TSDK_S_JOIN_CONF_IND_INFO;
            service_memset_s(notifyInfo, sizeof(TSDK_S_JOIN_CONF_IND_INFO), 0, sizeof(TSDK_S_JOIN_CONF_IND_INFO));
            memcpy_s(notifyInfo, sizeof(TSDK_S_JOIN_CONF_IND_INFO), pResult, sizeof(TSDK_S_JOIN_CONF_IND_INFO));
            ::PostMessage(maindlg->GetSafeHwnd(), WM_CONF_CTRL_JOIN_RESULT, (WPARAM)notifyInfo, (LPARAM)param1);
        }
        else
        {
            maindlg->MessageBox(_T("join conf failed!"));
        }
        break;
    }
    case TSDK_E_CONF_EVT_INFO_AND_STATUS_UPDATE:
    {
        CHECK_POINTER(data);
        TSDK_S_CONF_STATUS_INFO* pResult = (TSDK_S_CONF_STATUS_INFO*)data;
        TSDK_S_CONF_STATUS_INFO* notifyInfo = new TSDK_S_CONF_STATUS_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CONF_STATUS_INFO), 0, sizeof(TSDK_S_CONF_STATUS_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CONF_STATUS_INFO), pResult, sizeof(TSDK_S_CONF_STATUS_INFO));

        unsigned int attendeenumber = pResult->attendee_num;
        if (0 == attendeenumber)
        {
            return;
        }
        notifyInfo->attendee_list = NULL;
        notifyInfo->attendee_list = (TSDK_S_ATTENDEE*)malloc(attendeenumber*sizeof(TSDK_S_ATTENDEE));
        if (NULL == notifyInfo->attendee_list)
        {
            return;
        }
        (void)service_memset_s(notifyInfo->attendee_list, attendeenumber*sizeof(TSDK_S_ATTENDEE), 0, attendeenumber*sizeof(TSDK_S_ATTENDEE));
        TSDK_S_ATTENDEE* pTempAttendee = notifyInfo->attendee_list;
        for (unsigned int i = 0; i < attendeenumber; i++)
        {
            if (pTempAttendee)
            {
                (void)strncpy_s(pTempAttendee->status_info.participant_id, TSDK_D_MAX_PARTICIPANTID_LEN + 1, pResult->attendee_list[i].status_info.participant_id, _TRUNCATE);
                (void)strncpy_s(pTempAttendee->base_info.number, TSDK_D_MAX_NUMBER_LEN + 1, pResult->attendee_list[i].base_info.number, _TRUNCATE);
                (void)strncpy_s(pTempAttendee->base_info.display_name, TSDK_D_MAX_DISPLAY_NAME_LEN + 1, pResult->attendee_list[i].base_info.display_name, _TRUNCATE);
                (void)strncpy_s(pTempAttendee->base_info.account_id, TSDK_D_MAX_ACCOUNT_LEN + 1, pResult->attendee_list[i].base_info.account_id, _TRUNCATE);
                (void)strncpy_s(pTempAttendee->base_info.email, TSDK_D_MAX_EMAIL_LEN + 1, pResult->attendee_list[i].base_info.email, _TRUNCATE);
                (void)strncpy_s(pTempAttendee->base_info.sms, TSDK_D_MAX_NUMBER_LEN + 1, pResult->attendee_list[i].base_info.sms, _TRUNCATE);

                pTempAttendee->base_info.role = (TSDK_E_CONF_ROLE)pResult->attendee_list[i].base_info.role;
                pTempAttendee->status_info.data_user_id = pResult->attendee_list[i].status_info.data_user_id;
                pTempAttendee->status_info.has_camera = pResult->attendee_list[i].status_info.has_camera;
                pTempAttendee->status_info.is_broadcast = pResult->attendee_list[i].status_info.is_broadcast;
                pTempAttendee->status_info.is_handup = pResult->attendee_list[i].status_info.is_handup;
                pTempAttendee->status_info.is_join_dataconf = pResult->attendee_list[i].status_info.is_join_dataconf;
                pTempAttendee->status_info.is_mute = pResult->attendee_list[i].status_info.is_mute;
                pTempAttendee->status_info.is_only_in_data_conf = pResult->attendee_list[i].status_info.is_only_in_data_conf;
                pTempAttendee->status_info.is_present = pResult->attendee_list[i].status_info.is_present;
                pTempAttendee->status_info.is_self = pResult->attendee_list[i].status_info.is_self;
                pTempAttendee->status_info.state = (TSDK_E_CONF_PARTICIPANT_STATUS)pResult->attendee_list[i].status_info.state;
            }
            else
            {
                break;
            }
            pTempAttendee++;
        }

        CDemoAudioMeetingDlg* pAudioMettingDlg = maindlg->GetDemoAudioMeetingDlg();
        CHECK_POINTER(pAudioMettingDlg);
        ::PostMessage(pAudioMettingDlg->GetSafeHwnd(), WM_CONF_CTRL_INFO_AND_STATUS_UPDATE, (WPARAM)notifyInfo, (LPARAM)param1);

        break;
    }
    case TSDK_E_CONF_EVT_SPEAKER_IND:
    {
        CHECK_POINTER(data);
        TSDK_S_CONF_SPEAKER_INFO* pResult = (TSDK_S_CONF_SPEAKER_INFO*)data;
        TSDK_S_CONF_SPEAKER_INFO* notifyInfo = new TSDK_S_CONF_SPEAKER_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CONF_SPEAKER_INFO), 0, sizeof(TSDK_S_CONF_SPEAKER_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CONF_SPEAKER_INFO), pResult, sizeof(TSDK_S_CONF_SPEAKER_INFO));

        CDemoAudioMeetingDlg* pAudioMettingDlg = maindlg->GetDemoAudioMeetingDlg();
        CHECK_POINTER(pAudioMettingDlg);
        ::PostMessage(pAudioMettingDlg->GetSafeHwnd(), WM_CONF_CTRL_ADDRESSER_UPDATE_IND, (WPARAM)notifyInfo, NULL);

        break;
    }
    case TSDK_E_CONF_EVT_QUERY_CONF_DETAIL_RESULT:
    {
        if (TSDK_SUCCESS == param1)
        {
            CHECK_POINTER(data);
            TSDK_S_CONF_DETAIL_INFO* pResult = (TSDK_S_CONF_DETAIL_INFO*)data;
            TSDK_S_CONF_DETAIL_INFO* notifyInfo = new TSDK_S_CONF_DETAIL_INFO;
            service_memset_s(notifyInfo, sizeof(TSDK_S_CONF_DETAIL_INFO), 0, sizeof(TSDK_S_CONF_DETAIL_INFO));
            memcpy_s(notifyInfo, sizeof(TSDK_S_CONF_DETAIL_INFO), pResult, sizeof(TSDK_S_CONF_DETAIL_INFO));
            CDemoMeetingDlg* mettingDlg = maindlg->GetDemoMeetingDlg();
            CHECK_POINTER(mettingDlg);
            ::PostMessage(mettingDlg->GetSafeHwnd(), WM_CONF_CTRL_GET_CONF_INFO_RESULT, (WPARAM)notifyInfo, NULL);
        }
        else
        {
            maindlg->MessageBox(_T("get conf detail failed!"));
        }
        break;
    }
    case TSDK_E_CONF_EVT_CONFCTRL_OPERATION_RESULT:
    {
        CHECK_POINTER(data);
        TSDK_S_CONF_OPERATION_RESULT* pResult = (TSDK_S_CONF_OPERATION_RESULT*)data;
        TSDK_S_CONF_OPERATION_RESULT* notifyInfo = new TSDK_S_CONF_OPERATION_RESULT;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CONF_OPERATION_RESULT), 0, sizeof(TSDK_S_CONF_OPERATION_RESULT));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CONF_OPERATION_RESULT), pResult, sizeof(TSDK_S_CONF_OPERATION_RESULT));

        CDemoAudioMeetingDlg* pAudioMettingDlg = maindlg->GetDemoAudioMeetingDlg();
        CHECK_POINTER(pAudioMettingDlg);
        ::PostMessage(pAudioMettingDlg->GetSafeHwnd(), WM_CONF_CTRL_OPERATION_RESULT, (WPARAM)notifyInfo, NULL);

        break;
    }
    case TSDK_E_CONF_EVT_CONF_END_IND:
    {
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_CONF_CLOSE_DLG, NULL, NULL);
        break;
    }
    case TSDK_E_CONF_EVT_CONF_INCOMING_IND:
    {
        CHECK_POINTER(data);
        TSDK_S_CONF_INCOMING_INFO* pResult = (TSDK_S_CONF_INCOMING_INFO*)data;
        TSDK_S_CONF_INCOMING_INFO* notifyInfo = new TSDK_S_CONF_INCOMING_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CONF_INCOMING_INFO), 0, sizeof(TSDK_S_CONF_INCOMING_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CONF_INCOMING_INFO), pResult, sizeof(TSDK_S_CONF_INCOMING_INFO));
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CONF_CTRL_CONF_COMMING, (WPARAM)notifyInfo, (LPARAM)param1);
        break;
    }
    case TSDK_E_CONF_EVT_GET_DATACONF_PARAM_RESULT:
    {
        if (TSDK_SUCCESS != param2)
        {
            maindlg->MessageBox(_T("get data conf param failed!"));
        }
        else
        {
            ::PostMessage(maindlg->GetSafeHwnd(), WM_CONF_CTRL_GET_DATA_CONF_PARAM, (WPARAM)param1, NULL);
        }
        break;
    }
    case TSDK_E_CONF_EVT_JOIN_DATA_CONF_RESULT:
    {
        ::PostMessage(maindlg->GetSafeHwnd(), WM_CONF_CTRL_JOIN_DATACONF_RESULT, (WPARAM)param1, (LPARAM)param2);
        break;
    }
    case TSDK_E_CONF_EVT_AS_OWNER_CHANGE:
    {
        CHECK_POINTER(data);
        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_SHARING_SESSION, (WPARAM)param2, (LPARAM)data);
        break;
    }
    case TSDK_E_CONF_EVT_AS_STATE_CHANGE:
    {
        CHECK_POINTER(data);
        TSDK_S_CONF_AS_STATE_INFO* pResult = (TSDK_S_CONF_AS_STATE_INFO*)data;
        TSDK_S_CONF_AS_STATE_INFO* notifyInfo = new TSDK_S_CONF_AS_STATE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_CONF_AS_STATE_INFO), 0, sizeof(TSDK_S_CONF_AS_STATE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_CONF_AS_STATE_INFO), pResult, sizeof(TSDK_S_CONF_AS_STATE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_SHARING_STATE, (WPARAM)notifyInfo, (LPARAM)param2);
        break;
    }
    case TSDK_E_CONF_EVT_AS_SCREEN_DATA_UPDATE:
    {
        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_SCREEN_DATA, NULL, NULL);
        break;
    }
    case TSDK_E_CONF_EVT_PRESENTER_GIVE_IND:
    {
        ::PostMessage(maindlg->GetSafeHwnd(), WM_DATACONF_MODULE_PRESENTERCHG, NULL, NULL);
        break;
    }
    case TSDK_E_CONF_EVT_TRANS_TO_CONF_RESULT:
    {
		::PostMessage(maindlg->GetSafeHwnd(), WM_CALL_TRANS_TO_CONF_RESULT, NULL, (LPARAM)param2);
		break;
    }
	case TSDK_E_CONF_EVT_DS_DOC_LOAD_START:
	{
        CHECK_POINTER(data);
        TSDK_S_DOC_BASE_INFO* pResult = (TSDK_S_DOC_BASE_INFO*)data;
        TSDK_S_DOC_BASE_INFO* notifyInfo = new TSDK_S_DOC_BASE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_BASE_INFO), 0, sizeof(TSDK_S_DOC_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_BASE_INFO), pResult, sizeof(TSDK_S_DOC_BASE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_NEW,(WPARAM)notifyInfo,(LPARAM)param2);
		break;
	}
    case TSDK_E_CONF_EVT_DS_DOC_PAGE_LOADED:
    {
        CHECK_POINTER(data);
        TSDK_S_DOC_PAGE_BASE_INFO* pResult = (TSDK_S_DOC_PAGE_BASE_INFO*)data;
        TSDK_S_DOC_PAGE_BASE_INFO* notifyInfo = new TSDK_S_DOC_PAGE_BASE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), pResult, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_PAGE_LOADED, (WPARAM)notifyInfo, NULL);
        break;
    }
	case TSDK_E_CONF_EVT_DS_DOC_LOAD_FINISH:
	{
        CHECK_POINTER(data);
        TSDK_S_DOC_BASE_INFO* pResult = (TSDK_S_DOC_BASE_INFO*)data;
        TSDK_S_DOC_BASE_INFO* notifyInfo = new TSDK_S_DOC_BASE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_BASE_INFO), 0, sizeof(TSDK_S_DOC_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_BASE_INFO), pResult, sizeof(TSDK_S_DOC_BASE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_DOCLOADED, (WPARAM)notifyInfo, (LPARAM)param2);
		break;
	}
	case TSDK_E_CONF_EVT_DS_DOC_DRAW_DATA_NOTIFY:
    {
        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_DRAW_DATA,NULL,NULL);
		break;
	}
	case TSDK_E_CONF_EVT_DS_DOC_CURRENT_PAGE_IND:
	{
        CHECK_POINTER(data);
        TSDK_S_DOC_PAGE_BASE_INFO* pResult = (TSDK_S_DOC_PAGE_BASE_INFO*)data;
        TSDK_S_DOC_PAGE_BASE_INFO* notifyInfo = new TSDK_S_DOC_PAGE_BASE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), pResult, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
         
        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_PAGE_IND,(WPARAM)notifyInfo,NULL);
		break;
	}
    case TSDK_E_CONF_EVT_DS_DOC_DEL:
    {
        CHECK_POINTER(data);
        TSDK_S_DOC_SHARE_DEL_DOC_INFO* pResult = (TSDK_S_DOC_SHARE_DEL_DOC_INFO*)data;
        TSDK_S_DOC_SHARE_DEL_DOC_INFO* notifyInfo = new TSDK_S_DOC_SHARE_DEL_DOC_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_SHARE_DEL_DOC_INFO), 0, sizeof(TSDK_S_DOC_SHARE_DEL_DOC_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_SHARE_DEL_DOC_INFO), pResult, sizeof(TSDK_S_DOC_SHARE_DEL_DOC_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_DS_DELETE,(WPARAM)notifyInfo,(LPARAM)param2);
        break;
    }
    case TSDK_E_CONF_EVT_WB_DOC_NEW:
    {
        CHECK_POINTER(data);
        TSDK_S_DOC_BASE_INFO* pResult = (TSDK_S_DOC_BASE_INFO*)data;
        TSDK_S_DOC_BASE_INFO* notifyInfo = new TSDK_S_DOC_BASE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_BASE_INFO), 0, sizeof(TSDK_S_DOC_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_BASE_INFO), pResult, sizeof(TSDK_S_DOC_BASE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_DOC_NEW, (WPARAM)notifyInfo, (LPARAM)param2);
        break;
    }
    case TSDK_E_CONF_EVT_WB_DOC_CURRENT_PAGE:
    {
        CHECK_POINTER(data);
        TSDK_S_DOC_PAGE_BASE_INFO* pResult = (TSDK_S_DOC_PAGE_BASE_INFO*)data;
        TSDK_S_DOC_PAGE_BASE_INFO* notifyInfo = new TSDK_S_DOC_PAGE_BASE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), pResult, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_CURRENT_PAGE, (WPARAM)notifyInfo, (LPARAM)param2);
        break;
    }
    case TSDK_E_CONF_EVT_WB_DOC_CURRENT_PAGE_IND:
    {
        CHECK_POINTER(data);
        TSDK_S_DOC_PAGE_BASE_INFO* pResult = (TSDK_S_DOC_PAGE_BASE_INFO*)data;
        TSDK_S_DOC_PAGE_BASE_INFO* notifyInfo = new TSDK_S_DOC_PAGE_BASE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), pResult, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_CURRENT_PAGE_IND, (WPARAM)notifyInfo, (LPARAM)param2);
        break;
    }
    case TSDK_E_CONF_EVT_WB_PAGE_NEW:
    {
        CHECK_POINTER(data);
        TSDK_S_DOC_PAGE_BASE_INFO* pResult = (TSDK_S_DOC_PAGE_BASE_INFO*)data;
        TSDK_S_DOC_PAGE_BASE_INFO* notifyInfo = new TSDK_S_DOC_PAGE_BASE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), pResult, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_PAG_NEW, (WPARAM)notifyInfo, (LPARAM)param2);
        break;
    }
    case TSDK_E_CONF_EVT_WB_DOC_DRAW_DATA_NOTIFY:
    {
        CHECK_POINTER(data);
        TSDK_S_DOC_PAGE_BASE_INFO* pResult = (TSDK_S_DOC_PAGE_BASE_INFO*)data;
        TSDK_S_DOC_PAGE_BASE_INFO* notifyInfo = new TSDK_S_DOC_PAGE_BASE_INFO;
        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), pResult, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_DRAW_DATA, (WPARAM)notifyInfo, (LPARAM)param2);
        break;
    }
    case TSDK_E_CONF_EVT_WB_DOC_DEL:
    {
        CHECK_POINTER(data);
        TSDK_S_WB_DEL_DOC_INFO* pResult = (TSDK_S_WB_DEL_DOC_INFO*)data;
        TSDK_S_WB_DEL_DOC_INFO* notifyInfo = new TSDK_S_WB_DEL_DOC_INFO;

        service_memset_s(notifyInfo, sizeof(TSDK_S_WB_DEL_DOC_INFO), 0, sizeof(TSDK_S_WB_DEL_DOC_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_WB_DEL_DOC_INFO), pResult, sizeof(TSDK_S_WB_DEL_DOC_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), WM_DATACONF_MODULE_WB_DOC_DEL, (WPARAM)notifyInfo, (LPARAM)param2);
        break;
    }
    /*case TSDK_E_CONF_EVT_WB_PAGE_DEL:
    {
        CHECK_POINTER(data);
        TSDK_S_DOC_PAGE_BASE_INFO* pResult = (TSDK_S_DOC_PAGE_BASE_INFO*)data;
        TSDK_S_DOC_PAGE_BASE_INFO* notifyInfo = new TSDK_S_DOC_PAGE_BASE_INFO;

        service_memset_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), 0, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));
        memcpy_s(notifyInfo, sizeof(TSDK_S_DOC_PAGE_BASE_INFO), pResult, sizeof(TSDK_S_DOC_PAGE_BASE_INFO));

        CDemoDataconfCtrlDlg* pDataConfCtrlDlg = maindlg->GetDataConfCtrlDlg();
        CHECK_POINTER(pDataConfCtrlDlg);
        ::PostMessage(pDataConfCtrlDlg->GetSafeHwnd(), , (WPARAM)notifyInfo, (LPARAM)param2);
        break;
    }*/
    default:
        break;
    }
}
