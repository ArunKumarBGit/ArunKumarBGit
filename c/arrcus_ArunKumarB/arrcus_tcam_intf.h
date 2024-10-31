/********************************************************************
 *
 * File: arrcus_tcam_intf.h
 * Name: Arun Kumar B (arunkumar.be@gmail.com)
 *
 * Description:
 *  This file contains external interface APIs, for TCAM entry management
 *
 * Copyright (c) 2022 by Arrcus, Inc.
 * All rights reserved.
 *
 ********************************************************************/
#ifndef _ARRCUS_TCAM_INTF_H_
#define _ARRCUS_TCAM_INTF_H_

/*
 * Description:
 *  Initializes TCAN bank handler, serving the given hw_tcam
 *
 * Parameters:
 *  hw_tcam_p:      Pointer to TCAM location 0
 *  size:           Size of TCAM, maximum of 2048 entries capacity
 *  tcam_handle_pp: Upon successful init, TCAM handler pointer is populated
 *  flag:           To select contiguous/ spread mode of TCAM write
 *
 * Return:
 *  0:              SUCCESS; TCAM handler 'tcam_pp' is valid
 *  syserr_t:       SYSERR in case of failure; 'tcam_pp' would be NULL
 */
//int tcam_init(uint32_t size, void **tcam_pp);
int tcam_init(entry_t *hw_tcam_p, uint32_t size, 
              void **tcam_handle_pp, tcam_hndl_flag_t flag);


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
 *  tcam_handle_p:  TCAM handler received during 'tcam_init()'
 *  id:             Unique identity number, for a TCAM entry
 *                  
 * Return:          
 *  0:              SUCCESS
 *  syserr_t:       SYSERR with reason code, in case of failure
 */
int tcam_insert(void *tcam_handle_p, entry_t *entries, uint32_t num);


/*
 * Description:
 *  Removes a TCAM entry referred by given 'id', if that exists
 *
 * Parameters:
 *  tcam_handle_p:  TCAM handler received during 'tcam_init()'
 *  id:             Unique identity number, for a TCAM entry
 *                  
 * Return:          
 *  0:              SUCCESS
 *  syserr_t:       SYSERR with reason code, in case of failure
 */
int tcam_remove(void *tcam_handle_p, uint32_t id);

#endif
