//
//  service_def.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef __SERVICE_DEF_H__
#define __SERVICE_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef NULL
#define NULL (0)
#endif


    /**
     * @brief authentication and login component callback.
     *
     * @param [in] unsigned int evt         Msg id.
     * @param [in] unsigned int param1      Param1.
     * @param [in] unsigned int param2      Param2.
     * @param [in] void*  data				Data.
     * @retval void
     *
     * @attention: NA
     **/
    typedef void(*SERVICE_FN_CALLBACK_PTR)(unsigned int msg_id, unsigned int param1, unsigned int param2, void*  data);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
