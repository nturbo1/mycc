#include "nctest.h"
#include "ntstring.h"

#include <stddef.h>
#include <stdio.h>

/* ================================================================================ */
/* ================================= String Tests ================================= */
/* ================================================================================ */

typedef struct
{
    const size_t char_size;
    const size_t bytes_size;
    const size_t length;
    const u8* bytes;
}
StringTestData;

#define TEST_SUCCESSFUL_NEW_STRING_CREATION_WITH_DIFF_PARAMS_AND_NULL_TERM_STR_LITS_TEST_DATA_SIZE 5
TEST(test_successful_new_string_creation_with_diff_params_and_null_term_str_lits,
     "Test a successful String object creation with different parameter values")
{
    // GIVEN
    const StringTestData test_data[
        TEST_SUCCESSFUL_NEW_STRING_CREATION_WITH_DIFF_PARAMS_AND_NULL_TERM_STR_LITS_TEST_DATA_SIZE
    ] = {
        // NULL-terminated strings
        {
            .char_size = 1,
            .bytes_size = 6,
            .bytes = (const u8[]){ 'H', 'e', 'l', 'l', 'o', 0x0 },
            .length = 5
        },
        {
            .char_size = 2,
            .bytes_size = 8,
            .bytes = (const u8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92, 0x0, 0x0 },
            .length = 3
        },
        {
            .char_size = 3,
            .bytes_size = 9,
            .bytes = (const u8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92, 0x0, 0x0, 0x0 },
            .length = 2
        },
        {
            .char_size = 4,
            .bytes_size = 16,
            .bytes = (const u8[]) {
                                    0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                    0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                    0x0, 0x0, 0x0, 0x0
                                  },
            .length = 3
        },
        {
            .char_size = 4,
            .bytes_size = 100,
            .bytes = (const u8[]) {
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
                                    0x0, 0x0, 0x0, 0x0
                                  },
            .length = 24
        },
    };

    // WHEN
    for (size_t tdata_idx = 0;
         tdata_idx < TEST_SUCCESSFUL_NEW_STRING_CREATION_WITH_DIFF_PARAMS_AND_NULL_TERM_STR_LITS_TEST_DATA_SIZE;
         tdata_idx++)
    {
        const size_t char_size = test_data[tdata_idx].char_size;
        const size_t str_bytes_size = test_data[tdata_idx].bytes_size;
        const u8* str_bytes = test_data[tdata_idx].bytes;
        const size_t length = test_data[tdata_idx].length;

        String* s = new_string(char_size, str_bytes_size, str_bytes);

        // THEN
        ASSERT_TRUE(s != NULL);
        ASSERT_TRUE(s->char_size == char_size);
        ASSERT_TRUE(s->length == length);
        ASSERT_TRUE(s->bytes != NULL);
        for (size_t sbytes_idx = 0; sbytes_idx < str_bytes_size - 1; sbytes_idx++)
            ASSERT_TRUE(s->bytes[sbytes_idx] == str_bytes[sbytes_idx]);
    }

    // TODO: clean up the memory
}

