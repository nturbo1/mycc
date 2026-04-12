#include "nctest.h"
#include "darray.h"

#include <stddef.h>
#include <stdio.h>

#define VERIFY_DATA_AT_INDEX(darr, index, expected_data, data_size)\
    do {\
        const unsigned char* retrieved_data = (const unsigned char*) darray_get_at(darr, index);\
        for (size_t data_byte_i = 0; data_byte_i < data_size; data_byte_i++) {\
            ASSERT_TRUE(expected_data[data_byte_i] == retrieved_data[data_byte_i]);\
        }\
    } while(0)

TEST(testInitDArray, "Tests a DArray object initialization")
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

TEST(testFreeInitializedDArray, "Tests an initialized DArray object free")
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

TEST(test_no_expand_when_DArray_add, "Test DArray add doesn't expand the array capacity when a new element added.")
{
    // GIVEN
    size_t data_size = 8;
    size_t expected_capacity = 16;
    DArray* darr = init_darray(NULL, expected_capacity, data_size);
    ASSERT_TRUE(darr != NULL);
    ASSERT_TRUE(darr->capacity == expected_capacity); // Before add
    unsigned char data[data_size];

    // WHEN
    darray_add(darr, data, sizeof(data));

    // THEN
    ASSERT_TRUE(darr->capacity == expected_capacity); // After add
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
    data[0] = 0x12;
    data[1] = 0x34;
    data[2] = 0xfd;
    data[3] = 0xfe;
    data[4] = 0xaf;
    data[5] = 0xae;
    data[6] = 0xef;
    data[7] = 0xfe;

    darray_add(darr, data, sizeof(data));
    darray_add(darr, data, sizeof(data));
    darray_add(darr, data, sizeof(data));
    darray_add(darr, data, sizeof(data)); // now length == capacity

    // WHEN
    darray_add(darr, data, sizeof(data));

    // THEN
    ASSERT_TRUE(darr->capacity == expected_capacity);
    for (size_t i = 0; i < initial_capacity; i++)
    {
        VERIFY_DATA_AT_INDEX(darr, i, data, data_size);
    }

    VERIFY_DATA_AT_INDEX(darr, initial_capacity, data, data_size);
}

TEST(testDArrayAdd, "Tests DArray add")
{
    // GIVEN
    size_t data_size = 8;
    DArray* darr = init_darray(NULL, 16, data_size);
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
    const unsigned char* data_retrieved = (const unsigned char*) darray_get_at(darr, 0);
    for (size_t i = 0; i < data_size; i++) {
        // ASSERT_TRUE(data[i] == data_retrieved[i]);
        printf("data[%zu] = %hhu\tdata_retrieved[%zu] = %hhu\n",
                i, data[i], i, data_retrieved[i]);
    }
}
