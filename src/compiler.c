#include "compiler.h"
#include "hashtable.h"
#include "scanner.h"
#include "token.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

Compiler* init_compiler(Compiler* comp)
{
    if (comp == NULL)
    {
        comp = malloc(sizeof(Compiler));
        comp->symb_table = NULL;
    }

    if (comp->symb_table != NULL) {
        ht_delete(comp->symb_table);
    }

    comp->symb_table = ht_new(0);

    return comp;
}

void compile(const char* filepath)
{
    Scanner* scanner = init_scanner(NULL, filepath);

    Token* tok = next_tok(scanner);
    while (tok != NULL) {
        if (tok->type == TOKEN_TYPE_INT_LIT) {
            printf("Scanned token: {val: %ld, length: %zu, line: %zu, col: %zu, type: %d}\n",
                   (long int)(intptr_t) tok->val, tok->length, tok->line, tok->col, tok->type);
        } else {
            printf("Scanned token: {val: %s, length: %zu, line: %zu, col: %zu, type: %d}\n",
                   tok->val, tok->length, tok->line, tok->col, tok->type);
        }
        tok = next_tok(scanner);
    }
}
