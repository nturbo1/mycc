#include "scanner.h"
#include "token.h"
#include "error.h"
#include "hashtable.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>

extern const char* token_type_name[TOKEN_TYPES_NUM];

// static const char* operator[] = {
//     [TOKEN_TYPE_ADD] = "+",
//     [TOKEN_TYPE_SUB] = "-",
//     [TOKEN_TYPE_MUL] = "*",
//     [TOKEN_TYPE_QUO] = "/",
//     [TOKEN_TYPE_REM] = "%",
//     [TOKEN_TYPE_AND] = "&",
//     [TOKEN_TYPE_OR] = "|",
//     [TOKEN_TYPE_XOR] = "^",
//     [TOKEN_TYPE_SHL] = "<<",
//     [TOKEN_TYPE_SHR] = ">>",
//     [TOKEN_TYPE_AND_NOT] = "&^",
//
//     [TOKEN_TYPE_ADD_ASSIGN] = "+=",
//     [TOKEN_TYPE_SUB_ASSIGN] = "-=",
//     [TOKEN_TYPE_MUL_ASSIGN] = "*=",
//     [TOKEN_TYPE_QUO_ASSIGN] = "/=",
//     [TOKEN_TYPE_REM_ASSIGN] = "%=",
//     [TOKEN_TYPE_AND_ASSIGN] = "&=",
//     [TOKEN_TYPE_OR_ASSIGN] = "|=",
//     [TOKEN_TYPE_XOR_ASSIGN] = "^=",
//     [TOKEN_TYPE_SHL_ASSIGN] = "<<=",
//     [TOKEN_TYPE_SHR_ASSIGN] = ">>=",
//     [TOKEN_TYPE_AND_NOT_ASSIGN] = "&^=",
//
//     [TOKEN_TYPE_LAND] = "&&",
//     [TOKEN_TYPE_LOR] = "||",
//     [TOKEN_TYPE_RARROW] = "->",
//     [TOKEN_TYPE_INC] = "++",
//     [TOKEN_TYPE_DEC] = "--",
//
//     [TOKEN_TYPE_EQL] = "==",
//     [TOKEN_TYPE_LSS] = "<",
//     [TOKEN_TYPE_GTR] = ">",
//     [TOKEN_TYPE_ASSIGN] = "=",
//     [TOKEN_TYPE_NOT] = "!",
//
//     [TOKEN_TYPE_NEQ] = "!=",
//     [TOKEN_TYPE_LEQ] = "<=",
//     [TOKEN_TYPE_GEQ] = ">=",
// };

// Fills the current buffer that the scanner is currently processing with the next chunk of bytes from
// the src file.
static void fill_buffer(Scanner* s)
{
    char* buf = s->src + s->next;
    size_t n = fread(buf,
                     sizeof(char),
                     SCANNER_BUFFER_SIZE,
                     s->file);

    if (feof(s->file)) {
        buf[n] = EOF;
    }
}

static char next_char(Scanner* s)
{
    const char ch = s->src[s->next];

    if (ch != EOF) {
        s->next = ((s->next + 1) % (2 * SCANNER_BUFFER_SIZE));

        // next is the beginning of one of the buffers
        if (s->next % SCANNER_BUFFER_SIZE == 0) { 
            fill_buffer(s);
            s->bf_end = ((s->next + SCANNER_BUFFER_SIZE) % (2 * SCANNER_BUFFER_SIZE));
        }

        if (ch == '\n') {
            ++s->ln_offset;
            s->col_offset = 0;
        } else {
            ++s->col_offset;
        }
    }

    return ch;
}

static char peek_next(Scanner* s) {
    return s->src[s->next];
}

static bool is_whitespace(char ch)
{
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\v' || ch == '\f' || ch == '\r';
}

static bool is_alpha(char ch)
{
    return ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z');
}

static bool is_digit(char ch)
{
    return '0' <= ch && ch <= '9';
}

static bool is_hex_digit(char ch)
{
    return ('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F');
}

static bool is_alnum(char ch)
{
    return is_alpha(ch) || is_digit(ch);
}

static void skip_whitespace(Scanner* s)
{
    char ch = peek_next(s);
    while (is_whitespace(ch))
    {
        next_char(s); // skip whitespace
        ch = peek_next(s);
    }
}

