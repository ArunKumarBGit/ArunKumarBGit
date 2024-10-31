/********************************************************************
 *
 * File: arrcus_tcam_defs.h
 * Name: Arun Kumar B (arunkumar.be@gmail.com)
 *
 * Description:
 *  This file contains data structures used for TCAM entry management
 *
 * Copyright (c) 2022 by Arrcus, Inc.
 * All rights reserved.
 *
 ********************************************************************/
#ifndef _ARRCUS_TCAM_DEFS_H_
#define _ARRCUS_TCAM_DEFS_H_

#define TCAM_SIZE_MAX           2048
#define TCAM_ENTRY_EMPTY        0
#define TCAM_ENTRY_ID_INVALID   0

typedef enum tcam_pos_flag_ {
    TCAM_POS_FLAG_NONE              = 0,
    TCAM_POS_FLAG_PRIOR             = 1,
    TCAM_POS_FLAG_NEXT              = 2,

    /*
     * Add new error codes above this line and increment MAX
     */
    TCAM_POS_FLAG_MAX               = 3,
} tcam_pos_flag_t;

typedef enum tcam_hndl_flag_ {
    TCAM_HNDL_FLAG_NONE             = 0,
    TCAM_HNDL_FLAG_CONTIGUOUS_MODE  = 1,
    TCAM_HNDL_FLAG_SPREAD_MODE      = 2,

    /*
     * Add new error codes above this line and increment MAX
     */
    TCAM_HNDL_FLAG_MAX              = 3,
} tcam_hndl_flag_t;

typedef struct entry_ {
    uint32_t id;        // Must be unique, 0 means empty TCAM entry
    uint32_t prio;      // 0 means the highest priority
} entry_t;

typedef struct tcam_handle_ {
    entry_t  *tcam_p;
    uint32_t sz;
    uint32_t vld_entries;
    uint32_t last_hw_access;
    uint64_t total_hw_access;
    tcam_hndl_flag_t flag;
} tcam_handle_t;

typedef enum tcam_flag_ {
    TCAM_ACCESS_FLAG_ADD_ENTRY      = 1,
    TCAM_ACCESS_FLAG_REMOVE_ENTRY   = 2,
    TCAM_ACCESS_FLAG_SHIFT_ENTRY    = 3,

    /*
     * Add new error codes above this line and increment MAX
     */
    TCAM_ACCESS_FLAG_MAX            = 4,
} tcam_access_flag_t;

#endif
