#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// pointers to functions that take two ints
// and perform a binary operation on them
typedef int (*binaryOp)(int, int);

int
sum(int x, int y)
{
    return x + y;
}

int
product(int x, int y)
{
    return x * y;
}

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // both declarations of function pointers
    binaryOp add = sum;               // using typedef
    int (*add2)(int, int) = sum;      // explicilty
    binaryOp otherOp = prod;

    // function pointer declaration
    
    // creates a new variable
    int (*add3)(int, int);

    // somewhere there is an add4 function that returns int *
    int *add4(int, int);

    printf("add: %d\n", add(2,3));
    printf("add2: %d\n", add2(2,3));

    add2 = product;

    printf("add: %d\n", add(2,3));
    printf("add2: %d\n", add2(2,3));

    return 0;
}
