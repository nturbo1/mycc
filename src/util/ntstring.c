#include "ntstring.h"
#include "ntassert.h"

#include <stdlib.h>
#include <stdbool.h>

/* ================================================================================ */
/* ==================================== String ==================================== */
/* ================================================================================ */

// Counts the # of bytes until a NULL-terminator byte character is encountered
// or the bytes array end is reached by iterating through a given string bytes.
// 
// @param bytes String bytes.
// @param Size of the string bytes.
// @return # of byte characters excluding the NULL-terminator character.
inline static size_t length(const U8* const bytes, const size_t bytes_size);

String* new_string(const U8* const bytes, const size_t bytes_size)
{
    const size_t str_length = length(bytes, bytes_size);
    String* str = (String*) malloc(sizeof(String));
    assert_always(str != NULL, "Failed to allocate memory for a String instance!");
    U8* buf = (U8*) malloc(str_length + 1);
    assert_always(buf != NULL, "Failed to allocate memory for the bytes buffer of a String instance!");
    for (size_t i = 0; i < bytes_size; i++)
        buf[i] = bytes[i];
    buf[str_length] = 0;

    *((size_t*)&(str->length)) = str_length;
    *((char**)&(str->bytes)) = buf;

    return str;
}

const U8* get_string_bytes(String* str)
{
    if (str == NULL)
        return NULL;

    return str->bytes;
}

/* ================================================================================ */
/* ================================ StringBuilder ================================= */
/* ================================================================================ */

// Replaces the StringBuilder bytes buffer with a larger buffer that contains the copy
// of the sequence of StringBuilder bytes and some extra space for new bytes.
//
// Usually called when the StringBuilder bytes buffer capacity is full or reached a
// certain threshold and there is not enough space in the buffer for a new character
// bytes. Function sb_expand doesn't check for a full capacity or a threshold
// specifics, it just expands the StringBuilder bytes buffer. The conditions for the
// buffer expansion SHOULD be checked before calling the function sb_expand!
// static void sb_expand(StringBuilder* const sb)
// {
//     const size_t new_cap = 2 * sb->capacity;
//     assert_always(new_cap > sb->capacity, "Integer overflow: StringBuilder capacity is too big!");
//     char* new_buf = malloc(sizeof(sb->char_size) * 2 * sb->capacity);
// }

StringBuilder* new_string_builder(const U8* const bytes,
                                  const size_t bytes_size,
                                  const size_t capacity)
{
    const size_t str_length = length(bytes, bytes_size);
    const size_t str_bytes_size = str_length + 1;

    const size_t sb_capacity = capacity >= str_bytes_size ? capacity : str_bytes_size;
    U8* sb_buf = (U8*) malloc(sb_capacity);
    assert_always(sb_buf != NULL,
            "Failed to allocate memory for the bytes buffer of a StringBuilder instance!");

    StringBuilder* sb = (StringBuilder*) malloc(sizeof(StringBuilder));
    assert_always(sb != NULL, "Failed to allocate memory for a StringBuilder instance!");

    for (size_t i = 0; i < str_length; i++)
        sb_buf[i] = bytes[i];
    sb_buf[str_length] = 0; // append NULL-terminator byte character

    sb->length = str_length;
    sb->capacity = sb_capacity;
    sb->buf = sb_buf;

    return sb;
}

inline static size_t length(const U8* const bytes, const size_t bytes_size)
{
    size_t len = 0;
    for (size_t i = 0; i < bytes_size; i++)
    {
        if (bytes[i] == 0)
            break;
        len++;
    }

    return len;
}
