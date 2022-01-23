#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define INITIAL_SIZE (16)

// read a line from stdin
// terminated by newline or EOF
// returns 0 if receives EOF immediately
// otherwise returns malloc'd data (caller must free)
char *
getLine(void)
{
    size_t size = INITIAL_SIZE;  // how much space allocated
    size_t top = 0;              // first unused byte

    char *buffer = malloc(size);
    assert(buffer);

    int c;   // next character read from stdin

    for(;;) {
        // get next character
        c = getchar();

        // do we have space?
        if(top >= size) {
            // double my buffer
            size *= 2;
            buffer = realloc(buffer, size);
            assert(buffer);
        }

        switch(c) {
            case EOF:
                // did we get any characters?
                if(top == 0) {
                    // no
                    free(buffer);
                    return 0;
                } 
                // else fall through to next case
            case '\n':
                // end of line
                buffer[top++] = '\0';

                // realloc one last time to give back extra space
                buffer = realloc(buffer, top);

                return buffer;
                break;  // unnecessary but appeases the switch gods

            default:
                buffer[top++] = c;
                break;
        }
    }
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    char *buf;

    while((buf = getLine()) != 0) {
        puts(buf);
        free(buf);
    }

    return 0;
}
