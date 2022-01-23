#include <stdlib.h>

/* allocate and return a new integer array with n elements */
/* calls abort() if there isn't enough space */
int *
makeIntArray(int n)
{
    int *a;

    a = malloc(sizeof(int) * n);

    if(a == 0) abort();                 /* die on failure */

    return a;
}
