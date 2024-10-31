Index:
 A) Version history
 B) How to start :: Extract the code, ReadMe.txt, compile, test
 C) Steps to compile TCAM entry management code
 D) Steps to Unit Test TCAM entry management code
 E) Steps to modify Static Unit Test cases
 F) List of northbound APIs used
 G) Southbound API used
 H) List of utility APIs used
 I) Troubleshooting capability

/******************************************************************************/

A) Version history:
   |-----|---------------------------------------------------------------------|
   |v1.0 |  Northbound APIs implemented & static Unit Test tool integrated     |
   |-----|---------------------------------------------------------------------|
   |v1.1 |  Improved readability of Static Unit Test results                   | 
   |     |  Enable/ disable console error/ trace debug logs, using build option|
   |     |  ReadMe.txt with usage guide, API details, compilation, UT steps    |
   |-----|---------------------------------------------------------------------|
   |v1.2 |  Southbound API implemented & integrated to northbound APIs         |
   |     |  ReadMe.txt updated with version history                            |
   |-----|---------------------------------------------------------------------|
   |v1.3 |  Phase 1 code clean up done                                         |
   |-----|---------------------------------------------------------------------|
   |v1.4 |  Phase 2 code clean up done                                         |
   |     |  Standardised error handling mechanism, with syserr_t               |
   |     |  Added tcam_flag_t to southbound API, for statistics handling       |
   |-----|---------------------------------------------------------------------|
   |v1.5 |  Integrated Dynamic Unit Test suite                                 |
   |-----|---------------------------------------------------------------------|
   |v1.6 |  Spread logic (option) got added, for optimisation                  |
   |-----|---------------------------------------------------------------------|
   |v1.7 |  Place holder for TCAM groom functionality got added                |
   |-----|---------------------------------------------------------------------|

B) How to start :: Extract the code, ReadMe.txt, compile, test
linux$ tar xf arrcus_ArunKumarB_v_1_1.tar
linux$ cd arrcus_ArunKumarB
linux$ ls ReadMe.txt
linux$ cd build/
linux$ make clean
rm -f *.o
rm -f tcam
linux$ make
gcc -g -Wall -c arrcus_tcam_entry_mgmt.c -o arrcus_tcam_entry_mgmt.o
gcc -g -Wall -c arrcus_tcam_test.c -o arrcus_tcam_test.o
gcc -g -Wall -c arrcus_tcam_utils.c -o arrcus_tcam_utils.o
gcc  arrcus_tcam_entry_mgmt.o  arrcus_tcam_test.o  arrcus_tcam_utils.o -Wall -lm -o tcam
linux$
linux$ ./tcam --help

./tcam --help to display this help message
Available options:
   -st     Execute static test cases, having 21 UT cases
   -dt     Execute dynamic test cases, user driven

Example:
   ./tcam -st
   ./tcam -dt

linux$

C) Steps to compile TCAM entry management code:
 1) cd arrcus_ArunKumarB/build
 2) make

D) Steps to Unit Test TCAM entry management code:
 1) cd arrcus_ArunKumarB/build
 2) make
 3) ./tcam -st    <----- To run Static Unit Test, comprising on 21 cases
 3) ./tcam -dt    <----- To run Dynamic Unit Test, user driven model

E) Steps to modify Static Unit Test cases:
 1) vi arrcus_ArunKumarB/arrcus_tcam_test.c
 2) Function to modify: arrcus_tcam_static_test( );
 3) Sample TCAM entries:
    entry_t tst_entry_1[]   = {{4, 400}, {2, 200}, {3, 300}, {1, 100}};
    entry_t tst_entry_2[]   = {{6, 600}, {5, 500}};
    entry_t tst_entry_3[]   = {{9, 900}, {10, 1000}, {8, 800}, {7, 700}, 
                               {14, 1400}};
    entry_t tst_entry_4[]   = {{15, 200}};
    entry_t tst_entry_5[]   = {{16, 150}};
    entry_t tst_entry_6[]   = {{17, 650}};
    entry_t tst_entry_7[]   = {{18, 99}};
    entry_t tst_entry_8[]   = {{19, 44}};
    entry_t tst_entry_9[]   = {{20, 1500}};
    entry_t tst_entry_10[]  = {{21, 999}};

F) List of north bound APIs used:
    tcam_init( )             <-- To initialize TCAM with the given size
    tcam_insert( )           <-- To insert single/ batch of entries to TCAM
    tcam_remove( )           <-- To remove a TCAM entry, matching the given 'id'
    tcam_handle_release( )   <-- To gracefully free the allocated memory

G) Southbound API used:
    tcam_program( )          <-- Only API, having write access to TCAM
                                 All northbound APIs use it, for TCAM write
                             
H) List of utility APIs used:       
    tcam_stats_disp( )       <-- To display statistics about TCAM utilization
                                 size, number of valid entries, 
                                 last hardware access, total hardware access
    tcam_vld_entries_disp( ) <-- To display valid entries in the TCAM
    tcam_entries_disp( )     <-- To display all entries in the TCAM
    DISPLAY_ACK( )           <-- To display information & required ENTER to proceed
    DISPLAY( )               <-- To display information

I) Troubleshooting capability:
    1) Two logging levels methodology is adopted & here's the path of log files
        a) Error logs       <-- arrcus_ArunKumarB/build/arrcus_tcam_err_logs
        b) Trace logs       <-- arrcus_ArunKumarB/build/arrcus_tcam_trc_logs
       Note: These file would be created only during error/ trace conditions 

    2) Optionally, both the Error/ Trace logs could be displayed in console, 
       in addition to the default file logging
       Steps:
        a) vi arrcus_ArunKumarB/Makefile 
        b) As part of CFLAGS, add below knobs as per the requirement
            . ENABLE_CONSOLE_ERR_LOG    <-- Displays error logs in console,
                                            also logs in arrcus_tcam_err_logs
            . ENABLE_CONSOLE_TRC_LOG    <-- Displays trace logs in console,
                                            also logs in arrcus_tcam_trc_logs
/******************************************************************************/
