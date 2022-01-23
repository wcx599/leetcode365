#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TOO_SMALL (12)

int
main(int argc, char **argv)
{
    int a[TOO_SMALL];

    /* keep going until something blows up */
    for(int i = 0;; i++) {
        a[i] = 0;
    }

    return 0;
}
