#include "error.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char* err_names[] = {
    [NO_ERROR_TYPE] = "",
    [INVALID_IDENTIFIER_NAME_ERROR_TYPE] = "Invalid identifer name",
    [INVALID_NUMBER_ERROR_TYPE] = "Invalid number",
    [INVALID_TOKEN_ERROR_TYPE] = "Invalid token",
    [INCOMPATIBLE_NUMBER_SUFFIX_ERROR_TYPE] = "Incompatible number suffix",
};

static const char* err_msg[] = {
    [NO_ERROR_TYPE] = "",
    [INVALID_IDENTIFIER_NAME_ERROR_TYPE] = "Invalid identifer name",
    [INVALID_NUMBER_ERROR_TYPE] = "Invalid number",
    [INVALID_TOKEN_ERROR_TYPE] = "Invalid token",
    [INCOMPATIBLE_NUMBER_SUFFIX_ERROR_TYPE] = "Incompatible number suffix",
};

const char* err_name(ErrorType err)
{
    return err_names[err];
}

#define ERROR_MSG_FMT "%s:%zu:%zu: error: %s"
const char* get_err_msg(ErrorType err, const char* filepath, size_t line, size_t col)
{
    const char* msg = err_msg[err];
    // the msg_buf_size value depends on the value of macro ERROR_MSG_FMT
    size_t msg_buf_size = strlen(filepath) + 32 + 32 + 11 + strlen(msg);
    char* msg_buf = (char*) malloc(msg_buf_size);
    snprintf(msg_buf, msg_buf_size, ERROR_MSG_FMT, filepath, line, col, msg);

    return msg_buf;
}

Error* new_errinfo(ErrorType err, const char* filepath, const size_t line, const size_t col)
{
    Error* errinfo = (Error*) malloc(sizeof(Error));
    errinfo->name = err_name(err);
    errinfo->msg = get_err_msg(err, filepath, line, col);
    *(size_t*)&(errinfo->line) = line;
    *(size_t*)&(errinfo->col) = col;

    return errinfo;
}
