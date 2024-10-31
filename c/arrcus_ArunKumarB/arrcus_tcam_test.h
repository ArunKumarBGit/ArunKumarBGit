/********************************************************************
 *
 * File: arrcus_tcam_test.h
 * Name: Arun Kumar B (arunkumar.be@gmail.com)
 *
 * Description:
 *  This file contains macros used for TCAM entry management Unit Test
 *
 * Copyright (c) 2022 by Arrcus, Inc.
 * All rights reserved.
 *
 ********************************************************************/
#ifndef _ARRCUS_TCAM_TEST_H_
#define _ARRCUS_TCAM_TEST_H_

#define DISPLAY(fmt, arg...)        printf(fmt"\n", ##arg)
#define DISPLAY_ACK(fmt, arg...)    \
{                                   \
printf("\n"fmt, ##arg);             \
getchar();                          \
}
#define READ(fmt, arg...)           scanf(fmt, ##arg)

#define ARGV_STR_LEN_MAX            5
#define ARGV_STR_STATIC_UT          "-st"
#define ARGV_STR_DYNAMIC_UT         "-dt"
#define ARGV_STR_PERFORMANCE_UT     "-pt"
#define ARGV_OPTION_INDEX           1
#define ARRCUS_TCAM_DT_STR_LEN      16
#define ARRCUS_TCAM_DT_ENTRY_MAX    10

typedef enum arrcus_tcam_dt_tc_ {
    ARRCUS_TCAM_DT_TC_NONE                  =  0,
    ARRCUS_TCAM_DT_TC_TCAM_INIT             =  1,
    ARRCUS_TCAM_DT_TC_TCAM_INSERT           =  2,
    ARRCUS_TCAM_DT_TC_TCAM_REMOVE           =  3,
    ARRCUS_TCAM_DT_TC_DISP_STATS            =  4,
    ARRCUS_TCAM_DT_TC_DISP_VLD_TCAM_DATA    =  5,
    ARRCUS_TCAM_DT_TC_DISP_ALL_TCAM_DATA    =  6,
    ARRCUS_TCAM_DT_TC_DISP_TCAM_HANDLER     =  7,
    ARRCUS_TCAM_DT_TC_ENABLE_CON_ERR        =  8,
    ARRCUS_TCAM_DT_TC_DISABLE_CON_ERR       =  9,
    ARRCUS_TCAM_DT_TC_ENABLE_CON_TRC        = 10,
    ARRCUS_TCAM_DT_TC_DISABLE_CON_TRC       = 11,
    ARRCUS_TCAM_DT_TC_EXIT                  = 12,

    /*
     * Add new error codes above this line and increment MAX
     */
    ARRCUS_TCAM_DT_TC_MAX                   = 13,
} arrcus_tcam_dt_tc_t;


#endif
