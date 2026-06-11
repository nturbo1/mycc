#include "parser.h"
#include "token.h"
#include "scanner.h"
#include "ntassert.h"
#include "darray.h"
#include "log.h"

#include <stdlib.h>
#include <stddef.h>

// Skips all the tokens until the first occurrence of and including token ';' or the end of a file.
void skip_stmt(Parser* p)
{
    Token* tok = next_tok(p->scanner);
    while(p->scanner->err != EOF_ERROR_TYPE)
    {
        if (tok != NULL && tok->type == TOKEN_TYPE_SEMICOLON)
            return;

        tok = next_tok(p->scanner);
    }
    // we reached the end of a file
}

// Reads the next token, assigns it to `p->next_tok` for consecutive calls, and
// returns the token.
//
// If the token is invalid or there is a lexical error, it sets `p->scanner->err`
// to the error and `p->next_tok` to `NULL`, and returns NULL.
static Token* ppeek_next(Parser* p)
{
    if (p->next_tok == NULL)
    {
        p->next_tok = next_tok(p->scanner);
        assert_debug( (p->next_tok == NULL) == (p->scanner->err != NO_ERROR_TYPE),
                p->next_tok == NULL ?
                "The scanner next_tok function returned a NULL token while the scanner"
                "err type was set to NO_ERROR_TYPE"
                :
                "The scanner next_tok function returned a non NULL token while the "
                "scanner err type was set to a specific error type other than "
                "NO_ERROR_TYPE");

        if (p->scanner->err != NO_ERROR_TYPE)
        {
            p->next_tok = NULL;
            return NULL;
        }
    }

    return p->next_tok;
}

static Token* pnext_tok(Parser* p)
{
    if (p->next_tok != NULL)
    {
        Token* tok = p->next_tok;
        p->next_tok = NULL;

        return tok;
    }

    return next_tok(p->scanner);
}

// Parses a declaration specifier.
//
// If a lexical or parsing error is encountered, the `p->scanner->err` is set to
// the error type and `NULL` returned. It is the caller's responsibility to
// add the error to `p->errs` and handle it properly.
// Function `parse_decl_specfr` only updates the `p->scanner->err`.
static DeclSpecifier* parse_decl_specfr(Parser* p)
{
    Token* tok = pnext_tok(p);
    assert_debug( (tok == NULL) == (p->scanner->err != NO_ERROR_TYPE),
            tok == NULL ?
            "The pnext_tok function returned NULL token while the scanner"
            "err type was set to NO_ERROR_TYPE"
            :
            "The pnext_tok function returned a non NULL token while the "
            "scanner err type was set to a specific error type other than "
            "NO_ERROR_TYPE");

    if (p->scanner->err != NO_ERROR_TYPE)
        return NULL;

    assert_debug(tok != NULL,
            "The scanner err was set to `NO_ERROR_TYPE`, so expected `tok` to be NOT NULL.");

    log_fatal("%s", "Implement the rest of function `parse_decl_specfr`!");

    // switch(tok->type)
    // {
    // case TOKEN_TYPE_CHAR,
    //      TOKEN_TYPE_SHORT,
    //      TOKEN_TYPE_INT,
    //      TOKEN_TYPE_LONG,
    //      TOKEN_TYPE_FLOAT,
    //      TOKEN_TYPE_DOUBLE,
    //      TOKEN_TYPE_VOID:
    //          if (tok->type == TOKEN_TYPE_VOID)
    // }

    return NULL;
}

// Parses the next declaration in a file.
//
// If there is a lexical or parsing error, it skips the current statement
// entirely and tries to parse a valid declaration again for better diagnostics
// unless it gets EOF error.
//
// Returns `NULL` if there is no valid declaration.
static Decl* parse_decl(Parser* p)
{
    assert_debug(p != NULL, "NULL parser was passed to `parse_decl` function!");

    DeclSpecifier* decl_specfr = NULL;
    while (decl_specfr == NULL)
    {
        decl_specfr = parse_decl_specfr(p);
        assert_debug( (decl_specfr == NULL) == (p->scanner->err != NO_ERROR_TYPE),
                decl_specfr == NULL ?
                "The parse_decl_specfr function returned NULL token while the scanner"
                "err type was set to NO_ERROR_TYPE"
                :
                "The parse_decl_specfr function returned a non NULL token while the "
                "scanner err type was set to a specific error type other than "
                "NO_ERROR_TYPE");

        if (p->scanner->err != NO_ERROR_TYPE)
        {
            if (p->scanner->err == EOF_ERROR_TYPE)
                return NULL;

            Error* err = new_err(p->scanner->err,
                                 p->scanner->filepath,
                                 p->scanner->ln_offset,
                                 p->scanner->col_offset);
            assert_debug(err != NULL, "The new err MUST NOT be NULL");
            darray_add(p->errs, err, sizeof(Error));

            skip_stmt(p);
            if (p->scanner->err == EOF_ERROR_TYPE)
                return NULL;
        }
    }

    log_fatal("%s", "Implement the rest of function `parse_decl`!");

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
    assert_debug(p != NULL, "A NULL parser was passed while parsing a file!");

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
    p->next_tok = NULL;

    return p;
}
