#include "scanner.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>

const char* operators[] = {
    [TOK_CATG_ADD] = "+",
    [TOK_CATG_SUB] = "-",
    [TOK_CATG_MUL] = "*",
    [TOK_CATG_QUO] = "/",
    [TOK_CATG_REM] = "%",
    [TOK_CATG_AND] = "&",
    [TOK_CATG_OR] = "|",
    [TOK_CATG_XOR] = "^",
    [TOK_CATG_SHL] = "<<",
    [TOK_CATG_SHR] = ">>",
    [TOK_CATG_AND_NOT] = "&^",

    [TOK_CATG_ADD_ASSIGN] = "+=",
    [TOK_CATG_SUB_ASSIGN] = "-=",
    [TOK_CATG_MUL_ASSIGN] = "*=",
    [TOK_CATG_QUO_ASSIGN] = "/=",
    [TOK_CATG_REM_ASSIGN] = "%=",
    [TOK_CATG_AND_ASSIGN] = "&=",
    [TOK_CATG_OR_ASSIGN] = "|=",
    [TOK_CATG_XOR_ASSIGN] = "^=",
    [TOK_CATG_SHL_ASSIGN] = "<<=",
    [TOK_CATG_SHR_ASSIGN] = ">>=",
    [TOK_CATG_AND_NOT_ASSIGN] = "&^=",

    [TOK_CATG_LAND] = "&&",
    [TOK_CATG_LOR] = "||",
    [TOK_CATG_RARROW] = "->",
    [TOK_CATG_INC] = "++",
    [TOK_CATG_DEC] = "--",

    [TOK_CATG_EQL] = "==",
    [TOK_CATG_LSS] = "<",
    [TOK_CATG_GTR] = ">",
    [TOK_CATG_ASSIGN] = "=",
    [TOK_CATG_NOT] = "!",

    [TOK_CATG_NEQ] = "!=",
    [TOK_CATG_LEQ] = "<=",
    [TOK_CATG_GEQ] = ">=",
    [TOK_CATG_ELLIPSIS] = "...",

    [TOK_CATG_LPAREN] = "(",
    [TOK_CATG_LBRACK] = "[",
    [TOK_CATG_LBRACE] = "{",
    [TOK_CATG_COMMA] = ",",
    [TOK_CATG_PERIOD] = ".",

    [TOK_CATG_RPAREN] = ")",
    [TOK_CATG_RBRACK] = "]",
    [TOK_CATG_RBRACE] = "}",
    [TOK_CATG_SEMICOLON] = ";",
    [TOK_CATG_COLON] = ":",
};

const char* keywords[] = {
    [TOK_CATG_CONST] = "const",
    [TOK_CATG_IF] = "if", 
    [TOK_CATG_ELSE] = "else", 
    [TOK_CATG_FOR] = "for", 
    [TOK_CATG_BREAK] = "break", 
    [TOK_CATG_CONTINUE] = "continue", 
    [TOK_CATG_GOTO] = "goto", 
    [TOK_CATG_RETURN] = "return", 
    [TOK_CATG_STRUCT] = "struct", 
    [TOK_CATG_UNION] = "union", 
    [TOK_CATG_ENUM] = "enum", 
    [TOK_CATG_SWITCH] = "switch", 
    [TOK_CATG_CASE] = "case", 
    [TOK_CATG_DEFAULT] = "default", 
    [TOK_CATG_WHILE] = "while", 
    [TOK_CATG_DO] = "do", 
    [TOK_CATG_VOID] = "void", 
    [TOK_CATG_STATIC] = "static", 
    [TOK_CATG_EXTERN] = "extern", 
    [TOK_CATG_REGISTER] = "register", 
    [TOK_CATG_SIGNED] = "signed", 
    [TOK_CATG_UNSIGNED] = "unsigned", 
    [TOK_CATG_SIZEOF] = "sizeof", 
    [TOK_CATG_TYPEDEF] = "typedef", 
    [TOK_CATG_VOLATILE] = "volatile", 

    [TOK_CATG_CHAR] = "char", 
    [TOK_CATG_SHORT] = "short", 
    [TOK_CATG_INT] = "int", 
    [TOK_CATG_LONG] = "long", 
    [TOK_CATG_FLOAT] = "float", 
    [TOK_CATG_DOUBLE] = "double", 

    // [TOK_CATG_] = "auto", 
    //
    // [TOK_CATG_] = "inline",               // (C99)
    // [TOK_CATG_] = "restrict",             // (C99)
    // [TOK_CATG_] = "_Complex",             // (C99)
    // [TOK_CATG_] = "_Imaginary",           // (C99)
    // [TOK_CATG_] = "_Bool",                // (C99)(deprecated in C23)
    //
    // [TOK_CATG_] = "_Atomic",              // (C11)
    // [TOK_CATG_] = "_Generic",             // (C11)
    // [TOK_CATG_] = "_Alignas",             // (C11)(deprecated in C23)
    // [TOK_CATG_] = "_Alignof",             // (C11)(deprecated in C23)
    // [TOK_CATG_] = "_Noreturn",            // (C11)(deprecated in C23)
    // [TOK_CATG_] = "_Static_assert",       // (C11)(deprecated in C23)
    // [TOK_CATG_] = "_Thread_local",        // (C11)(deprecated in C23)
    //
    // [TOK_CATG_] = "_BitInt",              // (C23)
    // [TOK_CATG_] = "_Decimal128",          // (C23)
    // [TOK_CATG_] = "_Decimal32",           // (C23)
    // [TOK_CATG_] = "_Decimal64",           // (C23)
    // [TOK_CATG_] = "alignas"               // (C23)
    // [TOK_CATG_] = "alignof",              // (C23)
    // [TOK_CATG_] = "bool",                 // (C23)
    // [TOK_CATG_] = "constexpr",            // (C23)
    // [TOK_CATG_] = "typeof",               // (C23)
    // [TOK_CATG_] = "typeof_unqual",        // (C23)
    // [TOK_CATG_] = "thread_local",         // (C23)
    // [TOK_CATG_] = "true",                 // (C23)
    // [TOK_CATG_] = "static_assert",        // (C23)
    // [TOK_CATG_] = "false",                // (C23)
    // [TOK_CATG_] = "nullptr",              // (C23)
};

// Fills the current buffer that the scanner is currently processing with the next chunk of bytes from
// the src file.
static void fill_buffer(Scanner* s)
{
    int ch;
    size_t i = s->next;
    while ((ch = fgetc(s->file)) != EOF && i < s->bf_end)
    {
        // TODO: Handle file io errors
        s->src[i] = ch;
        i++;
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
    }

    return ch;
}

Token next_tok(Scanner* s)
{
    // TODO: IMPLEMENT!!! The below code is garbage just to avoid compiler errors/warnings temporarily
    next_char(s);
    Token t = { NULL, 0, 0, 0, TOK_CATG_DOUBLE};
    return t;
}

Scanner* init_scanner(Scanner* s, const char* filepath)
{
    if (s == NULL) {
        s = (Scanner*) calloc(1, sizeof(Scanner));
        if (s == NULL) {
            printf("Failed to create a new scanner\n");
            exit(1);
        }
    } else {
        s->bf_end = SCANNER_BUFFER_SIZE;
        s->next = 0;
        s->ln_offset = 0;
        s->col_offset = 0;
    }
    s->mode = PP_MODE;

    FILE* src_file = fopen(filepath, "r");
    if (src_file == NULL) {
        printf("Failed to open %s\n", filepath);
        exit(1);
    }

    s->file = src_file;

    return s;
}
