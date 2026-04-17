#include "token.h"

#include <stdlib.h>

Token* new_token(const char* val, const size_t length, const size_t line, const size_t col, const TokenType type)
{
    Token* tok = malloc(sizeof(Token));
    *(char **)&tok->val = (char*) val;
    *(size_t *)&tok->length = length;
    *(size_t *)&tok->line = line;
    *(size_t *)&tok->col = col;
    *(TokenType *)&tok->type = type;

    return tok;
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
