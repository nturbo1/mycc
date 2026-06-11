#ifndef SRC_INCLUDE_ERROR_H
#define SRC_INCLUDE_ERROR_H

#include <stddef.h>

typedef enum ErrorType {
    NO_ERROR_TYPE,
    INVALID_IDENTIFIER_NAME_ERROR_TYPE,
    INVALID_NUMBER_ERROR_TYPE,
    INVALID_TOKEN_ERROR_TYPE,
    INCOMPATIBLE_NUMBER_SUFFIX_ERROR_TYPE,
    EOF_ERROR_TYPE,
} ErrorType;

const char* err_name(ErrorType err);
const char* get_err_msg(ErrorType err, const char* filepath, size_t line, size_t col);

typedef struct Error {
    const char* name;
    const char* msg;
    const size_t col;
    const size_t line;
} Error;

Error* new_err(ErrorType err, const char* filepath, const size_t line, const size_t col);

#endif // SRC_INCLUDE_ERROR_H
