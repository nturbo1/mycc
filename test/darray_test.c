#include "nctest.h"
#include "darray.h"

#include <stddef.h>
#include <stdio.h>

#define VERIFY_DATA_AT_INDEX(darr, index, expected_data, data_size)\
    do {\
        const unsigned char* retrieved_data = (const unsigned char*) darray_get_at(darr, index);\
        for (size_t data_byte_i = 0; data_byte_i < data_size; data_byte_i++) {\
            ASSERT_TRUE(retrieved_data[data_byte_i] == expected_data[data_byte_i]);\
        }\
    } while(0)

TEST(testInitDArray, "GIVEN NULL DArray pointer, WHEN DArray init, THEN create a new DArray object and initialize it with proper data.")
{
    // GIVEN
    const size_t expected_capacity = 16;
    const size_t expected_data_size = 8;

    DArray* darr = init_darray(NULL, expected_capacity, expected_data_size);

    ASSERT_TRUE(darr != NULL);
    ASSERT_TRUE(darr->length == 0);
    ASSERT_TRUE(darr->capacity == expected_capacity);
    ASSERT_TRUE(darr->data_size == expected_data_size);
    ASSERT_TRUE(darr->arr != NULL);
}

TEST(testFreeInitializedDArray, "GIVEN initialized DArray object, WHEN free DArray, THEN properly free the resources.")
{
    DArray* darr = init_darray(NULL, 16, 8);
    ASSERT_TRUE(darr != NULL);
    free_darray(&darr);
    ASSERT_TRUE(darr == NULL);
}

TEST(testFreeNULLDArray, "Tests a NULL DArray object free")
{
    DArray* darr = NULL;
    free_darray(&darr);
}

TEST(testDArrayAdd, "GIVEN an initialized DArray object with 0 length, WHEN add a new element, THEN the copy of the data should exist in the array")
{
    // GIVEN
    size_t data_size = 8;
    size_t capacity = 16;
    DArray* darr = init_darray(NULL, capacity, data_size);
    ASSERT_TRUE(darr != NULL);
    unsigned char data[data_size];
    data[0] = 0x12;
    data[1] = 0x34;
    data[2] = 0xfd;
    data[3] = 0xfe;
    data[4] = 0xaf;
    data[5] = 0xae;
    data[6] = 0xef;
    data[7] = 0xfe;

    // WHEN
    darray_add(darr, data, sizeof(data));

    // THEN
    ASSERT_TRUE(darr->length == 1);
    ASSERT_TRUE(darr->capacity == capacity);

    const unsigned char* data_retrieved = (const unsigned char*) darray_get_at(darr, 0);
    for (size_t i = 0; i < data_size; i++) {
        ASSERT_TRUE(data[i] == data_retrieved[i]);
    }
}

TEST(test_multiple_DArray_add, "GIVEN a DArray object with 0 elements, WHEN add multiple elements, THEN each added element is placed in the array in the added order.")
{
    // GIVEN
    size_t data_size = 8;
    size_t capacity = 16;
    DArray* darr = init_darray(NULL, capacity, data_size);
    ASSERT_TRUE(darr != NULL);
    ASSERT_TRUE(darr->capacity == capacity);

    unsigned char data[data_size];
    data[0] = 0x12;
    data[1] = 0x34;
    data[2] = 0xfd;
    data[3] = 0xfe;
    data[4] = 0xaf;
    data[5] = 0xae;
    data[6] = 0xef;
    data[7] = 0xfe;

    // WHEN
    ASSERT_TRUE(darr->length == 0);
    darray_add(darr, data, sizeof(data));
    ASSERT_TRUE(darr->length == 1);
    darray_add(darr, data, sizeof(data));
    ASSERT_TRUE(darr->length == 2);
    darray_add(darr, data, sizeof(data));
    ASSERT_TRUE(darr->length == 3);
    darray_add(darr, data, sizeof(data));

    // THEN
    ASSERT_TRUE(darr->length == 4);
    ASSERT_TRUE(darr->capacity == capacity);

    for (size_t i = 0; i < darr->length; i++)
    {
        VERIFY_DATA_AT_INDEX(darr, i, data, data_size);
    }
}

TEST(test_expand_when_DArray_add, "GIVEN a DArray object with elements at full capacity, WHEN add a new element, THEN expand the capacity and copy the elements properly.")
{
    // GIVEN
    size_t data_size = 8;
    size_t initial_capacity = 4;
    size_t expected_capacity = 2 * initial_capacity;

    DArray* darr = init_darray(NULL, initial_capacity, data_size);
    ASSERT_TRUE(darr != NULL);
    ASSERT_TRUE(darr->capacity == initial_capacity);

    unsigned char data[data_size];
    data[0] = 18;
    data[1] = 52;
    data[2] = 253;
    data[3] = 254;
    data[4] = 175;
    data[5] = 174;
    data[6] = 239;
    data[7] = 45;

    darray_add(darr, data, sizeof(data));
    darray_add(darr, data, sizeof(data));
    darray_add(darr, data, sizeof(data));
    darray_add(darr, data, sizeof(data)); // now length == capacity

    // WHEN
    darray_add(darr, data, sizeof(data));

    // THEN
    ASSERT_TRUE(darr->length == 5);
    ASSERT_TRUE(darr->capacity == expected_capacity); // the array is expanded

    for (size_t i = 0; i < darr->length; i++)
    {
        VERIFY_DATA_AT_INDEX(darr, i, data, data_size);
    }
}
