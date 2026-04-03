#ifndef NCTEST_H
#define NCTEST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef void (*NT_TestFn)(void);

typedef struct {
    const char* name;
    NT_TestFn   fn;
    const char* description;
} NT_Test;

typedef struct {
    const char* test_name;
    const char* fail_file;
    int         fail_line;
    bool        failed;
    char        fail_msg[256];
} NT_TestState;

extern NT_TestState _nctest_curr_test_state;

#define TEST(name, description)                                                                     \
    void NT_Test_##name(void);                                                                      \
    static NT_Test _nt_test_##name                                                                  \
        __attribute__((section("test_registry"),                                                    \
                    aligned(1),                                                                     \
                    used)) =                                                                        \
        { #name, NT_Test_##name, description };                                                     \
    void NT_Test_##name(void)

#define ASSERT_TRUE(cond) \
    do {                                                        \
        if (!(cond)) {                                            \
            _nctest_curr_test_state.failed = true;              \
            _nctest_curr_test_state.fail_file = __FILE__;       \
            _nctest_curr_test_state.fail_line = __LINE__;       \
            snprintf(_nctest_curr_test_state.fail_msg,          \
                    sizeof(_nctest_curr_test_state.fail_msg),   \
                    "ASSERT_TRUE(%s) failed",                   \
                    #cond);                                     \
            return;                                             \
        }                                                       \
    } while(0)

void nctest_run_all(bool verbose);

#endif
