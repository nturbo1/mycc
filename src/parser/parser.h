#ifndef SRC_PARSER_PARSE_H
#define SRC_PARSER_PARSE_H

#include "ast.h"
#include "scanner.h"
#include "darray.h"
#include "error.h"

typedef struct {
    Scanner* scanner;

    // DArray<ErrInfo>
    DArray* errs;       // A list of errors encountered during parsing and scanning
} Parser;

Parser* init_parser(Scanner* s);

AstFile* parse_file(Parser* p);

#endif // SRC_PARSER_PARSE_H
