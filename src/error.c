#include "error.h"

static const char* err_names[] = {
    [INVALID_IDENTIFIER_NAME] = "Invalid identifer name",
    [INVALID_TOKEN] = "Invalid token"
};

const char* err_name(Error err)
{
    return err_names[err];
}
