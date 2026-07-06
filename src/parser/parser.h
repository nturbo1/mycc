#ifndef SRC_PARSER_PARSE_H
#define SRC_PARSER_PARSE_H

#include "ast.h"
#include "scanner.h"
#include "util_inc.h"
#include "error.h"
#include "token.h"

typedef struct {
    Scanner* scanner;

    // DArray<Error>
    DArray* errs; // A list of errors encountered during parsing and scanning

    Token* next_tok; // one token look-ahead
} Parser;

Parser* init_parser(Scanner* s);

AstFile* parse_file(Parser* p);

#endif // SRC_PARSER_PARSE_H
