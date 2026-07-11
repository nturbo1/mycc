#include "ntstring.h"
#include "ntassert.h"

#include <stdlib.h>
#include <stdbool.h>

/* ================================================================================ */
/* ==================================== String ==================================== */
/* ================================================================================ */

inline static bool is_null_terminated(const size_t char_size, const size_t size, const u8* const bytes);
inline static void set_char_at(const size_t index,
                               const size_t char_size,
                               const u8* const char_bytes,
                               const size_t size,
                               u8* const bytes);

String* new_string(const size_t char_size, const size_t str_bytes_size, const u8* const str_bytes)
{
    assert_always(MAX_CHAR_SIZE >= char_size, "Character size %zu is too big for a String object.", char_size);
    assert_always(str_bytes_size >= char_size,
                  "Not enough size for a String bytes to hold a single character.");
    assert_always(str_bytes_size % char_size == 0,
                  "A String bytes size MUST be divisible by the character size.");

    const bool str_bytes_null_terminated = is_null_terminated(char_size, str_bytes_size, str_bytes);
    size_t str_size = str_bytes_null_terminated ? str_bytes_size : (str_bytes_size + char_size);
    const size_t str_length = (str_size / char_size) - 1; // the NULL-terminator character is not counted

    String* str = (String*) malloc(sizeof(String));
    assert_always(str != NULL, "Failed to allocate memory for a String instance!");

    u8* buf = (u8*) malloc(str_size);
    assert_always(buf != NULL, "Failed to allocate memory for the bytes buffer of a String instance!");
    if (!str_bytes_null_terminated)
    {
        u8 null_char[MAX_CHAR_SIZE];
        for (size_t null_char_idx = 0; null_char_idx < char_size; null_char_idx++)
            null_char[null_char_idx] = 0;
        // append the NULL-terminator character
        set_char_at(str_length, char_size, null_char, str_size, buf);
    }

    for (size_t i = 0; i < str_bytes_size; i++)
        buf[i] = str_bytes[i];

    *((size_t*)&(str->char_size)) = char_size;
    *((size_t*)&(str->length)) = str_length;
    *((char**)&(str->bytes)) = buf;

    return str;
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
static void sb_expand(StringBuilder* const sb)
{
    const size_t new_cap = 2 * sb->capacity;
    assert_always(new_cap > sb->capacity, "Integer overflow: StringBuilder capacity is too big!");
    char* new_buf = malloc(sizeof(sb->char_size) * 2 * sb->capacity);
}

StringBuilder* new_string_builder(const size_t char_size,
                                  const size_t str_bytes_size,
                                  const u8* const str_bytes,
                                  const size_t capacity)
{
    assert_always(MAX_CHAR_SIZE >= char_size,
                  "Character size %zu is too big for a StringBuilder object.",
                  char_size);
    assert_always(str_bytes_size >= char_size,
                  "Not enough size for a StringBuilder bytes to hold a single character.");
    assert_always(str_bytes_size % char_size == 0,
                  "A StringBuilder bytes size MUST be divisible by the character size.");

    const bool str_bytes_null_terminated = is_null_terminated(char_size, str_bytes_size, str_bytes);
    size_t str_size = str_bytes_null_terminated ? str_bytes_size : (str_bytes_size + char_size);
    const size_t str_length = (str_size / char_size) - 1; // the NULL-terminator character is not counted

    const size_t sb_capacity = capacity >= str_size ? capacity : str_size;
    u8* sb_buf = (u8*) malloc(sb_capacity);
    assert_always(sb_buf != NULL, "Failed to allocate memory for the bytes buffer of a StringBuilder instance!");

    if (!str_bytes_null_terminated)
    {
        u8 null_char[MAX_CHAR_SIZE];
        for (size_t null_char_idx = 0; null_char_idx < char_size; null_char_idx++)
            null_char[null_char_idx] = 0;
        // append the NULL-terminator character
        set_char_at(str_length, char_size, null_char, str_size, sb_buf);
    }

    StringBuilder* sb = (StringBuilder*) malloc(sizeof(StringBuilder));
    assert_always(sb != NULL, "Failed to allocate memory for a StringBuilder instance!");

    for (size_t i = 0; i < str_bytes_size; i++)
        sb_buf[i] = str_bytes[i];

    *((size_t*) &(sb->char_size)) = char_size;
    sb->length = str_length;
    sb->buf = sb_buf;
    sb->capacity = sb_capacity;

    return sb;
}

inline static bool is_null_terminated(const size_t char_size, const size_t size, const u8* const bytes)
{
    if (size < char_size)
        return false;

    for (size_t i = size - char_size; i < size; i++)
        if (bytes[i] != 0)
            return false;

    return true;
}

inline static void set_char_at(const size_t index,
                               const size_t char_size,
                               const u8* const char_bytes,
                               const size_t size,
                               u8* const bytes)
{
    assert_always(size >= (index + 1) * char_size, "Index out of bounds for a bytes array.");
    u8* idx_char_bytes = bytes + (index * char_size);
    for (size_t i = 0; i < char_size; i++)
        idx_char_bytes[i] = char_bytes[i];
}
