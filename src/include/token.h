#ifndef SRC_INCLUDE_TOKEN_H
#define SRC_INCLUDE_TOKEN_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    TOKEN_TYPE_beg,

    TOKEN_TYPE_ILLEGAL,
	TOKEN_TYPE_EOF,
	TOKEN_TYPE_COMMENT,

    TOKEN_TYPE_PREPROCESSOR_DIRECTIVE,

    TOKEN_TYPE_punctuator_beg,

	TOKEN_TYPE_LPAREN, // (
	TOKEN_TYPE_LBRACK, // [
	TOKEN_TYPE_LBRACE, // {

	TOKEN_TYPE_RPAREN,    // )
	TOKEN_TYPE_RBRACK,    // ]
	TOKEN_TYPE_RBRACE,    // }

	TOKEN_TYPE_COMMA,  // ,
	TOKEN_TYPE_PERIOD, // .
	TOKEN_TYPE_COLON,     // :
	TOKEN_TYPE_SEMICOLON, // ;
	TOKEN_TYPE_ELLIPSIS, // ...

    TOKEN_TYPE_punctuator_end,

	TOKEN_TYPE_literal_beg,
	// Identifiers and basic type literals
	// (these tokens stand for classes of literals)
	TOKEN_TYPE_IDENT,  // main
	TOKEN_TYPE_INT_LIT,    // 12345
	TOKEN_TYPE_FLOAT_LIT,  // 123.45
	TOKEN_TYPE_CHAR_LIT,   // 'a'
	TOKEN_TYPE_STRING_LIT, // "abc"

	TOKEN_TYPE_literal_end,

	TOKEN_TYPE_operator_beg,
	// Operators and delimiters
	TOKEN_TYPE_ADD, // +
	TOKEN_TYPE_SUB, // -
	TOKEN_TYPE_MUL, // *
	TOKEN_TYPE_QUO, // /
	TOKEN_TYPE_REM, // %

	TOKEN_TYPE_AND,     // &
	TOKEN_TYPE_OR,      // |
	TOKEN_TYPE_XOR,     // ^
	TOKEN_TYPE_SHL,     // <<
	TOKEN_TYPE_SHR,     // >>
	TOKEN_TYPE_AND_NOT, // &^

	TOKEN_TYPE_ADD_ASSIGN, // +=
	TOKEN_TYPE_SUB_ASSIGN, // -=
	TOKEN_TYPE_MUL_ASSIGN, // *=
	TOKEN_TYPE_QUO_ASSIGN, // /=
	TOKEN_TYPE_REM_ASSIGN, // %=

	TOKEN_TYPE_AND_ASSIGN,     // &=
	TOKEN_TYPE_OR_ASSIGN,      // |=
	TOKEN_TYPE_XOR_ASSIGN,     // ^=
	TOKEN_TYPE_SHL_ASSIGN,     // <<=
	TOKEN_TYPE_SHR_ASSIGN,     // >>=
	TOKEN_TYPE_AND_NOT_ASSIGN, // &^=

	TOKEN_TYPE_LAND,  // &&
	TOKEN_TYPE_LOR,   // ||
	TOKEN_TYPE_RARROW, // ->
	TOKEN_TYPE_INC,   // ++
	TOKEN_TYPE_DEC,   // --

	TOKEN_TYPE_EQL,    // ==
	TOKEN_TYPE_LSS,    // <
	TOKEN_TYPE_GTR,    // >
	TOKEN_TYPE_ASSIGN, // =
	TOKEN_TYPE_NOT,    // !

	TOKEN_TYPE_NEQ,      // !=
	TOKEN_TYPE_LEQ,      // <=
	TOKEN_TYPE_GEQ,      // >=

	TOKEN_TYPE_operator_end,

	TOKEN_TYPE_keyword_beg,
	// Keywords
	TOKEN_TYPE_CONST,
	TOKEN_TYPE_IF,
	TOKEN_TYPE_ELSE,
	TOKEN_TYPE_FOR,
	TOKEN_TYPE_BREAK,
	TOKEN_TYPE_CONTINUE,
	TOKEN_TYPE_GOTO,
	TOKEN_TYPE_RETURN,
	TOKEN_TYPE_STRUCT,
	TOKEN_TYPE_UNION,
	TOKEN_TYPE_ENUM,
	TOKEN_TYPE_SWITCH,
	TOKEN_TYPE_CASE,
	TOKEN_TYPE_DEFAULT,
	TOKEN_TYPE_WHILE,
	TOKEN_TYPE_DO,
	TOKEN_TYPE_VOID,
	TOKEN_TYPE_STATIC,
	TOKEN_TYPE_EXTERN,
	TOKEN_TYPE_REGISTER,
	TOKEN_TYPE_SIGNED,
	TOKEN_TYPE_UNSIGNED,
	TOKEN_TYPE_SIZEOF,
	TOKEN_TYPE_TYPEDEF,
	TOKEN_TYPE_VOLATILE,
    TOKEN_TYPE_AUTO, 
    TOKEN_TYPE_INLINE,          // (C99)
    TOKEN_TYPE_RESTRICT,        // (C99)
    TOKEN_TYPE_COMPLEX,         // (C99)
    TOKEN_TYPE_IMAGINARY,       // (C99)
    TOKEN_TYPE_BOOL,            // (C99)(deprecated in C23)
    TOKEN_TYPE_ATOMIC,          // (C11)
    TOKEN_TYPE_GENERIC,         // (C11)

	TOKEN_TYPE_CHAR,
	TOKEN_TYPE_SHORT,
	TOKEN_TYPE_INT,
	TOKEN_TYPE_LONG,
	TOKEN_TYPE_FLOAT,
	TOKEN_TYPE_DOUBLE,

	TOKEN_TYPE_keyword_end,

    TOKEN_TYPE_end 

    // TODO: Consider the below token types later!
    //
    // [TOKEN_TYPE_] = "_Alignas",             // (C11)(deprecated in C23)
    // [TOKEN_TYPE_] = "_Alignof",             // (C11)(deprecated in C23)
    // [TOKEN_TYPE_] = "_Noreturn",            // (C11)(deprecated in C23)
    // [TOKEN_TYPE_] = "_Static_assert",       // (C11)(deprecated in C23)
    // [TOKEN_TYPE_] = "_Thread_local",        // (C11)(deprecated in C23)
    //
    // [TOKEN_TYPE_] = "_BitInt",              // (C23)
    // [TOKEN_TYPE_] = "_Decimal128",          // (C23)
    // [TOKEN_TYPE_] = "_Decimal32",           // (C23)
    // [TOKEN_TYPE_] = "_Decimal64",           // (C23)
    // [TOKEN_TYPE_] = "alignas"               // (C23)
    // [TOKEN_TYPE_] = "alignof",              // (C23)
    // [TOKEN_TYPE_] = "bool",                 // (C23)
    // [TOKEN_TYPE_] = "constexpr",            // (C23)
    // [TOKEN_TYPE_] = "typeof",               // (C23)
    // [TOKEN_TYPE_] = "typeof_unqual",        // (C23)
    // [TOKEN_TYPE_] = "thread_local",         // (C23)
    // [TOKEN_TYPE_] = "true",                 // (C23)
    // [TOKEN_TYPE_] = "static_assert",        // (C23)
    // [TOKEN_TYPE_] = "false",                // (C23)
    // [TOKEN_TYPE_] = "nullptr",              // (C23)
} TokenType;

typedef enum {
    NO_SUFF, U_SUFF, L_SUFF, LL_SUFF, UL_SUFF, ULL_SUFF, F_SUFF
} NumberSuffix;

typedef struct {
    const long int integral;
    const double fractional;
    const long int exponent;
    const TokenType type;
    const NumberSuffix suff;
} Number;

Number* new_number(
        const long int integral,
        const double fractional,
        const long int exponent,
        const TokenType type,
        const NumberSuffix suff);

#define TOKEN_TYPES_NUM (TOKEN_TYPE_end - TOKEN_TYPE_beg + 1)

typedef struct {
    const char* txt;        // The string value of the token of any type but numbers,
                            // `txt` will be NULL for numbers

    const size_t length;    // The length of `txt`

    const Number* number;   // Contains information about the number value of the token if the token
                            // of type a number

    const size_t line;      // The source line that the token starts
    const size_t col;       // The source column that the token starts
    const TokenType type;
} Token;

Token* new_token(
        const char* val,
        const size_t length,
        const size_t line,
        const size_t col,
        const TokenType type,
        const Number* number);

bool is_keyword(Token* tok);
bool is_operator(Token* tok);
bool is_literal(Token* tok);

#endif // SRC_INCLUDE_TOKEN_H
