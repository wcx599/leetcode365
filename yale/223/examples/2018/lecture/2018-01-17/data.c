#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    unsigned char uc;
    signed char sc;
    int x;

    uc = 3;
    uc = uc - 5; // no error message!

    sc = 3;
    sc = sc - 5;

    printf("uc = %d\n", uc);
    printf("sc = %d\n", sc);

    x = 352;

    sc = x;
    printf("sc = %d\n", sc);

    return 0;
}
