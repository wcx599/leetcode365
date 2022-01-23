#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    int c;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    /* take all of stdin and send it to stdout */
    while((c = getchar()) != EOF) {
        /* do something with c */
        putchar(c);
    }

    return 0;
}
