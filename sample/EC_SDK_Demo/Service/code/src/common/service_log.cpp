//
//  service_log.cpp
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2017, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#include <stdio.h>
#include <stdlib.h>
#include "service_log.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


#define SERVICE_D_SET_VA_INFO(_log_info, _fmt_log_info)\
{\
    va_list     _arg_info = {0};\
    va_start(_arg_info, (_log_info));\
    (void)_vsnprintf((char *)(_fmt_log_info), 1023,\
                            (char *)(_log_info), _arg_info);\
    va_end(_arg_info);\
}


    const char* g_log_level_description[SERVICE_E_LOG_BUTT] = { "ERROR", "WARN", "INFO", "DEBUG" };



    /**
     * @brief log output adapt
     *
     * @param [in] char *level        Log level.
     * @param [in] char *module       Module name.
     * @param [in] char *function     Function name.
     * @param [in] char *file         File name.
     * @param [in] char *line         Line number.
     * @param [in] char *log_info     Log info string
     * @retval void
     *
     * @attention: Developers can modify the adaptation according to the needs
     **/
    void service_log_print
        (
            SERVICE_E_LOG_LEVEL level,
            const char* module,
            const char* function,
            const char* file,
            unsigned int line,
            const char* log_info,
            ...
            )
    {
        char fmt_log_info[1024] = { 0 };

        /* Internal call, temporarily not determine the validity of the input parameters  */

        if (level >= SERVICE_E_LOG_BUTT)
        {
            return;
        }

        //SERVICE_D_SET_VA_INFO(log_info, fmt_log_info);

        /* Developers can modify adaptation  */
        printf("[%s][%s][%s][%s:%u]:%s",
            g_log_level_description[level], module, function, file, line, fmt_log_info);

        return;
    }



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

