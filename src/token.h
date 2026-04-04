#ifndef SRC_TOKEN_H
#define SRC_TOKEN_H

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    TOK_CATG_ILLEGAL,
	TOK_CATG_EOF,
	TOK_CATG_COMMENT,
    TOK_CATG_HASH, // #

	TOK_CATG_literal_beg,
	// Identifiers and basic type literals
	// (these tokens stand for classes of literals)
	TOK_CATG_IDENT,  // main
	TOK_CATG_INT_LIT,    // 12345
	TOK_CATG_FLOAT_LIT,  // 123.45
	TOK_CATG_CHAR_LIT,   // 'a'
	TOK_CATG_STRING_LIT, // "abc"
	TOK_CATG_literal_end,

	TOK_CATG_operator_beg,
	// Operators and delimiters
	TOK_CATG_ADD, // +
	TOK_CATG_SUB, // -
	TOK_CATG_MUL, // *
	TOK_CATG_QUO, // /
	TOK_CATG_REM, // %

	TOK_CATG_AND,     // &
	TOK_CATG_OR,      // |
	TOK_CATG_XOR,     // ^
	TOK_CATG_SHL,     // <<
	TOK_CATG_SHR,     // >>
	TOK_CATG_AND_NOT, // &^

	TOK_CATG_ADD_ASSIGN, // +=
	TOK_CATG_SUB_ASSIGN, // -=
	TOK_CATG_MUL_ASSIGN, // *=
	TOK_CATG_QUO_ASSIGN, // /=
	TOK_CATG_REM_ASSIGN, // %=

	TOK_CATG_AND_ASSIGN,     // &=
	TOK_CATG_OR_ASSIGN,      // |=
	TOK_CATG_XOR_ASSIGN,     // ^=
	TOK_CATG_SHL_ASSIGN,     // <<=
	TOK_CATG_SHR_ASSIGN,     // >>=
	TOK_CATG_AND_NOT_ASSIGN, // &^=

	TOK_CATG_LAND,  // &&
	TOK_CATG_LOR,   // ||
	TOK_CATG_RARROW, // ->
	TOK_CATG_INC,   // ++
	TOK_CATG_DEC,   // --

	TOK_CATG_EQL,    // ==
	TOK_CATG_LSS,    // <
	TOK_CATG_GTR,    // >
	TOK_CATG_ASSIGN, // =
	TOK_CATG_NOT,    // !

	TOK_CATG_NEQ,      // !=
	TOK_CATG_LEQ,      // <=
	TOK_CATG_GEQ,      // >=
	TOK_CATG_ELLIPSIS, // ...

	TOK_CATG_LPAREN, // (
	TOK_CATG_LBRACK, // [
	TOK_CATG_LBRACE, // {
	TOK_CATG_COMMA,  // ,
	TOK_CATG_PERIOD, // .

	TOK_CATG_RPAREN,    // )
	TOK_CATG_RBRACK,    // ]
	TOK_CATG_RBRACE,    // }
	TOK_CATG_SEMICOLON, // ;
	TOK_CATG_COLON,     // :
	TOK_CATG_operator_end,

	TOK_CATG_keyword_beg,
	// Keywords
	TOK_CATG_CONST,
	TOK_CATG_IF,
	TOK_CATG_ELSE,
	TOK_CATG_FOR,
	TOK_CATG_BREAK,
	TOK_CATG_CONTINUE,
	TOK_CATG_GOTO,
	TOK_CATG_RETURN,
	TOK_CATG_STRUCT,
	TOK_CATG_UNION,
	TOK_CATG_ENUM,
	TOK_CATG_SWITCH,
	TOK_CATG_CASE,
	TOK_CATG_DEFAULT,
	TOK_CATG_WHILE,
	TOK_CATG_DO,
	TOK_CATG_VOID,
	TOK_CATG_STATIC,
	TOK_CATG_EXTERN,
	TOK_CATG_REGISTER,
	TOK_CATG_SIGNED,
	TOK_CATG_UNSIGNED,
	TOK_CATG_SIZEOF,
	TOK_CATG_TYPEDEF,
	TOK_CATG_VOLATILE,

	TOK_CATG_CHAR,
	TOK_CATG_SHORT,
	TOK_CATG_INT,
	TOK_CATG_LONG,
	TOK_CATG_FLOAT,
	TOK_CATG_DOUBLE,

	TOK_CATG_keyword_end
} Token_Catg;

typedef struct {
    const char* start;
    size_t length;
    size_t col;
    size_t row;
    const Token_Catg catg;  // Token category/type
} Token;

bool is_keyword(Token* tok);
bool is_operator(Token* tok);
bool is_literal(Token* tok);

#endif
