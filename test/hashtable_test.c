#include "nctest.h"
#include "hashtable.h"

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

TEST(test_hashtable_new_and_delete, "Test hashtable new and delete functions")
{
    // GIVEN
    HashTable* ht = ht_new(); 

    // THEN
    ASSERT_TRUE(ht->size == 0);

    // Clean-up
    ht_delete(ht);
}

TEST(test_hashtable_get_and_put, "Test hashtable get and put functions")
{
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

        ASSERT_TRUE(strncmp(inserted_key, key, key_size) == 0);
        ASSERT_TRUE(inserted_value == value);
    }

    // CLEAN-UP
    ht_delete(ht);
}
