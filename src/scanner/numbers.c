#include "numbers.h"
#include "hashtable.h"
#include "darray.h"
#include "error.h"

#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Converts a char to a digit.
// Updates the error value pointed by a given err parameter accordingly, if the character is
// not a digit.
static long int char_to_dig(Error* err_ptr, char ch, NumBase base);

// Converts a given char sequence, num_chars, into a number value according to a given base.
//
// The num_chars is expected to be of type DArray<char> meaning it directly stores the char values
// as (void*) in the array buffer. So, the elements should be properly reverted back to char type
// when accessed from the array.
//
// Updates the error value pointed by a given err parameter, if the char sequence contains an
// invalid or non-digit character.
static long int txt_to_num(DArray* num_chars, NumBase base, Error* err_ptr);

Number* scan_number_lit(Scanner* s, NumBase base, bool (*is_digit) (char))
{
    s->err = NO_ERROR;
    char ch = peek_next(s);

    if (ch == EOF) {
        s->err = INVALID_NUMBER;
        return NULL;
    }
    if (!is_digit(ch)) {
        s->err = INVALID_NUMBER;
        return NULL;
    }

    DArray* num_chars = init_darray(NULL, 16, 1);
    assert(num_chars != NULL);
    ch = next_char(s);
    darray_add(num_chars, &ch, 1);
    ch = peek_next(s);

    while (is_digit(ch))
    {
        ch = next_char(s);
        darray_add(num_chars, (void*) &ch, 1);
        ch = peek_next(s);
    }

    switch (ch) {
    case ';':
    case ')':
    case ']':
    case '}':
        return new_number(txt_to_num(num_chars, base, &s->err), 0.0, 0, TOKEN_TYPE_INT_LIT);
    case '.':; // Just to bypass the error: a label can only be part of a statement and a declaration is not a statement
                // [-Werror=free-labels]
        // TODO: Better evaluate the char sequence to a number as it's being scanned instead of storing
        //       the whole char sequence into a DArray first and then evaluate it, basically scanning
        //       it twice.
        long int integral = txt_to_num(num_chars, base, &s->err);
        Number* number = scan_fraction(s);
        *(long int*)&number->integral = integral;
        return number;
    default:
        if (is_whitespace(ch)) {
            return new_number(txt_to_num(num_chars, base, &s->err), 0.0, 0, TOKEN_TYPE_INT_LIT);
        }
        s->err = INVALID_NUMBER;
        return NULL;
    }
}

Number* scan_fraction(Scanner* s)
{
    printf("TODO: IMPLEMENT scan_fraction FUNCTION!!! s = %p\n", (void*)s);
    return NULL;
}

Number* scan_number(Scanner* s)
{
    char ch = peek_next(s);

    if (ch == EOF)
    {
        s->err = INVALID_NUMBER;
        return NULL;
    }
    else if (ch == '0')
    {
        next_char(s); // skip the 0
        ch = peek_next(s);
        switch (ch) {
        case ';':
        case ')':
        case ']':
        case '}': ; // Just to bypass the error: a label can only be part of a statement and a declaration is not a statement
                // [-Werror=free-labels]
            return new_number(0, 0.0, 0, TOKEN_TYPE_INT_LIT);
        case 'x':
        case 'X':
            next_char(s); // skip 'x' or 'X'
            return scan_number_lit(s, BASE_16, is_hex_digit);
        case 'b':
        case 'B':
            next_char(s); // skip 'b' or 'B'
            return scan_number_lit(s, BASE_2, is_hex_digit);
        case '.':
            return scan_fraction(s);
        default:
            if (is_whitespace(ch)) {
                return new_number(0, 0.0, 0, TOKEN_TYPE_INT_LIT);
            }
            return scan_number_lit(s, BASE_8, is_hex_digit);
        }
    }
    else if (is_dec_digit(ch))
    {
        return scan_number_lit(s, BASE_10, is_hex_digit);
    }
    else
    {
        s->err = INVALID_NUMBER;
        return NULL;
    }
}

bool is_dec_digit(char ch)
{
    return '0' <= ch && ch <= '9';
}

bool is_hex_digit(char ch)
{
    return ('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F');
}

bool is_bin_digit(char ch)
{
    return ch == '0' || ch == '1';
}

bool is_oct_digit(char ch)
{
    return '0' <= ch && ch <= '7';
}

static long int char_to_dig(Error* err_ptr, char ch, NumBase base)
{
    switch (base) {
    case BASE_10:
        switch (ch) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            *err_ptr = INVALID_NUMBER;
            return 0;
        }
    case BASE_2:
        switch (ch) {
        case '0':
            return 0;
        case '1':
            return 1;
        default:
            *err_ptr = INVALID_NUMBER;
            return 0;
        }
    case BASE_8:
        switch (ch) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        default:
            *err_ptr = INVALID_NUMBER;
            return 0;
        }
    case BASE_16:
        switch (ch) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
        default:
            *err_ptr = INVALID_NUMBER;
            return 0;
        }
        break;
    default:
        printf("Unknown number base were passed to char to digit conversion function: %d\n", base);
        abort();
    }
}

static long int txt_to_num(DArray* num_chars, NumBase base, Error* err_ptr)
{
    assert(num_chars != NULL);
    long int radix = 10;
    switch (base) {
    case BASE_10:
        break;
    case BASE_2:
        radix = 2;
        break;
    case BASE_8:
        radix = 8;
        break;
    case BASE_16:
        radix = 16;
        break;
    default:
        printf("Unknown number base were passed to char sequence to number conversion function: %d\n", base);
        abort();
    }

    long int number = 0;
    size_t num_chars_len = num_chars->length;

    for (size_t i = 0; i < num_chars_len; ++i)
    {
        char ch = * (char*) darray_get_at(num_chars, num_chars_len - 1 - i);

        *err_ptr = NO_ERROR;
        long int digit = char_to_dig(err_ptr, ch, base);
        if (*err_ptr != NO_ERROR) {
            return 0;
        }

        number += ((long int) pow(radix, i) * digit);
    }

    return number;
}
