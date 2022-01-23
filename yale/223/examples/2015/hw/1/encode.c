/*
 * Encode text on stdin by alphabet rotation with shifting offset.
 *
 * Initially, each character 'A'..'Z' or 'a'..'z' is rotated 17 positions.
 *
 * After encoding an uppercase letter, the offset is increased by 5 (mod 26).
 *
 * After encoding a lowercase letter, the offset is increased by 3 (mod 26).
 *
 * These parameters are set using the INITIAL_OFFSET, UPPERCASE_STEP, and LOWERCASE_STEP
 * constants defined below.
 *
 */
#include <stdio.h>

#define INITIAL_OFFSET (17)

#define UPPERCASE_STEP (5)
#define LOWERCASE_STEP (3)

#define MODULUS ('z' - 'a' + 1)

int
main(int argc, char **argv)
{
    int offset = INITIAL_OFFSET;
    int c;

    while((c = getchar()) != EOF) {
        if(('a' <= c) && (c <= 'z')) {
            putchar(((c - 'a') + offset) % MODULUS + 'a');
            offset = (offset + LOWERCASE_STEP) % MODULUS;
        } else if(('A' <= c) && (c <= 'Z')) {
            putchar(((c - 'A') + offset) % MODULUS + 'A');
            offset = (offset + UPPERCASE_STEP) % MODULUS;
        } else {
            putchar(c);
        }
    }

    return 0;
}
