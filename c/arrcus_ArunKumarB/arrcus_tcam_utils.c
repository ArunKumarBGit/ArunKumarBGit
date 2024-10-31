/********************************************************************
 *
 * File: arrcus_tcam_utils.c
 * Name: Arun Kumar B (arunkumar.be@gmail.com)
 *
 * Description:
 *  This file contains southbound API, utility APIs, for TCAM entry 
 *  management
 *
 * Copyright (c) 2022 by Arrcus, Inc.
 * All rights reserved.
 *
 ********************************************************************/
#include "arrcus_tcam.h"


/*
 * Description:
 *  . Southbound API
 *  . Only this API has write access to the TCAM memory
 *  . Handles TCAM hardware access statistics
 *  . Entire operation is automic
 */
syserr_t
tcam_program (void *tcam_hndl_p, entry_t *entry_p, 
              uint32_t position, tcam_access_flag_t flag)
{
    tcam_handle_t *tcam_handle_p = tcam_hndl_p;

    if ((tcam_hndl_p == NULL) || (entry_p == NULL)) {
        ARRCUS_TCAM_ERR("NULL parameter passed. tcam_handle_p = '%p', "
                        "entry_p = '%p'", tcam_hndl_p, entry_p);
        return(ARRCUS_SYSERR_NULL_PARAM);
    }

    if (position >= TCAM_SIZE_MAX) {
        ARRCUS_TCAM_ERR("Invalid position '%u' passed, for TCAM size '%d'",
                        position, TCAM_SIZE_MAX);
        return(ARRCUS_SYSERR_INVALID_PARAM);
    }

    // Write to TCAM
    memcpy((tcam_handle_p->tcam_p + position), entry_p, sizeof(entry_t));

    // Update TCAM hardware write access statistics
    tcam_handle_p->total_hw_access++;
    tcam_handle_p->last_hw_access++;

    if (flag == TCAM_ACCESS_FLAG_ADD_ENTRY) {
        tcam_handle_p->vld_entries++;
    } else if (flag == TCAM_ACCESS_FLAG_REMOVE_ENTRY) {
        tcam_handle_p->vld_entries--;
    }

    return(SUCCESS);
}


/*
 * Description:
 *  . Grooms TCAM entires by spreading them in non-disruptive way
 *  . Make TCAM layout efficient for further write operations
 *  . Note:
 *     > Entires with same priorities should stay adjacent, also
 *       their order should be retained as it is during grooming
 *     > Shift same priority entries as one batch
 */
void
tcam_groom (tcam_handle_t *tcam_handle_p)
{
    uint32_t vld_loc_arr[TCAM_SIZE_MAX] = { 0 };
    uint32_t vld_gap_arr[TCAM_SIZE_MAX] = { 0 };
    int i                               = 0;
    int j                               = 0;
    int k                               = 0;

    for (i = 0; i < tcam_handle_p->sz; i++) {
        if ((tcam_handle_p->tcam_p + i)->id != TCAM_ENTRY_EMPTY) {
            vld_loc_arr[j++] = i;
            ARRCUS_TCAM_TRC("Valid location: %d'", i);
            if (j > 1) {
                vld_gap_arr[k++] = vld_loc_arr[j-1] - vld_loc_arr[j-2];
                ARRCUS_TCAM_TRC("Gap between valid entires '%d' and '%d' "
                                "is '%d'", vld_loc_arr[j-1], 
                                vld_loc_arr[j-2], vld_gap_arr[k-1]);
            }
        }
    }
    // Follow an optimal algorithm, to move TCAM entries and spread efficiently
}


/*
 * Description:
 *  Identifies optimal empty slot prior/ next to the given position
 */
