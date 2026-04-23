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

TEST(scan_number_literals,
    "GIVEN tokens of numbers with different bases and formats, "
    "WHEN scan the tokens in a file, "
    "THEN return correct Token values.")
{
    const char* tmp_filepath = "test/input/scanner/tmp_numbers.txt";
    FILE* tmp_file = fopen(tmp_filepath, "w");
    ASSERT_TRUE(tmp_file != NULL);

    const size_t test_data_size = 1;
    const char* nums_txt[test_data_size];
    const Token num_tokens[test_data_size];

#define INIT_NUM_TOKENS_TEST_DATA(index, num_txt, exp_tok)\
    do {\
        *(char**) &nums_txt[(index)] = (num_txt);\
        Token* tk_data = (Token*) (num_tokens + (index));\
        *(char**)&tk_data->val = (char*)(exp_tok).val;\
        *(size_t*)&tk_data->length = (size_t)(exp_tok).length;\
        *(TokenType*)&tk_data->type = (TokenType)(exp_tok).type;\
    } while(0)

    // Initialize test data
    Token tk0 = {
        .val = (const char*) (intptr_t) 69,
        .length = 1,
        .type = TOKEN_TYPE_INT_LIT
        // THE REST OF THE FIELDS ARE NOT IMPORTANT FOR THIS TEST CASE, SO THEY'RE NOT SET AND TESTED!
    };
    INIT_NUM_TOKENS_TEST_DATA(0, "69", tk0);

    // Put the test numbers text to the temporary file to be scanned later.
    for (size_t i = 0; i < test_data_size; i++)
    {
        ASSERT_TRUE(fprintf(tmp_file, "%s ", nums_txt[i]) > -1);
    }
    fflush(tmp_file);

    Scanner* s = init_scanner(NULL, tmp_filepath);
    ASSERT_TRUE(s != NULL);

    for (size_t i = 0; i < test_data_size; i++)
    {
        Token* t = next_tok(s);
        ASSERT_TRUE(t != NULL);
        Token exp_t = num_tokens[i];
        ASSERT_TRUE(exp_t.val == t->val);
        ASSERT_TRUE(exp_t.length == t->length);
        ASSERT_TRUE(exp_t.type == t->type);
    }

    // Clean up
    ASSERT_TRUE(remove(tmp_filepath) > -1);
    fclose(tmp_file);
}
