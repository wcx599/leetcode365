#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "eval.h"

/* make n copies of a string and return a new malloc'd string */
char *
replicate(size_t n, const char *src)
{
    char *dst;
    size_t i;
    char *top;
    size_t len;

    dst = malloc(strlen(src)*n + 1);  // n copies of src plus terminating null
    assert(dst);

    dst[0] = '\0';

    len = strlen(src);

    for(i = 0, top = dst; i < n; i++, top += len) {
        strcpy(top, src);
    }

    return dst;
}

#define N (1000000)

int
main(int argc, char **argv)
{
    char *d;

    d = replicate(10, "abc");
    puts(d);

    free(d);

    d = replicate(N, "abc");
    EvalF(zu, strlen(d));

    free(d);

    return 0;
}