void
tcam_get_optimal_position (tcam_handle_t *tcam_handle_p, uint32_t pos, 
                           uint32_t *optimal_pos_p, tcam_pos_flag_t pos_flag)
{
    int i               = 0;
    uint32_t opt_pos_lo = 0;
    uint32_t opt_pos_hi = 0;
    entry_t *tcam_p     = tcam_handle_p->tcam_p;

    opt_pos_hi = pos;
    opt_pos_lo = pos;

    if (tcam_handle_p->flag == TCAM_HNDL_FLAG_CONTIGUOUS_MODE) {
        *optimal_pos_p = pos;
        return;
    }

    // Identify empty slot range, prior to the given position
    if (pos_flag == TCAM_POS_FLAG_PRIOR) {
        for (i = pos-1; i >= 0; i--) {
            opt_pos_lo = i;
            if (tcam_p[i].id != TCAM_ENTRY_EMPTY) {
                opt_pos_lo = i + 1;
                break;
            }
        }
    }

    // Identify empty slot range, next to the given position
    if (pos_flag == TCAM_POS_FLAG_NEXT) {
        for (i = pos+1; i < tcam_handle_p->sz; i++) {
            opt_pos_hi = i;
            if (tcam_p[i].id != TCAM_ENTRY_EMPTY) {
                opt_pos_hi = i - 1;
                break;
            }
        }
    }

    // Compute optimal position
    *optimal_pos_p = (opt_pos_hi + opt_pos_lo) / 2;
    ARRCUS_TCAM_TRC("opt_pos_hi = '%u', opt_pos_lo = '%u', optimal_pos = '%u'",
                    opt_pos_hi, opt_pos_lo, *optimal_pos_p);
}

/*
 * Description:
 *  Validates entry id (id '0' is invalid)
 */
syserr_t
tcam_validate_entry_id (entry_t *entries_p, uint32_t num)
{
    int i = 0;

    for (i = 0; i < num; i++) {
        if (entries_p[i].id == TCAM_ENTRY_ID_INVALID) {
            return(ARRCUS_SYSERR_ENTRY_ID_INVALID);
        }
    }

    return(SUCCESS);
}


/*
 * Description:
 *  . Sort the batch of given entries in ascending order,
 *    with reference to their priority field
 *  . This improves performance, by optimizing hardware access
 */
syserr_t
tcam_sort_entries (entry_t *entries_p, uint32_t num)
{
    int i = 0;
    int j = 0;
    bool swapped = FALSE;
    entry_t temp_entry;

    if (num == 1) {
        return(SUCCESS);
    }
    
    for (i = 0; i < num-1; i++) {
        swapped = FALSE;
        for (j = 0; j < num-i-1; j++) {
            if (entries_p[j].prio > entries_p[j+1].prio) {
                swapped = TRUE;
                temp_entry = entries_p[j];
                entries_p[j] = entries_p[j+1];
                entries_p[j+1] = temp_entry;
            }
        } // j

        if (swapped == FALSE) {
            break;
        }
    } // i

    return(SUCCESS);
}


/*
 * Description:
 *  . Shifts TCAM entries upwards
 *  . Existing TCAM entries would continue to be effect
 *  . No traffic hit is the goal
 */
syserr_t
tcam_shift_entries_up (tcam_handle_t *tcam_handle_p, int begin, int end)
{
    int i                = begin;
    uint32_t optimal_pos = 0;
    entry_t *tcam_p      = tcam_handle_p->tcam_p;

    for (i = begin; i < end; i++) {
        if (((i + 1) == end) || 
            (tcam_p[i+1].prio == tcam_p[i+2].prio)) {
            optimal_pos = i;
        } else {
            tcam_get_optimal_position(tcam_handle_p, i, &optimal_pos,
                                      TCAM_POS_FLAG_PRIOR);
        }
        tcam_program(tcam_handle_p, &tcam_p[i+1], optimal_pos, 
                     TCAM_ACCESS_FLAG_SHIFT_ENTRY);
        tcam_p[i+1].id = 0;
        tcam_p[i+1].prio = 0;
    }

    return(SUCCESS);
}


/*
 * Description:
 *  . Shifts TCAM entries downwards
 *  . Existing TCAM entries would continue to be effect
 *  . No traffic hit is the goal
 */
syserr_t
tcam_shift_entries_down (tcam_handle_t *tcam_handle_p, int begin, int end)
{
    int i                = end;
    uint32_t optimal_pos = 0;
    entry_t *tcam_p      = tcam_handle_p->tcam_p;

    for (i = end; i > begin; i--) {
        if (((i - 1) == begin) || 
            (tcam_p[i-1].prio == tcam_p[i-2].prio)) {
            optimal_pos = i;
        } else {
            tcam_get_optimal_position(tcam_handle_p, i, &optimal_pos,
                                      TCAM_POS_FLAG_NEXT);
        }
        tcam_program(tcam_handle_p, &tcam_p[i-1], optimal_pos, 
                     TCAM_ACCESS_FLAG_SHIFT_ENTRY);
        tcam_p[i-1].id = 0;
        tcam_p[i-1].prio = 0;
    }

    return(SUCCESS);
}


