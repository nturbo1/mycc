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
    const char* filepath = "src/scanner/scanner_test.c";
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

const Number numbers[] = {
    [0] = { 0, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [1] = { 1, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [2] = { 2, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [3] = { 3, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [4] = { 4, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [5] = { 5, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [6] = { 6, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [7] = { 7, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [8] = { 8, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [9] = { 9, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [10] = { 10, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [11] = { 69, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [12] = { 234322, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [13] = { 9092123, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [14] = { 18, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [15] = { 805, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [16] = { 65429, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [17] = { 708079, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [18] = { 32, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
    [19] = { 29, 0.0, 0, TOKEN_TYPE_INT_LIT, NO_SUFF },
};

static const ScanNumberLiteralsTestData scan_number_literals_test_data = {
    .size = 45,
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
        [34] = "0B111001001101010010",  // 234322

        // Octadecimal
        [35] = "00",        // == 0
        [36] = "01",        // == 1
        [37] = "02",        // == 2
        [38] = "03",        // == 3
        [39] = "04",        // == 4
        [40] = "05",        // == 5
        [41] = "06",        // == 6
        [42] = "07",        // == 7
        [43] = "0711522",    // == 234322
        [44] = "042536033",  // == 9092123
    },
    .num_tokens = (const Token[]) {
        // Decimals
        [0] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[0] },
        [1] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[1] },
        [2] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[2] },
        [3] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[3] },
        [4] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[4] },
        [5] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[5] },
        [6] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[6] },
        [7] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[7] },
        [8] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[8] },
        [9] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[9] },
        [10] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[10] },
        [11] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[11] },
        [12] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[12] },
        [13] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[13] },

        // Hexadecimals
        [14] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[14] },
        [15] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[15] },
        [16] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[16] },
        [17] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[16] },
        [18] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[0] },
        [19] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[1] },
        [20] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[2] },
        [21] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[9] },
        [22] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[17] },
        [23] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[17] },
        [24] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[13] },
        [25] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[13] },
        [26] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[12]},

        // Binary integers
        [27] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[0] },
        [28] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[0] },
        [29] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[1] },
        [30] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[1] },
        [31] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[18] },
        [32] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[19] },
        [33] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[12] },
        [34] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[12] },

        // Octadecimal
        [35] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[0] },
        [36] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[1] },
        [37] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[2] },
        [38] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[3] },
        [39] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[4] },
        [40] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[5] },
        [41] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[6] },
        [42] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[7] },
        [43] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[12] },
        [44] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[13] },
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
        ASSERT_TRUE(exp_t.type == exp_t.number->type); // Make sure the test data is itself correct

        ASSERT_TRUE(exp_t.type == t->type);
        ASSERT_TRUE(exp_t.number->integral == t->number->integral);
        ASSERT_TRUE(exp_t.number->fractional == t->number->fractional);
        ASSERT_TRUE(exp_t.number->exponent == t->number->exponent);
        ASSERT_TRUE(exp_t.number->type == t->number->type);
        ASSERT_TRUE(exp_t.number->suff == t->number->suff);
    }

    // Clean up
    ASSERT_TRUE(remove(tmp_filepath) > -1);
    fclose(tmp_file);
}
