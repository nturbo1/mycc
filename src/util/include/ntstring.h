#ifndef SRC_UTIL_INCLUDE_STRING_H
#define SRC_UTIL_INCLUDE_STRING_H

#include "base_inc.h"

#include <stddef.h>

#define MAX_CHAR_SIZE 8 // in bytes

/* ================================================================================ */
/* ==================================== String ==================================== */
/* ================================================================================ */

// Represents immutable string type that contains one or more bytes sized characters.
typedef struct
{
    const size_t char_size; // in bytes
    const size_t length; // # of characters excluding the NULL-terminator character
    const u8* bytes; // NULL terminated, so bytes size = (length + 1) * char_size
}
String;

/**
 * Creates a new String object and returns a pointer to it.
 *
 * - If a given string bytes are not NULL-terminated, then a NULL-terminated
 * character with a given character size is appended at the end of the copied
 * string bytes of the String object.
 *
 * @param char_size The size of one character in bytes.
 * @param str_bytes_size The size of the string bytes.
 * @param str_bytes The string bytes.
 * @return A pointer to the newly created String object.
 */
String* new_string(const size_t char_size, const size_t str_bytes_size, const u8* const str_bytes);

/* ================================================================================ */
/* ================================ StringBuilder ================================= */
/* ================================================================================ */

// StringBuilder type holds information about mutable string bytes with one or
// more bytes sized characters. Mostly used for dynamically constructing a
// string object or literal, which are immutable.
typedef struct
{
    const size_t char_size; // in bytes
    size_t length; // # of characters excluding the NULL-terminator character
    u8* buf;
    size_t capacity; // buffer size in bytes
}
StringBuilder;

/**
 * Creates a new StringBuilder object and returns a pointer to it.
 *
 * - If a given string bytes are not NULL-terminated, then a NULL-terminated
 * character with a given character size is appended at the end of the copied
 * string bytes of the StringBuilder object.
 * - If a given capacity is less than the underlying byte buffer size, then the
 * StringBuilder capacity is set to the buffer size.
 *
 * @param char_size The size of one character in bytes.
 * @param size The size of the string bytes.
 * @param bytes The string bytes.
 * @param capacity The capacity of the underlying buffer in bytes.
 * @return A pointer to the newly created StringBuilder object.
 */
StringBuilder* new_string_builder(const size_t char_size,
                                  const size_t str_bytes_size,
                                  const u8* const str_bytes,
                                  const size_t capacity);

#endif // SRC_UTIL_INCLUDE_STRING_H
