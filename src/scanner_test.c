#include "nctest.h"
#include "scanner.h"
#include "error.h"
#include "token.h"

#include <string.h>
#include <stdio.h>
#include <stddef.h>

TEST(init_scanner,
     "GIVEN a NULL scanner passed to init_scanner with a valid filepath, "
     "WHEN init_scanner, "
     "THEN initialize a scanner fields with correct values.")
{
    Scanner* s = NULL;
    const char* filepath = "src/scanner_test.c";
    s = init_scanner(s, filepath);

    ASSERT_TRUE(s != NULL);
    ASSERT_TRUE(s->file != NULL);
    ASSERT_TRUE(s->bf_end == SCANNER_BUFFER_SIZE);
    ASSERT_TRUE(s->next == 0);
    ASSERT_TRUE(s->ln_offset == 0);
    ASSERT_TRUE(s->col_offset == 0);
    ASSERT_TRUE(s->keywords != NULL);
    ASSERT_TRUE(strncmp(s->filepath, filepath, strlen(filepath)) == 0);
    ASSERT_TRUE(s->err == NO_ERROR);

    fclose(s->file);
}

typedef struct {
    const size_t size;
    const char *const *const nums_txt;
    const Token *const num_tokens;
} ScanNumberLiteralsTestData;

static const ScanNumberLiteralsTestData scan_number_literals_test_data = {
    .size = 35,
    .nums_txt = (const char *const[]) {
        // Decimals
        [0] = "0",
        [1] = "1",
        [2] = "2",
        [3] = "3",
        [4] = "4",
        [5] = "5",
        [6] = "6",
        [7] = "7",
        [8] = "8",
        [9] = "9",
        [10] = "10",
        [11] = "69",
        [12] = "234322",
        [13] = "9092123",

        // Hexadecimals
        [14] = "0x12",      // == 18
        [15] = "0x325",     // == 805
        [16] = "0xff95",    // == 65429
        [17] = "0xFF95",    // == 65429
        [18] = "0x0",       // == 0
        [19] = "0x1",       // == 1
        [20] = "0x2",       // == 2
        [21] = "0x9",       // == 9
        [22] = "0xacdef",   // == 708079
        [23] = "0xaCdEF",   // == 708079
        [24] = "0x8ABC1B",   // == 9092123
        [25] = "0x8abC1B",   // == 9092123
        [26] = "0x39352",   // == 234322

        // Binary integers
        [27] = "0b0",                   // == 0
        [28] = "0b00000",               // == 0
        [29] = "0b1",                   // == 1
        [30] = "0b00000001",            // == 1
        [31] = "0b100000",              // == 32
        [32] = "0b011101",              // == 29
        [33] = "0b111001001101010010",  // 234322
        [34] = "0B111001001101010010"   // 234322
    },
    .num_tokens = (const Token[]) {
        // Decimals
        [0] = {
            .val = (const char*) (intptr_t) 0,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [1] = {
            .val = (const char*) (intptr_t) 1,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [2] = {
            .val = (const char*) (intptr_t) 2,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [3] = {
            .val = (const char*) (intptr_t) 3,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [4] = {
            .val = (const char*) (intptr_t) 4,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [5] = {
            .val = (const char*) (intptr_t) 5,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [6] = {
            .val = (const char*) (intptr_t) 6,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [7] = {
            .val = (const char*) (intptr_t) 7,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [8] = {
            .val = (const char*) (intptr_t) 8,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [9] = {
            .val = (const char*) (intptr_t) 9,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [10] = {
            .val = (const char*) (intptr_t) 10,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [11] = {
            .val = (const char*) (intptr_t) 69,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [12] = {
            .val = (const char*) (intptr_t) 234322,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [13] = {
            .val = (const char*) (intptr_t) 9092123,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },

        // Hexadecimals
        [14] = {
            .val = (const char*) (intptr_t) 18,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [15] = {
            .val = (const char*) (intptr_t) 805,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [16] = {
            .val = (const char*) (intptr_t) 65429,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [17] = {
            .val = (const char*) (intptr_t) 65429,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [18] = {
            .val = (const char*) (intptr_t) 0,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [19] = {
            .val = (const char*) (intptr_t) 1,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [20] = {
            .val = (const char*) (intptr_t) 2,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [21] = {
            .val = (const char*) (intptr_t) 9,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [22] = {
            .val = (const char*) (intptr_t) 708079,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [23] = {
            .val = (const char*) (intptr_t) 708079,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [24] = {
            .val = (const char*) (intptr_t) 9092123,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [25] = {
            .val = (const char*) (intptr_t) 9092123,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [26] = {
            .val = (const char*) (intptr_t) 234322,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },

        // Binary integers
        [27] = {
            .val = (const char*) (intptr_t) 0,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [28] = {
            .val = (const char*) (intptr_t) 0,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [29] = {
            .val = (const char*) (intptr_t) 1,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [30] = {
            .val = (const char*) (intptr_t) 1,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [31] = {
            .val = (const char*) (intptr_t) 32,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [32] = {
            .val = (const char*) (intptr_t) 29,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [33] = {
            .val = (const char*) (intptr_t) 234322,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
        [34] = {
            .val = (const char*) (intptr_t) 234322,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
        },
    }
};

TEST(scan_number_literals,
    "GIVEN tokens of numbers with different bases and formats, "
    "WHEN scan the tokens in a file, "
    "THEN return correct Token values.")
{
    const char* tmp_filepath = "test/input/scanner/tmp_numbers.txt";
    FILE* tmp_file = fopen(tmp_filepath, "w");
    ASSERT_TRUE(tmp_file != NULL);

    // Put the test numbers text to the temporary file to be scanned later.
    for (size_t i = 0; i < scan_number_literals_test_data.size; i++)
    {
        ASSERT_TRUE(fprintf(tmp_file, "%s ", scan_number_literals_test_data.nums_txt[i]) > -1);
    }
    fflush(tmp_file);

    Scanner* s = init_scanner(NULL, tmp_filepath);
    ASSERT_TRUE(s != NULL);

    for (size_t i = 0; i < scan_number_literals_test_data.size; i++)
    {
        Token* t = next_tok(s);
        ASSERT_TRUE(t != NULL);
        Token exp_t = scan_number_literals_test_data.num_tokens[i];
        ASSERT_TRUE(exp_t.val == t->val);
        ASSERT_TRUE(exp_t.length == t->length);
        ASSERT_TRUE(exp_t.type == t->type);
    }

    // Clean up
    ASSERT_TRUE(remove(tmp_filepath) > -1);
    fclose(tmp_file);
}
