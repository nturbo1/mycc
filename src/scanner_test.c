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
    .size = 14,
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
    },
    .num_tokens = (const Token[]) {
        [0] = {
            .val = (const char*) (intptr_t) 0,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [1] = {
            .val = (const char*) (intptr_t) 1,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [2] = {
            .val = (const char*) (intptr_t) 2,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [3] = {
            .val = (const char*) (intptr_t) 3,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [4] = {
            .val = (const char*) (intptr_t) 4,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [5] = {
            .val = (const char*) (intptr_t) 5,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [6] = {
            .val = (const char*) (intptr_t) 6,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [7] = {
            .val = (const char*) (intptr_t) 7,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [8] = {
            .val = (const char*) (intptr_t) 8,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [9] = {
            .val = (const char*) (intptr_t) 9,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [10] = {
            .val = (const char*) (intptr_t) 10,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [11] = {
            .val = (const char*) (intptr_t) 69,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [12] = {
            .val = (const char*) (intptr_t) 234322,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        },
        [13] = {
            .val = (const char*) (intptr_t) 9092123,
            .length = 1,
            .type = TOKEN_TYPE_INT_LIT
            // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE,
            // SO THEY'RE NOT SET AND TESTED!
        }
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
