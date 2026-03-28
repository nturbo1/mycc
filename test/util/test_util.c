#include "test_util.h"

#include <stdio.h>

const char* test_output(const char* message)
{
    const size_t message_size = strlen(message);
    const size_t output_message_size = FILE_NAME_MAX_SIZE + 16 + message_size + 1;
    char* output = (char*) calloc(output_message_size, sizeof(char));

    snprintf(output, output_message_size - 1, __FILE__ ":%d: %s", __LINE__, message);

    return output;
}

static void print_test_result(const TestResult* test_result)
{
    if (test_result != NULL) {
        printf(TEST_TITLE_FORMAT, (test_result->is_passed ? PASSED : FAILED), test_result->title);
        if (!(test_result->is_passed)) {
            printf("\t%s\n", test_result->output);
        }
    }
}

void print_test_suite_results(TestSuiteResult* ts_results, size_t ts_count)
{
    if (ts_results == NULL)
        return;

    printf("\n\n************************************************************************************************************************************\n");
    printf("************************************************************* TEST RESULS **********************************************************\n");
    printf("************************************************************************************************************************************\n\n");

    for (size_t i = 0; i < ts_count; i++)
    {
        if (ts_results[i].tests != NULL && ts_results[i].test_count > 0) {
            printf("====================================================================================================================================\n");
            printf(TEST_SUITE_TITLE_FORMAT,
                    ts_results[i].is_passed ? PASSED : FAILED,
                    ts_results[i].title);
            printf("------------------------------------------------------------------------------------------------------------------------------------\n");

            // Print the results of each test in the test suite
            for (size_t j = 0; j < ts_results[i].test_count; j++)
            {
                print_test_result(&ts_results[i].tests[j]);
            }
        }
    }
}
