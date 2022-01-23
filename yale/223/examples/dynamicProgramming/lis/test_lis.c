#include <stdio.h>
#include <stdlib.h>

#include "lis.h"

/* read integer values from stdin using scanf until error or EOF */
/* return freshly-malloc'd vector */
/* length goes in *n */
/* returns 0 on allocation error */
static int *
getnums(int *n)
{
    int *a;
    int size;
    int x;

    *n = 0;
    size = 1;
    a = malloc(sizeof(*a) * size);
    if(a == 0) return 0;

    while(scanf("%d", &x) == 1) {
        while(*n >= size - 1) {
            size *= 2;
            a = realloc(a, sizeof(*a) * size);
            if(a == 0) return 0;
        }
        a[*n] = x;
        (*n)++;
    }

    return a;
}

/* print n integer values from a */
static void
putnums(const int a[], int n)
{
    int i;

    for(i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
}

int
main(int argc, char **argv)
{
    int *a;             /* input array */
    int n;              /* length of a */
    int *output;        /* output array */
    int len;            /* length of output */

    a = getnums(&n);
    if(a == 0) return 1;

    output = malloc(sizeof(*output) * n);
    if(output == 0) return 1;

    len = longest_increasing_subsequence(a, n, output);

    printf("%d: ", len);
    putnums(output, len);
    putchar('\n');

    free(output);
    free(a);

    return 0;
}
