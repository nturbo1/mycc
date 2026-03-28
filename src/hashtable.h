#ifndef SRC_HASHTABLE_H
#define SRC_HASHTABLE_H

// Parameters for FNV Hash algorithms
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

#include <stddef.h>
#include <stdint.h>

// Represents a node in a linked list of a bucket
typedef struct ht_bucket_entry {
    const char* key;
    size_t key_size; // excluding the NULL-terminator
    void* value;
    struct ht_bucket_entry* next;
} HtBucketEntry;

// Uses separate chaining with a linked list
typedef struct {
    HtBucketEntry* root; // root of the linked list
    size_t entry_count;
} HtBucket;

typedef struct {
    size_t size;
    size_t capacity;
    HtBucket* buckets;
} HashTable;

// Creates a new hash table and allocates memory on the heap
HashTable* ht_new();

// Deletes the hash table and all the associated heap memory with it.
void ht_delete(HashTable* ht);

void* ht_get(const HashTable* ht, const char* key, const size_t key_size);
const char* ht_put(HashTable* ht, const char* key, const size_t key_size, void* value);

void ht_print(const HashTable* ht);

#endif
