#include "ast.h"

#include "ntassert.h"

#include <stdlib.h>

AstFile* new_astfile(DArray* decls)
{
    AstFile* astfile = (AstFile*) malloc(sizeof(AstFile));
    assert_always(astfile != NULL, "Failed to allocate memory for AstFile!");
    astfile->decls = decls;

    return astfile;
}
