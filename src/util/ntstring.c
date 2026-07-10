#include "ntstring.h"
#include "ntassert.h"

#include <stdlib.h>

/* ================================================================================ */
/* ==================================== String ==================================== */
/* ================================================================================ */

String* new_string(const size_t size, const size_t char_size, const char* bytes)
{
    assert_always(size >= char_size, "Not enough size for a String bytes to hold a single character.");
    const size_t buf_size = size;
    if (bytes[size - 1] != 0)
    {
        assert_always(
                size % char_size == 0,
                "Non-NULL terminated String bytes size MUST be divisible by the character size.");
        buf_size = size + 1;
    }
    else
    {
        assert_always(
                (size - 1) % char_size == 0,
                "String bytes size excluding the NULL-terminator MUST be divisible by the character size.");
    }

    String* str = (String*) malloc(sizeof(String));
    assert_always(str != NULL, "Failed to allocate memory for a String instance!");

    char* buf = (char*) malloc(buf_size);
    assert_always(buf != NULL, "Failed to allocate memory for the bytes buffer of a String instance!");
    buf[buf_size - 1] = 0;

    for (size_t i = 0; i < size; i++)
        buf[i] = bytes[i];

    *((size_t*) str->char_size) = char_size;
    *((size_t*) str->length) = (buf_size - 1) / char_size;
    *((char**) str->bytes) = buf;

    return str;
}

StringBuilder* new_string_builder(const size_t char_size,
                                  const size_t size,
                                  char* const bytes,
                                  const size_t capacity)
{
    assert_always(size >= char_size, "Not enough size for a StringBuilder bytes to hold a single character.");
    const size_t buf_size = size;
    if (bytes[size - 1] != 0)
    {
        assert_always(
                size % char_size == 0,
                "Non-NULL terminated StringBuilder bytes size MUST be divisible by the character size.");
        buf_size = size + 1;
    }
    else
    {
        assert_always(
                (size - 1) % char_size == 0,
                "StringBuilder bytes size excluding the NULL-terminator MUST be divisible by"
                "the character size.");
    }

    StringBuilder* sb = (StringBuilder*) malloc(sizeof(StringBuilder));
    assert_always(sb != NULL, "Failed to allocate memory for a StringBuilder instance!");

    char* buf = (char*) malloc(buf_size);
    assert_always(buf != NULL, "Failed to allocate memory for the bytes buffer of a StringBuilder instance!");
    buf[buf_size - 1] = 0;

    for (size_t i = 0; i < size; i++)
        buf[i] = bytes[i];

    *((size_t*) sb->char_size) = char_size;
    sb->length = (buf_size - 1) / char_size;
    sb->bytes = bytes;
    sb->capacity = capacity;

    return sb;
}
