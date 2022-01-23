#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>

// reverse all the letters in stdin, preserving case
// and position of non-letters
//
// "Hi there!" -> "Re ehtih!"

// initial buffer size for getInput
#define INITIAL_SIZE (1024)
#define SIZE_MULTIPLIER (2)

// read stdin until EOF
// *n gets number of characters read
// return value is pointer malloc'd bytes
// (caller must free)
// Note: allows binary data, so no null terminator!
char *
getInput(size_t *n)
{
    size_t size = INITIAL_SIZE;  // space allocated to buf
    char *buf = malloc(size);
    int c;

    assert(buf);

    *n = 0;

    while((c = getchar()) != EOF) {

        if(*n >= size) {
            size *= SIZE_MULTIPLIER;
            buf = realloc(buf, size);
            assert(buf);
        }

        buf[(*n)++] = c;
    }

    buf = realloc(buf, *n);

    return buf;
}

// return c with case of reference
char
matchCase(char reference, char c)
{
    if(isupper(reference) && islower(c)) {
        c = toupper(c);
    } else if(islower(reference) && isupper(c)) {
        c = tolower(c);
    }

    return c;
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // read everything
    size_t n;
    char *s = getInput(&n);

    // algorithm:
    // 
    // i is next position to print, starts at 0
    // j is upper bound on next alpha character, starts a n-1
    //
    // when s[i] is an alpha char, move j down until it hits an alpha,
    // then print s[j] (with case swapped as needed) instead

    size_t i = 0;
    size_t j = n-1;

    for(; i < n; i++) {
        if(isalpha(s[i])) {

            // find actual character to print
            while(!isalpha(s[j])) {
                j--;
            }

            putchar(matchCase(s[i], s[j]));

            j--;

        } else {

            // just print it
            putchar(s[i]);

        }
    } 

    free(s);

    return 0;
}
