#include "error.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char* err_names[] = {
    [NO_ERROR] = "",
    [INVALID_IDENTIFIER_NAME] = "Invalid identifer name",
    [INVALID_NUMBER] = "Invalid number",
    [INVALID_TOKEN] = "Invalid token",
    [INCOMPATIBLE_NUMBER_SUFFIX] = "Incompatible number suffix",
};

static const char* err_msg[] = {
    [NO_ERROR] = "",
    [INVALID_IDENTIFIER_NAME] = "Invalid identifer name",
    [INVALID_NUMBER] = "Invalid number",
    [INVALID_TOKEN] = "Invalid token",
    [INCOMPATIBLE_NUMBER_SUFFIX] = "Incompatible number suffix",
};

const char* err_name(Error err)
{
    return err_names[err];
}

#define ERROR_MSG_FMT "%s:%zu:%zu: error: %s"
const char* get_err_msg(Error err, const char* filepath, size_t line, size_t col)
{
    const char* msg = err_msg[err];
    // the msg_buf_size value depends on the value of macro ERROR_MSG_FMT
    size_t msg_buf_size = strlen(filepath) + 32 + 32 + 11 + strlen(msg);
    char* msg_buf = (char*) malloc(msg_buf_size);
    snprintf(msg_buf, msg_buf_size, ERROR_MSG_FMT, filepath, line, col, msg);

    return msg_buf;
}
