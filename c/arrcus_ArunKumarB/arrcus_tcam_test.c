/********************************************************************
 *
 * File: arrcus_tcam_test.c
 * Name: Arun Kumar B (arunkumar.be@gmail.com)
 *
 * Description:
 *  This file contains unit testing infrastructure APIs
 *
 * Copyright (c) 2022 by Arrcus, Inc.
 * All rights reserved.
 *
 ********************************************************************/
#include "arrcus_tcam.h"

static entry_t hw_tcam[TCAM_SIZE_MAX];

#if defined(ENABLE_CONSOLE_ERR_LOG)
bool console_err_en = TRUE;
#else
bool console_err_en = FALSE;
#endif

#if defined(ENABLE_CONSOLE_TRC_LOG)
bool console_trc_en = TRUE;
#else
bool console_trc_en = FALSE;
#endif

void *tcam_handle_dt_p = NULL;
entry_t entries_dt[ARRCUS_TCAM_DT_ENTRY_MAX];

/*
 * Description:
 *  . Contains static unit test handling code
 *  . Around 20+ test cases are incorporated
 *  . Following each test case, TCAM statistics and 
 *    TCAM contents are displayed
 *  . Negative test cases are also covered:
 *     > Check graceful handling of bigger batch size,
 *       than the available TCAM space
 *     > Delete an entry, which doesn't exist
 */
