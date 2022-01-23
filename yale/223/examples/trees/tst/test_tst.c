#include <stdio.h>
#include <stdlib.h>

#include "tst.h"

/* test for tst.c */
/* reads lines from stdin and echoes lines that haven't appeared before */

/* read a line of text from stdin
 * and return it (without terminating newline) as a freshly-malloc'd block.
 * Caller is responsible for freeing this block.
 * Returns 0 on error or EOF.
 */
char *
getLine(void)
{
    char *line;         /* line buffer */
    int n;              /* characters read */
    int size;           /* size of line buffer */
    int c;

    size = 1;
    line = malloc(size);
    if(line == 0) return 0;
    
    n = 0;

    while((c = getchar()) != '\n' && c != EOF) {
        while(n >= size - 1) {
            size *= 2;
            line = realloc(line, size);
            if(line == 0) return 0;
        }
        line[n++] = c;
    }

    if(c == EOF && n == 0) {
        /* got nothing */
        free(line);
        return 0;
    } else {
        line[n++] = '\0';
        return line;
    }
}

int
main(int argc, char **argv)
{
    TST t;
    char *line;

    t = EMPTY_TST;

    while((line = getLine()) != 0) {
        if(!tst_contains(t, line)) {
            puts(line);
        }

        /* try to insert it either way */
        /* this tests that insert doesn't blow up on duplicates */
        t = tst_insert(t, line);

        free(line);
    }

    tst_destroy(t);

    return 0;
}
