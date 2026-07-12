#include "nctest.h"
#include "ntstring.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* ================================================================================ */
/* ============================= StringBuilder Tests ============================== */
/* ================================================================================ */

typedef struct
{
    const U8* const input_bytes;
    const size_t input_bytes_size;
    const size_t input_capacity;

    const size_t expected_length;
    const size_t expected_capacity;
}
StringBuilderTestData;

#define TEST_SUCCESSFUL_NEW_STRING_TEST_DATA_SIZE 10
TEST(test_successful_new_string_builder,
     "Test a successful StringBuilder object creation with different parameter values")
{
    // GIVEN
    const StringBuilderTestData test_data[
       TEST_SUCCESSFUL_NEW_STRING_TEST_DATA_SIZE 
    ] = {
        // NULL-terminated string bytes
        {
            .input_bytes = (const U8[]){ 'H', 'e', 'l', 'l', 'o', 0x0 },
            .input_bytes_size = 6,
            .input_capacity = 256,
            .expected_length = 5,
            .expected_capacity = 256,
        },
        {
            .input_bytes = (const U8[]){ 'H', 'e', 'l', 'l', 'o', 0x0 },
            .input_bytes_size = 6,
            .input_capacity = 3,
            .expected_length = 5,
            .expected_capacity = 6,
        },
        {
            .input_bytes = (const U8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92, 0x0, 0x0, 0x94, 0x21 },
            .input_bytes_size = 10,
            .input_capacity = 256,
            .expected_length = 6,
            .expected_capacity = 256,
        },
        {
            .input_bytes = (const U8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92, 0x0, 0x0, 0x94, 0x21 },
            .input_bytes_size = 10,
            .input_capacity = 2,
            .expected_length = 6,
            .expected_capacity = 7,
        },
        {
            .input_bytes = (const U8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92, 0x0, 0x0, 0x0 },
            .input_bytes_size = 9,
            .input_capacity = 256,
            .expected_length = 6,
            .expected_capacity = 256,
        },
        {
            .input_bytes = (const U8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92, 0x0, 0x0, 0x0, 0x0, 0x0 },
            .input_bytes_size = 11,
            .input_capacity = 9,
            .expected_length = 6,
            .expected_capacity = 9,
        },
        {
            .input_bytes = (const U8[]) {
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
                                        },
            .input_bytes_size = 102,
            .input_capacity = 36,
            .expected_length = 96,
            .expected_capacity = 97,
        },

        // NOT NULL-terminated string bytes
        {
            .input_bytes = (const U8[]){ 'H', 'e', 'l', 'l', 'o' },
            .input_bytes_size = 5,
            .input_capacity = 256,
            .expected_length = 5,
            .expected_capacity = 256,
        },
        {
            .input_bytes = (const U8[]){ 'H', 'e', 'l', 'l', 'o' },
            .input_bytes_size = 5,
            .input_capacity = 2,
            .expected_length = 5,
            .expected_capacity = 6,
        },
        {
            .input_bytes = (const U8[]) {
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                            0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                            0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32
                                        },
            .input_bytes_size = 96,
            .input_capacity = 17,
            .expected_length = 96,
            .expected_capacity = 97,
        },
    };

    for (size_t tdata_idx = 0;
         tdata_idx < TEST_SUCCESSFUL_NEW_STRING_TEST_DATA_SIZE;
         tdata_idx++)
    {
        const size_t input_bytes_size = test_data[tdata_idx].input_bytes_size;
        const U8* input_bytes = test_data[tdata_idx].input_bytes;
        const size_t input_cap = test_data[tdata_idx].input_capacity;
        const size_t expected_length = test_data[tdata_idx].expected_length;
        const size_t expected_cap = test_data[tdata_idx].expected_capacity;

        // WHEN
        StringBuilder* sb = new_string_builder(input_bytes, input_bytes_size, input_cap);

        // THEN
        ASSERT_TRUE(sb != NULL);
        ASSERT_TRUE(sb->length == expected_length);
        ASSERT_TRUE(sb->buf != NULL);
        ASSERT_TRUE(sb->capacity == expected_cap);
        for (size_t i = 0; i < expected_length - 1; i++)
            ASSERT_TRUE(sb->buf[i] == input_bytes[i]);
        ASSERT_TRUE(sb->buf[expected_length] == 0);
    }

    // TODO: clean up the memory
}

TEST(test_successful_sb_str_bytes, "Tests successful sb_str_bytes function return cases")
{
    // GIVEN
    const StringBuilderTestData test_data = {
        .input_bytes = (const U8[]){ 'H', 'e', 'l', 'l', 'o', 0x0 },
        .input_bytes_size = 6,
        .input_capacity = 256,
        .expected_length = 5,
        .expected_capacity = 256,
    };
    const StringBuilder* sb = new_string_builder(test_data.input_bytes,
                                           test_data.input_bytes_size,
                                           test_data.input_capacity);
    ASSERT_TRUE(sb != NULL);

    // WHEN
    const U8* str_bytes = sb_str_bytes(sb);

    // THEN
    ASSERT_TRUE(str_bytes != NULL);
    ASSERT_TRUE(str_bytes != sb->buf); // ensure the returned bytes are copies
    for (size_t i = 0; i < sb->length; i++)
        ASSERT_TRUE(str_bytes[i] == sb->buf[i]); // ensure the bytes are copied correctly
    ASSERT_TRUE(str_bytes[sb->length] == 0); // ensure the returned string bytes are NULL-terminated

    // Clean-up
    free((U8*) str_bytes);
    str_bytes = NULL;
    // TODO: clean up the StringBuilder object
}
