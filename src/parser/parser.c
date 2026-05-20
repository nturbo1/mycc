#include "parser.h"
#include "token.h"
#include "scanner.h"
#include "ntassert.h"

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>

// Skips all the tokens until the first occurrence of and including token ';' or the end of a file.
void skip_stmt(Parser* p)
{
    Token* tok = next_tok(p->scanner);
    while(tok != NULL || p->scanner->err != NO_ERROR_TYPE) // == not the end of a file
    {
        if (tok != NULL && tok->type == TOKEN_TYPE_SEMICOLON)
            return;

        tok = next_tok(p->scanner);
    }
    // we reached the end of a file
}

// static Stmt* parse_stmt(Parser* p)
// {
//     assert(p != NULL && "NULL parser was passed to `parse_decl` function!");
//     return NULL;
// }

// Parses the next declaration in a file.
//
// Returns `NULL` if there is no declaration or the declaration is invalid.
static Decl* parse_decl(Parser* p)
{
    assert(p != NULL && "NULL parser was passed to `parse_decl` function!");
    // Token* tok = peek_next(p->scanner);
    return NULL;
}

// Parses a single file and returns an `AstFile` type instance that contains
// a parsed AST for the file.
//
// Returns NULL if there is no valid declaration in the file or the file is
// empty.
//
// It appends scanner and/or parser errors to a list of errors of a given
// `Parser` object while parsing.
AstFile* parse_file(Parser* p)
{
    assert(p != NULL && "A NULL parser was passed while parsing a file!");

    Decl* decl = parse_decl(p);
    if (decl == NULL)
        return NULL; // No valid declaration in a file or the file is empty

    DArray* decls = init_darray(NULL, 0, sizeof(Decl));

    while (decl != NULL)
    {
        darray_add(decls, decl, sizeof(Decl));
    }

    return new_astfile(decls);
}

Parser* init_parser(Scanner* s)
{
    assert_always(s != NULL, "NULL scanner was passed to init_parser!");
    DArray* errs = init_darray(NULL, 0, sizeof(Error));

    Parser* p = (Parser*) malloc(sizeof(Parser));
    assert_always(p != NULL, "Failed to allocate memory for Parser!");
    p->scanner = s;
    p->errs = errs;
    p->tok = NULL;

    return p;
}
