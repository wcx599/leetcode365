#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // typedef creates type aliases, not new types!
    typedef int Apples;
    typedef int Oranges;

    Apples a = 5;
    Oranges o = 3;

    int total = a + o;

    printf("%d\n", total);

    // int64_t is a typedef'd name
    int64_t big = 37;

    // array of size 3
    // example of what can't be done with #define
    typedef int A3[3];

    A3 xyz = { 1, 2, 3 };

    // I don't know how big this needs to be
    // typedef int Dollars;     // my personal wealth
    typedef intmax_t Dollars;   // Elon Musk's personoal wealth

    Dollars wealth = 1200000000000;

    printf("%ld\n", xyz[0] + big + wealth);

    return 0;
}