/*
 * Description:
 *  . Adds one entry to the TCAM
 *  . Identifies the optimal TCAM location for the new entry
 *  . Shifts existing TCAM entries upwards/ downwards
 *  . Existing TCAM entries would continue to be effect
 *  . No traffic hit is the goal, while adding new TCAM entry
 */
syserr_t
tcam_add_single_entry (tcam_handle_t *tcam_handle_p, entry_t *entry_p)
{
    int i                   = 0;
    int j                   = 0;
    uint32_t vld_cnt        = 0;
    bool found_hole         = FALSE;
    uint32_t hole_index     = 0;
    int ins_index           = -1;
    int pre_vac_index       = -1;
    uint32_t nxt_vac_index  = 0;
    entry_t *tcam_p         = tcam_handle_p->tcam_p;
    uint32_t optimal_pos    = 0;
    int ret_val             = SUCCESS;

    for (i = 0; i < tcam_handle_p->sz; i++) {
        if (tcam_p[i].id != TCAM_ENTRY_EMPTY) {
            vld_cnt++;
        } else {
            found_hole = TRUE;
            hole_index = i;
            continue;
        }

        if ((entry_p->prio > tcam_p[i].prio) && 
            (vld_cnt < tcam_handle_p->vld_entries)) {
            ARRCUS_TCAM_TRC("entry_p->prio = '%d', tcam.prio = '%d'",
                            entry_p->prio, tcam_p[i].prio);
            continue;
        } else if ((entry_p->prio <= tcam_p[i].prio) && (i != 0)) {
            if (tcam_p[i-1].id == TCAM_ENTRY_EMPTY) {
                if (entry_p->prio < tcam_p[i].prio) {
                    tcam_get_optimal_position(tcam_handle_p, i-1, &optimal_pos,
                                              TCAM_POS_FLAG_PRIOR);
                } else if (entry_p->prio == tcam_p[i].prio) {
                    optimal_pos = i-1;
                }
                tcam_program(tcam_handle_p, entry_p, optimal_pos, 
                             TCAM_ACCESS_FLAG_ADD_ENTRY);
                break;
            } else {
                // Find next vacant slot below
                for (j = i+1; j < tcam_handle_p->sz; j++) {
                    if (tcam_p[j].id == TCAM_ENTRY_EMPTY) {
                        nxt_vac_index = j;
                        break;
                    }
                }

                ins_index = i;

                // Find previous vacant slot above
                if (found_hole == TRUE) {
                    pre_vac_index = hole_index;
                }
                
                // Optimal vacant slot selection
                if (pre_vac_index == -1) {
                    ins_index = i;
                    ret_val = tcam_shift_entries_down(tcam_handle_p, ins_index, nxt_vac_index);
                    if (ret_val != SUCCESS) {
                        ARRCUS_TCAM_ERR("Failed to shift TCAM entries downwards. "
                                        "Begin = '%d', End = '%d", 
                                        ins_index, nxt_vac_index);
                        return(ARRCUS_SYSERR_SHIFT_DOWNWARDS);
                    }
                } else if ((ins_index - pre_vac_index) <= 
                           (nxt_vac_index - ins_index)) {
                    ins_index = i - 1;
                    ret_val = tcam_shift_entries_up(tcam_handle_p, 
                                                    pre_vac_index, ins_index);
                    if (ret_val != SUCCESS) {
                        ARRCUS_TCAM_ERR("Failed to shift TCAM entries upwards. "
                                        "Begin = '%d', End = '%d", hole_index, i);
                        return(ARRCUS_SYSERR_SHIFT_UPWARDS);
                    }
                } else if ((ins_index - pre_vac_index) > 
                           (nxt_vac_index - ins_index)) {
                    ins_index = i;
                    ret_val = tcam_shift_entries_down(tcam_handle_p, ins_index, 
                                                      nxt_vac_index);
                    if (ret_val != SUCCESS) {
                        ARRCUS_TCAM_ERR("Failed to shift TCAM entries downwards. "
                                        "Begin = '%d', End = '%d", 
                                        ins_index, nxt_vac_index);
                        return(ARRCUS_SYSERR_SHIFT_DOWNWARDS);
                    }
                }

                tcam_program(tcam_handle_p, entry_p, ins_index, 
                             TCAM_ACCESS_FLAG_ADD_ENTRY);
                break;
            }
        } else if ((entry_p->prio <= tcam_p[i].prio) && (i == 0)) {
            // Find next vacant slot below
            for (j = i+1; j < tcam_handle_p->sz; j++) {
                if (tcam_p[j].id == TCAM_ENTRY_EMPTY) {
                    nxt_vac_index = j;
                    break;
                }
            }

            ins_index = i;
            tcam_shift_entries_down(tcam_handle_p, ins_index, nxt_vac_index);
            tcam_program(tcam_handle_p, entry_p, ins_index, 
                         TCAM_ACCESS_FLAG_ADD_ENTRY);
            break;
        } else if ((entry_p->prio > tcam_p[i].prio) && 
                   ((i + 1) == tcam_handle_p->sz)) {
            ret_val = tcam_shift_entries_up(tcam_handle_p, hole_index, i);
            if (ret_val != SUCCESS) {
                ARRCUS_TCAM_ERR("Failed to shift TCAM entries upwards. "
                                "Begin = '%d', End = '%d", hole_index, i);
                return(ARRCUS_SYSERR_SHIFT_UPWARDS);
            }

            tcam_program(tcam_handle_p, entry_p, i,
                         TCAM_ACCESS_FLAG_ADD_ENTRY);
        } else if ((entry_p->prio > tcam_p[i].prio) && 
                   ((i + 1) < tcam_handle_p->sz)) {
            if (vld_cnt < tcam_handle_p->vld_entries) {
                continue;
            }
        }

        if ((vld_cnt == tcam_handle_p->vld_entries) && 
            ((i + 1) < tcam_handle_p->sz)) {
            ARRCUS_TCAM_TRC("entry_p->prio = '%d', tcam.prio = '%d'",
                            entry_p->prio, tcam_p[i].prio);
            tcam_get_optimal_position(tcam_handle_p, i+1, &optimal_pos,
                                      TCAM_POS_FLAG_NEXT);
            tcam_program(tcam_handle_p, entry_p, optimal_pos, 
                         TCAM_ACCESS_FLAG_ADD_ENTRY);
            break;
        } else if ((vld_cnt == tcam_handle_p->vld_entries) && 
                   ((i + 1) == tcam_handle_p->sz)) {
            ARRCUS_TCAM_TRC("Reached end of TCAM. Add using hole "
                            "location '%d'", hole_index);
            ret_val = tcam_shift_entries_up(tcam_handle_p, hole_index, i);
            if (ret_val != SUCCESS) {
                ARRCUS_TCAM_ERR("Failed to shift TCAM entries upwards. "
                                "Begin = '%d', End = '%d", hole_index, i);
                return(ARRCUS_SYSERR_SHIFT_UPWARDS);
            }

            tcam_program(tcam_handle_p, entry_p, i,
                         TCAM_ACCESS_FLAG_ADD_ENTRY);
        }
    }

    return(SUCCESS);
}


