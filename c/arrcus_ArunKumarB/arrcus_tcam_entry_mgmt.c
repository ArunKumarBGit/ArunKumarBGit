/********************************************************************
 *
 * File: arrcus_tcam_entry_mgmt.c
 * Name: Arun Kumar B (arunkumar.be@gmail.com)
 *
 * Description:
 *  This file contains northbound APIs, for TCAM entry management
 *
 * Copyright (c) 2022 by Arrcus, Inc.
 * All rights reserved.
 *
 ********************************************************************/
 #include "arrcus_tcam.h"

/*
 * Description:
 *  Initializes TCAN bank handler, serving the given hw_tcam
 *
 * Parameters:
 *  hw_tcam_p:      Pointer to TCAM location 0
 *  size:           Size of TCAM, maximum of 2048 entries capacity
 *  tcam_handle_pp: Upon successful init, TCAM handler pointer is populated
 *
 * Return:
 *  0:              SUCCESS; TCAM handler 'tcam_pp' is valid
 *  syserr_t:       SYSERR in case of failure; 'tcam_pp' would be NULL
 */
syserr_t
tcam_init (entry_t *hw_tcam_p, uint32_t size, void **tcam_handle_pp,
           tcam_hndl_flag_t flag)
{
    tcam_handle_t *tcam_handle_p = NULL;

    if ((hw_tcam_p == NULL) || (tcam_handle_pp == NULL)) {
        ARRCUS_TCAM_ERR("NULL parameter passed");
        *tcam_handle_pp = NULL;
        return(ARRCUS_SYSERR_NULL_PARAM);
    }

    if (size == 0) {
        ARRCUS_TCAM_ERR("Invalid size passed");
        *tcam_handle_pp = NULL;
        return(ARRCUS_SYSERR_INVALID_PARAM);
    }

    if (*tcam_handle_pp != NULL) {
        ARRCUS_TCAM_ERR("TCAM handle is already initialized");
        return(ARRCUS_SYSERR_TCAM_HNDL_VLD);
    }

    // Initialize TCAM
    memset(hw_tcam_p, 0, (size * sizeof(entry_t)));

    // Allocate memory for TCAM handle
    tcam_handle_p = (tcam_handle_t *)malloc(sizeof(tcam_handle_t));
    if (tcam_handle_p == NULL) {
        ARRCUS_TCAM_ERR("Failed to allocate memory for TCAM handle, size '%lu'",
                        sizeof(tcam_handle_t));
        *tcam_handle_pp = NULL;
        return(ARRCUS_SYSERR_MALLOC_FAILED);
    }

    // Initialize TCAM handle
    tcam_handle_p->tcam_p = hw_tcam_p;
    tcam_handle_p->sz = size;
    tcam_handle_p->vld_entries = 0;
    tcam_handle_p->total_hw_access = 0;
    tcam_handle_p->last_hw_access = 0;
    tcam_handle_p->flag = flag;

    *tcam_handle_pp = tcam_handle_p;

    return(SUCCESS);
}


/*
 * Description:
 *  . Inserts a batch of entries into the TCAM 
 *  . Insertion operation is automic, either successful entirely or 
 *    it fails and no entry is inserted
 *  . If th batch size is more than the available space in TCAM,
 *    insertion fails gracefully, without any partial insertion
 *  . Existing TCAM entries would be in effect, during new insertion
 *  . No traffic hit would occur, during the entire insertion operation
 *  . New batch of entries are sorted based on the priority field,
 *    before starting insertion sequence. This is done for optimization.
 *
 * Parameters:
 *  tcam_hndl_p:    TCAM handler received during 'tcam_init()'
 *  id:             Unique identity number, for a TCAM entry
 *                  
 * Return:          
 *  0:              SUCCESS
 *  syserr_t:       SYSERR with reason code, in case of failure
 */
syserr_t
tcam_insert (void *tcam_hndl_p, entry_t *entries_p, uint32_t num)
{
    tcam_handle_t *tcam_handle_p    = tcam_hndl_p;
    uint32_t avbl_sz                = 0;

    if ((tcam_hndl_p == NULL) || (entries_p == NULL)) {
        ARRCUS_TCAM_ERR("NULL parameter passed. tcam_hndl_p = '%p', "
                        "entries_p = '%p'", tcam_hndl_p, entries_p);
        return(ARRCUS_SYSERR_NULL_PARAM);
    }

    if (num == 0) {
        ARRCUS_TCAM_ERR("Invalid number of entries '%d'", num);
        return(ARRCUS_SYSERR_INVALID_PARAM);
    }

    // Handle TCAM full case
    if (tcam_handle_p->vld_entries == tcam_handle_p->sz) {
        ARRCUS_TCAM_ERR("TCAM is full");
        return(ARRCUS_SYSERR_TCAM_FULL);
    }

    // Handle insufficient TCAM space case
    avbl_sz = tcam_handle_p->sz - tcam_handle_p->vld_entries;
    if (avbl_sz < num) {
        ARRCUS_TCAM_ERR("Available TCAM space '%d' is not sufficient "
                        "for '%d' entries", avbl_sz, num);
        return(ARRCUS_SYSERR_TCAM_SPACE_INSUFFICIENT);
    }

    // Groom TCAM entries for efficiency/ optimal hw_access
    tcam_groom(tcam_handle_p);

    return(tcam_add_entries(tcam_handle_p, entries_p, num));
}


/*
 * Description:
 *  Removes a TCAM entry referred by given 'id', if that exists
 *
 * Parameters:
 *  tcam_hndl_p:    TCAM handler received during 'tcam_init()'
 *  id:             Unique identity number, for a TCAM entry
 *                  
 * Return:          
 *  0:              SUCCESS
 *  syserr_t:       SYSERR with reason code, in case of failure
 */
syserr_t
tcam_remove (void *tcam_hndl_p, uint32_t id)
{
    tcam_handle_t *tcam_handle_p    = tcam_hndl_p;
    entry_t blank_entry;
    uint32_t i                      = 0;
    char is_deleted                 = 0;

    if (tcam_hndl_p == NULL) {
        ARRCUS_TCAM_ERR("NULL parameter passed for tcam_hndl_p");
        return(ARRCUS_SYSERR_NULL_PARAM);
    }

    if (id == TCAM_ENTRY_EMPTY) {
        ARRCUS_TCAM_ERR("Invalid value passed for id '%d'", id);
        return(ARRCUS_SYSERR_INVALID_PARAM);
    }

    // Handle TCAM empty case
    if (tcam_handle_p->vld_entries == 0) {
        ARRCUS_TCAM_ERR("TCAM is empty");
        return(ARRCUS_SYSERR_TCAM_EMPTY);
    }

    memset(&blank_entry, 0, sizeof(entry_t));
    tcam_handle_p->last_hw_access = 0;

    for (i = 0; i < tcam_handle_p->sz; i++) {
        if ((tcam_handle_p->tcam_p + i)->id == id) {
            tcam_program(tcam_handle_p, &blank_entry, i,
                         TCAM_ACCESS_FLAG_REMOVE_ENTRY);
            is_deleted = 1;
            break;
        }
    }

    if (is_deleted == 0) {
        ARRCUS_TCAM_ERR("No entry found in TCAM with id '%d'", id);
        return(ARRCUS_SYSERR_REMOVE_FAILED);
    }

    // Groom TCAM entries for efficiency/ optimal hw_access
    tcam_groom(tcam_handle_p);

    return(SUCCESS);
}
