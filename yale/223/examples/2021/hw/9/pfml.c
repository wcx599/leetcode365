#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "bytes.h"

// constants for Pancake Flipper Markup Language
#define PFML_OPEN_DELIMITER ('{')
#define PFML_CLOSE_DELIMITER ('}')

// Utilities for flipping strings.

// flip all characters in b
static void
flipBytes(Bytes b)
{
    unsigned char *start = bytesData(b);
    unsigned char *end = bytesData(b) + bytesLen(b) - 1;

    while(start < end) {
        unsigned char temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}
         

// PFML reader implemented as a recursive descent parser

// reads a sequence of characters and groups,
// stopping if it reaches PFML_CLOSE_DELIMITER or EOF
static Bytes
readSequence(FILE *f)
{
    Bytes b = bytesCreate();
    Bytes b2;  // for recursion

    int c;

    while((c = getc(f)) != EOF) {
        switch(c) {

            case PFML_OPEN_DELIMITER:
                // recurse and flip
                b2 = readSequence(f);
                flipBytes(b2);
                bytesAppendBytes(b, b2);
                bytesDestroy(b2);
                break;

            case PFML_CLOSE_DELIMITER:
                goto done;

            default:
                bytesAppendChar(b, c);
                break;

        }
    }

done:
    return b;
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    Bytes b = readSequence(stdin);
    bytesWrite(b, stdout);
    bytesDestroy(b);

    return 0;
}