/*
 * Description:
 *  . Adds a batch of new entries to the TCAM
 *  . If the batch size is bigger than the available TCAM space,
 *    gracefully prevents the entire batch addition
 */
syserr_t
tcam_add_entries (tcam_handle_t *tcam_handle_p, entry_t *entries_p, 
                  uint32_t num)
{
    int i                = 0;
    uint32_t optimal_pos = 0;
    int ret_val          = SUCCESS;

    ret_val = tcam_validate_entry_id(entries_p, num);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Entry id check failed");
        return(ARRCUS_SYSERR_ENTRY_ID_INVALID);
    }

    ret_val = tcam_sort_entries(entries_p, num);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to sort entries");
        return(ARRCUS_SYSERR_SORT_ENTRIES);
    }

    tcam_handle_p->last_hw_access = 0;
    
    if (tcam_handle_p->vld_entries == 0) {
        optimal_pos = 0;
        for (i = 0; i < num; i++) {
            tcam_get_optimal_position(tcam_handle_p, optimal_pos, &optimal_pos,
                                      TCAM_POS_FLAG_NEXT);
            tcam_program(tcam_handle_p, (entries_p + i), optimal_pos,
                         TCAM_ACCESS_FLAG_ADD_ENTRY);
            optimal_pos++;
        }
    } else {
        for (i = 0; i < num; i++) {
            ret_val = tcam_add_single_entry(tcam_handle_p, entries_p + i);
            if (ret_val != SUCCESS) {
                ARRCUS_TCAM_ERR("Failed to add an entry to TCAM with "
                                "id '%d', prio '%d'", 
                                entries_p[i].id, entries_p[i].prio);
                return(ARRCUS_SYSERR_SORT_ENTRIES);
            }
        }
    }

    return(SUCCESS);
}


