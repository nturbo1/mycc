#ifndef SRC_COMPILER_H
#define SRC_COMPILER_H

#include "hashtable.h"

typedef struct {
    HashTable* symb_table;
} Compiler;

Compiler* init_compiler(Compiler* comp);

// Takes a C source file as an input, compiles it, and creates an object file that
// contains the compiled machine code.
void compile(const char* filepath);

#endif // SRC_COMPILER_H
