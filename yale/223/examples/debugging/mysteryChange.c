#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    int x;
    int a[10];
    int i;

    x = 5;

    for(i = -1; i < 11; i++) {
        a[i] = 37;
    }

    assert(x == 5);

    return 0;
}