#define TEST_SUCCESSFUL_NEW_STRING_CREATION_WITH_DIFF_PARAMS_AND_NOT_NULL_TERM_STR_LITS_TEST_DATA_SIZE 5
TEST(test_successful_new_string_creation_with_diff_params_and_not_null_term_str_lits,
     "Test a successful String object creation with different parameter values")
{
    // GIVEN
    const StringTestData test_data[
        TEST_SUCCESSFUL_NEW_STRING_CREATION_WITH_DIFF_PARAMS_AND_NOT_NULL_TERM_STR_LITS_TEST_DATA_SIZE
    ] = {
        // NULL-terminated strings
        {
            .char_size = 1,
            .bytes_size = 5,
            .bytes = (const u8[]){ 'H', 'e', 'l', 'l', 'o' },
            .length = 5
        },
        {
            .char_size = 2,
            .bytes_size = 6,
            .bytes = (const u8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92 },
            .length = 3
        },
        {
            .char_size = 3,
            .bytes_size = 6,
            .bytes = (const u8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92 },
            .length = 2
        },
        {
            .char_size = 4,
            .bytes_size = 12,
            .bytes = (const u8[]) {
                                    0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                    0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32
                                  },
            .length = 3
        },
        {
            .char_size = 4,
            .bytes_size = 96,
            .bytes = (const u8[]) {
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
            .length = 24
        },
    };

    // WHEN
    for (size_t tdata_idx = 0;
         tdata_idx < TEST_SUCCESSFUL_NEW_STRING_CREATION_WITH_DIFF_PARAMS_AND_NOT_NULL_TERM_STR_LITS_TEST_DATA_SIZE;
         tdata_idx++)
    {
        const size_t char_size = test_data[tdata_idx].char_size;
        const size_t str_bytes_size = test_data[tdata_idx].bytes_size;
        const u8* str_bytes = test_data[tdata_idx].bytes;
        const size_t length = test_data[tdata_idx].length;

        String* s = new_string(char_size, str_bytes_size, str_bytes);

        // THEN
        ASSERT_TRUE(s != NULL);
        ASSERT_TRUE(s->char_size == char_size);
        ASSERT_TRUE(s->length == length);
        ASSERT_TRUE(s->bytes != NULL);
        for (size_t sbytes_idx = 0; sbytes_idx < str_bytes_size - 1; sbytes_idx++)
            ASSERT_TRUE(s->bytes[sbytes_idx] == str_bytes[sbytes_idx]);
    }

    // TODO: clean up the memory
}

/* ================================================================================ */
/* ============================= StringBuilder Tests ============================== */
/* ================================================================================ */

typedef struct
{
    const size_t char_size;
    const size_t bytes_size;
    const u8* const bytes;
    const size_t input_capacity;
    const size_t expected_capacity;
    const size_t length;
}
StringBuilderTestData;

#define TEST_SUCCESSFUL_NEW_STRING_BUILDER_CREATION_WITH_DIFFERENT_PARAMS_AND_NULL_TERM_STR_LITS_TEST_DATA_SIZE 5
TEST(test_successful_new_string_builder_creation_with_different_params_and_null_term_str_lits,
     "Test a successful StringBuilder object creation with different parameter values")
{
    // GIVEN
    const StringBuilderTestData test_data[
        TEST_SUCCESSFUL_NEW_STRING_BUILDER_CREATION_WITH_DIFFERENT_PARAMS_AND_NULL_TERM_STR_LITS_TEST_DATA_SIZE
    ] = {
        {
            .char_size = 1,
            .bytes_size = 6,
            .bytes = (const u8[]){ 'H', 'e', 'l', 'l', 'o', 0x0 },
            .length = 5,
            .input_capacity = 256,
            .expected_capacity = 256,

        },
        {
            .char_size = 2,
            .bytes_size = 8,
            .bytes = (const u8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92, 0x0, 0x0 },
            .length = 3,
            .input_capacity = 256,
            .expected_capacity = 256,

        },
        {
            .char_size = 3,
            .bytes_size = 9,
            .bytes = (const u8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92, 0x0, 0x0, 0x0 },
            .length = 2,
            .input_capacity = 256,
            .expected_capacity = 256,

        },
        {
            .char_size = 4,
            .bytes_size = 16,
            .bytes = (const u8[]) {
                                    0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                    0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32,
                                    0x0, 0x0, 0x0, 0x0
                                  },
            .length = 3,
            .input_capacity = 256,
            .expected_capacity = 256,

        },
        {
            .char_size = 4,
            .bytes_size = 100,
            .bytes = (const u8[]) {
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
                                    0x0, 0x0, 0x0, 0x0
                                  },
            .length = 24,
            .input_capacity = 12,
            .expected_capacity = 100,

        },
    };

    for (size_t tdata_idx = 0;
         tdata_idx < TEST_SUCCESSFUL_NEW_STRING_BUILDER_CREATION_WITH_DIFFERENT_PARAMS_AND_NULL_TERM_STR_LITS_TEST_DATA_SIZE;
         tdata_idx++)
    {
        const size_t char_size = test_data[tdata_idx].char_size;
        const size_t str_bytes_size = test_data[tdata_idx].bytes_size;
        const u8* str_bytes = test_data[tdata_idx].bytes;
        const size_t cap = test_data[tdata_idx].input_capacity;
        const size_t expected_cap = test_data[tdata_idx].expected_capacity;
        const size_t length = test_data[tdata_idx].length;

        // WHEN
        StringBuilder* sb = new_string_builder(char_size, str_bytes_size, (const u8*) str_bytes, cap);

        // THEN
        ASSERT_TRUE(sb != NULL);
        ASSERT_TRUE(sb->char_size == char_size);
        ASSERT_TRUE(sb->length == length);
        ASSERT_TRUE(sb->buf != NULL);
        ASSERT_TRUE(sb->capacity == expected_cap);
        for (size_t i = 0; i < str_bytes_size - 1; i++)
            ASSERT_TRUE(sb->buf[i] == str_bytes[i]);
    }

    // TODO: clean up the memory
}

#define TEST_SUCCESSFUL_NEW_STRING_BUILDER_CREATION_WITH_DIFFERENT_PARAMS_AND_NOT_NULL_TERM_STR_LITS_TEST_DATA_SIZE 5
TEST(test_successful_new_string_builder_creation_with_different_params_and_not_null_term_str_lits,
     "Test a successful StringBuilder object creation with different parameter values")
{
    // GIVEN
    const StringBuilderTestData test_data[
        TEST_SUCCESSFUL_NEW_STRING_BUILDER_CREATION_WITH_DIFFERENT_PARAMS_AND_NOT_NULL_TERM_STR_LITS_TEST_DATA_SIZE
    ] = {
        {
            .char_size = 1,
            .bytes_size = 5,
            .bytes = (const u8[]){ 'H', 'e', 'l', 'l', 'o' },
            .length = 5,
            .input_capacity = 256,
            .expected_capacity = 256,
        },
        {
            .char_size = 2,
            .bytes_size = 6,
            .bytes = (const u8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92 },
            .length = 3,
            .input_capacity = 256,
            .expected_capacity = 256,
        },
        {
            .char_size = 3,
            .bytes_size = 6,
            .bytes = (const u8[]){ 0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92 },
            .length = 2,
            .input_capacity = 256,
            .expected_capacity = 256,
        },
        {
            .char_size = 4,
            .bytes_size = 12,
            .bytes = (const u8[]) {
                                    0xC4, 0x80, 0xC4, 0x8C, 0xC4, 0x92,
                                    0x23, 0xF9, 0xE2, 0xA2, 0xFF, 0x32
                                  },
            .length = 3,
            .input_capacity = 256,
            .expected_capacity = 256,
        },
        {
            .char_size = 4,
            .bytes_size = 96,
            .bytes = (const u8[]) {
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
            .length = 24,
            .input_capacity = 12,
            .expected_capacity = 100, // including the appended NULL-terminator character
        },
    };

    for (size_t tdata_idx = 0;
         tdata_idx < TEST_SUCCESSFUL_NEW_STRING_BUILDER_CREATION_WITH_DIFFERENT_PARAMS_AND_NOT_NULL_TERM_STR_LITS_TEST_DATA_SIZE;
         tdata_idx++)
    {
        const size_t char_size = test_data[tdata_idx].char_size;
        const size_t str_bytes_size = test_data[tdata_idx].bytes_size;
        const u8* str_bytes = test_data[tdata_idx].bytes;
        const size_t cap = test_data[tdata_idx].input_capacity;
        const size_t expected_cap = test_data[tdata_idx].expected_capacity;
        const size_t length = test_data[tdata_idx].length;

        // WHEN
        StringBuilder* sb = new_string_builder(char_size, str_bytes_size, (const u8*) str_bytes, cap);

        // THEN
        ASSERT_TRUE(sb != NULL);
        ASSERT_TRUE(sb->char_size == char_size);
        ASSERT_TRUE(sb->length == length);
        ASSERT_TRUE(sb->buf != NULL);
        ASSERT_TRUE(sb->capacity == expected_cap);
        ASSERT_TRUE(sb->buf[str_bytes_size] == 0); // NULL-terminator is added at the end
        for (size_t i = 0; i < str_bytes_size - 1; i++)
            ASSERT_TRUE(sb->buf[i] == str_bytes[i]);
    }

    // TODO: clean up the memory
}
