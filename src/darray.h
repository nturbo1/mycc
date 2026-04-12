#ifndef SRC_DARRAY_H
#define SRC_DARRAY_H

#include <stddef.h>

typedef struct {
    size_t length;
    size_t capacity;
    unsigned char* arr;
    size_t data_size;
} DArray;

// Initializes a given dynamic array if the pointer is not NULL and returns it.
// If the DArray pointer is NULL, then it allocates memory, initializes it, and returns the new DArray
// pointer.
DArray* init_darray(DArray* darr, const size_t capacity, const size_t data_size);

void free_darray(DArray** darr);

// Returns a pointer to the element at a given index.
// 
// Exits the the program if the index is out of bounds.
void* darray_get_at(DArray* darr, const size_t index);

// Copies the data at a given address to the place at a given index.
//
// If the data size is not equal to the size of an element of the array, then it leads to an undefined
// behavior.
void darray_set_at(DArray* darr, const size_t index, const void* data, const size_t data_size);

// Adds the data to the end of the array. The data is copied.
//
// If the data size is not equal to the size of an element of the array, then it leads to an undefined
// behavior.
void darray_add(DArray* darr, const void* data, const size_t data_size);

#endif // SRC_DARRAY_H
