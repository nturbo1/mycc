#ifndef SRC_NTASSERT_H
#define SRC_NTASSERT_H

#include <stdio.h>
#include <stdlib.h>

#define assert_always(cond, msg)\
    do {\
        if (!(cond)) {\
            fprintf(stderr, "[%s:%d]: %s\n", __FILE__, __LINE__, msg);\
            abort();\
        }\
    } while(0)

#endif // SRC_NTASSERT_H
