#ifndef SRC_INCLUDE_ERROR_H
#define SRC_INCLUDE_ERROR_H

#include <stddef.h>

typedef enum Error {
    NO_ERROR,
    INVALID_IDENTIFIER_NAME,
    INVALID_NUMBER,
    INVALID_TOKEN,
    INCOMPATIBLE_NUMBER_SUFFIX,
} Error;

const char* err_name(Error err);
const char* get_err_msg(Error err, const char* filepath, size_t line, size_t col);

typedef struct ErrInfo {
    const char* name;
    const char* msg;
    const size_t col;
    const size_t line;
} ErrInfo;

ErrInfo* new_errinfo(Error err, const char* filepath, const size_t line, const size_t col);

#endif // SRC_INCLUDE_ERROR_H
