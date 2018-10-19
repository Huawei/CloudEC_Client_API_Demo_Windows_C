//
//  service_log.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//


#ifndef __SERVICE_LOG_H__
#define __SERVICE_LOG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


    static const char *SDK_ADAPT_LOG_PATH = ".\\serviceLog\\";


    typedef enum tagSERVICE_E_LOG_LEVEL
    {
        SERVICE_E_LOG_ERROR = 0,
        SERVICE_E_LOG_WARN,
        SERVICE_E_LOG_INFO,
        SERVICE_E_LOG_DEBUG,
        SERVICE_E_LOG_BUTT
    }SERVICE_E_LOG_LEVEL;



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
            );


#define LOG_D_PRINT(_level, _module, _fmt, ...)\
    {\
        service_log_print(_level, _module, __FUNCTION__, __FILE__, __LINE__, _fmt, ##__VA_ARGS__);\
    }


#define LOG_D_DEBUG(_module, _fmt, ...) LOG_D_PRINT(SERVICE_E_LOG_DEBUG, _module, _fmt, ##__VA_ARGS__)
#define LOG_D_INFO(_module, _fmt, ...)  LOG_D_PRINT(SERVICE_E_LOG_INFO, _module, _fmt, ##__VA_ARGS__)
#define LOG_D_WARN(_module, _fmt, ...)  LOG_D_PRINT(SERVICE_E_LOG_WARN, _module, _fmt, ##__VA_ARGS__)
#define LOG_D_ERROR(_module, _fmt, ...) LOG_D_PRINT(SERVICE_E_LOG_ERROR, _module, _fmt, ##__VA_ARGS__)


#define LOG_D_COMM_DEBUG(_fmt, ...)  LOG_D_DEBUG("COMM", _fmt, ##__VA_ARGS__)
#define LOG_D_COMM_INFO(_fmt, ...)   LOG_D_INFO("COMM", _fmt, ##__VA_ARGS__)
#define LOG_D_COMM_WARN(_fmt, ...)   LOG_D_WARN("COMM", _fmt, ##__VA_ARGS__)
#define LOG_D_COMM_ERROR(_fmt, ...)  LOG_D_ERROR("COMM", _fmt, ##__VA_ARGS__)


#define LOG_D_AUTH_LOGIN_DEBUG(_fmt, ...)  LOG_D_DEBUG("AUTH_LOGIN", _fmt, ##__VA_ARGS__)
#define LOG_D_AUTH_LOGIN_INFO(_fmt, ...)   LOG_D_INFO("AUTH_LOGIN", _fmt, ##__VA_ARGS__)
#define LOG_D_AUTH_LOGIN_WARN(_fmt, ...)   LOG_D_WARN("AUTH_LOGIN", _fmt, ##__VA_ARGS__)
#define LOG_D_AUTH_LOGIN_ERROR(_fmt, ...)  LOG_D_ERROR("AUTH_LOGIN", _fmt, ##__VA_ARGS__)


#define LOG_D_CALL_DEBUG(_fmt, ...)  LOG_D_DEBUG("CALL", _fmt, ##__VA_ARGS__)
#define LOG_D_CALL_INFO(_fmt, ...)   LOG_D_INFO("CALL", _fmt, ##__VA_ARGS__)
#define LOG_D_CALL_WARN(_fmt, ...)   LOG_D_WARN("CALL", _fmt, ##__VA_ARGS__)
#define LOG_D_CALL_ERROR(_fmt, ...)  LOG_D_ERROR("CALL", _fmt, ##__VA_ARGS__)


#define LOG_D_IM_DEBUG(_fmt, ...)  LOG_D_DEBUG("IM", _fmt, ##__VA_ARGS__)
#define LOG_D_IM_INFO(_fmt, ...)   LOG_D_INFO("IM", _fmt, ##__VA_ARGS__)
#define LOG_D_IM_WARN(_fmt, ...)   LOG_D_WARN("IM", _fmt, ##__VA_ARGS__)
#define LOG_D_IM_ERROR(_fmt, ...)  LOG_D_ERROR("IM", _fmt, ##__VA_ARGS__)


#define LOG_D_VOICE_CONF_DEBUG(_fmt, ...)  LOG_D_DEBUG("VOICE_CONF", _fmt, ##__VA_ARGS__)
#define LOG_D_VOICE_CONF_INFO(_fmt, ...)   LOG_D_INFO("VOICE_CONF", _fmt, ##__VA_ARGS__)
#define LOG_D_VOICE_CONF_WARN(_fmt, ...)   LOG_D_WARN("VOICE_CONF", _fmt, ##__VA_ARGS__)
#define LOG_D_VOICE_CONF_ERROR(_fmt, ...)  LOG_D_ERROR("VOICE_CONF", _fmt, ##__VA_ARGS__)


#define LOG_D_DATA_CONF_DEBUG(_fmt, ...)  LOG_D_DEBUG("DATA_CONF", _fmt, ##__VA_ARGS__)
#define LOG_D_DATA_CONF_INFO(_fmt, ...)   LOG_D_INFO("DATA_CONF", _fmt, ##__VA_ARGS__)
#define LOG_D_DATA_CONF_WARN(_fmt, ...)   LOG_D_WARN("DATA_CONF", _fmt, ##__VA_ARGS__)
#define LOG_D_DATA_CONF_ERROR(_fmt, ...)  LOG_D_ERROR("DATA_CONF", _fmt, ##__VA_ARGS__)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SERVICE_LOG_H__ */
