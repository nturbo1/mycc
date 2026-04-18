#ifndef SRC_ERROR_H
#define SRC_ERROR_H

typedef enum {
    INVALID_IDENTIFIER_NAME,
    INVALID_NUMBER,
    INVALID_TOKEN
} Error;

const char* err_name(Error err);

#define EXIT_WITH_ERROR(err, line, column, msg)\
    do {\
        printf("[Error] %s at %zu:%zu\n\t%s\n",\
                err_name(err),\
                line,\
                column,\
                msg);\
        abort();\
    } while(0)

#endif // SRC_ERROR_H
