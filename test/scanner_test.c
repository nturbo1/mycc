#include "nctest.h"
#include "scanner.h"

// TEST(init_scanner,
//      "Should allocate memory with correct values when a NULL scanner and an existing file are passed")
// {
//     Scanner* s = NULL;
//     const char* filepath = "scanner_test.c";
//     s = init_scanner(s, filepath);
//
//     ASSERT_TRUE(s != NULL);
//     ASSERT_TRUE(s->file != NULL);
//     ASSERT_TRUE(s->bf_end == SCANNER_BUFFER_SIZE);
//     ASSERT_TRUE(s->next == 0);
//     ASSERT_TRUE(s->ln_offset == 0);
//     ASSERT_TRUE(s->col_offset == 0);
//
//     for ()
// }
