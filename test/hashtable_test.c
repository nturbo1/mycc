#include "hashtable.h"
#include "util/test_util.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    char* key;
    void* value;
} TEST_HT_Pair;

static TestResult* test_hashtable_new_and_delete(const char* title)
{
    TestResult* test_result = malloc(sizeof(TestResult));
    test_result->title = title;
    test_result->is_passed = true;
    test_result->output = NULL;

    // GIVEN
    HashTable* ht = ht_new(); 

    // THEN
    if (ht->size != 0) {
        test_result->is_passed = false;
        test_result->output = test_output("Size of a newly created hashtable must be zero!");
    }

    ht_delete(ht);

    return test_result;
}

static TestResult* test_hashtable_get_and_put(const char* title)
{
    TestResult* test_result = malloc(sizeof(TestResult));
    test_result->title = title;
    test_result->output = NULL;
    test_result->is_passed = true;

    // GIVEN
    const size_t test_data_size = 20;
    TEST_HT_Pair test_data[] = {
        {"alpha", NULL},
        {"bravo", NULL},
        {"charlie", NULL},
        {"delta", NULL},
        {"echo", NULL},
        {"foxtrot", NULL},
        {"golf", NULL},
        {"hotel", NULL},
        {"india", NULL},
        {"juliet", NULL},
        {"kilo", NULL},
        {"lima", NULL},
        {"mike", NULL},
        {"november", NULL},
        {"oscar", NULL},
        {"papa", NULL},
        {"quebec", NULL},
        {"romeo", NULL},
        {"sierra", NULL},
        {"tango", NULL}
    };

    for (size_t i = 0; i < test_data_size; i++)
    {
        test_data[i].value = malloc(16);
    }

    HashTable* ht = ht_new();

    for (size_t i = 0; i < test_data_size; i++)
    {
        // WHEN
        const char* key = test_data[i].key;
        void* value = test_data[i].value;
        const size_t key_size = strlen(key);

        const char* inserted_key = ht_put(ht, key, key_size, value);

        // THEN
        void* inserted_value = ht_get(ht, key, key_size);

        if (strncmp(inserted_key, key, key_size) != 0) {
            test_result->is_passed = false;
            test_result->output = test_output("ht_put returned a wrong key");

            goto end;
        }
        if (inserted_value != value) {
            test_result->is_passed = false;
            test_result->output = test_output("ht_get returned a wrong value address");

            goto end;
        }
    }

end:
    // CLEAN-UP

    ht_delete(ht);

    return test_result;
}

TestSuiteResult test_hashtable(const char* title)
{
    TestSuiteResult suite_result = {.title = title, .test_count = 0, .tests = NULL, .is_passed = true};

    TestResult* tr1 = test_hashtable_new_and_delete("Test hashtable new and delete");
    TestResult* tr2 = test_hashtable_get_and_put("Test hashtable get and put");

    const size_t test_count = 2;
    TestResult* trs = malloc(test_count * sizeof(TestResult));
    trs[0] = *tr1;
    trs[1] = *tr2;

    suite_result.tests = trs;
    suite_result.test_count = test_count;

    // TODO: THERE SHOULD BE A BETTER WAY OF ACHIEVING THIS, MAYBE IMPLEMENT A SET OR A DYNAMIC ARRAY?
    if (!tr1->is_passed || !tr2->is_passed)
        suite_result.is_passed = false;

    return suite_result;
}
