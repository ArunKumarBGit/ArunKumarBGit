
#ifndef __FW
#define __FW

#include "time.h"
#include "sys/time.h"
#include "strings.h"

inline static char *
sha_ctime1 (void)
{
    struct  timeval  tv;
    static  char     buffer[32];
    static  char     tmpstr[32];
    
    gettimeofday( &tv, NULL );
    bzero(buffer, 32);
    bzero(tmpstr, 32);
    strftime(buffer, 32, "%m/%d/%Y %H:%M:%S" ,localtime(&tv.tv_sec));
    sprintf(tmpstr, "%s.%lu", buffer, tv.tv_usec);
    
    return tmpstr;
}

#define log_to_file(format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/bootflash/abanusim_dbg_file", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#define FWD(format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/bootflash/dump_file", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#define FW(format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/tmp/dump_file", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#define FW0(format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/mnt/plog/dump_file", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s(%d) %s\n", \
                __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}
#define FWD(format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/bootflash/dump_file", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}
#define FWD1(format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/bootflash/dump_file1", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#define FWB(format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/mnt/pss/dump_file", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#define FW_VPC(err,format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/tmp/dump_file_1", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#define FWA(args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/mnt/pss/dump_file", "a+"); \
    if (file) { \
        fprintf(file, ##args); \
        fclose(file); \
    } \
}

#define FW1(format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/tmp/dump_file_1", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#define FW2(format, args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/tmp/dump_file_2", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#define FW3(tmpbuf) \
{ \
    FILE *file; \
    file = fopen("/tmp/dump_file_2", "a+"); \
    if (file) { \
        fprintf(file, "%s %s", sha_ctime1(), tmpbuf); \
        fclose(file); \
    } \
}

#define FW_PID(format,args...) \
{ \
    FILE *file; \
    char fname[100]; \
    char tmpbuf[2049]; \
    snprintf(fname, 99, "/tmp/dump_file-%d", getpid()); \
    file = fopen(fname, "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#define TR() \
{ \
    void *stack_bt[250]; \
    int stack_depth, i; \
    char **strings; \
    FILE *file; \
    \
    stack_depth = backtrace(stack_bt, 250); \
    strings = backtrace_symbols(stack_bt, stack_depth); \
    file = fopen("/bootflash/dump_file", "a+"); \
    \
    if (strings && file) { \
        fprintf(file, "dumping stack trace\n"); \
        for (i = 0; i < stack_depth ; i++) { \
            fprintf(file, "%s ", \
                    strings[i] ? strings[i] : "NULL"); \
        } \
        fprintf(file, "\n"); \
    } \
    \
    if (file) { \
        fclose(file); \
    } \
} \


#define TR_PID() \
{ \
    void *stack_bt[50]; \
    int stack_depth, i; \
    char **strings; \
    FILE *file; \
    \
    stack_depth = backtrace(stack_bt, 50); \
    strings = backtrace_symbols(stack_bt, stack_depth); \
    char fname[100]; \
    snprintf(fname, 99, "/tmp/dump_file-%d", getpid()); \
    file = fopen(fname, "a+"); \
    \
    if (strings && file) { \
        fprintf(file, "dumping stack trace\n"); \
        for (i = 0; i < stack_depth ; i++) { \
            fprintf(file, "%s ", \
                    strings[i] ? strings[i] : "NULL"); \
        } \
        fprintf(file, "\n"); \
    } \
    \
    if (strings) { \
        free(strings); \
    } \
    \
    if (file) { \
        fclose(file); \
    } \
} \

#define FW11(format,args...) \
{ \
    FILE *file; \
    char tmpbuf[2049]; \
    file = fopen("/bootflash/debug_file", "a+"); \
    if (file) { \
        snprintf(tmpbuf, 2048, format, ##args); \
        fprintf(file, "%s %s(%d) %s\n", sha_ctime1(), __FUNCTION__, __LINE__, tmpbuf); \
        fclose(file); \
    } \
}

#endif