// Scans an identifier starting from the next char position in the src input buffer of the scanner.
// An identifier is of the form
//                                  [a-zA-Z]+[a-zA-Z0-9]*
// .
static const char* scan_identifier(Scanner* s)
{
    char idf_name_buf[MAX_IDENTIFIER_NAME_SIZE];
    size_t idf_name_len = 0;

    char ch = peek_next(s);

    if (ch == EOF) {
        EXIT_WITH_ERROR(
            INVALID_IDENTIFIER_NAME,
            s->ln_offset + 1,
            s->col_offset + 1,
            "Expected an identifier."
        );
    }

    if (ch != '_' && !is_alpha(ch))
    {
        EXIT_WITH_ERROR(
            INVALID_IDENTIFIER_NAME,
            s->ln_offset + 1,
            s->col_offset + 1,
            "An identifier must start with '_' (underscore) or an alphabetic character!"
        );
    }
    ch = next_char(s);

    idf_name_buf[idf_name_len] = ch;
    ++idf_name_len;

    bool idf_end = false;
    while(!idf_end)
    {
        ch = peek_next(s);

        switch (ch) {
            case EOF:
            case ';': 
            case '(': 
            case '[': 
            case '{': 
                idf_end = true;
                break;
            default:
                if (ch == '_' || is_alnum(ch)) {
                    if (idf_name_len == MAX_IDENTIFIER_NAME_SIZE) {
                        EXIT_WITH_ERROR(
                            INVALID_IDENTIFIER_NAME,
                            s->ln_offset + 1,
                            s->col_offset + 1,
                            "Identifier name is too long!"
                        );
                    }
                    ch = next_char(s);
                    idf_name_buf[idf_name_len] = ch;
                    ++idf_name_len;
                }
                else if (is_whitespace(ch)) {
                    idf_end = true;
                }
                else {
                    EXIT_WITH_ERROR(
                        INVALID_IDENTIFIER_NAME,
                        s->ln_offset + 1,
                        s->col_offset + 1,
                        "An identifier must contain '_' or alphanumeric characters!"
                    );
                }
        }
    }

    const char* idf_name = (const char*) malloc(idf_name_len + 1);
    strncpy((char*) idf_name, idf_name_buf, idf_name_len);
    *(char *)&idf_name[idf_name_len] = 0;

    return idf_name;
}

static const char* scan_str_literal(Scanner* s) {
    printf("IMPLEMENT STRING LITERAL SCANNER!!! scanner = %p\n", (void*) s);
    exit(1);
    return NULL;
}

static const char* scan_char_literal(Scanner* s) {
    printf("IMPLEMENT CHARACTER LITERAL SCANNER!!! scanner = %p\n", (void*) s);
    exit(1);
    return NULL;
}

typedef struct {
    const char* lit;
    const size_t lit_len;
    TokenType type;
} NumberScan;

static NumberScan scan_number(Scanner* s) {
    printf("IMPLEMENT NUMBER SCANNER!!! scanner = %p\n", (void*) s);
    exit(1);
    is_hex_digit(0);
    NumberScan ns = {NULL, 0, 0};
    return ns;
}

// Scans a line (// ...) or mult-line (/* ... */) comment and ignores them.
static void scan_comment(Scanner* s, bool is_multiline) {
    printf("IMPLEMENT COMMENT SCANNER!!! scanner = %p, is_multiline = %d\n", (void*) s, is_multiline);
    exit(1);
}

