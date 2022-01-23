#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int *
badPointer(void)
{
    int x = 37;

    printf("x == %d\n", x);

    return &x;
}

void
useless(void)
{
    int y = 55;

    printf("y == %d\n", y);
}


int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    int *p = badPointer();
    printf("%d\n", *p);   // segfaults here

    // we don't actually get here
    useless();
    printf("%d\n", *p);



    return 0;
}
