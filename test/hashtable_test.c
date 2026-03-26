#include "hashtable.h"

#include <stdio.h>

int main()
{
    HashTable* ht = ht_new();
    if (ht == NULL) {
        printf("Failed to create a hash table\n");
    } else {
        printf("HashTable was succesfully created! Trying to delete it...\n");
        ht_delete(ht);
    }

    return 0;
}
