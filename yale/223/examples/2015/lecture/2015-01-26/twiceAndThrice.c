#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void
twiceAndThrice(int x, int *x2, int *x3)
{
    *x2 = x*2;
    *x3 = x*3;

    printf("%d %d\n", *x2, *x3);
}

int
main(int argc, char **argv)
{
    int a;
    int b;
    int c;

    a = 5;

    twiceAndThrice(a, &b, &c);

    printf("%d %d\n", b, c);

    return 0;
}
