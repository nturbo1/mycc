#ifndef SRC_INCLUDE_SCANNER_H
#define SRC_INCLUDE_SCANNER_H

#include "token.h"
#include "error.h"
#include "util_inc.h"

#include <stdio.h>
#include <stddef.h>

#define SCANNER_BUFFER_SIZE 8192
#define MAX_IDENTIFIER_NAME_SIZE 256

typedef struct {
    FILE* file;
    const char* filepath;
    // Contains 2 buffers:  Buffer 0              Buffer 1
    //                     [ | | | ... | | | |   | |   | ... | | |    ]
    //                      0 1 2 ........... n-1 n n+1 ......... 2n-1
    char src[2 * SCANNER_BUFFER_SIZE];
    size_t bf_end;      // end of the current buffer being processed
    size_t next;        // the next character index in the src buffer
    size_t ln_offset;
    size_t col_offset; 
    HashTable* keywords;    // of type HashTable<const char*, TokenType>
                            // IMPORTANT!!!: Values shouldn't be dereferenced or freed because
                            // they don't store memory addresses, rather TokenType enum values.

    ErrorType err;          // The first encountered lexer/scanner error.
} Scanner;

// Scans the next token in the src given by a scanner and returns a valid token.
//
// If there is a lexical error, it sets `s->err` to the appropriate `ErrorType`
// and returns `NULL`.
//
// If the end of the file is reached before a valid token scanning completion,
// then it returns `NULL` and sets `s->err` to `EOF_ERROR_TYPE`.
Token* next_tok(Scanner* s);

// Initializes a new scanner with correct initial values and opens a src file with a given filepath.
// If a given Scanner* s parameter is NULL, it will allocate a new memory for a new scanner and returns
// the new pointer. Otherwise, it just resets the data pointed by the given scanner pointer.
//
// It will exit in case of any IO or memory error.
Scanner* init_scanner(Scanner* s, const char* filepath);

char next_char(Scanner* s);
char peek_next(Scanner* s);
bool is_whitespace(char ch);
bool is_alpha(char ch);
bool is_alnum(char ch);
void skip_whitespace(Scanner* s);

#endif // SRC_INCLUDE_SCANNER_H
