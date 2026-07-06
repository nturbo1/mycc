#ifndef SRC_INCLUDE_NTASSERT_H
#define SRC_INCLUDE_NTASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define ASSERT_IMPL(cond, ...)                                      \
    do {                                                            \
        if (!(cond)) {                                              \
            fprintf(stderr,                                         \
                    "[%s:%d]: Assertion (%s) failed.\n\t",          \
                    __FILE__, __LINE__, #cond);                     \
            fprintf(stderr, __VA_ARGS__);                           \
            fputc('\n', stderr);                                    \
            abort();                                                \
        }                                                           \
    } while (0)

#define assert_always(cond, ...) ASSERT_IMPL(cond, __VA_ARGS__)

#ifdef DEBUG
# define assert_debug(cond, ...) ASSERT_IMPL(cond, __VA_ARGS__)
#else
# define assert_debug(...) do {} while (0);
#endif

#endif // SRC_INCLUDE_NTASSERT_H
