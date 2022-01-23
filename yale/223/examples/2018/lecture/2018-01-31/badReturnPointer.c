#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int *
returnPointer(void)
{
    int x = 17;
    int *p;

    p = &x;

    return p;
}

int
main(int argc, char **argv)
{
    int *q;

    q = returnPointer();

    puts("hi there");

    /* does not print 17 */
    printf("%d\n", *q);

    return 0;
}
