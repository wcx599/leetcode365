#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{
    // how big are bitfields?
    struct bitFieldExample {
        int x : 5;
        int y : 6;
        int z : 7;
        int q : 9;
        int zzy : 1;
    } bf;

    printf("sizeof(bf) == %zu\n", sizeof(bf));

    struct charFieldExample {
        char x ;
        char y ;
        char z ;
        char q ;
        char zzy ;
        int i;
    } cf;

    printf("sizeof(cf) == %zu\n", sizeof(cf));

    cf.x = 12;
    cf.i = 15;

    struct charFieldExample cf2 = cf;

    printf("%d\n", cf2.x);

    return 0;
}
