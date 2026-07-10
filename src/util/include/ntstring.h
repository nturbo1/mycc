#ifndef SRC_UTIL_INCLUDE_STRING_H
#define SRC_UTIL_INCLUDE_STRING_H

#include <stddef.h>

/* ================================================================================ */
/* ==================================== String ==================================== */
/* ================================================================================ */

// Represents a string type that contains variable size characters.
typedef struct
{
    const size_t char_size; // in bytes
    const size_t length; // # of characters excluding the NULL-terminator
    const char* bytes; // NULL terminated
}
String;

/**
 * Creates a new String object and returns a pointer to it.
 *
 * @param char_size The size of one character in bytes.
 * @param size The size of the string bytes.
 * @param bytes The string bytes.
 * @return A pointer to the newly created String object.
 */
String* new_string(const size_t char_size, const size_t size, const char* const bytes);

/* ================================================================================ */
/* ================================ StringBuilder ================================= */
/* ================================================================================ */

typedef struct
{
    const size_t char_size; // in bytes
    size_t length; // # of characters excluding the NULL-terminator
    char* buf;
    size_t capacity; // buffer size in bytes
}
StringBuilder;

/**
 * Creates a new StringBuilder object and returns a pointer to it.
 *
 * @param char_size The size of one character in bytes.
 * @param size The size of the string bytes.
 * @param bytes The string bytes.
 * @param capacity The capacity of the underlying buffer in bytes.
 * @return A pointer to the newly created StringBuilder object.
 */
StringBuilder* new_string_builder(const size_t char_size,
                                  const size_t size,
                                  char* const bytes,
                                  const size_t capacity);

#endif // SRC_UTIL_INCLUDE_STRING_H
