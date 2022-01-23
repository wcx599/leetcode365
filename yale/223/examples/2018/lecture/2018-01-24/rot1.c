#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    int c;

    /* take all of stdin and send it to stdout */
    while((c = getchar()) != EOF) {
        /* do something with c */
        putchar(c ^ 0x01);
    }

    return 0;
}
