#include "token.h"

bool is_keyword(Token* tok) {
    Token_Catg catg = tok->catg;

    return TOK_CATG_keyword_beg < catg && catg < TOK_CATG_keyword_end;
}
bool is_operator(Token* tok) {
    Token_Catg catg = tok->catg;
    
    return TOK_CATG_operator_beg < catg && catg < TOK_CATG_operator_end;
}
bool is_literal(Token* tok) {
    Token_Catg catg = tok->catg;

    return TOK_CATG_literal_beg < catg && catg < TOK_CATG_literal_end;
}
