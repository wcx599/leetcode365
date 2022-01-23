#include <stdlib.h>

/* allocate and return a new integer array with n elements */
/* initializes array to zero */
/* calls abort() if there isn't enough space */
int *
makeIntArray(int n)
{
    int *a;

    a = calloc(n, sizeof(int));

    if(a == 0) abort();                 /* die on failure */

    return a;
}
