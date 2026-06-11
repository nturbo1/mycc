#include "compiler.h"
#include "hashtable.h"
#include "scanner.h"
#include "token.h"
#include "parser/parser.h"
#include "ntassert.h"

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
    assert_always(scanner != NULL, "Scanner was initialized to NULL!");
    Parser* parser = init_parser(scanner);
    assert_always(parser != NULL, "Parser was initialized to NULL!");
    scanner = NULL; // the parser owns the scanner now

    AstFile* ast = parse_file(parser);
    // TODO: REMOVE AFTER YOU'RE DONE WITH TESTING!!!
    printf("Parsed ast: %p\n", (void*) ast);
}
