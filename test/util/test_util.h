#ifndef TEST_UTIL_TEST_ASSERT_H
#define TEST_UTIL_TEST_ASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

#define FILE_NAME_MAX_SIZE 256 // Probably a bad idea

// Creates a formatted string with a given message and some additional useful information that describes
// errors and failed assertions.
const char* test_output(const char* message);

typedef struct {
    const char* title;
    const char* output;
    bool is_passed;
} TestResult;

typedef struct {
    const char* title;
    size_t test_count;
    TestResult* tests;
    bool is_passed;
} TestSuiteResult;

#define TEST_TITLE_FORMAT "%s [TEST] %s\n"
#define TEST_SUITE_TITLE_FORMAT "%s [TEST SUITE] %s\n"
#define PASSED "PASSED"
#define FAILED "FAILED"

void print_test_suite_results(TestSuiteResult* ts_results, size_t ts_count);

#endif
