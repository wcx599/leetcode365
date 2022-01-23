#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>   /* for isdigit */

/* read and return a non-negative integer from stdin */
int
readInt(void)
{
    int x = 0;   /* return value accumulator */
    int c;

    while((c = getchar()) != EOF) {
        if(isdigit(c)) {
            /* assumes '0'..'9' are contiguous */
            x = x * 10 + (c - '0');
        } else {
            /* put it back */
            ungetc(c, stdin);

            /* escapes from innermost loop */
            break;
        }
    }

    return x;
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    printf("%d\n", readInt());

    return 0;
}
