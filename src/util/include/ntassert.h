#ifndef SRC_INCLUDE_NTASSERT_H
#define SRC_INCLUDE_NTASSERT_H

#include <stdio.h>
#include <stdlib.h>

#define assert_always(cond, msg)                                                \
    do {                                                                        \
        if (!(cond)) {                                                          \
            fprintf(stderr, "[%s:%d]: Assertion %s failed.\n\t%s\n",            \
                    __FILE__,                                                   \
                    __LINE__,                                                   \
                    #cond,                                                      \
                    msg);                                                       \
            abort();                                                            \
        }                                                                       \
    } while(0)

# ifdef DEBUG
# define assert_debug(cond, msg)                                                \
    do {                                                                        \
        if (!(cond)) {                                                          \
            fprintf(stderr, "[%s:%d]: Assertion %s failed.\n\t%s\n",            \
                    __FILE__,                                                   \
                    __LINE__,                                                   \
                    #cond,                                                      \
                    msg);                                                       \
            abort();                                                            \
        }                                                                       \
    } while(0)
# else
# define assert_debug(cond, fmt, ...) do {} while(0)
# endif

#endif // SRC_INCLUDE_NTASSERT_H
