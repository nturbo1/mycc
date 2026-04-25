#include "token.h"

#include <stdlib.h>

Token* new_token(
        const char* txt,
        const size_t length,
        const size_t line,
        const size_t col,
        const TokenType type,
        const Number* number)
{
    Token* tok = malloc(sizeof(Token));
    tok->txt = txt;
    *(size_t *)&tok->length = length;
    *(size_t *)&tok->line = line;
    *(size_t *)&tok->col = col;
    *(TokenType *)&tok->type = type;
    tok->number = number;

    return tok;
}

Number* new_number(
        const long int integral,
        const double fractional,
        const long int exponent,
        const TokenType type,
        const NumberSuffix suff)
{
    Number* num = (Number*) malloc(sizeof(Number));
    *(long int*)&num->integral = integral;
    *(double*)&num->fractional = fractional;
    *(long int*)&num->exponent = exponent;
    *(TokenType*)&num->type = type;
    *(NumberSuffix*)&num->suff = suff;

    return num;
}

bool is_keyword(Token* tok) {
    TokenType type = tok->type;

    return TOKEN_TYPE_keyword_beg < type && type < TOKEN_TYPE_keyword_end;
}
bool is_operator(Token* tok) {
    TokenType type = tok->type;
    
    return TOKEN_TYPE_operator_beg < type && type < TOKEN_TYPE_operator_end;
}
bool is_literal(Token* tok) {
    TokenType type = tok->type;

    return TOKEN_TYPE_literal_beg < type && type < TOKEN_TYPE_literal_end;
}

const char* token_type_name[TOKEN_TYPES_NUM] = {
    // PUNCTUATORS
    [TOKEN_TYPE_LPAREN] = "(",
    [TOKEN_TYPE_LBRACK] = "[",
    [TOKEN_TYPE_LBRACE] = "{",

    [TOKEN_TYPE_RPAREN] = ")",
    [TOKEN_TYPE_RBRACK] = "]",
    [TOKEN_TYPE_RBRACE] = "}",

    [TOKEN_TYPE_COMMA] = ",",
    [TOKEN_TYPE_PERIOD] = ".",
    [TOKEN_TYPE_COLON] = ":",
    [TOKEN_TYPE_SEMICOLON] = ";",

    [TOKEN_TYPE_ELLIPSIS] = "...",

    // OPERATORS
    [TOKEN_TYPE_ADD] = "+",
    [TOKEN_TYPE_SUB] = "-",
    [TOKEN_TYPE_MUL] = "*",
    [TOKEN_TYPE_QUO] = "/",
    [TOKEN_TYPE_REM] = "%",
    [TOKEN_TYPE_AND] = "&",
    [TOKEN_TYPE_OR] = "|",
    [TOKEN_TYPE_XOR] = "^",
    [TOKEN_TYPE_SHL] = "<<",
    [TOKEN_TYPE_SHR] = ">>",
    [TOKEN_TYPE_AND_NOT] = "&^",

    [TOKEN_TYPE_ADD_ASSIGN] = "+=",
    [TOKEN_TYPE_SUB_ASSIGN] = "-=",
    [TOKEN_TYPE_MUL_ASSIGN] = "*=",
    [TOKEN_TYPE_QUO_ASSIGN] = "/=",
    [TOKEN_TYPE_REM_ASSIGN] = "%=",
    [TOKEN_TYPE_AND_ASSIGN] = "&=",
    [TOKEN_TYPE_OR_ASSIGN] = "|=",
    [TOKEN_TYPE_XOR_ASSIGN] = "^=",
    [TOKEN_TYPE_SHL_ASSIGN] = "<<=",
    [TOKEN_TYPE_SHR_ASSIGN] = ">>=",
    [TOKEN_TYPE_AND_NOT_ASSIGN] = "&^=",

    [TOKEN_TYPE_LAND] = "&&",
    [TOKEN_TYPE_LOR] = "||",
    [TOKEN_TYPE_RARROW] = "->",
    [TOKEN_TYPE_INC] = "++",
    [TOKEN_TYPE_DEC] = "--",

    [TOKEN_TYPE_EQL] = "==",
    [TOKEN_TYPE_LSS] = "<",
    [TOKEN_TYPE_GTR] = ">",
    [TOKEN_TYPE_ASSIGN] = "=",
    [TOKEN_TYPE_NOT] = "!",

    [TOKEN_TYPE_NEQ] = "!=",
    [TOKEN_TYPE_LEQ] = "<=",
    [TOKEN_TYPE_GEQ] = ">=",

    // KEYWORDS
    [TOKEN_TYPE_CONST] = "const",
    [TOKEN_TYPE_IF] = "if", 
    [TOKEN_TYPE_ELSE] = "else", 
    [TOKEN_TYPE_FOR] = "for", 
    [TOKEN_TYPE_BREAK] = "break", 
    [TOKEN_TYPE_CONTINUE] = "continue", 
    [TOKEN_TYPE_GOTO] = "goto", 
    [TOKEN_TYPE_RETURN] = "return", 
    [TOKEN_TYPE_STRUCT] = "struct", 
    [TOKEN_TYPE_UNION] = "union", 
    [TOKEN_TYPE_ENUM] = "enum", 
    [TOKEN_TYPE_SWITCH] = "switch", 
    [TOKEN_TYPE_CASE] = "case", 
    [TOKEN_TYPE_DEFAULT] = "default", 
    [TOKEN_TYPE_WHILE] = "while", 
    [TOKEN_TYPE_DO] = "do", 
    [TOKEN_TYPE_VOID] = "void", 
    [TOKEN_TYPE_STATIC] = "static", 
    [TOKEN_TYPE_EXTERN] = "extern", 
    [TOKEN_TYPE_REGISTER] = "register", 
    [TOKEN_TYPE_SIGNED] = "signed", 
    [TOKEN_TYPE_UNSIGNED] = "unsigned", 
    [TOKEN_TYPE_SIZEOF] = "sizeof", 
    [TOKEN_TYPE_TYPEDEF] = "typedef", 
    [TOKEN_TYPE_VOLATILE] = "volatile", 

    [TOKEN_TYPE_CHAR] = "char", 
    [TOKEN_TYPE_SHORT] = "short", 
    [TOKEN_TYPE_INT] = "int", 
    [TOKEN_TYPE_LONG] = "long", 
    [TOKEN_TYPE_FLOAT] = "float", 
    [TOKEN_TYPE_DOUBLE] = "double"
};
