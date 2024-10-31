#include <stdio.h>

#define SUCCESS     0
#define INFO        1
#define ERR         2
#define STD_OUT     stdout
#define STD_ERR     stderr

#define LOG_MESSAGE(prio, stream, msg, ...) do {\
                        char *str;\
                        if (prio == INFO)\
                            str = "INFO";\
                        else if (prio == ERR)\
                            str = "ERR";\
                        fprintf(stream, "[%s] : %s : %d : "msg" \n", \
                                str, __FILE__, __LINE__, ##__VA_ARGS__);\
                    } while (0)

int
main (void)
{
    int ret_val = SUCCESS;

    LOG_MESSAGE(ERR, STD_ERR, "Error msg");

    return(ret_val);
}
