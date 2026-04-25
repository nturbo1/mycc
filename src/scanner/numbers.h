#ifndef SRC_SCANNER_NUMBERS_H
#define SRC_SCANNER_NUMBERS_H

#include "scanner.h"
#include "token.h"

#include <stdbool.h>

typedef enum { BASE_2, BASE_8, BASE_10, BASE_16 } NumBase;

// Scans an integer literal in a given base.
// If there's a lexical error, it sets the scanner error, s->err, to an appropriate error type and
// returns.
// The `is_digit` parameter is a function that determines if a character represents a valid digit
// in the given base.
Number* scan_number_lit(Scanner* s, NumBase base, bool (*is_digit) (char));

// Scans for a number (decimal, hex, binary, octal).
// Sets the scanner error (s->err) to an appropriate error value, if there is a lexical error.
Number* scan_number(Scanner* s);

// Syntax:
//  (1) digit-sequence decimal-exponent suffix (optional)
//          digit-sequence representing a whole number without a decimal separator,
//          in this case the exponent is not optional: 1e10, 1e-5L.
//
//  (2) digit-sequence . decimal-exponent (optional) suffix (optional)
//          digit-sequence representing a whole number with a decimal separator,
//          in this case the exponent is optional: 1., 1.e-2.
//
//  (3) digit-sequence (optional) . digit-sequence decimal-exponent (optional) suffix (optional)
//          digit-sequence representing a fractional number.
//          The exponent is optional: 3.14, .1f, 0.1e-1L.
Number* scan_float(Scanner* s);

// Scans the fractional part of a number literal.
// Could be a part of a number literal already being scanned or could be a number literal that consists
// of only a fractional part and/or an exponent.
//
// Syntax:
//  . decimal-exponent (optional) suffix (optional)
//          digit-sequence representing a whole number with a decimal separator,
//          in this case the exponent is optional: ., .e-2., .14, .1f, .1e-1L
//
// In case of a lexical error, it sets the scanner error, `s->err`, to an appropriate error type and
// returns `NULL`;
Number* scan_fraction(Scanner* s);

bool is_dec_digit(char ch);
bool is_hex_digit(char ch);
bool is_bin_digit(char ch);
bool is_oct_digit(char ch);

#endif // SRC_SCANNER_NUMBERS_H
