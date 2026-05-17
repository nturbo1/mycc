#ifndef SRC_PARSER_PARSER_H
#define SRC_PARSER_PARSER_H

#include "parser.h"
#include "token.h"
#include "scanner.h"
#include "ntassert.h"

#include <assert.h>
#include <stdlib.h>

// Skips all the tokens until the first occurrence of and including token ';' or the end of a file.
void skip_stmt(Parser* p)
{
    Token* tok = next_tok(p->scanner);
    while(tok != NULL || p->scanner->err != NO_ERROR) // == not the end of a file
    {
        if (tok != NULL && tok->type == TOKEN_TYPE_SEMICOLON)
            return;

        tok = next_tok(p->scanner);
    }
    // we reached the end of a file
}

static Decl* parseDecl(Parser* p)
{
    printf("IMPLEMENT parseDecl! p = %p\n", (void*) p);
    exit(1);
}

AstNode* parse_file(Parser* p)
{
    assert(p != NULL || "A NULL parser was passed while parsing a file!");
    p->scanner->err = NO_ERROR;
    Token* tok = next_tok(p->scanner);
    while (tok != NULL || p->scanner->err != NO_ERROR) // == not the end of a file
    {
        if (p->scanner->err != NO_ERROR)
        {
            ErrInfo* errinfo = new_errinfo(
                    p->scanner->err,
                    p->scanner->filepath,
                    p->scanner->ln_offset + 1,
                    p->scanner->col_offset + 1);

            darray_add(p->errs, errinfo, sizeof(errinfo));
            skip_stmt(p);
        }
        else
        {
            // TODO: FIX THE BELOW!!!
            parseDecl(p);
        }

        tok = next_tok(p->scanner);
    }

    // TODO: REMOVE THE BELOW!
    return NULL;
}

Parser* init_parser(Scanner* s)
{
    assert_always(s != NULL, "NULL scanner was passed to init_parser!");
    DArray* errs = init_darray(NULL, 0, sizeof(ErrInfo));

    Parser* p = (Parser*) malloc(sizeof(Parser));
    assert_always(p != NULL, "Failed to allocate memory for Parser!");
    p->scanner = s;
    p->errs = errs;

    return p;
}

#endif // SRC_PARSER_PARSER_H
