#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// this is a function declaration
// look like definition with ; instead of the body
int add(int x, int y);

// argument names optional
// (but recommended for documentation)
// note this function is never defined, but as long
// as it's not used, that's OK.
int sum(int, int, int);

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    // C complains about implicit of declaration of add if not declared
    // undeclared functions are assumed to return int
    // and allow arbitrary arguments ☹
    // solution: declare function before use
    printf("2+3 == %d\n", add(2,3));

    return 0;
}

// returns the sum of x and y
int
add(int x, int y)
{
    return x+y;
}