/*
 * Description:
 *  . Displays TCAM statistics, having
 *     > size of TCAM
 *     > valid number of entries
 *     > last TCAM write access count, for the last batch
 *     > total TCAM write access count, for all batches
 */
syserr_t
tcam_stats_disp (void *tcam_hndl_p)
{
    tcam_handle_t *tcam_handle_p = tcam_hndl_p;

    if (tcam_hndl_p == NULL) {
        ARRCUS_TCAM_ERR("NULL parameter passed for tcam_hndl_p");
        return(ARRCUS_SYSERR_NULL_PARAM);
    }

    DISPLAY("\nTCAM statistics:");
    DISPLAY("  size                    = %u", tcam_handle_p->sz);
    DISPLAY("  valid number of entries = %u", tcam_handle_p->vld_entries);
    DISPLAY("  last_hw_access          = %u", tcam_handle_p->last_hw_access);
    DISPLAY("  total_hw_access         = %llu", tcam_handle_p->total_hw_access);

    return(SUCCESS);
}


/*
 * Description:
 *  . Displays TCAM handler contents, having
 *     > pointer to actual TCAM, offset 0
 *     > size of TCAM
 *     > valid number of entries
 *     > last TCAM write access count, for the last batch
 *     > total TCAM write access count, for all batches
 */
syserr_t
tcam_handle_disp (void *tcam_hndl_p)
{
    tcam_handle_t *tcam_handle_p = tcam_hndl_p;

    if (tcam_hndl_p == NULL) {
        ARRCUS_TCAM_ERR("NULL parameter passed for tcam_hndl_p");
        return(ARRCUS_SYSERR_NULL_PARAM);
    }

    DISPLAY("TCAM handle:");
    DISPLAY("    tcam_p = %p", tcam_handle_p->tcam_p);
    DISPLAY("    size = %u", tcam_handle_p->sz);
    DISPLAY("    valid number of entries = %u", tcam_handle_p->vld_entries);
    DISPLAY("    last_hw_access          = %u", tcam_handle_p->last_hw_access);
    DISPLAY("    total_hw_access         = %llu", tcam_handle_p->total_hw_access);

    return(SUCCESS);
}


/*
 * Description:
 *  Displays entire TCAM entries
 */
syserr_t
tcam_entries_disp (void *tcam_hndl_p)
{
    tcam_handle_t *tcam_handle_p = tcam_hndl_p;
    int i = 0;

    if (tcam_hndl_p == NULL) {
        ARRCUS_TCAM_ERR("NULL parameter passed for tcam_hndl_p");
        return(ARRCUS_SYSERR_NULL_PARAM);
    }

    DISPLAY("\nTCAM entries:");
    for (i = 0; i < tcam_handle_p->sz; i++) {
        DISPLAY("Index:%5d,   ID:%4d,   PRIO:%5d", i, 
                (tcam_handle_p->tcam_p + i)->id,
                (tcam_handle_p->tcam_p + i)->prio);
    }

    return(SUCCESS);
}


/*
 * Description:
 *  Displays valid TCAM entries
 */
syserr_t
tcam_vld_entries_disp (void *tcam_hndl_p)
{
    tcam_handle_t *tcam_handle_p = tcam_hndl_p;
    int i = 0;

    if (tcam_hndl_p == NULL) {
        ARRCUS_TCAM_ERR("NULL parameter passed for tcam_hndl_p");
        return(ARRCUS_SYSERR_NULL_PARAM);
    }

    // Handle empty TCAM gracefully
    if (tcam_handle_p->vld_entries == 0) {
        return(SUCCESS);
    }

    DISPLAY("\nTCAM entries:");
    for (i = 0; i < tcam_handle_p->sz; i++) {
        if ((tcam_handle_p->tcam_p + i)->id != 0) {
            DISPLAY("Index:%5d,   ID:%4d,   PRIO:%5d", i, 
                    (tcam_handle_p->tcam_p + i)->id,
                    (tcam_handle_p->tcam_p + i)->prio);
        }
    }

    return(SUCCESS);
}


/*
 * Description:
 *  Frees memory allocated for TCAM handler
 */
syserr_t
tcam_handle_release (void **tcam_handle_pp)
{
    if (tcam_handle_pp == NULL) {
        ARRCUS_TCAM_ERR("NULL parameter passed for tcam_handle_pp");
        return(ARRCUS_SYSERR_NULL_PARAM);
    }

    free(*tcam_handle_pp);
    *tcam_handle_pp = NULL;

    return(SUCCESS);
}
