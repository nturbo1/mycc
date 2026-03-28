#include "util/test_util.h"
#include "hashtable_test.h"

#include <stdio.h>

int main()
{
    TestSuiteResult tsrs[] = {test_hashtable("Test hashtable")};

    print_test_suite_results(tsrs, 1);

    return 0;
}
