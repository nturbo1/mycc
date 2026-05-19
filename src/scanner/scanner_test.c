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
    ASSERT_TRUE(s->err == NO_ERROR_TYPE);

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

    [21] = { 0, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [22] = { 0, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [23] = { 0, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [24] = { 0, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [25] = { 0, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [26] = { 0, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [27] = { 1, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [28] = { 1, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [29] = { 1, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [30] = { 1, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [31] = { 1, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [32] = { 1, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [33] = { 2, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [34] = { 2, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [35] = { 2, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [36] = { 2, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [37] = { 2, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [38] = { 2, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [39] = { 3, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [40] = { 3, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [41] = { 3, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [42] = { 3, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [43] = { 3, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [44] = { 3, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [45] = { 4, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [46] = { 4, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [47] = { 4, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [48] = { 4, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [49] = { 4, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [50] = { 4, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [51] = { 5, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [52] = { 5, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [53] = { 5, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [54] = { 5, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [55] = { 5, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [56] = { 5, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [57] = { 6, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [58] = { 6, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [59] = { 6, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [60] = { 6, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [61] = { 6, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [62] = { 6, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [63] = { 7, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [64] = { 7, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [65] = { 7, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [66] = { 7, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [67] = { 7, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [68] = { 7, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [69] = { 8, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [70] = { 8, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [71] = { 8, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [72] = { 8, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [73] = { 8, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [74] = { 8, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [75] = { 9, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [76] = { 9, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [77] = { 9, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [78] = { 9, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [79] = { 9, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [80] = { 9, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [81] = { 10, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [82] = { 10, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [83] = { 10, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [84] = { 10, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [85] = { 10, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [86] = { 10, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [87] = { 69, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [88] = { 69, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [89] = { 69, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [90] = { 69, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [91] = { 69, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [92] = { 69, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [93] = { 234322, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [94] = { 234322, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [95] = { 234322, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [96] = { 234322, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [97] = { 234322, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [98] = { 234322, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [99] = { 9092123, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [100] = { 9092123, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [101] = { 9092123, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [102] = { 9092123, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [103] = { 9092123, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [104] = { 9092123, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [105] = { 18, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [106] = { 18, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [107] = { 18, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [108] = { 18, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [109] = { 18, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [110] = { 18, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [111] = { 805, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [112] = { 805, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [113] = { 805, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [114] = { 805, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [115] = { 805, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [116] = { 805, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [117] = { 65429, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [118] = { 65429, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [119] = { 65429, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [120] = { 65429, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [121] = { 65429, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [122] = { 65429, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [123] = { 708079, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [124] = { 708079, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [125] = { 708079, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [126] = { 708079, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [127] = { 708079, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [128] = { 708079, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [129] = { 32, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [130] = { 32, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [131] = { 32, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [132] = { 32, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [133] = { 32, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [134] = { 32, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },

    [135] = { 29, 0.0, 0, TOKEN_TYPE_INT_LIT, L_SUFF },
    [136] = { 29, 0.0, 0, TOKEN_TYPE_INT_LIT, LL_SUFF },
    [137] = { 29, 0.0, 0, TOKEN_TYPE_INT_LIT, U_SUFF },
    [138] = { 29, 0.0, 0, TOKEN_TYPE_INT_LIT, UL_SUFF },
    [139] = { 29, 0.0, 0, TOKEN_TYPE_INT_LIT, ULL_SUFF },
    [140] = { 29, 0.0, 0, TOKEN_TYPE_INT_LIT, F_SUFF },
};

static const ScanNumberLiteralsTestData scan_number_literals_test_data = {
    .size = 117,
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

        // Decimals with suffixes
        [45] = "0L",
        [46] = "1L",
        [47] = "2L",
        [48] = "3L",
        [49] = "4L",
        [50] = "5l",
        [51] = "6L",
        [52] = "7l",
        [53] = "8l",
        [54] = "9l",
        [55] = "10L",
        [56] = "69l",
        [57] = "234322ll",
        [58] = "234322Ll",
        [59] = "234322lL",
        [60] = "9092123LL",
        [61] = "9092123LLU",
        [62] = "9092123llU",
        [63] = "9092123LlU",
        [64] = "9092123lLU",
        [65] = "9092123ulL",
        [66] = "9092123ULL",
        [67] = "9092123uLL",
        [68] = "9092123u",
        [69] = "9092123U",
        [70] = "9092123Ul",
        [71] = "9092123uL",
        [72] = "9092123UL",

        // Hexadecimals with suffixes
        [73] = "0x12l",      // == 18
        [74] = "0x325L",     // == 805
        [75] = "0xff95u",    // == 65429
        [76] = "0xFF95U",    // == 65429
        [77] = "0x0ll",       // == 0
        [78] = "0x1lL",       // == 1
        [79] = "0x2Ll",       // == 2
        [80] = "0x9LL",       // == 9
        [81] = "0xacdeful",   // == 708079
        [82] = "0xaCdEFuL",   // == 708079
        [83] = "0x8ABC1Bull",   // == 9092123
        [84] = "0x8abC1BuLL",   // == 9092123
        [85] = "0x39352ULL",   // == 234322
        [86] = "0x39352LLU",   // == 234322
        [87] = "0x39352llu",   // == 234322
        [88] = "0x39352lLu",   // == 234322

        // Binary integers with suffixes
        [89] = "0b0L",                   // == 0
        [90] = "0b00000l",               // == 0
        [91] = "0b1LL",                   // == 1
        [92] = "0b00000001ll",            // == 1
        [93] = "0b100000lL",              // == 32
        [94] = "0b011101u",              // == 29
        [95] = "0b111001001101010010U",  // 234322
        [96] = "0B111001001101010010ul",  // 234322
        [97] = "0B111001001101010010Ul",  // 234322
        [98] = "0B111001001101010010UL",  // 234322
        [99] = "0B111001001101010010ULL",  // 234322
        [100] = "0B111001001101010010uLl",  // 234322
        [101] = "0B111001001101010010LLU",  // 234322
        [102] = "0B111001001101010010lLU",  // 234322

        // Octadecimal with suffixes
        [103] = "00l",        // == 0
        [104] = "01L",        // == 1
        [105] = "02u",        // == 2
        [106] = "03U",        // == 3
        [107] = "04ll",        // == 4
        [108] = "05LL",        // == 5
        [109] = "06lL",        // == 6
        [110] = "07ul",        // == 7
        [111] = "0711522uL",    // == 234322
        [112] = "042536033ulL",  // == 9092123
        [113] = "042536033llu",  // == 9092123
        [114] = "042536033Llu",  // == 9092123
        [115] = "042536033LLU",  // == 9092123
        [116] = "042536033ULL",  // == 9092123
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

        // Decimals with suffixes
        [45] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[21] },
        [46] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[27] },
        [47] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[33] },
        [48] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[39] },
        [49] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[45] },
        [50] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[51] },
        [51] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[57] },
        [52] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[63] },
        [53] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[69] },
        [54] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[75] },
        [55] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[81] },
        [56] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[87] },
        [57] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[94] },
        [58] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[94] },
        [59] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[94] },
        [60] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[100] },
        [61] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [62] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [63] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [64] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [65] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [66] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [67] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [68] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[101] },
        [69] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[101] },
        [70] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[102] },
        [71] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[102] },
        [72] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[102] },

        // Hexadecimals with suffixes
        [73] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[105] },
        [74] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[111] },
        [75] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[119] },
        [76] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[119] },
        [77] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[22] },
        [78] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[28] },
        [79] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[34] },
        [80] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[76] },
        [81] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[126] },
        [82] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[126] },
        [83] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [84] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [85] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[97] },
        [86] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[97] },
        [87] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[97] },
        [88] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[97] },

        // Binary integers with suffixes
        [89] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[21] },
        [90] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[21] },
        [91] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[28] },
        [92] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[28] },
        [93] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[130] },
        [94] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[137] },
        [95] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[95] },
        [96] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[96] },
        [97] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[96] },
        [98] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[96] },
        [99] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[97] },
        [100] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[97] },
        [101] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[97] },
        [102] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[97] },

        // Octadecimal with suffixes
        [103] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[21] },
        [104] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[27] },
        [105] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[35] },
        [106] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[41] },
        [107] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[46] },
        [108] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[52] },
        [109] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[58] },
        [110] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[66] },
        [111] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[96] },
        [112] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [113] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [114] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [115] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
        [116] = { .type = TOKEN_TYPE_INT_LIT, .number = &numbers[103] },
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
