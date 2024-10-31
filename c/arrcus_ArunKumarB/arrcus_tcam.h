/********************************************************************
 *
 * File: arrcus_tcam.h
 * Name: Arun Kumar B (arunkumar.be@gmail.com)
 *
 * Description:
 *  This file contains declaration of southbound API, utility APIs
 *  and consolidated header files list
 *
 * Copyright (c) 2022 by Arrcus, Inc.
 * All rights reserved.
 *
 ********************************************************************/
#ifndef _ARRCUS_TCAM_H_
#define _ARRCUS_TCAM_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arrcus_tcam_defs.h"
#include "arrcus_tcam_intf.h"
#include "arrcus_tcam_debug.h"
#include "arrcus_tcam_test.h"

// Southbound API, for TCAM write
syserr_t tcam_program(void *tcam_hndl_p, entry_t *ent_p, 
                      uint32_t position, tcam_access_flag_t flag);

// Internal utility APIs
void tcam_groom(tcam_handle_t *tcam_handle_p);
syserr_t tcam_sort_entries(entry_t *entries_p, uint32_t num);
syserr_t tcam_add_entries(tcam_handle_t *tcam_handle_p, entry_t *entries_p, 
                          uint32_t num);
syserr_t tcam_stats_disp(void *tcam_hndl_p);
syserr_t tcam_handle_disp(void *tcam_hndl_p);
syserr_t tcam_entries_disp(void *tcam_hndl_p);
syserr_t tcam_vld_entries_disp(void *tcam_hndl_p);
syserr_t tcam_handle_release(void **tcam_hndl_p);

#endif
