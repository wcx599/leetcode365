#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>

#define MAX_RUN (10)  // longest run to encode

void
printWithCount(int count, int c)
{
    putchar(count - 1 + '0');
    putchar(c);
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // Simple RLE encoder.
    //
    // A digit x in 0-9 indicates the following character
    // should be repeated an extra x times.
    //
    // To allow digits in input, digits are always encoded.
    //
    // Non-digits are only encoded if doing so reduces length,
    // which means when there are three or more copies.
    //
    // Example: 1aabbb -> 01aa2b
    //
    // If a character occurs more than 10 times in a row, encode
    // it in blocks of 10 as long as possible:
    //
    // Example: xxxxxxxxxxxxxxxxx -> 9x6x
    
    int c;       // character to encode
    int cnext;   // next character
    int count;   // how many c's did we get?

    while((c = getchar()) != EOF) {
        // count the c's up to MAX_RUN
        for(count = 1; (cnext = getchar()) == c && count < MAX_RUN; count++);

        // push back extra character
        ungetc(cnext, stdin);

        if(isdigit(c)) {
            // always use count
            printWithCount(count, c);
        } else {
            switch(count) {
                case 2:
                    putchar(c);
                    // fall through
                case 1:
                    putchar(c);
                    break;
                default:
                    printWithCount(count, c);
                    break;
            }
        }
    }

    return 0;
}
