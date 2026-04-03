#include "nctest.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define PRINT_HELP() \
    do { \
        printf("Usage:\n\tnctest\n\tnctest -v\n\tnctest --verbose\n"); \
    } while(0)

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        nctest_run_all(false);
    }
    else if (argc == 2)
    {
        const char* param = argv[1];
        size_t len = strlen(argv[1]);

        if ((len == 2 && param[1] == 'v') ||
            (len > 2 && strncmp(param, "--verbose", len) == 0))
        {
            nctest_run_all(true);
        }
        else
        {
            PRINT_HELP();
        }
    }
    else
    {
        PRINT_HELP();
    }
    
    return 0;
}
