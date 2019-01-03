//
//  service_conf_def.h
//  EC_SDK_DEMO
//
//  Created by EC Open support team.
//  Copyright(C), 2018, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
//

#ifndef __SERVICE_CONF_DEF_H__
#define __SERVICE_CONF_DEF_H__

#include "tsdk_conference_def.h"
#include "tsdk_manager_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


    /**
    * [en]This struct is used to describe book conf info.
    * [cn]预约会议信息
    */
    typedef struct tagSERVICE_S_BOOK_CONF_INFO
    {
        TSDK_CHAR subject[TSDK_D_MAX_SUBJECT_LEN + 1];                   /**< [en]Indicates conference subject  ,this param is optional.
                                                                              [cn]会议主题 */
        TSDK_CHAR start_time[TSDK_D_MAX_TIME_FORMATE_LEN + 1];           /**< [en]Indicates conference start time, format:YYYY-MM-DD HH:MM  ,this param is optional.
                                                                              [cn]可选，会议开始时间，格式：YYYY-MM-DD HH:MM，立即会议时无需填写 */
        TSDK_E_CONF_TYPE conf_type;                                      /**< [en]Indicates conference type.
                                                                              [cn]会议类型 */
        TSDK_E_CONF_MEDIA_TYPE conf_media_type;                          /**< [en]Indicates conference media type.
                                                                              [cn]媒体类型 */
        TSDK_UINT32 attendee_num;                                        /**< [en]Indicates attendee number. 
                                                                              [cn]与会者数量 */
        TSDK_S_ATTENDEE_BASE_INFO* attendee_list;                        /**< [en]Indicates attendee list. 
                                                                              [cn]与会者列表 */
    }SERVICE_S_BOOK_CONF_INFO;

    /**
    * [en]Pen attribute structure.
    * [cn]画笔信息
    */
    typedef struct tagSERVICE_ANNO_PEN_INFO
    {
        int                style;        //pen stytle
        unsigned int    color;        //pen color
        int                width;        //pen width
    }SERVICE_ANNO_PEN_INFO;


#define    SERVICE_DATA_dsNullID    ((unsigned int)(0))
#define SERVICE_DATA_dsNullOffset ((unsigned int)(-1))

//Defines a subtype of page annotation 
#define    SERVICE_DS_ANNOTDRAWING_TYPE_FREEHAND                1    /*Pencil line */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_HILIGHT                2    /*Highlight line */
#define SERVICE_DS_ANNOTDRAWING_TYPE_RECTANGLE                3    /*hollow rectangle */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_FILLRECTANGLE            4    /*Filled rectangle */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_ROUNDRECTANGLE            5    /*Hollow rounded rectangle */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_FILLROUNDRECTANGLE        6    /*Rounded rectangle */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_ELLIPSE                7    /*hollow ellipse */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_FILLELLIPSE            8    /*Filled ellipse */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_LINE                    9    /*straight line */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_LINEARROW                10    /*Single arrow line*/
#define    SERVICE_DS_ANNOTDRAWING_TYPE_LINEDOUBLEARROW        11    /*Double arrow line */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_WBPEN                    12    /*Electronic whiteboard pen */
#define    SERVICE_DS_ANNOTDRAWING_TYPE_WBERASE                13    /*Electronic whiteboard eraser */
#define SERVICE_DS_ANNOTDRAWING_TYPE_PAGEFRAME                14    /*Whiteboard border */


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SERVICE_CONF_DEF_H__ */
