#include "compiler.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("No file is provided!\n");
        return 0;
    }

    compile(argv[1]);

    return 0;
}
