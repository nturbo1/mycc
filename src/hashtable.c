#include "hashtable.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define LOAD_FACTOR_VALUE 0.75

// Uses FNV-1a hash algorithm
static uint64_t hash(const char* key, size_t key_size) {
    uint64_t hashval = FNV_OFFSET;

    for (size_t i = 0; i < key_size; i++)
    {
        hashval ^= (uint64_t)(unsigned char) key[i];
        hashval *= FNV_PRIME;
    }

    return hashval;
}

static size_t get_ht_bucket_index(const char* key, const size_t key_size, const size_t ht_capacity)
{
    uint64_t keyhash = hash(key, key_size);

    return (size_t) (keyhash & (uint64_t) (ht_capacity - 1));
}

static void ht_delete_bucket_entries(HashTable* ht)
{
    if (ht == NULL)
        return;

    for (size_t i = 0; i < ht->capacity; i++)
    {
        // Free the bucket chain if exists
        HtBucketEntry* curr_entry = ht->buckets[i].root;
        HtBucketEntry* prev_entry = NULL;
        while (curr_entry != NULL)
        {
            prev_entry = curr_entry;
            curr_entry = curr_entry->next;
            free(prev_entry->key);
            free(prev_entry->value);
            free(prev_entry);
        }
    }
}

static const char* ht_put_ht_bucket_entry(
        size_t* ht_size,
        const size_t ht_capacity,
        HtBucket* buckets,
        const char* key,
        const size_t key_size,
        void* value
) {
    size_t bucket_index = get_ht_bucket_index(key, key_size, ht_capacity);
    HtBucket* bucket = buckets + bucket_index;

    if (*ht_size <= bucket_index) { // bucket is out of bounds
        bucket->root = NULL;
        bucket->entry_count = 0;
    }

    HtBucketEntry* curr_entry = bucket->root;
    HtBucketEntry* prev_entry = NULL;

    while (curr_entry != NULL)
    {
        if (strncmp(curr_entry->key, key, curr_entry->key_size) == 0) {
            curr_entry->value = value;
            return curr_entry->key;
        }

        prev_entry = curr_entry;
        curr_entry = curr_entry->next;
    }

    // No existing bucket entry with the given key found -> creating a new entry
    curr_entry = (HtBucketEntry*) malloc(sizeof(HtBucketEntry));

    // Setting the key
    curr_entry->key = (char*) malloc((key_size + 1) * sizeof(char));
    strncpy(curr_entry->key, key, key_size);
    curr_entry->key[key_size] = 0;
    curr_entry->key_size = key_size;

    // Setting the value
    curr_entry->value = value;
    curr_entry->next = NULL;

    if (bucket->root == NULL)
        bucket->root = curr_entry;
    else
        prev_entry->next = curr_entry;

    bucket->entry_count++;
    (*ht_size)++;

    return curr_entry->key;
}

// Doubles the capacity of the hashtable and inserts all of its elements to a new expanded location.
static bool ht_expand(HashTable* ht)
{
    size_t new_capacity = ht->capacity * 2;
    if (new_capacity < ht->capacity) // overflow (capacity would be too big)
        return false;

    HtBucket* expanded_buckets = (HtBucket*) malloc(ht->capacity * sizeof(HtBucket));

    size_t new_size = 0;
    for (size_t i = 0; i < ht->size; i++)
    {
        HtBucketEntry* entry = ht->buckets[i].root;
        while (entry != NULL)
        {
            ht_put_ht_bucket_entry(
                    &new_size,
                    new_capacity,
                    expanded_buckets,
                    entry->key,
                    entry->key_size,
                    entry->value);

            entry = entry->next;
        }
    }

    ht_delete_bucket_entries(ht);
    free(ht->buckets);

    ht->size = new_size;
    ht->capacity = new_capacity;
    ht->buckets = expanded_buckets;

    return true;
}

#define HT_INITIAL_CAPACITY 16
HashTable* ht_new()
{
    HashTable* ht = malloc(sizeof(HashTable));
    if (ht == NULL)
        return NULL; // TODO: Check for the errors

    ht->size = 0;
    ht->capacity = HT_INITIAL_CAPACITY;
    ht->buckets = (HtBucket*) calloc(ht->capacity, sizeof(HtBucket));
    if (ht->buckets == NULL)
    {
        free(ht);
        return NULL;
    }

    return ht;
}

void ht_delete(HashTable* ht)
{
    assert(ht != NULL || "NULL hashtable pointer was given to ht_delete");

    ht_delete_bucket_entries(ht);

    free(ht->buckets);
    free(ht);
}

void* ht_get(const HashTable* ht, const char* key, const size_t key_size)
{
    assert(ht != NULL || "NULL hashtable was passed to ht_get");
    assert(key != NULL || "NULL key was passed to ht_get");
    assert(key_size > 0 || "An empty key was passed to ht_get");

    HtBucket* bucket = ht->buckets + get_ht_bucket_index(key, key_size, ht->capacity);

    if (bucket == NULL)
        return NULL;

    HtBucketEntry* curr_entry = bucket->root; 

    while (curr_entry != NULL)
    {
        if (strncmp(curr_entry->key, key, curr_entry->key_size) == 0)
            return curr_entry->value;

        curr_entry = curr_entry->next;
    }

    return NULL;
}

const char* ht_put(HashTable* ht, const char* key, const size_t key_size, void* value)
{
    assert(ht != NULL || "NULL hashtable was passed to ht_put");
    assert(key != NULL || "NULL key was passed to ht_put");
    assert(key_size > 0 || "An empty key was passed to ht_put");
    assert(value != NULL || "NULL value was passed to ht_put");

    if (LOAD_FACTOR_VALUE <= ht->size / ht->capacity) {
        ht_expand(ht);
    }

    return ht_put_ht_bucket_entry(&(ht->size), ht->capacity, ht->buckets, key, key_size, value);
}

// For debugging purposes only
// NOTE: Should probably be removed
void ht_print(const HashTable* ht)
{
    if (ht == NULL) {
        printf("NULL\n");
    } else {
        printf("{size: %zu, capacity: %zu, buckets: &%p[", ht->size, ht->capacity, (void*) ht->buckets);
        for (size_t i = 0; i < ht->capacity - 1; i++)
        {
            printf("{root: %p, entry_count: %zu}, ",
                    (void*) ht->buckets[i].root, ht->buckets[i].entry_count);
        }
        printf("{root: %p, entry_count: %zu}]\n",
                (void*) ht->buckets[ht->capacity - 1].root, ht->buckets[ht->capacity - 1].entry_count);
    }
}
