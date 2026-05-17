#include "darray.h"
#include "ntassert.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define COPY_DATA_AT_INDEX(arr, index, data, data_size)\
    do {\
        const unsigned char* data_src = (const unsigned char*) data;\
        unsigned char* data_dest = arr + (data_size * index);\
        for (size_t data_byte_i = 0; data_byte_i < data_size; data_byte_i++) {\
            data_dest[data_byte_i] = data_src[data_byte_i];\
        }\
    } while(0)

static void darray_expand(DArray* darr)
{
    size_t new_capacity = 2 * darr->capacity;
    assert_always(new_capacity > darr->capacity, "Overflow happened! The array has gotten too big!");

    unsigned char* new_arr = NULL;
    new_arr = (unsigned char*) malloc(darr->data_size * new_capacity);
    assert_always(new_arr != NULL, "Failed to allocate memory for a new capacity.");

    for (size_t i = 0; i < darr->length; i++)
    {
        COPY_DATA_AT_INDEX(
            new_arr,
            i,
            darray_get_at(darr, i),
            darr->data_size
        );
    }

    darr->capacity = new_capacity;
    free(darr->arr);
    darr->arr = new_arr;
}

#define DA_INITIAL_CAPACITY 16
DArray* init_darray(DArray* darr, const size_t capacity, const size_t data_size)
{
    if (darr == NULL) {
        darr = malloc(sizeof(DArray));
        if (darr == NULL) {
            fprintf(stderr, "Failed to initialize a DArray instance\n");
            exit(1);
        }
    }
    darr->arr = malloc(capacity * data_size);
    darr->length = 0;
    darr->capacity = (capacity > 0 ? capacity : DA_INITIAL_CAPACITY);
    darr->data_size = data_size;

    return darr;
}

void free_darray(DArray** darr_ptr)
{
    assert_always(darr_ptr != NULL, "Non NULL DArray** value should be provided");
    DArray* darr = *darr_ptr;

    if (darr == NULL)
        return;

    if (darr->arr != NULL)
        free(darr->arr);

    free(darr);
    *darr_ptr = NULL;
}

void* darray_get_at(DArray* darr, const size_t index)
{
    assert_always(darr != NULL, "NULL object of type DArray was passed");
    assert_always(index < darr->length, "Index is out of bounds");

    return (void*) (darr->arr + (darr->data_size * index));
}

void darray_set_at(DArray* darr, const size_t index, const void* data, const size_t data_size)
{
    assert_always(darr != NULL, "NULL object of type DArray was passed");
    assert_always(index < darr->length, "Index is out of bounds");
    assert_always(darr->data_size == data_size, "Incompatible data size");
    
    COPY_DATA_AT_INDEX(darr->arr, index, data, data_size);
}

void darray_add(DArray* darr, const void* data, const size_t data_size)
{
    assert_always(darr != NULL, "NULL object of type DArray was passed");
    assert_always(darr->data_size == data_size, "Incompatible data size");

    if (darr->length == darr->capacity)
        darray_expand(darr);

    COPY_DATA_AT_INDEX(darr->arr, darr->length, data, data_size);
    darr->length++;
}


