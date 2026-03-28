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
        if (ht->buckets[i].entry_count > 0) {
            assert(ht->buckets[i].root != NULL ||
                    "HashTable bucket root is NULL while the bucket entry_count >0");
            HtBucketEntry* curr_entry = ht->buckets[i].root;
            HtBucketEntry* prev_entry = NULL;
            while (curr_entry != NULL)
            {
                prev_entry = curr_entry;
                curr_entry = curr_entry->next;
                free((char*) prev_entry->key);
                free(prev_entry->value);
                free(prev_entry);
            }
        }
    }
}

static const char* ht_put_ht_bucket_entry(
        size_t* ht_size,
        const size_t ht_capacity,
        HtBucket* buckets,
        const char* key,
        const size_t key_size,
        void* value,
        bool is_expansion
) {
    size_t bucket_index = get_ht_bucket_index(key, key_size, ht_capacity);
    assert(bucket_index < ht_capacity || "Bucket index >= ht_capacity");
    HtBucket* bucket = buckets + bucket_index;
    assert((bucket->entry_count > 0 && bucket->root != NULL) ||
            (bucket->entry_count == 0 && bucket->root == NULL) ||
            "HashTable bucket entry_count and root are not in sync");

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
    if (!is_expansion) {
        curr_entry->key = (char*) malloc((key_size + 1) * sizeof(char));
        strncpy((char*) curr_entry->key, key, key_size);
        ((char*) curr_entry->key)[key_size] = 0;
    } else {
        // No need to copy the existing valid keys inside the hashtable during an expansion
        curr_entry->key = key;
    }
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
    assert(ht != NULL || "NULL hashtable was given to ht_expand"); // Maybe you should just ht_new()???

    size_t new_capacity = ht->capacity * 2;
    if (new_capacity < ht->capacity) // overflow (capacity would be too big)
        return false; // TODO: MAYBE YOU SHOULD LOG ABOUT IT???

    HtBucket* expanded_buckets = (HtBucket*) calloc(new_capacity, sizeof(HtBucket));

    size_t new_size = 0;
    for (size_t i = 0; i < ht->capacity; i++)
    {
        if (ht->buckets[i].entry_count > 0) {
            assert(ht->buckets[i].root != NULL || "HashTable bucket root is NULL while entry_count >0");

            HtBucketEntry* curr_entry = ht->buckets[i].root;
            HtBucketEntry* prev_entry = NULL;

            while (curr_entry != NULL)
            {
                ht_put_ht_bucket_entry(
                        &new_size,
                        new_capacity,
                        expanded_buckets,
                        curr_entry->key,
                        curr_entry->key_size,
                        curr_entry->value,
                        true);

                prev_entry = curr_entry;
                curr_entry = curr_entry->next;

                // The pointers to the key and value are copied in the new entry of the expanded buckets
                // above, so no need to free the valid memory of the key and value that have been existed
                // in the hashtable, only freeing the old entry
                free(prev_entry);
            }
        }
    }

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

    const size_t bucket_index = get_ht_bucket_index(key, key_size, ht->capacity);
    assert(bucket_index < ht->capacity || "HashTable bucket_index >= ht->capacity");
    HtBucket* bucket = ht->buckets + bucket_index;

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

    if (LOAD_FACTOR_VALUE <= ((double) ht->size) / ht->capacity) {
        ht_expand(ht); // TODO: CHECK THE FUNCTION RETURN VALUE AND HANDLE IT, MAYBE LOG THE SITUATION???
    }

    return ht_put_ht_bucket_entry(&(ht->size), ht->capacity, ht->buckets, key, key_size, value, false);
}

// For debugging purposes only
// NOTE: Should probably be removed
void ht_print(const HashTable* ht)
{
    if (ht == NULL) {
        printf("NULL\n");

        return;
    }

    printf("{ size: %zu, capacity: %zu, buckets: &%p [\n",
            ht->size, ht->capacity, (void*) ht->buckets);

    for (size_t i = 0; i < ht->capacity - 1; i++)
    {
        printf("\t%zu {root: %p, entry_count: %zu}: ",
                i, (void*) ht->buckets[i].root, ht->buckets[i].entry_count);

        if (ht->buckets[i].entry_count > 0) {
            HtBucketEntry* curr = ht->buckets[i].root;
            while (curr != NULL)
            {
                printf("{key: %s, key_size: %zu, value: %p, next: %p} -> ",
                        curr->key, curr->key_size, (void*) curr->value, (void*) curr->next);
                curr = curr->next;
            }

            printf("NULL\n");
        } else {
            printf("EMPTY\n");
        }
    }

    printf("\t%zu {root: %p, entry_count: %zu}: ",
            ht->capacity - 1,
            (void*) ht->buckets[ht->capacity - 1].root,
            ht->buckets[ht->capacity - 1].entry_count);

    if (ht->buckets[ht->capacity - 1].entry_count > 0) {
        assert(ht->buckets[ht->capacity - 1].root != NULL ||
                "HashTable's last bucket root is NULL while its entry_count >0");
        HtBucketEntry* curr = ht->buckets[ht->capacity - 1].root;
        while (curr != NULL)
        {
            printf("{key: %s, key_size: %zu, value: %p, next: %p} -> ",
                    curr->key, curr->key_size, (void*) curr->value, (void*) curr->next);
            curr = curr->next;
        }

        printf("NULL\n]}\n");
    } else {
        printf("EMPTY\n]}\n");
    }
}