// Scans for the next token and returns a non NULL Token pointer if it finds a valid token.
// Returns NULL if it reaches the end of the file.
//
// Exits the program with an error message if there's a lexical error.
Token* next_tok(Scanner* s)
{
scan_again:
    skip_whitespace(s);
    char ch = peek_next(s);

    if (ch == EOF) {
        return NULL;
    }

    const size_t tok_line = s->ln_offset + 1;
    const size_t tok_col = s->col_offset + 1;

    if (is_digit(ch))
    {
        NumberScan number = scan_number(s);
        return new_token(
            number.lit,
            number.lit_len,
            tok_line,
            tok_col,
            number.type
        );
    }
    else
    {
        switch (ch) {
            case '#':
                next_char(s); // skip '#'
                const char* pp_directive = scan_identifier(s);
                return new_token(
                    pp_directive,
                    strlen(pp_directive),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_PREPROCESSOR_DIRECTIVE
                );
            case '"': ; // Just to bypass the error: a label can only be part of a statement and a declaration is not a statement
                // [-Werror=free-labels]
                const char* str_literal = scan_str_literal(s);
                return new_token(
                    str_literal,
                    strlen(str_literal),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_STRING_LIT
                );
            case '\'': ; // Just to bypass the error: a label can only be part of a statement and a declaration is not a statement
                // [-Werror=free-labels]
                const char* char_literal = scan_char_literal(s);
                return new_token(
                    char_literal,
                    strlen(char_literal),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_CHAR_LIT
                );
            case '(':
                next_char(s);
                return new_token(
                    token_type_name[TOKEN_TYPE_LPAREN],
                    strlen(token_type_name[TOKEN_TYPE_LPAREN]),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_LPAREN
                );
            case '[':
                next_char(s);
                return new_token(
                    token_type_name[TOKEN_TYPE_LBRACK],
                    strlen(token_type_name[TOKEN_TYPE_LBRACK]),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_LBRACK
                );
            case '{':
                next_char(s);
                return new_token(
                    token_type_name[TOKEN_TYPE_LBRACE],
                    strlen(token_type_name[TOKEN_TYPE_LBRACE]),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_LBRACE
                );
            case ')':
                next_char(s);
                return new_token(
                    token_type_name[TOKEN_TYPE_RPAREN],
                    strlen(token_type_name[TOKEN_TYPE_RPAREN]),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_RPAREN
                );
            case ']':
                next_char(s);
                return new_token(
                    token_type_name[TOKEN_TYPE_RBRACK],
                    strlen(token_type_name[TOKEN_TYPE_RBRACK]),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_RBRACK
                );
            case '}':
                next_char(s);
                return new_token(
                    token_type_name[TOKEN_TYPE_RBRACE],
                    strlen(token_type_name[TOKEN_TYPE_RBRACE]),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_RBRACE
                );
            case ',':
                next_char(s);
                return new_token(
                    token_type_name[TOKEN_TYPE_COMMA],
                    strlen(token_type_name[TOKEN_TYPE_COMMA]),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_COMMA
                );
            case '.':
                next_char(s);
                if ('.' == peek_next(s))
                {
                    next_char(s);
                    if ('.' == peek_next(s))
                    {
                        next_char(s);
                        return new_token(
                            token_type_name[TOKEN_TYPE_ELLIPSIS],
                            strlen(token_type_name[TOKEN_TYPE_ELLIPSIS]),
                            tok_line,
                            tok_col,
                            TOKEN_TYPE_ELLIPSIS
                        );
                    }
                    else
                    {
                        EXIT_WITH_ERROR(
                            INVALID_TOKEN,
                            tok_line,
                            tok_col,
                            "Expected a member name."
                        );
                    }
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_PERIOD],
                        strlen(token_type_name[TOKEN_TYPE_PERIOD]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_PERIOD
                    );
                }
            case ':':
                next_char(s);
                return new_token(
                    token_type_name[TOKEN_TYPE_COLON],
                    strlen(token_type_name[TOKEN_TYPE_COLON]),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_COLON
                );
            case ';':
                next_char(s);
                return new_token(
                    token_type_name[TOKEN_TYPE_SEMICOLON],
                    strlen(token_type_name[TOKEN_TYPE_SEMICOLON]),
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_SEMICOLON
                );
            case '+':
                next_char(s);
                ch = peek_next(s);
                if (ch == '+')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_INC],
                        strlen(token_type_name[TOKEN_TYPE_INC]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_INC
                    );
                }
                else if (ch == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_ADD_ASSIGN],
                        strlen(token_type_name[TOKEN_TYPE_ADD_ASSIGN]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_ADD_ASSIGN
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_ADD],
                        strlen(token_type_name[TOKEN_TYPE_ADD]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_ADD
                    );
                }
            case '-':
                next_char(s);
                ch = peek_next(s);
                if (ch == '-')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_DEC],
                        strlen(token_type_name[TOKEN_TYPE_DEC]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_DEC
                    );
                }
                else if (ch == '>')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_RARROW],
                        strlen(token_type_name[TOKEN_TYPE_RARROW]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_RARROW
                    );
                }
                else if (ch == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_SUB_ASSIGN],
                        strlen(token_type_name[TOKEN_TYPE_SUB_ASSIGN]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_SUB_ASSIGN
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_SUB],
                        strlen(token_type_name[TOKEN_TYPE_SUB]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_SUB
                    );
                }
            case '*':
                next_char(s);
                if (peek_next(s) == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_MUL_ASSIGN],
                        strlen(token_type_name[TOKEN_TYPE_MUL_ASSIGN]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_MUL_ASSIGN
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_MUL],
                        strlen(token_type_name[TOKEN_TYPE_MUL]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_MUL
                    );
                }
            case '/':
                next_char(s);
                ch = peek_next(s);
                if (ch == '/' || ch == '*')
                {
                    next_char(s);
                    scan_comment(s, ch == '*');
                    goto scan_again;
                }
                else if (ch == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_QUO_ASSIGN],
                        strlen(token_type_name[TOKEN_TYPE_QUO_ASSIGN]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_QUO_ASSIGN
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_QUO],
                        strlen(token_type_name[TOKEN_TYPE_QUO]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_QUO
                    );
                }
            case '%':
                next_char(s);
                if (peek_next(s) == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_REM_ASSIGN],
                        strlen(token_type_name[TOKEN_TYPE_REM_ASSIGN]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_REM_ASSIGN
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_REM],
                        strlen(token_type_name[TOKEN_TYPE_REM]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_REM
                    );
                }
            case '&':
                next_char(s);
                ch = peek_next(s);
                if (ch == '&')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_LAND],
                        strlen(token_type_name[TOKEN_TYPE_LAND]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_LAND
                    );
                }
                else if (ch == '^')
                {
                    next_char(s);
                    if (peek_next(s) == '=')
                    {
                        next_char(s);
                        return new_token(
                            token_type_name[TOKEN_TYPE_AND_NOT_ASSIGN],
                            strlen(token_type_name[TOKEN_TYPE_AND_NOT_ASSIGN]),
                            tok_line,
                            tok_col,
                            TOKEN_TYPE_AND_NOT_ASSIGN
                        );
                    }
                    else
                    {
                        return new_token(
                            token_type_name[TOKEN_TYPE_AND_NOT],
                            strlen(token_type_name[TOKEN_TYPE_AND_NOT]),
                            tok_line,
                            tok_col,
                            TOKEN_TYPE_AND_NOT
                        );
                    }
                }
                else if (ch == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_AND_ASSIGN],
                        strlen(token_type_name[TOKEN_TYPE_AND_ASSIGN]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_AND_ASSIGN
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_AND],
                        strlen(token_type_name[TOKEN_TYPE_AND]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_AND
                    );
                }
            case '|':
                next_char(s);
                ch = peek_next(s);
                if (ch == '|')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_LOR],
                        strlen(token_type_name[TOKEN_TYPE_LOR]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_LOR
                    );
                }
                else if (ch == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_OR_ASSIGN],
                        strlen(token_type_name[TOKEN_TYPE_OR_ASSIGN]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_OR_ASSIGN
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_OR],
                        strlen(token_type_name[TOKEN_TYPE_OR]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_OR
                    );
                }
            case '^':
                next_char(s);
                if (peek_next(s) == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_XOR_ASSIGN],
                        strlen(token_type_name[TOKEN_TYPE_XOR_ASSIGN]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_XOR_ASSIGN
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_XOR],
                        strlen(token_type_name[TOKEN_TYPE_XOR]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_XOR
                    );
                }
            case '<':
                next_char(s);
                ch = peek_next(s);
                if (ch == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_LEQ],
                        strlen(token_type_name[TOKEN_TYPE_LEQ]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_LEQ
                    );
                }
                else if (ch == '<')
                {
                    next_char(s);
                    if (peek_next(s) == '=')
                    {
                        next_char(s);
                        return new_token(
                            token_type_name[TOKEN_TYPE_SHL_ASSIGN],
                            strlen(token_type_name[TOKEN_TYPE_SHL_ASSIGN]),
                            tok_line,
                            tok_col,
                            TOKEN_TYPE_SHL_ASSIGN
                        );
                    }
                    else
                    {
                        return new_token(
                            token_type_name[TOKEN_TYPE_SHL],
                            strlen(token_type_name[TOKEN_TYPE_SHL]),
                            tok_line,
                            tok_col,
                            TOKEN_TYPE_SHL
                        );
                    }
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_LSS],
                        strlen(token_type_name[TOKEN_TYPE_LSS]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_LSS
                    );
                }
            case '>':
                next_char(s);
                ch = peek_next(s);
                if (ch == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_GEQ],
                        strlen(token_type_name[TOKEN_TYPE_GEQ]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_GEQ
                    );
                }
                else if (ch == '>')
                {
                    next_char(s);
                    if (peek_next(s) == '=')
                    {
                        next_char(s);
                        return new_token(
                            token_type_name[TOKEN_TYPE_SHR_ASSIGN],
                            strlen(token_type_name[TOKEN_TYPE_SHR_ASSIGN]),
                            tok_line,
                            tok_col,
                            TOKEN_TYPE_SHR_ASSIGN
                        );
                    }
                    else
                    {
                        return new_token(
                            token_type_name[TOKEN_TYPE_SHR],
                            strlen(token_type_name[TOKEN_TYPE_SHR]),
                            tok_line,
                            tok_col,
                            TOKEN_TYPE_SHR
                        );
                    }
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_GTR],
                        strlen(token_type_name[TOKEN_TYPE_GTR]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_GTR
                    );
                }
            case '=':
                next_char(s);
                if (peek_next(s) == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_EQL],
                        strlen(token_type_name[TOKEN_TYPE_EQL]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_EQL
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_ASSIGN],
                        strlen(token_type_name[TOKEN_TYPE_ASSIGN]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_ASSIGN
                    );
                }
            case '!':
                next_char(s);
                if (peek_next(s) == '=')
                {
                    next_char(s);
                    return new_token(
                        token_type_name[TOKEN_TYPE_NEQ],
                        strlen(token_type_name[TOKEN_TYPE_NEQ]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_NEQ
                    );
                }
                else
                {
                    return new_token(
                        token_type_name[TOKEN_TYPE_NOT],
                        strlen(token_type_name[TOKEN_TYPE_NOT]),
                        tok_line,
                        tok_col,
                        TOKEN_TYPE_NOT
                    );
                }

            default: ; // Just to bypass the error: a label can only be part of a statement and a declaration is not a statement
                // [-Werror=free-labels]
                const char* identifier = scan_identifier(s);
                size_t idf_len = strlen(identifier);

                if (idf_len > 1) { // all the keywords have >1 length
                    TokenType tt = (TokenType) ht_get(s->keywords, identifier, idf_len);
                    if (tt > 0) { // TokenType starts with TOKEN_TYPE_beg, so all the actual/valid TokenType values are >0
                        free((char*) identifier);
                        return new_token(
                            token_type_name[tt],
                            idf_len,
                            tok_line,
                            tok_col,
                            tt
                        );
                    }
                }

                return new_token(
                    identifier,
                    idf_len,
                    tok_line,
                    tok_col,
                    TOKEN_TYPE_IDENT
                );
        }
    }
}

Scanner* init_scanner(Scanner* s, const char* filepath)
{
    FILE* src_file = fopen(filepath, "r");
    if (src_file == NULL)
    {
        printf("Failed to open %s\n", filepath);
        exit(1);
    }

    if (s == NULL)
    {
        s = (Scanner*) malloc(sizeof(Scanner));
        if (s == NULL) {
            printf("Failed to create a new scanner\n");
            exit(1);
        }
    }

    s->file = src_file;
    s->bf_end = SCANNER_BUFFER_SIZE;
    s->next = 0;

    fill_buffer(s);

    s->ln_offset = 0;
    s->col_offset = 0;
    const size_t keywords_num = TOKEN_TYPE_keyword_end - TOKEN_TYPE_keyword_beg - 1;
    s->keywords = ht_new(keywords_num);

    TokenType tt_keyword = TOKEN_TYPE_keyword_beg + 1;

    while (tt_keyword < TOKEN_TYPE_keyword_end)
    {
        ht_put(
            s->keywords,
            token_type_name[tt_keyword],
            strlen(token_type_name[tt_keyword]),
            (const void*)(intptr_t)(tt_keyword)
        );

        ++tt_keyword;
    }

    return s;
}
