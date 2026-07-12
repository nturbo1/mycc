#ifndef SRC_UTIL_INCLUDE_STRING_H
#define SRC_UTIL_INCLUDE_STRING_H

#include "base_inc.h"

#include <stddef.h>

/* ================================================================================ */
/* ==================================== String ==================================== */
/* ================================================================================ */

// Represents immutable string type.
typedef struct
{
    size_t length; // # of characters excluding the NULL-terminator character
    const U8* bytes; // NULL terminated
}
String;

/**
 * Creates a new String object and returns a pointer to it.
 *
 * - If a given string bytes are not NULL-terminated, then a NULL-terminated
 *   byte character is appended at the end of the copied string bytes of the
 *   String object.
 * - Any trailing character bytes after a NULL-terminator byte character is
 *   discarded.
 *
 * @param bytes_size The size of the string bytes.
 * @param bytes The string bytes.
 * @return A pointer to the newly created String object.
 */
String* new_string(const U8* const bytes, const size_t bytes_size);

// Returns a pointer to the immutable bytes of a given String object.
const U8* get_string_bytes(String* str);

/* ================================================================================ */
/* ================================ StringBuilder ================================= */
/* ================================================================================ */

// StringBuilder type holds information about mutable string bytes with one or
// more bytes sized characters. Mostly used for dynamically constructing a
// string object or literal, which are immutable.
typedef struct
{
    size_t length; // # of characters excluding the NULL-terminator character
    size_t capacity; // buffer size in bytes
    U8* buf;
}
StringBuilder;

/**
 * Creates a new StringBuilder object and returns a pointer to it.
 *
 * - If a given string bytes are not NULL-terminated, then a NULL-terminated
 *   byte character is appended at the end of the copied string bytes of the
 *   StringBuilder object.
 * - Any trailing character bytes after a NULL-terminator byte character is
 *   discarded.
 * - If a given capacity is less than the underlying byte buffer size, then the
 *   StringBuilder capacity is set to the buffer size.
 *
 * @param bytes_size The size of the string bytes.
 * @param bytes The string bytes.
 * @param capacity The capacity of the underlying buffer in bytes.
 * @return A pointer to the newly created StringBuilder object.
 */
StringBuilder* new_string_builder(const U8* const bytes,
                                  const size_t bytes_size,
                                  const size_t capacity);

#endif // SRC_UTIL_INCLUDE_STRING_H