syserr_t
arrcus_tcam_static_test()
{
    void *tcam_handle_p     = NULL;
    uint32_t test_tcam_size = TCAM_SIZE_MAX; // 10
    tcam_hndl_flag_t flag   = TCAM_HNDL_FLAG_SPREAD_MODE;
    unsigned char sno       = 0;
    int ret_val             = 0;
    entry_t tst_entry_1[]   = {{6, 600}, {5, 500}};
    entry_t tst_entry_2[]   = {{4, 400}, {2, 200}, {3, 300}, {1, 100}};
    entry_t tst_entry_3[]   = {{9, 900}, {10, 1000}, {8, 800}, {7, 700}, 
                               {14, 1400}};
    entry_t tst_entry_3a[]   = {{29, 900}, {30, 1000}, {31, 800}, {32, 700}, 
                               {33, 1400}};
    entry_t tst_entry_4[]   = {{15, 200}};
    entry_t tst_entry_5[]   = {{16, 150}};
    entry_t tst_entry_6[]   = {{17, 650}};
    entry_t tst_entry_7[]   = {{18, 99}};
    entry_t tst_entry_8[]   = {{19, 44}};
    entry_t tst_entry_9[]   = {{20, 1500}};
    entry_t tst_entry_10[]  = {{21, 999}};

    DISPLAY_ACK("%2d of 21) Press ENTER ... To initialize TCAM of size '%u'", 
                ++sno, test_tcam_size);
    DISPLAY("Enter '1' for Contiguous mode, '2' for Spread mode: ");
    READ("%d", &flag);
    ret_val = tcam_init(hw_tcam, test_tcam_size, &tcam_handle_p, flag);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to initialize TCAM");
    } else {
        DISPLAY("\t  TCAM initiatlized successfully");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_1)/sizeof(tst_entry_1[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_1,
                          (sizeof(tst_entry_1)/sizeof(tst_entry_1[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_2)/sizeof(tst_entry_2[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_2,
                          (sizeof(tst_entry_2)/sizeof(tst_entry_2[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_3)/sizeof(tst_entry_3[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_3,
                          (sizeof(tst_entry_3)/sizeof(tst_entry_3[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To remove entry with id '%d'", ++sno, 2);
    ret_val = tcam_remove(tcam_handle_p, 2);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to remove TCAM entry with id '%d'", 2);
    } else {
        DISPLAY("\t  TCAM removal successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_3a)/sizeof(tst_entry_3a[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_3a,
                          (sizeof(tst_entry_3a)/sizeof(tst_entry_3a[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To remove entry with id '%d'", ++sno, 3);
    ret_val = tcam_remove(tcam_handle_p, 3);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to remove TCAM entry with id '%d'", 3);
    } else {
        DISPLAY("\t  TCAM removal successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_4)/sizeof(tst_entry_4[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_4,
                          (sizeof(tst_entry_4)/sizeof(tst_entry_4[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To remove entry with id '%d'", ++sno, 10);
    ret_val = tcam_remove(tcam_handle_p, 10);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to remove TCAM entry with id '%d'", 10);
    } else {
        DISPLAY("\t  TCAM removal successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_5)/sizeof(tst_entry_5[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_5,
                          (sizeof(tst_entry_5)/sizeof(tst_entry_5[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To remove entry with id '%d', '%d'", 
                ++sno, 1, 8);
    ret_val = tcam_remove(tcam_handle_p, 1);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to remove TCAM entry with id '%d'", 10);
    }
    ret_val = tcam_remove(tcam_handle_p, 8);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to remove TCAM entry with id '%d'", 10);
    } else {
        DISPLAY("\t  TCAM removal successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_6)/sizeof(tst_entry_6[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_6,
                          (sizeof(tst_entry_6)/sizeof(tst_entry_6[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_7)/sizeof(tst_entry_7[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_7,
                          (sizeof(tst_entry_7)/sizeof(tst_entry_7[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }
    
    DISPLAY_ACK("%2d of 21) Press ENTER ... To remove entry with id '%d'", ++sno, 7);
    ret_val = tcam_remove(tcam_handle_p, 7);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to remove TCAM entry with id '%d'", 7);
    } else {
        DISPLAY("\t  TCAM removal successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_8)/sizeof(tst_entry_8[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_8,
                          (sizeof(tst_entry_8)/sizeof(tst_entry_8[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To remove entry with id '%d'", ++sno, 6);
    ret_val = tcam_remove(tcam_handle_p, 6);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to remove TCAM entry with id '%d'", 6);
    } else {
        DISPLAY("\t  TCAM removal successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_9)/sizeof(tst_entry_9[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_9,
                          (sizeof(tst_entry_9)/sizeof(tst_entry_9[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To remove entry with id '%d'", ++sno, 5);
    ret_val = tcam_remove(tcam_handle_p, 5);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to remove TCAM entry with id '%d'", 5);
    } else {
        DISPLAY("\t  TCAM removal successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_10)/sizeof(tst_entry_10[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_10,
                          (sizeof(tst_entry_10)/sizeof(tst_entry_10[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To remove entry with id '%d'", ++sno, 49);
    ret_val = tcam_remove(tcam_handle_p, 49);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to remove TCAM entry with id '%d'", 5);
    } else {
        DISPLAY("\t  TCAM removal successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 21) Press ENTER ... To release TCAM handle", ++sno);
    ret_val = tcam_handle_release(&tcam_handle_p);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to release TCAM handle");
    } else {
        DISPLAY("\t  TCAM handle released successfully\n");
    }

    return(SUCCESS);
}


/*
 * Description:
 *  Displays menu for the dynamic test suite
 */
void
arrcus_tcam_dynamic_test_menu ()
{
    DISPLAY("\nDynamic unit test of TCAM entry management");
    DISPLAY("Menu:");
    DISPLAY("  1) Initialize TCAM                 2) Insert entries to TCAM\n"
            "  3) Remove an entry                 4) Display usage statistics\n"
            "  5) Display valid TCAM entries      6) Display all TCAM entries\n"
            "  7) Display TCAM handler data       8) Enable console error logging\n"
            "  9) Disable console error logging  10) Enable console trace logging\n"
            " 11) Disable console trace logging  12) Exit\n");
    DISPLAY("Enter test case number (1 to 12): ");
}


/*
 * Description:
 *  Executes the selected test case
 */
void
arrcus_tcam_dynamic_test_handle (arrcus_tcam_dt_tc_t tc_num)
{
    int size              = 0;
    void *tcam_handle_p   = tcam_handle_dt_p;
    tcam_hndl_flag_t flag   = TCAM_HNDL_FLAG_SPREAD_MODE;
    int i                 = 0;
    int entry_id          = 0;
    syserr_t ret_val      = SUCCESS;

    switch (tc_num) {
        case ARRCUS_TCAM_DT_TC_TCAM_INIT:
            DISPLAY("Enter the size of TCAM: ");
            READ("%d", &size);
            DISPLAY("Enter '1' for Contiguous mode, '2' for Spread mode: ");
            READ("%d", &flag);

            if ((size <=0) || (size > TCAM_SIZE_MAX )) {
                DISPLAY_ACK("Invalid size '%d'. ENTER to proceed", size);
                break;
            }

            ret_val = tcam_init(hw_tcam, size, &tcam_handle_dt_p, flag);
            if (ret_val == SUCCESS) {
                DISPLAY("Initiatlized TCAM of size '%d' successfully", size);
            }
            tcam_handle_p = tcam_handle_dt_p;
            break;

        case ARRCUS_TCAM_DT_TC_TCAM_INSERT:
            DISPLAY("Enter the batch size of TCAM entries: ");
            READ("%d", &size);

            for (i = 0; i < size; i++) {
                DISPLAY("Enter entry data in 'id, prio' format (4, 400): ");
                READ("%d, %d", &entries_dt[i].id, &entries_dt[i].prio);
            }

            ret_val = tcam_insert(tcam_handle_p, entries_dt, size);
            if (ret_val == SUCCESS) {
                DISPLAY("Inserted '%d' entries to TCAM successfully", size);
            }
            break;

        case ARRCUS_TCAM_DT_TC_TCAM_REMOVE:
            DISPLAY("Enter the entry 'id':");
            READ("%d", &entry_id);

            ret_val = tcam_remove(tcam_handle_p, entry_id);
            if (ret_val == SUCCESS) {
                DISPLAY("Removed TCAM entry with id '%d' successfully", 
                        entry_id);
            }
            break;

        case ARRCUS_TCAM_DT_TC_DISP_STATS:
            tcam_stats_disp(tcam_handle_p);
            break;

        case ARRCUS_TCAM_DT_TC_DISP_VLD_TCAM_DATA:
            tcam_vld_entries_disp(tcam_handle_p);
            break;

        case ARRCUS_TCAM_DT_TC_DISP_ALL_TCAM_DATA:
            tcam_entries_disp(tcam_handle_p);
            break;

        case ARRCUS_TCAM_DT_TC_DISP_TCAM_HANDLER:
            tcam_handle_disp(tcam_handle_p);
            break;

        case ARRCUS_TCAM_DT_TC_ENABLE_CON_ERR:
            console_err_en = TRUE;
            DISPLAY("Enabled console error logging successfully");
            break;

        case ARRCUS_TCAM_DT_TC_DISABLE_CON_ERR:
            console_err_en = FALSE;
            DISPLAY("Disabled console error logging successfully");
            break;

        case ARRCUS_TCAM_DT_TC_ENABLE_CON_TRC:
            console_trc_en = TRUE;
            DISPLAY("Enabled console trace logging successfully");
            break;

        case ARRCUS_TCAM_DT_TC_DISABLE_CON_TRC:
            console_trc_en = FALSE;
            DISPLAY("Disabled console trace logging successfully");
            break;

        case ARRCUS_TCAM_DT_TC_EXIT:
            tcam_handle_release(&tcam_handle_p);
            DISPLAY("Released TCAM handle successfully. Exiting cleanly");
            break;

        default:
            DISPLAY("Found an unhandled test case '%d'", tc_num);
            break;
    }
}


/*
 * Description:
 *  . Menu driven unit test suite
 *  . User can initialize TCAM of any size, upto 2048 entries
 *  . Dynamically TCAM entries could be added/ deleted
 *  . TCAM statistics display
 *  . TCAM entries display
 */
syserr_t
arrcus_tcam_dynamic_test ()
{
    char str[ARRCUS_TCAM_DT_STR_LEN]    = { 0 };
    arrcus_tcam_dt_tc_t tc_num          = 0;

    while (tc_num != ARRCUS_TCAM_DT_TC_EXIT) {
        arrcus_tcam_dynamic_test_menu();
        READ("%s", str);
        tc_num = atoi(str);

        if ((tc_num < ARRCUS_TCAM_DT_TC_TCAM_INIT) || 
            (tc_num > ARRCUS_TCAM_DT_TC_EXIT)) {
            DISPLAY_ACK("Invalid choice '%s'\nPress ENTER to continue...", str);
            DISPLAY_ACK("");
            continue;
        }

        arrcus_tcam_dynamic_test_handle(tc_num);

        if (tc_num == ARRCUS_TCAM_DT_TC_EXIT) {
            break;
        }
    }

    DISPLAY("\n...Dynamic unit test is completed successfully...\n");

    return(SUCCESS);
}


/*
 * Description:
 *  . Contains performance measuring unit test cases
 *  . Targets to check number of TCAM write accesses
 */
syserr_t
arrcus_tcam_performance_test()
{
    void *tcam_handle_p     = NULL;
    uint32_t test_tcam_size = TCAM_SIZE_MAX;
    tcam_hndl_flag_t flag   = TCAM_HNDL_FLAG_SPREAD_MODE;
    unsigned char sno       = 0;
    int ret_val             = 0;
    entry_t tst_entry_1[]   = {{6, 600}, {5, 500}};
    entry_t tst_entry_2[]   = {{4, 400}, {2, 200}, {3, 300}, {1, 100}};
    entry_t tst_entry_3[]   = {{9, 900}, {10, 1000}, {8, 800}, {7, 700}, 
                               {14, 1400}};
    entry_t tst_entry_4[]   = {{15, 200}};

    DISPLAY_ACK("%2d of 6) Press ENTER ... To initialize TCAM of size '%u'", 
                ++sno, test_tcam_size);
    DISPLAY("Enter '1' for Contiguous mode, '2' for Spread mode: ");
    READ("%d", &flag);
    ret_val = tcam_init(hw_tcam, test_tcam_size, &tcam_handle_p, flag);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to initialize TCAM");
    } else {
        DISPLAY("\t  TCAM initiatlized successfully");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 6) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_1)/sizeof(tst_entry_1[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_1,
                          (sizeof(tst_entry_1)/sizeof(tst_entry_1[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 6) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_2)/sizeof(tst_entry_2[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_2,
                          (sizeof(tst_entry_2)/sizeof(tst_entry_2[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 6) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_3)/sizeof(tst_entry_3[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_3,
                          (sizeof(tst_entry_3)/sizeof(tst_entry_3[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 6) Press ENTER ... To insert batch of '%lu' entries",
                ++sno, (sizeof(tst_entry_4)/sizeof(tst_entry_4[0])));
    ret_val = tcam_insert(tcam_handle_p, tst_entry_4,
                          (sizeof(tst_entry_4)/sizeof(tst_entry_4[0])));
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to insert entries to TCAM");
    } else {
        DISPLAY("\t  TCAM insertion successful");
        tcam_stats_disp(tcam_handle_p);
        tcam_vld_entries_disp(tcam_handle_p);
    }

    DISPLAY_ACK("%2d of 6) Press ENTER ... To release TCAM handle", ++sno);
    ret_val = tcam_handle_release(&tcam_handle_p);
    if (ret_val != SUCCESS) {
        ARRCUS_TCAM_ERR("Failed to release TCAM handle");
    } else {
        DISPLAY("\t  TCAM handle released successfully\n");
    }

    return(SUCCESS);
}


/*
 * Description:
 *  . Handles command line inputs to this unit test utility
 *  . Gracefully display syntax, in case of '--help'/ wrong usage
 */
int
main (int argc, char *argv[])
{
    if (argc == 2) {
        if (strncmp(argv[ARGV_OPTION_INDEX], ARGV_STR_STATIC_UT, 
                    ARGV_STR_LEN_MAX) == 0) {
            return(arrcus_tcam_static_test());
        } else if (strncmp(argv[ARGV_OPTION_INDEX], ARGV_STR_DYNAMIC_UT, 
                           ARGV_STR_LEN_MAX) == 0) {
            return(arrcus_tcam_dynamic_test());
        } else if (strncmp(argv[ARGV_OPTION_INDEX], ARGV_STR_PERFORMANCE_UT, 
                           ARGV_STR_LEN_MAX) == 0) {
            return(arrcus_tcam_performance_test());
        } 
    }

    DISPLAY("\n./tcam --help to display this help message");
    DISPLAY("Available options:");
    DISPLAY("   -st     Execute static test cases, having 21 UT cases");
    DISPLAY("   -dt     Execute dynamic test cases, user driven\n");
    DISPLAY("Example:\n   ./tcam -st\n   ./tcam -dt\n");

    return(SUCCESS);
}
