#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // Simple RLE decoder.
    //
    // A digit x in 0-9 indicates the following character
    // (if not EOF)
    // should be repeated an extra x times.
    // Example: 01234a -> 1333aaaaa

    int c;     // current character
    int cnext; // next character

    while((c = getchar()) != EOF) {
        if(isdigit(c)) {
            // grab another character and repeat it
            if((cnext = getchar()) != EOF) {
                for(int count = 0; count < c - '0' + 1; count++) {
                    putchar(cnext);
                }
            }
        } else {
            // no repeat, just copy through
            putchar(c);
        }
    }

    return 0;
}
