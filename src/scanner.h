#ifndef SRC_LEXER_H
#define SRC_LEXER_H

#include "token.h"

#include <stdio.h>
#include <stddef.h>

#define SCANNER_BUFFER_SIZE 8192

typedef enum {
    PP_MODE,    // Pre-processor mode
    C_MODE      // C source code mode
} ScannerMode;

typedef struct {
    FILE* file;
    // Contains 2 buffers:  Buffer 0              Buffer 1
    //                     [ | | | ... | | | |   | |   | ... | | |    ]
    //                      0 1 2 ........... n-1 n n+1 ......... 2n-1
    char src[2 * SCANNER_BUFFER_SIZE];
    size_t bf_end;      // end of the current buffer being processed
    size_t next;        // the next character index in the src buffer
    size_t ln_offset;
    size_t col_offset; 
    ScannerMode mode;
} Scanner;

Token next_tok(Scanner* s);

// Initializes a new scanner with correct initial values and opens a src file with a given filepath.
// If a given Scanner* s parameter is NULL, it will allocate a new memory for a new scanner and returns
// the new pointer. Otherwise, it just resets the data pointed by the given scanner pointer.
//
// It will exit in case of any IO or memory error.
Scanner* init_scanner(Scanner* s, const char* filepath);

#endif
