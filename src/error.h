#ifndef SRC_ERROR_H
#define SRC_ERROR_H

#include <stddef.h>

typedef enum {
    NO_ERROR,
    INVALID_IDENTIFIER_NAME,
    INVALID_NUMBER,
    INVALID_TOKEN
} Error;

const char* err_name(Error err);
const char* get_err_msg(Error err, const char* filepath, size_t line, size_t col);

#endif // SRC_ERROR_H
