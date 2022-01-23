#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "printFixed.h"

// compute base**exponent
// doesn't deal with overflow
static long long
intExp(long long base, unsigned int exponent)
{
    long long result = 1;

    while(exponent-- > 0) {
        result *= base;
    }

    return result;
}

// print a single digit
static void
printDigit(int digit)
{
    putchar('0' + digit);
}

// probably don't need this level of generality,
// but a good habit
#define BASE (10)             // base for decimal expansion
#define DIGITS_PER_GROUP (3)  // digits per group

void
printFixed(long long number, char separator, char decimalPoint, unsigned int precision)
{
    unsigned long long abs;     // absolute value of number

    // print sign bit if needed and convert to unsigned long long
    if(number < 0) {
        putchar('-');
        abs = -number;
    } else {
        abs = number;
    }

    // split up abs into integer and fractional parts
    unsigned long long divisor = intExp(BASE, precision);
    unsigned long long integerPart = abs / divisor;
    unsigned long long fractionalPart = abs % divisor;

    // for grabbing digits
    int digit = 0;      // which digit should we print next?
    unsigned long long digitValue = 1; // value of digit position, 10^digit
    int firstDigit;     // first digit

    // print the integerPart
    // 0 is a special case
    if(integerPart == 0) {
        printDigit(0);
    } else {
        // find first digit
        // we have to be a little careful here to prevent overflow
        while(integerPart / digitValue >= BASE) {
            digit++;
            digitValue *= BASE;
        }

        while(digit >= 0) {
            // print first digit
            firstDigit = integerPart / digitValue;
            printDigit(firstDigit);

            // remove first digit
            integerPart -= firstDigit * digitValue;

            // maybe print separator
            if(digit % DIGITS_PER_GROUP == 0 && digit != 0) {
                putchar(separator);
            } 

            // update digit and digitValue
            digit--;
            digitValue /= BASE;
        }
    }

    // print decimal point
    putchar(decimalPoint);

    // print remaining digits
    // we can't just use printf for this because we can't
    // specify width. So we'll re-use digit and digitValue.
    digit = precision - 1;
    digitValue = divisor / 10; 

    while(digit >= 0) {
        // there is some duplication here
        // but it is annoying to factor out
        firstDigit = fractionalPart / digitValue;

        printDigit(firstDigit);

        fractionalPart -= firstDigit * digitValue;

        digit--;
        digitValue /= BASE;
    }
}
