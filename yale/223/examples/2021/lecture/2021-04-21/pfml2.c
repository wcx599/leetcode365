#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

// constants for Pancake Flipper Markup Language
#define PFML_OPEN_DELIMITER ('{')
#define PFML_CLOSE_DELIMITER ('}')

// Utilities for flipping strings.

// flip all characters in s
static void
flipString(char *s)
{
    size_t len = strlen(s);
    for(size_t i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

#define BUFFER_INITIAL_SIZE (16)
#define BUFFER_SIZE_MULTIPLIER (2)

// PFML reader implemented as a recursive descent parser

// reads a sequence of characters and groups,
// stopping if it reaches PFML_CLOSE_DELIMITER or EOF
//
// returns malloc'd string resulting from this sequence
//
// Note: does not handle null characters!
static char *
readSequence(FILE *f)
{
    int c;
    size_t size = BUFFER_INITIAL_SIZE;   // space allocated for buffer
    size_t len = 0;                      // number of character in buffer (not counting nul)
    char *buffer = malloc(BUFFER_INITIAL_SIZE);

    char *b2; // malloc'd data from recursive call
    char charBuffer[2];  // buffer for single character

    buffer[0] = '\0';
    charBuffer[1] = '\0';

    while((c = getc(f)) != EOF) {
        switch(c) {

            case PFML_OPEN_DELIMITER:
                // recurse and flip
                b2 = readSequence(f);
                flipString(b2);
                if(strlen(buffer) + strlen(b2) >= size) {
                    size = strlen(buffer) + strlen(b2) + 1;
                    buffer = realloc(buffer, size);
                }
                assert(buffer);
                strcat(buffer, b2);
                len = strlen(buffer);   // this may be slow but it doesn't happen often
                free(b2);
                break;

            case PFML_CLOSE_DELIMITER:
                goto done;

            default:
                if(len + 1 >= size) {
                    size *= BUFFER_SIZE_MULTIPLIER;
                    buffer = realloc(buffer, size);
                    assert(buffer);
                }

                charBuffer[0] = c;
                strcat(buffer, charBuffer);
                len++;

                break;
        }
    }

done:
    return buffer;
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    char *b = readSequence(stdin);
    fputs(b, stdout);  // puts will add newline
    free(b);

    return 0;
}
