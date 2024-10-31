/********************************************************************
 *
 * File: arrcus_tcam_debug.h
 * Name: Arun Kumar B (arunkumar.be@gmail.com)
 *
 * Description:
 *  This file contains debugging infra related utility macros
 *
 * Copyright (c) 2022 by Arrcus, Inc.
 * All rights reserved.
 *
 ********************************************************************/
#ifndef _ARRCUS_TCAM_DEBUG_H_
#define _ARRCUS_TCAM_DEBUG_H_

#include <time.h>
#include <sys/time.h>
#include <strings.h>

#define ARRCUS_TCAM_DBG_TIME_BUF_SZ         32
#define ARRCUS_TCAM_DBG_LOG_SZ              512
#define TRUE                                1
#define FALSE                               0
#define SUCCESS                             ARRCUS_SYSERR_SUCCESS

typedef enum syserr_ {
    ARRCUS_SYSERR_SUCCESS                   =   0,
    ARRCUS_SYSERR_INVALID_PARAM             =  -1,
    ARRCUS_SYSERR_NULL_PARAM                =  -2,
    ARRCUS_SYSERR_MALLOC_FAILED             =  -3,
    ARRCUS_SYSERR_TCAM_FULL                 =  -4,
    ARRCUS_SYSERR_TCAM_EMPTY                =  -5,
    ARRCUS_SYSERR_TCAM_SPACE_INSUFFICIENT   =  -6,
    ARRCUS_SYSERR_REMOVE_FAILED             =  -7,
    ARRCUS_SYSERR_SORT_ENTRIES              =  -8,
    ARRCUS_SYSERR_SHIFT_UPWARDS             =  -9,
    ARRCUS_SYSERR_SHIFT_DOWNWARDS           = -10,
    ARRCUS_SYSERR_TCAM_HNDL_VLD             = -11,
    ARRCUS_SYSERR_ENTRY_ID_INVALID          = -12,

    /*
     * Add new error codes above this line and decrement MAX
     */
    ARRCUS_SYSERR_MAX                       = -13
} syserr_t;

extern bool console_err_en;
extern bool console_trc_en;

inline static char *
arrcus_tcam_get_time (void)
{   
    struct timeval  tv;
    char buffer[ARRCUS_TCAM_DBG_TIME_BUF_SZ];
    static char tmpstr[ARRCUS_TCAM_DBG_TIME_BUF_SZ];
    
    gettimeofday(&tv, NULL);
    bzero(buffer, ARRCUS_TCAM_DBG_TIME_BUF_SZ);
    bzero(tmpstr, ARRCUS_TCAM_DBG_TIME_BUF_SZ);
    strftime(buffer, ARRCUS_TCAM_DBG_TIME_BUF_SZ, 
             "%m/%d/%Y %H:%M:%S" ,localtime(&tv.tv_sec));
    sprintf(tmpstr, "%s.%d", buffer, tv.tv_usec);
    
    return (tmpstr);
}

#define error_log(format, args...)                                  \
{                                                                   \
    FILE *fp;                                                       \
    char tmpbuf[ARRCUS_TCAM_DBG_LOG_SZ];                            \
    fp = fopen("./arrcus_tcam_err_logs", "a+");                     \
    if (fp) {                                                       \
        snprintf(tmpbuf, ARRCUS_TCAM_DBG_LOG_SZ, format, ##args);   \
        fprintf(fp, "%s %s(%d) %s\n", arrcus_tcam_get_time(),       \
                __FUNCTION__, __LINE__, tmpbuf);                    \
        fclose(fp);                                                 \
    }                                                               \
                                                                    \
    if (console_err_en == TRUE) {                                   \
        printf("%s %s(%d) %s\n", arrcus_tcam_get_time(),            \
                __FUNCTION__, __LINE__, tmpbuf);                    \
    }                                                               \
}

#define trace_log(format, args...)                                  \
{                                                                   \
    FILE *fp;                                                       \
    char tmpbuf[ARRCUS_TCAM_DBG_LOG_SZ];                            \
    fp = fopen("./arrcus_tcam_trc_logs", "a+");                     \
    if (fp) {                                                       \
        snprintf(tmpbuf, ARRCUS_TCAM_DBG_LOG_SZ, format, ##args);   \
        fprintf(fp, "%s %s(%d) %s\n", arrcus_tcam_get_time(),       \
                __FUNCTION__, __LINE__, tmpbuf);                    \
        fclose(fp);                                                 \
    }                                                               \
                                                                    \
    if (console_trc_en == TRUE) {                                   \
        printf("%s %s(%d) %s\n", arrcus_tcam_get_time(),            \
                __FUNCTION__, __LINE__, tmpbuf);                    \
    }                                                               \
}

#define ARRCUS_TCAM_ERR(format, args...)    error_log("ERR: "format, ##args)
#define ARRCUS_TCAM_TRC(format, args...)    trace_log("TRC: "format, ##args)

#endif
